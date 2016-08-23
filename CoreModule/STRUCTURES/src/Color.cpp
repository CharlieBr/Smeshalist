#include "Color.h"

#include <cmath>

Color::Color(int group_id){
    this -> red = abs(sin(group_id));
    this -> green = abs(cos(0.5 * group_id));
    this -> blue = abs(sin(0.1 * group_id));
};
