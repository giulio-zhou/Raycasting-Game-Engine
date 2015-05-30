#ifndef __MAP_H_INCLUDED__
#define __MAP_H_INCLUDED__
#include "player.h"

class Map {
    public: 
        int size;
        int* wallgrid;
        Map(){};
        Map(int size);
        ~Map();
        void set_wallgrid(int* wallgrid);
        double cast(Player* player, double angle, double distance);
        double round(double val, double dval);
        double distance(double x, double y, double curr_x, double curr_y);
        int in_bounds(double x, double y);
        int check_wall(Player* player, double dx, double dy);
};

#endif
