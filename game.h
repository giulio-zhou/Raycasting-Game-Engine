#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__
#include "player.h"
#include "map.h"

class Game {
    public:
        int resolution;
        double focal_length;
        double* walls;
        Player player;
        Map map; 
        Game(){};
        Game(int resolution, double focal_length, Map map, Player player);
        ~Game(){};

        void draw_vectors();
};

#endif
