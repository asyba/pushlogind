#include <unistd.h>
#include <stdio.h>
#include "config.h"
#include "lastlog.h"
#include "inotify.h"
#include "curl.h"

int main() {
  CURL *curl = curl_init(TOKEN, USER);
  struct watcher watcher = watch(LASTLOG);
  char event[EVENT_SIZE];
  ssize_t bytes;
  signed int ssize = ll_size();
  struct lastlog ll[ssize];
  struct lastlog recent;
  signed int recent_id, i;
  FILE *fp;

  for(;;) {
    sleep(FREQUENCY);
    bytes = read(watcher.fd, event, EVENT_SIZE);
    if(bytes == EVENT_SIZE) {
      fp = fopen(LASTLOG, "rb");
      fread(ll, LSIZE, ssize, fp);
      
      for(i = 0; i < ssize; i++) {
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
