#include <stdio.h>
#include <stdlib.h>
#include "lastlog.h"
#include "curl.h"

int main() {
  CURL *curl = curl_init("aa", "aa");
  int fd = watch_lastlog();
  char buf[BUF_LEN];
  ssize_t numread;

  for(;;) {
    numread = read(fd, buf, BUF_LEN);
    for (p = buf; p < buf + numread; p += sizeof(struct inotify_event) + event->len)
      curl_push();
  }

  curl_cleanup(curl);
  close_lastlog();
  return 0;
}
