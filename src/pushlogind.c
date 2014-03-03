#include "config.h"
#include "lastlog.h"
#include "inotify.h"
#include "curl.h"

int main() {
  CURL *curl = curl_init(TOKEN, USER);
  struct watcher watcher = watch(LASTLOG);
  struct inotify_event *event;
  char buf[EVENT_SIZE];
  ssize_t bytes;

  for(;;) {
    sleep(FREQUENCY);
    bytes = read(watcher.fd, buf, EVENT_SIZE);
    if(bytes == EVENT_SIZE) {
      /* event = (struct inotify_event *) buf; */
      curl_easy_perform(curl);
    }
  }

  curl_cleanup(curl);
  unwatch(&watcher);
  return 0;
}
