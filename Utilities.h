#ifndef UTILITIES_H
#define UTILITIES_H
extern std::string curlData;

void writeCallback(char *buf, size_t size, size_t nmemb, void *up);
void makeCurlRequest(std::string url);
#endif