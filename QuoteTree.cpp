/* This file contains the class method implementations for QuoteTree */
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

#include "QuoteTree.h"
#include "Utilities.h"
std::string curlData;

QuoteTree::QuoteTree()
{
    root = NULL;
}

QuoteTree::~QuoteTree()
{
    DeleteAll(root);
}
int QuoteTree::countQuoteNodes()
{
    return quoteCount;
}
void QuoteTree::addQuoteNode(std::string quote)
{
    quoteCount++;
    QuoteNode *tmp = new QuoteNode;
    tmp = root;
    QuoteNode *node = new QuoteNode;
    node -> quote = quote;
    node -> right = NULL;
    node -> left = NULL;
    node -> parent = NULL;
    QuoteNode *parent = new QuoteNode;
    if(tmp == NULL){
        root = node;
        quoteCount=1;
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
	std::string URL = "https://en.wikiquote.org/wiki/";
	URL += first + "_" + last;
	makeCurlRequest(URL);
	if (pageFound(curlData)) {
		rawData = curlData;
	}
	else {
		std::cout << "This person is not on Wikiquote, please try another" << std::endl;
	}
}
void QuoteTree::findQuote(std::string quote)
{
    bool found = false;
    QuoteNode *node = root;
    while(node!=NULL && !found)
    {
        if(node->quote.compare(quote)>0)
            node = node -> left;
        else if(node->quote.compare(quote)<0)
            node = node -> right;
        else
        {
            if(node->quote == quote) 
            {
                std::cout<<"Quote is real."<<std::endl;
            	found = true;
            }
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
	std::string text = "<b>Wikiquote does not have an article with this exact name.</b>";
	if (document.find(text) != -1) {
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

void QuoteTree::parseQuotes() {
	// Function to parse quotes and add them to the QuoteTree
	std::string startHTML = "<h2><span class=\"mw-headline\" id=\"Quotes\">Quotes</span>";
	std::string endHTML = "<h2>";
	std::string trimmedDoc = trimDoc(rawData, startHTML, endHTML);
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