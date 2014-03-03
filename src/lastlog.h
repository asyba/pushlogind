#include <lastlog.h>
#include <pwd.h>

#define LASTLOG "/var/log/lastlog"
#define LSIZE   sizeof(struct lastlog)

signed int ll_size() {
  FILE *fp = fopen(LASTLOG, "rb");
  fseek(fp, 0, SEEK_END);
  signed int ssize = ftell(fp) / sizeof(struct lastlog);
  fclose(fp);
  return ssize;
}

int ll_compare(struct lastlog a, struct lastlog b) {
  return a.ll_time - b.ll_time;
}
