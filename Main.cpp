#include "game.h"
#include "player.h"
#include "map.h"

#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#include <cmath>
#include <iostream>
const int left = 1;
const int right = 2;
const int forward = 4;
const int backward = 8;
static int move = 0;
static Game* g;

int init_resources() {
    return 1;
}

void onDisplay() {
    glDrawPixels(500, 500,  GL_LUMINANCE, GL_UNSIGNED_BYTE, g->frame);
    glutSwapBuffers();
}

void free_resources() {

}

void special(int key, int x, int y) {
    if(key == GLUT_KEY_LEFT)
        move |= left;
    if(key == GLUT_KEY_RIGHT)
        move |= right;
    if(key == GLUT_KEY_UP)
        move |= forward;
    if(key == GLUT_KEY_DOWN)
        move |= backward;
}

void specialup(int key, int x, int y) {
    if(key == GLUT_KEY_LEFT)
        move &= ~left;
    if(key == GLUT_KEY_RIGHT)
        move &= ~right;
    if(key == GLUT_KEY_UP)
        move &= ~forward;
    if(key == GLUT_KEY_DOWN)
        move &= ~backward;
}

void idle() {
    static int pt = 0;
    const float move_speed = 5;

    int t = glutGet(GLUT_ELAPSED_TIME);
    float dt = (t - pt) * 1.0e-3;
    pt = t;

    //Calculate movement vectors
    float dx = 3 * cos(g->player->direction) * dt;
    float dy = 3 * sin(g->player->direction) * dt;

    //Update player position
    if(move & left)
        g->player->rotate(-M_PI * dt);
    if(move & right)
        g->player->rotate(M_PI * dt);
    if(move & forward)
        g->player->walk_forward(dx, dy);
    if(move & backward)
        g->player->walk_forward(-dx, -dy);

    if(move) {
        g->draw_vectors();
        glutPostRedisplay();
    }
}

int main(int argc, char* argv[]) {
    Player *p = new Player(30, 20, 0);
    printf("%f\n", p->x);
    Map *m = new Map(40);
    for (int i = 0; i < 40; i++) {
        (*m).wallgrid[39 + i*40] = 1;
        if (i < 19 || i > 21) {
            (*m).wallgrid[35 + i*40] = 1;
        }
    }
    printf("%d\n", m->size);
    g = new Game(500, 0.8, m, p);
    g->draw_vectors();
    for (int i = 0; i < 500; i++) {
        printf("%f\n", (*g).walls[i]);
    }

    // Initialize OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Hello World");
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        return EXIT_FAILURE;
    }
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    if (init_resources()) {
        /* We can display it if everything goes OK */
        glutSpecialFunc(special);
        glutSpecialUpFunc(specialup);
        glutIdleFunc(idle);
        glutDisplayFunc(onDisplay);
        glutMainLoop();
    }

    free_resources();
    return 0;
}
