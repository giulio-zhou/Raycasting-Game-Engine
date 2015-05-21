#include "map.h"
#include "player.h"

Map::Map(int size) {
    this->size = size;
    this->wallgrid = new int[size*size];
}

Map::~Map() {
    delete[] this->wallgrid;
}

void Map::set_wallgrid(int* wallgrid) {
    this->wallgrid = wallgrid;
}

double Map::cast(Player player, double angle) {
    return -1;
}
