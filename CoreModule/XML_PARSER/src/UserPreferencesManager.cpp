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

int UserPreferencesManager::getCorePort() {
    int result = 8383;

    string port = getPreference("port.CORE");

    if (port != "") {
        result = stoi(port);
    }

    return result;
}

Color UserPreferencesManager::getXAxisColor() {
    string rSTR = getPreference("axes.x.r");
    string gSTR = getPreference("axes.x.g");
    string bSTR = getPreference("axes.x.b");

    double r = 255, g = 0, b = 0;

    if (rSTR != "") {
        r = stoi(rSTR);
    }
    if (gSTR != "") {
        g = stoi(gSTR);
    }
    if (bSTR != "") {
        b = stoi(bSTR);
    }

    return Color(r,g,b);
}

Color UserPreferencesManager::getYAxisColor() {
    string rSTR = getPreference("axes.y.r");
    string gSTR = getPreference("axes.y.g");
    string bSTR = getPreference("axes.y.b");

    double r = 1, g = 0, b = 0;

    if (rSTR != "") {
        r = stoi(rSTR)/255.0;
    }
    if (gSTR != "") {
        g = stoi(gSTR)/255.0;
    }
    if (bSTR != "") {
        b = stoi(bSTR)/255.0;
    }

    return Color(r,g,b);
}

Color UserPreferencesManager::getZAxisColor() {
    string rSTR = getPreference("axes.z.r");
    string gSTR = getPreference("axes.z.g");
    string bSTR = getPreference("axes.z.b");

    double r = 1, g = 0, b = 0;

    if (rSTR != "") {
        r = stoi(rSTR)/255.0;
    }
    if (gSTR != "") {
        g = stoi(gSTR)/255.0;
    }
    if (bSTR != "") {
        b = stoi(bSTR)/255.0;
    }

    return Color(r,g,b);
}

Color UserPreferencesManager::getCuttingPlaneColor() {
    string rSTR = getPreference("cuttingPlane.r");
    string gSTR = getPreference("cuttingPlane.g");
    string bSTR = getPreference("cuttingPlane.b");
    string aSTR = getPreference("cuttingPlane.a");

    double r = 0.5, g = 0.1, b = 0.1, a = 0.1;

    if (rSTR != "") {
        r = stoi(rSTR)/255.0;
    }
    if (gSTR != "") {
        g = stoi(gSTR)/255.0;
    }
    if (bSTR != "") {
        b = stoi(bSTR)/255.0;
    }
    if (aSTR != "") {
        a = stoi(aSTR)/255.0;
    }

    return Color(r,g,b,a);
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
