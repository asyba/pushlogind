#include <curl/curl.h>
#include <stdio.h>

CURL *curl_init() {
  CURL *curl; 
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, "https://api.pushover.net/1/messages.json");
  return curl;
}

/* Pushes a login message using information from
 * ll_user struct (see lastlog.h) and config.h:
 */
static inline void curl_push(CURL *curl, struct ll_user user) {
  char *post;
  asprintf(&post, "token=%s&user=%s&sound=%s&priority=%d&message=%s+has+logged+in+from+%s+(%s)", TOKEN, USER,
    SOUND, PRIORITY, getpwuid(user.id)->pw_name, user.ll.ll_host, user.ll.ll_line);

  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post);
  curl_easy_perform(curl);
}

inline void curl_cleanup(CURL *curl) {
  curl_easy_cleanup(&curl);
  curl_global_cleanup();
}
