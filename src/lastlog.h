#include <stdlib.h>
#include <sys/types.h>
#include <sys/inotify.h>

#define EVENT_SIZE  sizeof(struct inotify_event)
#define BUF_LEN     1024 * (EVENT_SIZE + 16)

int watch_lastlog() {
  int fd = inotify_init();
  int wd = inotify_add_watch(fd, "/var/log/lastlog", IN_MODIFY);
}


inline void close_lastlog(int fd, int wd) {
  (void) inotify_rm_watch(fd, wd);
  (void) close(fd);
}
