#include <GL/freeglut.h>
//#include <OpenGL/gl.h>
#include <vector>
#include "objects.h"
#include "mode.h"

Player player = Player();
EnemyList enemy_list = EnemyList();
BulletList player_bullets;
BulletList enemy_bullets;
Gamemode mode = NORMAL;
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

void drawTri() {
    glBegin(GL_TRIANGLES);
        glVertex2f(0, 0);
        glVertex2f(PLAYER_WIDTH, 0);
        glVertex2f(PLAYER_WIDTH / 2, PLAYER_HEIGHT);
    glEnd();
}

void drawRect() {
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(BULLET_WIDTH, 0);
        glVertex2f(BULLET_WIDTH, BULLET_HEIGHT);
        glVertex2f(0, BULLET_HEIGHT);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    triangle player_shape = *player.get_shape();
    triangle enemy_shape = *enemy_list.getEnemy().get_shape();
    std::vector <rectangle> player_bullet_shapes;
    std::vector <rectangle> enemy_bullet_shapes;

    int i;
    switch (over) {
    case 0:
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
        glLoadIdentity();
        glTranslatef(player_shape.x, player_shape.y, 0);
        drawTri();

        //player bullet
        player_bullet_shapes = player_bullets.get_bullet_shapes();
        for (i = 0; i < player_bullet_shapes.size(); i++) {
            rectangle bullet_shape = player_bullet_shapes[i];
            glLoadIdentity();
            glTranslatef(bullet_shape.x, bullet_shape.y, 0);
            drawRect();
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
        glLoadIdentity();
        glRotatef(180, 0, 0, 1);
        glTranslatef(-enemy_shape.x - PLAYER_WIDTH, -enemy_shape.y, 0);
        drawTri();

        //enemy bullet
        enemy_bullet_shapes = enemy_bullets.get_bullet_shapes();
        for (i = 0; i < enemy_bullet_shapes.size(); i++) {
            rectangle bullet_shape = enemy_bullet_shapes[i];
            glLoadIdentity();
            glRotatef(180, 0, 0, 1);
            glTranslatef(-bullet_shape.x, -bullet_shape.y, 0);
            drawRect();
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
    case 'p':
        enemy_bullets.shoot(false);
        break;
    case 32:  //space bar
        player_bullets.shoot(true);
        break;
    }
    glutPostRedisplay();
}

void specialkeyboard(int key, int x, int y) {
    triangle player_shape = *player.get_shape();

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
    player_bullets.move_bullets(UP);
    enemy_bullets.move_bullets(DOWN);
    enemy_list.move();

    glutPostRedisplay();
}

void timer_func(int a) {
    enemy_bullets.shoot(false);
    if (enemy_list.getIndex() == 2) { enemy_list.move_2(); }

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
