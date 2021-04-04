#define GL_SILENCE_DEPRECATION
#include <GL/freeglut.h>
//#include <OpenGL/gl.h>
#include <vector>
#include "objects/player.h"
#include "objects/enemy.h"
#include "objects/bullet.h"
#include "objects/item.h"
#include "mode.h"
#include "graph.h"
#include "hit.h"

Player player = Player();
EnemyList enemy_list = EnemyList();
BulletList player_bullets = BulletList(PLAYER);
BulletList enemy_bullets = BulletList(ENEMY);
ItemList item_list = ItemList();
Gamemode mode = NORMAL;
float planet[5] = { 0.3f, 0.3f, 0.1f, 0.1f, 0.0f };
float planet2[5] = { 0.8f, 0.9f, 0.05f, 0.05f, 0.0f };

float plane[3] = { 0.5f, 0.15f, 130.0f };
bool plane_rotate = true;
int over = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    /*
    player.x = 0.01;
    player.y = 0.01;
    player.width = 0.15;
    player.height = 0.18;
    */
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    Position player_position = player.get_position();
    Position enemy_position = enemy_list.getEnemy().get_position();
    std::vector <Position> player_bullet_positions;
    std::vector <Position> enemy_bullet_positions;
    std::vector<Position> item_positions;

    int i;
    switch (over) {
    case 0:
        // Planetary System
        glLoadIdentity();
        Planet_System(planet[0], planet[1], planet[2], planet[3], planet[4]);
        Planet_System(planet2[0], planet2[1], planet2[2], planet2[3], -planet2[4]);

        //player
        switch (player.getHP()) {
        case 3:
            glColor3f(0, 1.0, 0);
            break;
        case 2:
            glColor3f(1.0, 1.0, 0);
            break;
        case 1:
            glColor3f(1.0, 0, 0);
            break;
        }
        Plane(player_position.x, player_position.y, plane[2]);

        //player bullet
        player_bullet_positions = player_bullets.get_bullet_positions();
        for (i = 0; i < player_bullet_positions.size(); i++) {
            Position bullet_position = player_bullet_positions[i];
            Bullet(bullet_position.x, bullet_position.y, BULLET_RADIUS);
        }

        //enemy
        switch (enemy_list.getIndex()) {
        case 0:
            glColor3f(1.0, 0, 0);
            break;
        case 1:
            glColor3f(1.0, 0.5, 0);
            break;
        case 2:
            glColor3f(1.0, 1.0, 0);
            break;
        case 3:
            glColor3f(0, 1.0, 0);
            break;
        case 4:
            glColor3f(0, 0, 1.0);
            break;
        }

        Rotatete();
        Plane(-enemy_position.x, -enemy_position.y, 220 - plane[2]);
        Origin();

        //enemy bullet
        enemy_bullet_positions = enemy_bullets.get_bullet_positions();
        for (i = 0; i < enemy_bullet_positions.size(); i++) {
            Position bullet_position = enemy_bullet_positions[i];
            Bullet(bullet_position.x, bullet_position.y, BULLET_RADIUS);
        }

        //item
        item_positions = item_list.get_item_positions();
        for (i = 0; i < item_positions.size(); i++) {
            Position item_position = item_positions[i];
            Item(item_position.x, item_position.y, ITEM_LENGTH);
        }
        
        break;

    case 1:
        glLoadIdentity();
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINE_STRIP);             // W
        glVertex2f(0.3, 0.6);
        glVertex2f(0.325, 0.5);
        glVertex2f(0.35, 0.6);
        glVertex2f(0.375, 0.5);
        glVertex2f(0.4, 0.6);
        glEnd();

        glBegin(GL_LINE_STRIP);             // I
        glVertex2f(0.5, 0.6);
        glVertex2f(0.5, 0.5);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(0.475, 0.6);
        glVertex2f(0.525, 0.6);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(0.475, 0.5);
        glVertex2f(0.525, 0.5);
        glEnd();

        glBegin(GL_LINE_STRIP);             // N
        glVertex2f(0.6, 0.5);
        glVertex2f(0.6, 0.6);
        glVertex2f(0.675, 0.5);
        glVertex2f(0.675, 0.6);
        glEnd();
        break;
    case 2:
        glLoadIdentity();
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINE_STRIP);             // L
        glVertex2f(0.25, 0.6);
        glVertex2f(0.25, 0.5);
        glVertex2f(0.325, 0.5);
        glEnd();

        glBegin(GL_LINE_LOOP);              // O
        glVertex2f(0.4, 0.6);
        glVertex2f(0.4, 0.5);
        glVertex2f(0.475, 0.5);
        glVertex2f(0.475, 0.6);
        glEnd();

        glBegin(GL_LINE_STRIP);             // S
        glVertex2f(0.625, 0.6);
        glVertex2f(0.55, 0.6);
        glVertex2f(0.55, 0.55);
        glVertex2f(0.625, 0.55);
        glVertex2f(0.625, 0.5);
        glVertex2f(0.55, 0.5);
        glEnd();

        glBegin(GL_LINE_STRIP);             // E
        glVertex2f(0.775, 0.6);
        glVertex2f(0.7, 0.6);
        glVertex2f(0.7, 0.5);
        glVertex2f(0.775, 0.5);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(0.7, 0.55);
        glVertex2f(0.775, 0.55);
        glEnd();
        break;
    }

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {
    case 'i':
        player.move_up(0.01);
        break;
    case 'm':
        player.move_down(0.01);
        break;
    case 'k':
        player.move_right(0.01);
        break;
    case 'j':
        player.move_left(0.01);
        break;
    case 'c':
        if (mode == ALLPASS) mode = NORMAL;
        else mode = ALLPASS;
        break;
    case 'f':
        if (mode == ALLFAIL) mode = NORMAL;
        else mode = ALLFAIL;
        break;
    case 32:  //space bar
        player.shoot();
        break;
    }
    glutPostRedisplay();
}

void specialkeyboard(int key, int x, int y) {
    Position player_position = player.get_position();

    switch (key) {
    case GLUT_KEY_UP:
        player.move_up(0.01);
        break;
    case GLUT_KEY_DOWN:
        player.move_down(0.01);
        break;
    case GLUT_KEY_RIGHT:
        player.move_right(0.01);
        break;
    case GLUT_KEY_LEFT:
        player.move_left(0.01);
        break;
    }
    glutPostRedisplay();
}

void idle_func() {
    player_bullets.move_bullets();
    enemy_bullets.move_bullets();
    enemy_list.move();
    item_list.move_items();
    planet[4] += 0.5;
    planet2[4] += 1;

    if (plane_rotate == true)
        plane[2] -= 0.2;
    else
        plane[2] += 0.2;

    if (plane[2] > 120)
        plane_rotate = true;
    if (plane[2] < 100)
        plane_rotate = false;

    check_hit();

    check_get_item();

    glutPostRedisplay();
}

void timer_func(int a) {
    enemy_list.getEnemy().shoot();
    if (enemy_list.getIndex() != 0) { enemy_list.move_2(); }

    glutTimerFunc(500, timer_func, 1);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkeyboard);
    glutIdleFunc(idle_func);
    glutTimerFunc(500, timer_func, 1);            // Enemy shoots every 500ms
    glutMainLoop();
    return 0;
}