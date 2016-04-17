/* This file contains the main program driver 
http://stackoverflow.com/questions/11625759/how-to-properly-install-libcurl-and-link-it-to-a-c-program
http://stackoverflow.com/questions/9786150/save-curl-content-result-into-a-string-in-c
http://www.cplusplus.com/forum/unices/45878/
*/

#include <iostream>
#include <string>
#include <cstring>
#include <curl/curl.h>

using namespace std;

string data;

size_t writeCallback(char *buf, size_t size, size_t nmemb, void *up) {
	for (int i = 0; i < size*nmemb; i++) {
		data.push_back(buf[i]);
	}
}


int main(int argc, char const *argv[]) {

	if (argc != 3) {
		cout << "Correct Usage: " << argv[0] << "Firstname Lastname" << endl;
		exit(1);
	}
	CURL *curl;

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	char URL[100] = "https://en.wikiquote.org/wiki/";
	strcat(URL, argv[1]);
	strcat(URL, "_");
	strcat(URL, argv[2]);
	curl_easy_setopt(curl, CURLOPT_URL, URL);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);

	curl_easy_perform(curl);

	cout << endl << data << endl;


	curl_easy_cleanup(curl);
	curl_global_cleanup();
	return 0;
}