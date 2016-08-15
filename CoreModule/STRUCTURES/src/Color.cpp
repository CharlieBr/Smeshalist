#include "Color.h"

#include <cmath>

Color::Color(int group_id){
    this -> red = 255 * abs(sin(group_id));
    this -> green = 255 * abs(cos(0.5 * group_id));
    this -> blue = 255 * abs(sin(0.1 * group_id));
};
