#include "UserPreferencesManager.h"

map<double, Color*> UserPreferencesManager::qualityColorMap;
Color* UserPreferencesManager::negQualityColor;

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

Color* UserPreferencesManager::getQualityColor(double quality) {
    if (qualityColorMap.empty()) {  //load from XML
        vector<string> definedQualities = getAttributeValues("qualityColors.color", "q");

        for (auto quality : definedQualities) {
            string rSTR = getPreference("qualityColors.color(q="+quality+").r");
            string gSTR = getPreference("qualityColors.color(q="+quality+").g");
            string bSTR = getPreference("qualityColors.color(q="+quality+").b");

            double q = stod(quality);
            double r=0, g=0, b=0;

            if (rSTR != "") {
                r = stoi(rSTR)/255.0;
            }
            if (gSTR != "") {
                g = stoi(gSTR)/255.0;
            }
            if (bSTR != "") {
                b = stoi(bSTR)/255.0;
            }

            qualityColorMap[q] = new Color(r,g,b);
        }

        if (qualityColorMap.find(0) == qualityColorMap.end()) {
            qualityColorMap[0] = new Color(0,0,0);
        }
        if (qualityColorMap.find(1) == qualityColorMap.end()) {
            qualityColorMap[1] = new Color(1,1,1);
        }

        string rSTR = getPreference("qualityColors.negQualityColor.r");
        string gSTR = getPreference("qualityColors.negQualityColor.g");
        string bSTR = getPreference("qualityColors.negQualityColor.b");

        double r=159/255.0, g=0, b=1;

        if (rSTR != "") {
            r = stoi(rSTR)/255.0;
        }
        if (gSTR != "") {
            g = stoi(gSTR)/255.0;
        }
        if (bSTR != "") {
            b = stoi(bSTR)/255.0;
        }

        negQualityColor = new Color(r,g,b);
    }

    if (quality < 0 || quality > 1) {
        return negQualityColor;
    }

    if (qualityColorMap.find(quality) != qualityColorMap.end()) {
        return qualityColorMap[quality];
    }

    double a = 0;
    double b = 1;
    for (auto iter : qualityColorMap) {
        if (a < iter.first && iter.first < quality) {
            a = iter.first;
        }
        if (b > iter.first && iter.first > quality) {
            b = iter.first;
        }
    }

    Color begin = *qualityColorMap[a];
    Color end = *qualityColorMap[b];

    return interpolateColor(begin, end, a, b, quality);
}

Color UserPreferencesManager::getGroupColor(int groupID) {
    string key = "groups.g(id=" + to_string(groupID) + ").";

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

Color UserPreferencesManager::getYAxisColor() {
    string rSTR = getPreference("axes.y.r");
    string gSTR = getPreference("axes.y.g");
    string bSTR = getPreference("axes.y.b");

    double r = 0, g = 1, b = 0;

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

    double r = 0, g = 0, b = 1;

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
        XMLNode* childNode = NULL;

        string childKey, restOfPath;

        if (path.find_first_of('(') != string::npos && path.find_first_of('(')<path.find_first_of('.')) {
            string attrKey = path.substr(path.find_first_of('(')+1, path.find_first_of('=')-path.find_first_of('(')-1);
            string attrVal = path.substr(path.find_first_of('=')+1, path.find_first_of(')')-path.find_first_of('=')-1);

            childKey = path.substr(0, path.find_first_of('('));
            restOfPath = path.substr(path.find_first_of(')')+2);

            childNode = currentRoot -> getChildByAttributeValue(childKey, attrKey, attrVal);
        } else {
            childKey = path.substr(0, path.find_first_of('.'));
            restOfPath = path.substr(path.find_first_of('.')+1);

            childNode = currentRoot -> getChild(childKey);
        }

        if (childNode != NULL) {
            return getPreference(restOfPath, childNode);
        }
    } else {
        return currentRoot -> findAttribute(path);
    }
    return "";
}

vector<string> UserPreferencesManager::getAttributeValues(string path, string attribute) {
    XMLNode* root = parser -> getRoot();

    if (root != NULL) {
        return getAttributeValues(path, attribute, root);
    }

    vector<string> empty;
    return empty;
}

vector<string> UserPreferencesManager::getAttributeValues(string path, string attribute, XMLNode* currentRoot) {
    if (path.find_first_of('.') != string::npos) {
        string childKey = path.substr(0, path.find_first_of('.'));
        string restOfPath = path.substr(path.find_first_of('.')+1);

        XMLNode* childNode = NULL;

        if (childKey.find_first_of('(') != string::npos) {
            string attrKey = childKey.substr(childKey.find_first_of('(')+1, childKey.find_first_of('=')-childKey.find_first_of('(')-1);
            string attrVal = childKey.substr(childKey.find_first_of('=')+1, childKey.find_first_of(')')-childKey.find_first_of('=')-1);
            childKey = childKey.substr(0, childKey.find_first_of('('));

            childNode = currentRoot -> getChildByAttributeValue(childKey, attrKey, attrVal);
        } else {
            childNode = currentRoot -> getChild(childKey);
        }

        if (childNode != NULL) {
            return getAttributeValues(restOfPath, attribute, childNode);
        }
    } else {
        vector<XMLNode*> childrenNodes = currentRoot -> getChildren(path);
        vector<string> result;

        for (auto children : childrenNodes) {
            string value = children -> findAttribute(attribute);

            if (value != "") {
                result.push_back(value);
            }
        }

        return result;
    }

    vector<string> empty;
    return empty;
}

Color* UserPreferencesManager::interpolateColor(Color begin, Color end, double qualityBegin, double qualityEnd, double quality) {
    double r = ((begin.r() - end.r()) * quality + qualityBegin * end.r() - qualityEnd * begin.r()) / (qualityBegin - qualityEnd);
    double g = ((begin.g() - end.g()) * quality + qualityBegin * end.g() - qualityEnd * begin.g()) / (qualityBegin - qualityEnd);
    double b = ((begin.b() - end.b()) * quality + qualityBegin * end.b() - qualityEnd * begin.b()) / (qualityBegin - qualityEnd);

    return new Color(r,g,b);
}
