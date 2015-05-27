#include "game.h"
#include "player.h"
#include "map.h"

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#include <iostream>
int main(int argc, char* argv[]) {
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
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Hello World");
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawPixels(500, 500,  GL_LUMINANCE, GL_UNSIGNED_BYTE, g->frame);
    std::cin.get();
    return 0;
}
