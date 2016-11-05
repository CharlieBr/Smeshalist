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
        void setLength(int l) {
            nodeLength = l;
        }
        string getKey() {
            return key;
        }
        int getLength() {
            return nodeLength;
        }
        XMLNode* getChild(string key) {
            for (auto child : children) {
                if (child -> getKey() == key) {
                    return child;
                }
            }
            return NULL;
        }
        string findAttribute(string key) {
            map<string,string>::iterator it;
            it = attributes.find(key);

            if (it != attributes.end()) {
                return it -> second;
            }

            return "";
        }
    protected:
    private:
        string key;
        vector<XMLNode*> children;
        map<string, string> attributes;
        int nodeLength;
};

#endif // XMLNODE_H
