/* This file contains the class method implementations for QuoteTree */

QuoteTree::QuoteTree()
{
    root = NULL;
}

QuoteTree::~QuoteTree()
{
    DeleteAll(root);
}
