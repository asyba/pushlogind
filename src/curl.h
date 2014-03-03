#include <curl/curl.h>

CURL *curl_init(const char *token, const char *user) {
  CURL *curl;
  char *post;
 
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  asprintf(&post, "token=%s&user=%s&message=%s", token, user, "Someone+has+logged+in!");
  curl_easy_setopt(curl, CURLOPT_URL, "https://api.pushover.net/1/messages.json");
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post);

  return curl;
}

inline void curl_cleanup(CURL *curl) {
  curl_easy_cleanup(&curl);
  curl_global_cleanup();
}
