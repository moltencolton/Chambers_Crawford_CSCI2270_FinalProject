/* This file contains the class method implementations for QuoteTree */
#include "QuoteTree.h"
#include <iostream>
using namespace std;
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
void QuoteTree::addQuoteNode(string quote, string author)
{
    quoteCount++;
    QuoteNode *tmp = new QuoteNode;
    tmp = root;
    QuoteNode *node = new QuoteNode;
    node -> quote = quote;
    node -> author = author;
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
        string quote1;
        string quote2;
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
void QuoteTree::findQuote(string quote, string author)
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
            if(node->author == author)
                cout<<"Quote is real."<<endl;
            else
                cout<<"Quote is real but the real author is "<<node->author<<"."<<endl;
            found = true;
        }
    }
    if(!found)
        cout << "Quote not found." << endl;
}
void QuoteTree::DeleteAll(QuoteNode* node)
{
    if(node -> left!= NULL)
        DeleteAll(node->left);
    if(node->right!=NULL)
        DeleteAll(node->right);
    delete node;
}
