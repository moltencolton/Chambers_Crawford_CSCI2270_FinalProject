#include <string>
#include <curl/curl.h>

#include "Utilities.h"

void writeCallback(char *buf, size_t size, size_t nmemb, void *up) 
{
	// Data writing function
	for (int i = 0; i < size*nmemb; i++) {
		curlData.push_back(buf[i]);
	}
}

void makeCurlRequest(std::string url) 
{
	// Function to retrieve data from given URL
	CURL *curl;	
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);	

	curl_easy_perform(curl);

	curl_easy_cleanup(curl);
	curl_global_cleanup();
}