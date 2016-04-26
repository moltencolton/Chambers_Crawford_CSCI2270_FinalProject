/* This file contains the class definition for QuoteTree */
#ifndef QUOTETREE_H
#define QUOTETREE_H
#include <iostream>

struct QuoteNode{
    std::string quote;
    QuoteNode *parent;
    QuoteNode *left;
    QuoteNode *right;

    QuoteNode(){};

    QuoteNode(std::string in_quote)
    {
        quote = in_quote;
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
        void countQuoteNodes();
        void updateData(std::string first, std::string last);
        void addQuoteNode(std::string quote);
        void findQuote(std::string quote);
        void parseQuotes(std::string document);
        void printQuotes();
        void getRandomQuote();

    private:
        void DeleteAll(QuoteNode * node); //use this for the post-order traversal deletion of the tree
        QuoteNode* search(std::string quote);
        bool pageFound(std::string document);
        std::string trimDoc(std::string toTrim, std::string start, std::string finish);
        void traverseDoc(std::string document);
        std::string cleanQuote(std::string toClean);
        void printQuote(QuoteNode *node);
        QuoteNode *root;
        int quoteCount;
};

#endif // QUOTETREE_H
