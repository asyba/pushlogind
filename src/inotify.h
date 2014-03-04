#include <unistd.h>
#include <sys/types.h>
#include <sys/inotify.h>

#define EVENT_SIZE  sizeof(struct inotify_event)

struct watcher {
  int fd;
  int wd;
};

struct watcher watch(const char *file) {
  int fd = inotify_init();
  int wd = inotify_add_watch(fd, file, IN_MODIFY);
  struct watcher watcher = {fd, wd};
  return watcher;
}

inline void unwatch(struct watcher *watcher) {
  (void) inotify_rm_watch(watcher->fd, watcher->wd);
  (void) close(watcher->fd);
}
signed int inread(char buf[], struct watcher *watcher) {
  return read(watcher->fd, buf, EVENT_SIZE);
}
