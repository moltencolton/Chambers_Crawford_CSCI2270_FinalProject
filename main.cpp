/* This file contains the main program driver 
http://stackoverflow.com/questions/11625759/how-to-properly-install-libcurl-and-link-it-to-a-c-program
http://stackoverflow.com/questions/9786150/save-curl-content-result-into-a-string-in-c
http://www.cplusplus.com/forum/unices/45878/
*/

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <curl/curl.h>

using namespace std;

string data;

size_t writeCallback(char*, size_t, size_t, void*);
void makeCurlRequest(char[]);
bool pageFound(string);
string trimDoc(string, string, string);
void parseQuotes(string);
void traverseDoc(string);
string cleanQuote(string);

int main(int argc, char const *argv[]) {

	if (argc != 3) {
		cout << "Correct Usage: " << argv[0] << " Firstname Lastname" << endl;
		exit(1);
	}
	
	char URL[100] = "https://en.wikiquote.org/wiki/";
	strcat(URL, argv[1]);
	strcat(URL, "_");
	strcat(URL, argv[2]);

	makeCurlRequest(URL);
	parseQuotes(data);
	cout << "end" << endl;

	return 0;
}

/* ********** Parser Function Definitions ********** */

size_t writeCallback(char *buf, size_t size, size_t nmemb, void *up) {
	// Data writing function
	for (int i = 0; i < size*nmemb; i++) {
		data.push_back(buf[i]);
	}
}

void makeCurlRequest(char url[]) {
	// Function to retrieve data from given URL
	CURL *curl;	
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);

	curl_easy_perform(curl);

	curl_easy_cleanup(curl);
	curl_global_cleanup();
}

bool pageFound(string document) {
	// Function to find if is the 404 page
	string text = "<b>Wikiquote does not have an article with this exact name.</b>";
	if (document.find(text) != -1) {
		return false;
	}
	return true;
}

string trimDoc(string toTrim, string start, string finish) {
	// Function to trim document string to save time
	// Returns string found between start and finish
	int startIndex = toTrim.find(start);
	toTrim = toTrim.substr(startIndex+start.length());
	int finishIndex = toTrim.find(finish);

	return toTrim.substr(0, finishIndex);
}

void parseQuotes(string document) {
	// Function to parse quotes and add them to the QuoteTree
	if (!pageFound(document)) {
		cout << "This person is not on Wikiquote, please try another" << endl;

	}
	else {
		string startHTML = "<h2><span class=\"mw-headline\" id=\"Quotes\">Quotes</span>";
		string endHTML = "<h2>";
		string trimmedDoc = trimDoc(document, startHTML, endHTML);
		traverseDoc(trimmedDoc);
	}
}

void traverseDoc(string document) {
	// Function to traverse document to find quotes
	int index = 0;
	int start = 0;
	int end = 0;
	while (index < document.length()) {
		start = document.find("<ul>\n<li>", index);
		end = document.find("<ul>\n<li>", start+1);

		if (start != -1 && end != -1) {
			string quote = document.substr(start+8, end-start-8);
			quote = cleanQuote(quote);
			// Add the quote here

			int nestedUl = document.find("</ul>\n</li>\n</ul>", end);
			if (nestedUl != -1) {
				index = nestedUl + 11;
			}
			else {
				index = document.length();
			}
		}
		else {
			index = document.length();

		}
	}
}

string cleanQuote(string toClean) {
	// Function to strip HTML tags from quote
	stringstream ss;
	bool reading = true;
	for (int i = 0; i < toClean.length(); i++) {
		if (toClean[i] == '<') {
			reading = false;
		}
		else if (toClean[i] == '>') {
			reading = true;
		}
		else {
			if (reading) {
				ss << toClean[i];
			}
		}
	}
	string cleanedQuote;
	cleanedQuote = ss.str();
	return cleanedQuote;
}