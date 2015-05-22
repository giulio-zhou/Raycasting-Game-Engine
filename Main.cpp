#include "game.h"
#include "player.h"
#include "map.h"
#include <iostream>
int main() {
    Player *p = new Player(30, 20, 0.);
    printf("%f\n", p->x);
    int grid[100];
    Map *m = new Map(40);
    for (int i = 0; i < 40; i++) {
        (*m).wallgrid[39 + i*40] = 1;
    }
    printf("%d\n", m->size);
    Game *g = new Game(500, 0.8, *m, *p);
    g->draw_vectors();
    for (int i = 0; i < 500; i++) {
        printf("%f\n", (*g).walls[i]);
    }
    return 0;
}
