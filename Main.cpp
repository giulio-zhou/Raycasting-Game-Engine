#include "player.h"
#include "map.h"
#include <iostream>
int main() {
    Player *p = new Player(1, 1, 0.);
    printf("%d", p->x);
    int grid[100];
    Map *m = new Map(10);
    printf("%d", m->size);
    return 0;
}
