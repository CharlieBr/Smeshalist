#include "ColorsMap.h"

#include <cmath>

Color ColorsMap::get_color_for_group(int group_id){
    if(has_color(group_id)){
        return groups_colors.at(group_id);
    }
    Color color = create_new_color_for_group(group_id);
    groups_colors.insert(pair<int, Color>(group_id, color));
    return color;
}

bool ColorsMap::has_color(int group_id){
    map<int, Color>::iterator it = groups_colors.find(group_id);
    if(it == groups_colors.end()){
        return false;
    }
    return true;
}

Color ColorsMap::create_new_color_for_group(int group_id){
    double red = 255 * abs(sin(group_id));
    double green = 255 * abs(cos(0.5 * group_id));
    double blue = 255 * abs(sin(0.1 * group_id));
    return Color(red, green, blue);
}
