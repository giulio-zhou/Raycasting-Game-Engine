#include "map.h"
#include "player.h"
#include <cmath>
#include <iostream>

Map::Map(int size) {
    this->size = size;
    this->wallgrid = new int[size*size];
}

Map::~Map() {
    delete[] this->wallgrid;
}

void Map::set_wallgrid(int* wallgrid) {
    this->wallgrid = wallgrid;
}

double Map::cast(Player player, double angle, double dist) {
    double x = player.x;
    double y = player.y;
    double dx = cos(angle);
    double dy = sin(angle);
    while (distance(player.x, player.y, x, y) < dist) {
        double next_x = round(x, dx);
        double next_y = round(y, dy);
        printf("%f %f %f %f %f\n", angle, x, y, dx, dy);
        if ((next_x - x)/dx > (next_y - y)/dy) {
            x += ((next_y - y)/dy) * dx;
            y = next_y;
            double curr_dist = distance(player.x, player.y, x, y);
            if (curr_dist < dist && wallgrid[(int)(floor(x) + size*y)] == 1 && 
                                    wallgrid[(int)(ceil(x) + size*y)] == 1) {
                return curr_dist;
            }
        } else {
            y += ((next_x - x)/dx) * dy;
            x = next_x;
            double curr_dist = distance(player.x, player.y, x, y);
            if (curr_dist < dist && wallgrid[(int)(x + size*floor(y))] == 1 && 
                                    wallgrid[(int)(x + size*ceil(y))] == 1) {
                return curr_dist;
            }
        }
    }
    return INFINITY;
}

double Map::round(double val, double dval) {
    bool increasing = dval >= 0;
    if (val == floor(val)) {
        return (increasing) ? val + 1: val - 1;
    } else if (increasing) {
        return ceil(val);
    }
    return floor(val);
}

double Map::distance(double x, double y, double curr_x, double curr_y) {
    return pow(pow(curr_x - x, 2) + pow(curr_y - y, 2), 0.5);
}
