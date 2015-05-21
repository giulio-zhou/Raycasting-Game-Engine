#include "player.h"

Player::Player(int x, int y, double direction) {
    this->x = x;
    this->y = y;
    this->direction = direction;
}

void Player::set_location(int x, int y) {
    this->x = x;
    this->y = y;
}

void Player::set_direction(double direction) {
    this->direction = direction;
}
