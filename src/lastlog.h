#include <lastlog.h>
#include <pwd.h>

#define LL_PATH  "/var/log/lastlog"
#define LL_SSIZE (sizeof(struct lastlog))

signed int ll_count() {
struct ll_user {
  int id;
  struct lastlog ll;
};
  FILE *fp = fopen(LL_PATH, "rb");
  fseek(fp, 0, SEEK_END);
  signed int size = ftell(fp) / sizeof(struct lastlog);
  fclose(fp);
  return size;
}
struct ll_user ll_recent(struct lastlog *ll, signed int entries) {
  struct ll_user recent;
  signed int i;

  for(i = 0; i < entries; i++) {
    if(ll[i].ll_time > recent.ll.ll_time) {
      recent.ll = ll[i];
      recent.id = i;
    }
  }

  return recent;
}
