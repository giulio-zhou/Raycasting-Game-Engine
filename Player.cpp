#include "player.h"

Player::Player(double x, double y, double direction) {
    this->x = x;
    this->y = y;
    this->direction = direction;
}

void Player::set_location(double x, double y) {
    this->x = x;
    this->y = y;
}

void Player::set_direction(double direction) {
    this->direction = direction;
}
