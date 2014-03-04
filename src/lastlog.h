#include <lastlog.h>
#include <pwd.h>

#define LL_PATH  "/var/log/lastlog"
#define LL_SSIZE sizeof(struct lastlog)

signed int ll_count() {
  FILE *fp = fopen(LL_PATH, "rb");
  fseek(fp, 0, SEEK_END);
  signed int size = ftell(fp) / sizeof(struct lastlog);
  fclose(fp);
  return size;
}
