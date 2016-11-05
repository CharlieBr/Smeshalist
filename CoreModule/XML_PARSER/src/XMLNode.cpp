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
