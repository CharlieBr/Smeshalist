#ifndef XMLNODE_H
#define XMLNODE_H

#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

class XMLNode
{
    public:
        void setKey(string);
        void addChild(XMLNode*);
        void addAttribute(string, string);
        void setLength(int);
        string getKey();
        int getLength();
        XMLNode* getChild(string);
        XMLNode* getChildByAttributeValue(string, string, string);
        vector<XMLNode*> getChildren(string);
        string findAttribute(string);
    protected:
    private:
        string key;
        vector<XMLNode*> children;
        map<string, string> attributes;
        int nodeLength;
};

#endif // XMLNODE_H
