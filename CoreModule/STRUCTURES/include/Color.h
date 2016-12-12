#ifndef COLORSMAP_H
#define COLORSMAP_H

#include <iostream>
#include <map>
using namespace std;

class Color {
    double red;
    double green;
    double blue;
    double alpha;

    public:
        Color(double r, double g, double b, double a) : red(r), green(g), blue(b), alpha(a) {};
        Color(double r, double g, double b) : red(r), green(g), blue(b), alpha(1.0) {};
        Color(int);
        double r() const { return red; }
        double g() const { return green; }
        double b() const { return blue; }
        double a() const { return alpha; }
        bool operator==(const Color& col) const {
        return (this -> red == col.r()) &&
            ( this -> green == col.g()) &&
            ( this -> blue == col.b()) &&
            ( this -> alpha == col.a());
        }
};
#endif //COLORSMAP_H
