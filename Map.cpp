#include "map.h"
#include "player.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <list>

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

double Map::cast(Player* player, double angle, double dist) {
    double x = player->x;
    double y = player->y;
    double dx = cos(angle);
    double dy = sin(angle);
    while (distance(player->x, player->y, x, y) < dist) {
        double next_x = round(x, dx);
        double next_y = round(y, dy);
        if ((next_x - x)/dx > (next_y - y)/dy) {
            x += ((next_y - y)/dy) * dx;
            y = next_y;
            double curr_dist = distance(player->x, player->y, x, y);
            if (curr_dist < dist && wallgrid[(int)(floor(x) + size*y)] == 1 && 
                                    wallgrid[(int)(ceil(x) + size*y)] == 1 &&
                                    in_bounds(floor(x), y) && in_bounds(ceil(x), y)) {
                return curr_dist;
            }
        } else {
            y += ((next_x - x)/dx) * dy;
            x = next_x;
            double curr_dist = distance(player->x, player->y, x, y);
            if (curr_dist < dist && wallgrid[(int)(x + size*floor(y))] == 1 && 
                                    wallgrid[(int)(x + size*ceil(y))] == 1 &&
                                    in_bounds(floor(x), y) && in_bounds(ceil(x), y)) {
                return curr_dist;
            }
        }
    }
    return INFINITY;
}

double Map::round(double val, double dval) {
    bool increasing = dval >= 0;
    if (val == floor(val)) {
        return (increasing) ? val + 1: val - 1;
    } else if (increasing) {
        return ceil(val);
    }
    return floor(val);
}

double Map::distance(double x, double y, double curr_x, double curr_y) {
    return pow(pow(curr_x - x, 2) + pow(curr_y - y, 2), 0.5);
}

int Map::in_bounds(double x, double y) {
    return x >= 0 && y >= 0 && x < size && y < size;
}

int Map::check_wall(Player* player, double dx, double dy) {
    float x = player->x + dx;
    float y = player->y + dy;
    return in_bounds(x, y) && wallgrid[(int)(floor(x) + size*floor(y))] != 1;
}

void Map::generate_maze_Prim(int* wallgrid, int size) {
    for (int i = 0; i < size*size; i++) {
        wallgrid[i] = 0;
    }
    std::list<int>* queue = new std::list<int>();
    queue->push_front(0);
    while (queue->size() > 0) {
        int index = rand() % queue->size();
        std::list<int>::iterator it = queue->begin();
        for (int i = 0; i < index; i++) it++;
        int curr_element = *it;
        queue->erase(it);
        if (wallgrid[curr_element]) {
            continue;
        }
        int x = curr_element % size;
        int y = curr_element / size;
        int num_neighbors = 0;
        for (int i = -4; i <= 4 ; i++) {
            int curr_x = x + fmod(i, 3);
            int curr_y = y + (i / 3);
            if (!in_bounds(curr_x, curr_y) || i % 2 == 0) {
                continue;
            } else if (wallgrid[curr_x + curr_y*size]) {
                num_neighbors++;
            }
        }
        if (num_neighbors == 1 || curr_element == 0) {
            wallgrid[curr_element] = 1;
            for (int i = -1; i <= 1; i += 2) {
                if (in_bounds(x + i, y) && wallgrid[x + i + y*size] == 0) queue->push_front(x + i + y*size);
                if (in_bounds(x, y + i) && wallgrid[x + (y + i)*size] == 0) queue->push_front(x + (y + i)*size);
            }
        }
    }
}

void Map::set_maze_wallgrid(int* mazegrid, int size) {
    int WIDTH = 5;
    int OFFSET = WIDTH/2 + size*WIDTH*(WIDTH/2);
    this->wallgrid = new int[(int) pow(size*WIDTH, 2)];
    this->size = size*WIDTH;
    //Mark the borders with walls
    for (int i = 0; i < size*WIDTH; i++) {
        wallgrid[i] = 1;
        wallgrid[WIDTH*size*i] = 1;
        wallgrid[size*WIDTH*(size*WIDTH - 1) + i] = 1;
        wallgrid[WIDTH*size*i + (size*WIDTH - 1)] = 1;
    }
    //Draw a wall between each 0 and 1 in the grid
    for (int i = 0; i < size*size; i++) {
        int x = i % size;
        int y = i / size;
        for (int j = -3; j <= 3; j += 2) {
            int x_offset = fmod(j, 3);
            int y_offset = j / 3;
            int curr_x = x + x_offset;
            int curr_y = y + y_offset;
            if (in_bounds(curr_x, curr_y) && mazegrid[i] != mazegrid[curr_x + curr_y*size]) {
                for (int k = 0; k <= WIDTH/2 + 1; k++) {
                    wallgrid[OFFSET + (x*WIDTH + x_offset*(WIDTH/2)) + (y*WIDTH + y_offset*(WIDTH/2))*size*WIDTH + k*(x_offset*size*WIDTH + y_offset)] = 1;
                    wallgrid[OFFSET + (x*WIDTH + x_offset*(WIDTH/2)) + (y*WIDTH + y_offset*(WIDTH/2))*size*WIDTH - k*(x_offset*size*WIDTH + y_offset)] = 1;
                }
            }
        }
    }
}
