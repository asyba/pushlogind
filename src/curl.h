#include <curl/curl.h>

inline void curl_push(CURL *curl) {
  curl_easy_perform(curl);
}

CURL *curl_init(const char *token, const char *user) {
  CURL *curl;
 
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, "https://api.pushover.net/1/messages.json");
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "token=&user=&message=");

  return curl;
}

inline void curl_cleanup(CURL *curl) {
  curl_easy_cleanup(curl);
  curl_global_cleanup();
}
