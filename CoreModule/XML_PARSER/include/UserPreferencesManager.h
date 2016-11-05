#ifndef USERPREFERENCESMANAGER_H
#define USERPREFERENCESMANAGER_H

#include <string>
#include "XMLParser.h"
#include "../../STRUCTURES/include/Color.h"

using namespace std;


class UserPreferencesManager
{
    public:
        static UserPreferencesManager* getInstance();
        string getPreference(string);

        Color getBackgroudColor();
        Color getGroupColor(int);
    protected:
    private:
        XMLParser* parser;
        static UserPreferencesManager* instance;
        const string file = "user.config.xml";

        string getPreference(string, XMLNode*);
        UserPreferencesManager();
};

#endif // USERPREFERENCESMANAGER_H
