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

#include "QuoteTree.h"
#include "Utilities.h"

using namespace std;

int main() 
{
	QuoteTree quoteTree;
	
	bool quit = false;
	string userInput;

	while (quit != true)
	{
		printMenu();
		getline(cin, userInput);
		quit = handleUserInput(userInput, quoteTree);
	}

	return 0;
}