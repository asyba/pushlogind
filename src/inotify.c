#include <unistd.h>
#include <sys/types.h>
#include <sys/inotify.h>

#define EVENT_SIZE (sizeof(struct inotify_event))

struct watcher {
  int fd;
  int wd;
};

/**
 * Initializes a IN_MODIFY watcher and returns a watcher struct.
 */
struct watcher watch(const char *file) {
  int fd = inotify_init();
  int wd = inotify_add_watch(fd, file, IN_MODIFY);
  struct watcher watcher = {fd, wd};
  return watcher;
}

/**
 * Reads a single event from watcher and returns a read() code.
 */
signed int wread(char buf[], struct watcher *watcher) {
  return read(watcher->fd, buf, EVENT_SIZE);
}

inline void unwatch(struct watcher *watcher) {
  (void) inotify_rm_watch(watcher->fd, watcher->wd);
  (void) close(watcher->fd);
}
