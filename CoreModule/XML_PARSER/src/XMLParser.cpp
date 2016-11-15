#include "XMLParser.h"


// util methods


static inline string &ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(),not1(ptr_fun<int, int>(isspace))));
    return s;
}

// trim from end
static inline string &rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline string &trim(string &s) {
    return ltrim(rtrim(s));
}

//~Util methods




XMLParser::XMLParser(string fileName) {
    ifstream file;
    file.open(fileName);

    if (!file.is_open()) {
        cerr << "Unable to open user configuration\n";
        root = NULL;
        return;
    }

    string str;
    string file_contents;

    while (getline(file, str)) {
        file_contents += str;
        file_contents.push_back('\n');
    }
    file.close();
    root = getNode(file_contents);
}

XMLNode* XMLParser::getNode(string content) {
    XMLNode* result = new XMLNode();
    unsigned int index = content.find_first_of("<");

    try {
        //looking for node key
        while (index < content.length() && !isalnum(content[index])) {
            index++;
        }

        if (index >= content.length() || !isalnum(content[index])) {
            cerr << "Unable to parse user configuration\n";
            return NULL;
        }

        string key = "";
        while (isalnum(content[index])) {
            key += content[index++];
        }
        result -> setKey(key);
        //~looking for node key

        //looking for node attributes
        while (true) {
            while(isspace(content[index])) {
                index++;
            }
            if (content[index] != '/' && content[index] != '>') {
                string key="";
                string value="";

                while(content[index] != '=') {
                    key += content[index++];
                }
                key = ltrim(rtrim(key));
                index++;

                if (content[index] == '"') {
                    index++;
                }
                while(isalnum(content[index])) {
                    value += content[index++];
                }
                if (content[index] == '"') {
                    index++;
                }

                result -> addAttribute(key, value);
            } else {
                break;
            }
        }
        //~looking for node attributes

        //looking for closing clause
        if (content[index] == '/') {
            index++;
            while(isspace(content[index])) {
                index++;
            }
            if (content[index] == '>') {
                result -> setLength(index+1);
                return result;
            }
        }

        if (content[index] == '>') {
            index++;
            while (true) {
                while(isspace(content[index])) {
                    index++;
                }

                if (content.substr(index).find("</"+key+">") == 0) {
                    result -> setLength(index + key.length() + 3);
                    return result;
                }

                //some children
                XMLNode* child = getNode(content.substr(index));
                if (child != NULL) {
                    result -> addChild(child);
                    index += child -> getLength();

                    result -> getChild("");
                } else {
                    break;
                }
            }
        }


    } catch(exception& e) {
        e.what();
    }

    result -> setLength(index);
    return result;
}
