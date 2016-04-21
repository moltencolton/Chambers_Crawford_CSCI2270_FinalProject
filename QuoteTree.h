/* This file contains the class definition for QuoteTree */
#ifndef MOVIETREE_H
#define MOVIETREE_H
#include <iostream>

struct QuoteNode{
    std::string quote;
    std::string author;
    QuoteNode *parent;
    QuoteNode *left;
    QuoteNode *right;

    QuoteNode(){};

    QuoteNode(std::string in_quote, std::string in_author)
    {
        quote = in_quote;
        author = in_author;
        parent = NULL;
        left = NULL;
        right = NULL;
    }

};

class QuoteTree
{

    public:
        QuoteTree();
        ~QuoteTree();
        int countQuoteNodes();
        void addQuoteNode(std::string quote, std::string author);
        void findQuote(std::string quote, std::string author);

    protected:

    private:
        void DeleteAll(QuoteNode * node); //use this for the post-order traversal deletion of the tree
        QuoteNode* search(std::string quote);
        QuoteNode* treeMinimum(QuoteNode *node);
        QuoteNode *root;
        int quoteCount;
};

#endif // MOVIETREE_H
