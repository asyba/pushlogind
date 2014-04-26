#include <lastlog.h>
#include <stdio.h>
#include <pwd.h>

#define LL_PATH  "/var/log/lastlog"
#define LL_SSIZE (sizeof(struct lastlog))

/* Counts total amount of users in /var/log/lastlog:
 */
int ll_count() {
  FILE *fp = fopen(LL_PATH, "rb");
  fseek(fp, 0, SEEK_END);
  signed int size = ftell(fp) / sizeof(struct lastlog);
  fclose(fp);
  return size;
}

/* Reads and returns lastlog structs from /var/log/lastlog:
 */
int ll_read(struct lastlog *ll, signed int entries) {
  FILE *fp = fopen(LL_PATH, "rb");
  int code = fread(ll, LL_SSIZE, entries, fp);
  fclose(fp);
  return code;
}

/* Describes a user taken out of /var/log/lastlog:
 */
struct ll_user {
  int id;
  struct lastlog ll;
};

/* Takes an array of lastlog structs (see /usr/include/bits/utmp.h)
 * and finds the user with the most recent timestamp:
 */
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
