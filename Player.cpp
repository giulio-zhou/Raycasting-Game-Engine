#include "player.h"
#include <cmath>

Player::Player(double x, double y, double direction) {
    this->x = x;
    this->y = y;
    this->direction = direction;
}

void Player::walk_forward(double dx, double dy) {
    this->x += dx;
    this->y += dy;
}

void Player::rotate(double angle) {
    this->direction = fmod(this->direction + angle, 2*M_PI);
}
