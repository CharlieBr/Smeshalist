#ifndef USERPREFERENCESMANAGER_H
#define USERPREFERENCESMANAGER_H

#include <string>
#include "XMLParser.h"
#include "Color.h"

using namespace std;


class UserPreferencesManager
{
    public:
        static UserPreferencesManager* getInstance();
        string getPreference(string);

        Color getBackgroudColor();
        Color getGroupColor(int);

        int getCorePort();
        Color getXAxisColor();
        Color getYAxisColor();
        Color getZAxisColor();
        Color getCuttingPlaneColor();
        Color* getQualityColor(double);

        float getPointSize();
    protected:
    private:
        XMLParser* parser;
        static UserPreferencesManager* instance;
        const string file = "user.config.xml";

        string getPreference(string, XMLNode*);
        vector<string> getAttributeValues(string, string);
        vector<string> getAttributeValues(string, string, XMLNode*);
        UserPreferencesManager();
        Color* interpolateColor(Color, Color, double, double, double);

        static map<double, Color*> qualityColorMap;
        static Color* negQualityColor;
};

#endif // USERPREFERENCESMANAGER_H
