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
        Color(int);
        double r() const { return red; }
        double g() const { return green; }
        double b() const { return blue; }
        bool operator==(const Color& col) const {
        return (this -> red == col.r()) &&
            ( this -> green == col.g()) &&
            ( this -> blue == col.b());
        }
};
#endif //COLORSMAP_H
