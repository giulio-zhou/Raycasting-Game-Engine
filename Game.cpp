#include "game.h"
#include "map.h"
#include "player.h"
#include <cmath>
#define CIRCLE 2*M_PI

Game::Game(int resolution, double focal_length, Map map, Player player) {
    this->resolution = resolution;
    this->focal_length = focal_length;
    this->walls = new double[resolution];
    this->frame = new char[resolution*resolution];
    this->map = map;
    this->player = player;
}

void Game::draw_vectors() {
    for (int i = 0; i < resolution; i++) {
        double x = ((double) i) / ((double) resolution) - 0.5;
        double angle = atan2(x, focal_length);
        double distance = map.cast(player, fmod(player.direction + angle, CIRCLE), 100);
        walls[i] = distance;
    } 
}
