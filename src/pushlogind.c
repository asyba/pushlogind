#include "lastlog.c"
#include "inotify.c"
#include "curl.c"

int main() {
  CURL *curl = curl_init();

  /* Inotify-related -- initialize a watcher,
   * and create a 1-slot event buffer:
   */
  struct watcher watcher = watch(LL_PATH);
  char event[EVENT_SIZE];

  /* All about /var/log/lastlog -- count
   * number of possible users and allocate
   * a buffer for parsing the file:
   */
  signed int users = ll_count();
  struct lastlog ll[users];

  for(;;) {
    if(wread(event, &watcher) == EVENT_SIZE) {
      /* We need this double wread() call because
       * there are actually two modify events occur
       * each login.
       */
      wread(event, &watcher);
      if(ll_read(ll, users) != 1)
        curl_push(curl, ll_recent(ll, users));
    }
  }

  curl_cleanup(curl);
  unwatch(&watcher);
  return 0;
}
