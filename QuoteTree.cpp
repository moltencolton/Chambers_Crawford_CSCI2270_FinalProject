/* This file contains the class method implementations for QuoteTree */
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <cstdlib>

#include "QuoteTree.h"
#include "Utilities.h"
std::string curlData = "";

QuoteTree::QuoteTree()
{
	root = NULL;
	quoteCount = 0;
}

QuoteTree::~QuoteTree()
{
	if (root != NULL) {
		DeleteAll(root);
	}

}
void QuoteTree::countQuoteNodes()
{
	std::cout << "Number of Quotes by Author: " << quoteCount << std::endl;
}
int QuoteTree::getQuoteCount()
{
    return quoteCount;
}
void QuoteTree::addQuoteNode(std::string quote)
{

	QuoteNode *tmp = new QuoteNode;
	tmp = root;
	QuoteNode *node = new QuoteNode;
	node -> quote = quote;
	node -> right = NULL;
	node -> left = NULL;
	node -> parent = NULL;
	node -> num = quoteCount;
	quoteCount++;
	QuoteNode *parent = new QuoteNode;
	if(tmp == NULL){
		root = node;
	}
	else{
		while(tmp!=NULL)
		{
			parent = tmp;
			std::string quote1;
			std::string quote2;
			quote1 = node -> quote;
			quote2 = tmp -> quote;
			if(quote1.compare(quote2) < 0)
			{
				tmp = tmp->left;
			}
			else
				tmp = tmp->right;
		}
		if(parent == NULL)
		{
			root = NULL;
		}
		else if(node -> quote.compare(parent-> quote) < 0)
		{
			parent -> left = node;
			node -> parent = parent;
		}
		else
		{
			parent -> right = node;
			node -> parent = parent;
		}
	}
}

void QuoteTree::updateData(std::string first, std::string last)
{
    if(first + " " + last != currentAuthor){
        std::string URL = "https://en.wikiquote.org/wiki/";
        URL = URL + first + "_" + last;
        curlData = "";
        makeCurlRequest(URL);
        if (pageFound(curlData) && curlData != "") {
            // Person exists, delete previous tree and then create new
            if (root != NULL) {
                DeleteAll(root);
                root = NULL;
            }
            parseQuotes(curlData);
            if (quoteCount > 0) {
            	std::cout << "Quote data read in successfully" << std::endl;
            	currentAuthor = first + " " + last;
            }
            else {
            	std::cout << "Something went wrong while reading in quote data, please try another author." << std::endl;
            }
            
        }
        else if (curlData == "") {
            std::cout << "Could not retrieve quote data, please try again later." << std::endl;
        }
        else {
            std::cout << "This person is not on Wikiquote, please try another." << std::endl;
        }
    }
    else
        std::cout << currentAuthor +" is already the current author."<<std::endl;
}
void QuoteTree::findQuote(std::string quote)
{
	bool found = false;
	QuoteNode *node = root;
	while(node!=NULL && !found)
	{
		if (node->quote.find(quote) != -1) 
		{
            std::cout<<"Quote is real."<<std::endl;
            found = true;
            std::cout << "Full quote: " << node->quote << std::endl;
		}
		else if(node->quote.compare(quote)>0)
			node = node -> left;
		else if(node->quote.compare(quote)<0){
			node = node -> right;
		}
		
	}
	if(!found)
		std::cout << "Quote not found." << std::endl;
}
void QuoteTree::DeleteAll(QuoteNode* node)
{
	if(node -> left!= NULL)
		DeleteAll(node->left);
	if(node->right!=NULL)
		DeleteAll(node->right);
	delete node;
}

bool QuoteTree::pageFound(std::string document) {
	// Function to find if is the 404 page
	std::string text1 = "Wikiquote does not have an article with this exact name";
	std::string text2 = "The requested page title is empty or contains only the name of a namespace.";
	if (document.find(text1) != -1 || document.find(text2) != -1) {
		return false;
	}
	return true;
}

std::string QuoteTree::trimDoc(std::string toTrim, std::string start, std::string finish) {
	// Function to trim document string to save time
	// Returns string found between start and finish
	int startIndex = toTrim.find(start);
	toTrim = toTrim.substr(startIndex+start.length());
	int finishIndex = toTrim.find(finish);

	return toTrim.substr(0, finishIndex);
}

void QuoteTree::parseQuotes(std::string document) {
	// Function to parse quotes and add them to the QuoteTree
	std::string startHTML = "<h2><span class=\"mw-headline\" id=\"Quotes\">Quotes</span>";
	std::string endHTML = "<h2>";
	std::string trimmedDoc = trimDoc(document, startHTML, endHTML);
	traverseDoc(trimmedDoc);
}

void QuoteTree::traverseDoc(std::string document) {
	// Function to traverse document to find quotes
	int index = 0;
	int start = 0;
	int end = 0;
	while (index < document.length()) {
		start = document.find("<ul>\n<li>", index);
		end = document.find("<ul>\n<li>", start+1);

		if (start != -1 && end != -1) {
			std::string quote = document.substr(start+8, end-start-8);
			quote = cleanQuote(quote);
			// Add the quote here
			addQuoteNode(quote);
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

std::string QuoteTree::cleanQuote(std::string toClean) {
	// Function to strip HTML tags from quote
	std::stringstream ss;
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
	std::string cleanedQuote;
	cleanedQuote = ss.str();
	return cleanedQuote;
}

void QuoteTree::printQuotes()
{
	printQuote(root);
}

void QuoteTree::printQuote(QuoteNode *node)
{
	if (node->left != NULL)
	{
		printQuote(node->left);
	}
	std::cout<< "********************************************************************************";
	std::cout << std::endl << node->quote << std::endl;
	if (node->right != NULL)
	{
		printQuote(node->right);
	}
}

std::string QuoteTree::getAuthor()
{
    return currentAuthor;
}

void QuoteTree::getRandomQuote()
{
    int randNum = rand() % quoteCount;
    randomQuote(root, randNum);
}
void QuoteTree::randomQuote(QuoteNode *node, int randNum)
{
    if(node->left!=NULL)
        randomQuote(node->left, randNum);
    if(randNum == node->num)
        std::cout<<node->quote<<std::endl;
    if(node->right!=NULL)
        randomQuote(node->right, randNum);
}
bool QuoteTree::checkAuthor(std::string first, std::string last) 
{
	std::string URL = "https://en.wikiquote.org/wiki/";
    URL = URL + first + "_" + last;
    curlData = "";
    makeCurlRequest(URL);
    if (pageFound(curlData)) {
    	return true;
    }
    else {
    	return false;
    }
}
