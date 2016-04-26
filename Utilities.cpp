#include <iostream>
#include <string>
#include <curl/curl.h>

#include "Utilities.h"
#include "QuoteTree.h"

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

void printMenu()
{
	std::cout << "***** Quote Verifier *****" << std::endl;
	std::cout << "1. Get Quote Data" << std::endl;
	std::cout << "2. Verify a Quote" << std::endl;
	std::cout << "3. List All Quotes" << std::endl;
	std::cout << "4. Count Quotes" << std::endl;
	std::cout << "5. Get a Random Quote" << std::endl;
	std::cout << "6. Get Current Author" <<std::endl;
	std::cout << "7. Check For Author" <<std::endl;
	std::cout << "8. Quit" << std::endl;
}
bool handleUserInput(std::string input, QuoteTree &quoteTree)
{
	if (input == "1") {
		// Get Quote Data
		std::string first;
		std::string last;
		std::cout << "Enter the first name:" << std::endl;
		getline(std::cin, first);
		std::cout << "Enter the last name:" << std::endl;
		getline(std::cin, last);
		quoteTree.updateData(first, last);
	}
	else if (input == "2") {
		// Verify a Quote
		std::string toVerify;
		std::cout << "Enter a quote to verify:" << std::endl;
		getline(std::cin, toVerify);
		quoteTree.findQuote(toVerify);
	}
	else if (input == "3") {
		// List all Quotes
		if(quoteTree.getQuoteCount()!=0)
            quoteTree.printQuotes();
		else
            std::cout<<"Please enter quote data before printing the quotes."<<std::endl;
	}
	else if (input == "4") {
		// Count Quotes
		quoteTree.countQuoteNodes();
	}
	else if (input == "5") {
		// Get a random quote
		quoteTree.getRandomQuote();
	}
	else if (input == "6") {
        //Get the current author
        std::cout<<"The current author is "+quoteTree.getAuthor()+"."<<std::endl;
	}
	else if (input == "7") {
		// Check for author
		std::string first;
		std::string last;
		std::cout << "Enter the first name:" << std::endl;
		getline(std::cin, first);
		std::cout << "Enter the last name:" << std::endl;
		getline(std::cin, last);
		bool exists = quoteTree.checkAuthor(first, last);
		if (exists) {
			std::cout << "This author is on wikiquote." << std::endl;
		}
		else {
			std::cout << "This author is not on wikiquote." << std::endl;
		}
	}
	else if (input == "8") {
		// Quit
		return true;
	}
	return false;
}
