#include "UserPreferencesManager.h"

UserPreferencesManager::UserPreferencesManager()
{
    parser = new XMLParser(file);
}

UserPreferencesManager* UserPreferencesManager::getInstance() {
    static UserPreferencesManager instance;
    return &instance;
}

Color UserPreferencesManager::getBackgroudColor() {
    string theme = getPreference("background.theme");

    if (theme == "DARK") {
        return Color(57/255.0, 57/255.0, 57/255.0);
    }

    return Color(1, 1, 1);
}

Color UserPreferencesManager::getGroupColor(int groupID) {
    string key = "groups.g" + to_string(groupID) + ".";

    string rSTR = getPreference(key + "r");
    string gSTR = getPreference(key + "g");
    string bSTR = getPreference(key + "b");

    double r, g, b;

    if (rSTR != "") {
        r = stoi(rSTR)/255.0;
    } else {
        r = abs(sin(groupID));
    }

    if (gSTR != "") {
        g = stoi(gSTR)/255.0;
    } else {
        g = abs(cos(0.5 * groupID));
    }

    if (bSTR != "") {
        b = stoi(bSTR)/255.0;
    } else {
        b = abs(sin(0.1 * groupID));
    }

    return Color(r, g, b);
}

string UserPreferencesManager::getPreference(string path) {
    XMLNode* root = parser -> getRoot();

    if (root != NULL) {
        return getPreference(path, root);
    }

    return "";
}

string UserPreferencesManager::getPreference(string path, XMLNode* currentRoot) {
    if (path.find_first_of('.') != string::npos) {
        string childKey = path.substr(0, path.find_first_of('.'));
        string restOfPath = path.substr(path.find_first_of('.')+1);

        XMLNode* child = currentRoot->getChild(childKey);
        if (child != NULL) {
            return getPreference(restOfPath, child);
        }
    } else {
        return currentRoot -> findAttribute(path);
    }
    return "";
}
