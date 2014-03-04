#include <unistd.h>
#include <stdio.h>
#include "config.h"
#include "lastlog.h"
#include "inotify.h"
#include "curl.h"

int main() {
  CURL *curl = curl_init(TOKEN, USER);

  /* Inotify-related: initialize a watcher,
   * and create a 1-slot event buffer.
   */
  struct watcher watcher = watch(LL_PATH);
  char event[EVENT_SIZE];

  /* All about /var/log/lastlog: count
   * number of possible users and allocate
   * a buffer for parsing lastlog.
   */
  signed int users = ll_count();
  struct lastlog ll[users];
  struct lastlog recent;
  signed int recent_id, i;
  FILE *fp;

  for(;;) {
    sleep(FREQUENCY);

    if(read(watcher.fd, event, EVENT_SIZE) == EVENT_SIZE) {
      fp = fopen(LL_PATH, "rb");
      fread(ll, LL_SSIZE, users, fp);
      
      for(i = 0; i < users; i++) {
        if(ll[i].ll_time > recent.ll_time) {
          recent = ll[i];
          recent_id = i;
        }
      }

      curl_push(curl, recent_id, &ll[recent_id]);
      fclose(fp);
    }
  }

  curl_cleanup(curl);
  unwatch(&watcher);
  return 0;
}
