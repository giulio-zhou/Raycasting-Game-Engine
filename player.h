#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

class Player {
    public:
        double x;
        double y;
        double direction;
        Player(){};
        Player(double x, double y, double direction);
        ~Player(){};
        void set_location(double x, double y);
        void set_direction(double direction);
};

#endif
