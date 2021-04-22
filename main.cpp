#define GL_SILENCE_DEPRECATION
#include <GL/freeglut.h>
//#include <OpenGL/gl.h>
#include <vector>
#include "objects/player.h"
#include "objects/enemy.h"
#include "objects/bullet.h"
#include "objects/item.h"
#include "aircraft.hpp"
#include "mode.h"
#include "graph.h"
#include "hit.h"
#include "view.h"

Player player = Player();
EnemyList enemy_list = EnemyList();
BulletList player_bullets = BulletList(PLAYER);
BulletList enemy_bullets = BulletList(ENEMY);
ItemList item_list = ItemList();
Gamemode mode = NORMAL;
LineRendering line_rendering = SHOWING;
float planet[5] = { 0.3f, 0.3f, 0.1f, 0.1f, 0.0f };
float planet2[5] = { 0.8f, 0.9f, 0.05f, 0.05f, 0.0f };

float plane[3] = { 0.5f, 0.15f, 130.0f };
bool plane_rotate = true;
Viewmode view = TPS;
int over = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glFrustum(-4.0, 4.0, -4.0, 4.0, 1.0, 10.0);
    /*
    player.x = 0.01;
    player.y = 0.01;
    player.width = 0.15;
    player.height = 0.18;
    */
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glColor3f(1.0, 1.0, 1.0);
    
    Position player_position = player.get_position();
    Position enemy_position = enemy_list.getEnemy().get_position();
    std::vector <Position> player_bullet_positions;
    std::vector <Position> enemy_bullet_positions;
    std::vector<Position> item_positions;

    float iii = -5;
    int i;

    switch (over) {
    case 0:
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
        while (iii <= 10) {
            glVertex3f(-5, -0.1, iii);
            glVertex3f(10, -0.1, iii);

            glVertex3f(iii, -0.1, -5);
            glVertex3f(iii, -0.1, 10);
            iii += 0.15;
        }
        glEnd();
        
        if (line_rendering == HIDING) {
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        }
        else {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        }

        // Planet #1
        glPushMatrix();
            glColor3f(0.5, 0.5, 0.0);
            glTranslatef(9, -2, 4);
            glutSolidSphere(1, 100, 100);

            glColor3f(0.5, 0.0, 0.0);
            glRotatef(planet[4], 0, 1, 0);
            glTranslatef(1.5, 0.0, 1.5);
            glScalef(0.3, 0.3, 0.3);
            glutSolidSphere(1, 100, 100);

            glColor3f(0.0, 0.5, 0.0);
            glRotatef(planet[4] * 2, 0, 1, 0);
            glTranslatef(1.5, 0.0, 1.5);
            glScalef(0.3, 0.3, 0.3);
            glutSolidSphere(1, 100, 100);
        glPopMatrix();

        // Planet #2
        glPushMatrix();
            glColor3f(0.5, 0.5, 0.0);
            glTranslatef(3.0, 1.5, 4.0);
            glutSolidSphere(0.6, 100, 100);

            glColor3f(0.0, 0.8, 0.4);
            glRotatef(planet2[4], 0, 1, 0);
            glTranslatef(1.0, 0.0, 1.0);
            glScalef(0.3, 0.3, 0.3);
            glutSolidSphere(1, 100, 100);

            glColor3f(0.5, 0.5, 0.5);
            glRotatef(planet[4] * 2, 0, 1, 0);
            glTranslatef(1.0, 0.0, 1.0);
            glScalef(0.3, 0.3, 0.3);
            glutSolidSphere(1, 100, 100);
        glPopMatrix();

        //player
        /*switch (player.getHP()) {
        case 3:
            glColor3f(0, 1.0, 0);
            break;
        case 2:
            glColor3f(1.0, 1.0, 0);
            break;
        case 1:
            glColor3f(1.0, 0, 0);
            break;
        }*/

        // Player
        glPushMatrix();
            glTranslatef(player_position.x, 0, player_position.y);
            glScalef(0.1, 0.1, 0.1);
            draw_aircraft();
        glPopMatrix();
       
        // player bullet
        glColor3f(1.0f, 0.5f, 0.0f);
        player_bullet_positions = player_bullets.get_bullet_positions();
        for (i = 0; i < player_bullet_positions.size(); i++) {
            Position bullet_position = player_bullet_positions[i];
            glPushMatrix();
                glTranslatef(bullet_position.x, 0.0, bullet_position.y);
                glutSolidSphere(BULLET_RADIUS, 50, 50);
            glPopMatrix();
            //Bullet_(bullet_position.x, bullet_position.y, BULLET_RADIUS);
        }

        //enemy
        /*switch (enemy_list.getIndex()) {
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
        }*/

        // Enemy
        glPushMatrix();
            glTranslatef(enemy_position.x, 0.0, enemy_position.y);
            glRotatef(180, 0, 1, 0);
            glScalef(0.1, 0.1, 0.1);
            draw_aircraft();
        glPopMatrix();

        //enemy bullet
        glColor3f(1.0f, 0.5f, 1.0f);
        enemy_bullet_positions = enemy_bullets.get_bullet_positions();
        for (i = 0; i < enemy_bullet_positions.size(); i++) {
            Position bullet_position = enemy_bullet_positions[i];
            glPushMatrix();
                glTranslatef(bullet_position.x, 0.0, bullet_position.y);
                glutSolidSphere(BULLET_RADIUS, 50, 50);
            glPopMatrix();
        }

        //item
        item_positions = item_list.get_item_positions();
        for (i = 0; i < item_positions.size(); i++) {
            glColor3f(0.1f, 0.1f, 0.1f);
            Position item_position = item_positions[i];
            glPushMatrix();
                glTranslatef(item_position.x, 0.0, item_position.y);
                glutSolidSphere(ITEM_LENGTH, 50, 50);
            glPopMatrix();
        }
        glLoadIdentity();
        gluLookAt(player_position.x, 0.7, player_position.y - 2.0, player_position.x, -0.05, player_position.y + 1, 0, 1, 0);

        break;

    case 1:
        glLoadIdentity();
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_STRIP);             // W
        glVertex3f(0.3, 0.0, 0.6);
        glVertex3f(0.325, 0.0, 0.5);
        glVertex3f(0.35, 0.0, 0.6);
        glVertex3f(0.375, 0.0, 0.5);
        glVertex3f(0.4, 0.0, 0.6);
        glEnd();

        glBegin(GL_LINE_STRIP);             // I
        glVertex3f(0.5, 0.0, 0.6);
        glVertex3f(0.5, 0.0, 0.5);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex3f(0.475, 0.0, 0.6);
        glVertex3f(0.525, 0.0, 0.6);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex3f(0.475, 0.0, 0.5);
        glVertex3f(0.525, 0.0, 0.5);
        glEnd();

        glBegin(GL_LINE_STRIP);             // N
        glVertex3f(0.6, 0.0, 0.5);
        glVertex3f(0.6, 0.0, 0.6);
        glVertex3f(0.675, 0.0, 0.5);
        glVertex3f(0.675, 0.0, 0.6);
        glEnd();
        break;
    case 2:
        glLoadIdentity();
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_STRIP);             // L
        glVertex3f(0.25, 0.0, 0.6);
        glVertex3f(0.25, 0.0, 0.5);
        glVertex3f(0.325, 0.0, 0.5);
        glEnd();

        glBegin(GL_LINE_LOOP);              // O
        glVertex3f(0.4, 0.0, 0.6);
        glVertex3f(0.4, 0.0, 0.5);
        glVertex3f(0.475, 0.0, 0.5);
        glVertex3f(0.475, 0.0, 0.6);
        glEnd();

        glBegin(GL_LINE_STRIP);             // S
        glVertex3f(0.625, 0.0, 0.6);
        glVertex3f(0.55, 0.0, 0.6);
        glVertex3f(0.55, 0.0, 0.55);
        glVertex3f(0.625, 0.0, 0.55);
        glVertex3f(0.625, 0.0, 0.5);
        glVertex3f(0.55, 0.0, 0.5);
        glEnd();

        glBegin(GL_LINE_STRIP);             // E
        glVertex3f(0.775, 0.0, 0.6);
        glVertex3f(0.7, 0.0, 0.6);
        glVertex3f(0.7, 0.0, 0.5);
        glVertex3f(0.775, 0.0, 0.5);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(0.7, 0.0, 0.55);
        glVertex3f(0.775, 0.0, 0.55);
        glEnd();
        break;
    }
    //glLoadIdentity();
    //gluLookAt(player_position.x, 0.7, player_position.y - 2.0, player_position.x, -0.05, player_position.y + 1, 0, 1, 0);
    //gluLookAt(player_position.x, 5.0, player_position.y, player_position.x, -0.05, player_position.y, 0, 0, 1);
    glTranslatef(0.0, 0.0, -1.0);
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.5, 0.5, -0.5 * (GLfloat)h / (GLfloat)w, 0.5 * (GLfloat)h / (GLfloat)w, 0.5, 7.0);
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
        case 'v':
            printf("keyboard v\n");
            view_change();
            break;
        case 'r':
            if (line_rendering == SHOWING) line_rendering = HIDING;
            else line_rendering = SHOWING;
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
        player.move_up(0.05);
        break;
    case GLUT_KEY_DOWN:
        player.move_down(0.05);
        break;
    case GLUT_KEY_RIGHT:
        player.move_left(0.05);
        break;
    case GLUT_KEY_LEFT:
        player.move_right(0.05);
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

    /*if (plane_rotate == true)
        plane[2] -= 0.2;
    else
        plane[2] += 0.2;

    if (plane[2] > 120)
        plane_rotate = true;
    if (plane[2] < 100)
        plane_rotate = false;*/

    check_hit();
    check_get_item();

    glutPostRedisplay();
}

void timer_func(int a) {
    enemy_list.getEnemy().shoot();
    if (enemy_list.getIndex() != 0) { enemy_list.move_2(); }

    glutTimerFunc(1300, timer_func, 1);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(500, 300);
    glutCreateWindow(argv[0]);
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkeyboard);
    glutIdleFunc(idle_func);
    glutTimerFunc(700, timer_func, 1);            // Enemy shoots every 500ms

    glutMainLoop();
    return 0;
}