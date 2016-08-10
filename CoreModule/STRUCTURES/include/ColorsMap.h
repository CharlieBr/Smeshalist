#ifndef COLORSMAP_H
#define COLORSMAP_H

#include <iostream>
#include <map>
using namespace std;

class Color {
    double red;
    double green;
    double blue;

    public:
        Color(double r, double g, double b) : red(r), green(g), blue(b) {};
        double r(){ return red; }
        double g(){ return green; }
        double b(){ return blue; }
};

class ColorsMap {
    map<int, Color> groups_colors;

    public:
        ColorsMap(){};
        bool has_color(int);
        void add_group_with_color(int group_id, Color color){ groups_colors.insert(pair<int,Color>(group_id, color)); }
        Color get_color_for_group(int);
        Color create_new_color_for_group(int);
};
#endif //COLORSMAP_H
