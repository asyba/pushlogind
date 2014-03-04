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

  for(;;) {
    if(inread(event, &watcher) == EVENT_SIZE) {
      inread(event, &watcher);
      if(ll_read(ll, users) != 1)
        curl_push(curl, ll_recent(ll, users));
    }
  }

  curl_cleanup(curl);
  unwatch(&watcher);
  return 0;
}
