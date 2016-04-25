#ifndef UTILITIES_H
#define UTILITIES_H
#include "QuoteTree.h"

extern std::string curlData;

void writeCallback(char *buf, size_t size, size_t nmemb, void *up);
void makeCurlRequest(std::string url);
void printMenu();
bool handleUserInput(std::string input, QuoteTree &quoteTree);
#endif