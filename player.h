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
        void walk_forward(double dx, double dy);
        void rotate(double angle);
};

#endif
