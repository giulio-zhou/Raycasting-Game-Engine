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
        double cast(Player player, double angle); 
};

#endif
