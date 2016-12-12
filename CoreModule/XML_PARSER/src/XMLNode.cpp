#include "XMLNode.h"


void XMLNode::addAttribute(string key, string value) {
    attributes[key] = value;
}

void XMLNode::addChild(XMLNode* child) {
    children.push_back(child);
}

void XMLNode::setKey(string key) {
    this -> key = key;
}

void XMLNode::setLength(int l) {
    nodeLength = l;
}

string XMLNode::getKey() {
    return key;
}

int XMLNode::getLength() {
    return nodeLength;
}

XMLNode* XMLNode::getChild(string key) {
    for (auto child : children) {
        if (child -> getKey() == key) {
            return child;
        }
    }
    return NULL;
}

vector<XMLNode*> XMLNode::getChildren(string key) {
    vector<XMLNode*> result;

    for (auto child : children) {
        if (child -> getKey() == key) {
            result.push_back(child);
        }
    }

    return result;
}

XMLNode* XMLNode::getChildByAttributeValue(string key, string attribute, string value) {
    for(auto child : children) {
        if (child -> getKey() != key) {
            continue;
        }

        string attrValue = child -> findAttribute(attribute);

        if (attrValue == value) {
            return child;
        }
    }
    return NULL;
}

string XMLNode::findAttribute(string key) {
    map<string,string>::iterator it;
    it = attributes.find(key);

    if (it != attributes.end()) {
        return it -> second;
    }

    return "";
}
