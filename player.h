#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

class Player {
    public:
        int x;
        int y;
        double direction;
        Player(){};
        Player(int x, int y, double direction);
        ~Player(){};
        void set_location(int x, int y);
        void set_direction(double direction);
};

#endif
