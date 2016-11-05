#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "XMLNode.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;


class XMLParser
{
    public:
        XMLParser(string);
        XMLNode* getRoot() {
            return root;
        }
    protected:
    private:
        XMLNode* root;
        XMLNode* getNode(string);
};

#endif // XMLPARSER_H
