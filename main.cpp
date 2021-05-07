#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#include "shader.h"

#include "objects/player.h"
#include "objects/enemy.h"
#include "objects/bullet.h"
#include "objects/item.h"
#include "aircraft.hpp"
#include "mode.h"
#include "hit.h"
#include "view.h"
#include "graph.h"

Player player = Player();
EnemyList enemy_list = EnemyList();
BulletList player_bullets = BulletList(PLAYER);
BulletList enemy_bullets = BulletList(ENEMY);
ItemList item_list = ItemList();
Gamemode mode = NORMAL;
LineRendering line_rendering = HIDING;
float planet = 0.0f;
float planet2 = 0.0f;

Viewmode view = TPS;
int over = 0;

extern GLuint VBO;
extern GLuint VAO;
extern GLuint EBO;
extern GLuint shaderProgram;

void camera_control();
void proj_control(int w, int h);
void isWire();
void drawRect(glm::mat4 inn, glm::vec4 color);
void determineColor(glm::vec4* player_color, glm::vec4* enemy_color);

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

static void display()
{
    isWire();
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);

    /*GLfloat timetime = glutGet(GLUT_ELAPSED_TIME) / 100.f;
    GLfloat greenValue = sin(timetime) / 2.f + 0.5f;
    GLint vertexC = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexC, 0.0f, greenValue, 0.f, 1.f);*/

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    
    glBindVertexArray(VAO);

    camera_control();

    Position player_position = player.get_position();
    Position enemy_position = enemy_list.getEnemy().get_position();
    std::vector <Position> player_bullet_positions;
    std::vector <Position> enemy_bullet_positions;
    std::vector<Position> item_positions;
    glm::mat4 inn = glm::mat4(1.f);
    glm::vec4 player_color = glm::vec4(1.f, 1.f, 1.f, 1.f);
    glm::vec4 enemy_color = glm::vec4(1.f, 1.f, 1.f, 1.f);
    int i;
    determineColor(&player_color, &enemy_color);

    // Draw Player
    inn = glm::translate(inn, glm::vec3(player_position.x, 0.f, player_position.y));
    drawRect(inn, player_color);

    // Draw Enemy
    inn = glm::translate(glm::mat4(1.f), glm::vec3(enemy_position.x, 0.f, enemy_position.y));
    drawRect(inn, enemy_color);

    // Player Bullet
    player_bullet_positions = player_bullets.get_bullet_positions();
    for (i = 0; i < player_bullet_positions.size(); i++) {
        Position bullet_position = player_bullet_positions[i];

        inn = glm::translate(glm::mat4(1.f), glm::vec3(bullet_position.x, 0.f, bullet_position.y));
        inn = glm::scale(inn, glm::vec3(0.2f, 0.2f, 0.2f));
        drawRect(inn, glm::vec4(1.f, 0.5f, 0.f, 1.f));
    }

    // Enemy Bullet
    enemy_bullet_positions = enemy_bullets.get_bullet_positions();
    for (i = 0; i < enemy_bullet_positions.size(); i++) {
        Position bullet_position = enemy_bullet_positions[i];

        inn = glm::translate(glm::mat4(1.f), glm::vec3(bullet_position.x, 0.f, bullet_position.y));
        inn = glm::scale(inn, glm::vec3(0.2f, 0.2f, 0.2f));
        drawRect(inn, glm::vec4(1.f, 0.5f, 1.f, 1.f));
    }

    // Item
    item_positions = item_list.get_item_positions();
    for (i = 0; i < item_positions.size(); i++) {
        Position item_position = item_positions[i];
        
        inn = glm::translate(glm::mat4(1.f), glm::vec3(item_position.x, 0.f, item_position.y));
        inn = glm::scale(inn, glm::vec3(0.2f, 0.2f, 0.2f));
        drawRect(inn, glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
    }

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    proj_control(w, h);
}

void Init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'c':
        if (mode == ALLPASS) mode = NORMAL;
        else mode = ALLPASS;
        break;
    case 'f':
        if (mode == ALLFAIL) mode = NORMAL;
        else mode = ALLFAIL;
        break;
    case 'v':
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
    planet += 0.5;
    planet2 += 1;

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
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow(argv[0]);
    Init();
    glewInit();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkeyboard);
    glutIdleFunc(idle_func);
    glutTimerFunc(700, timer_func, 1);            // Enemy shoots every 500ms

    CreateVertexBuffer();
    CompileShaders();

    glutMainLoop();
    return 0;
}

void camera_control() {
    Position player_position = player.get_position();
    GLint mv_matrix_loc = glGetUniformLocation(shaderProgram, "model_view");
    glm::mat4 mv = glm::mat4(1.f);
    mv = glm::lookAt(glm::vec3(player_position.x, 0.7f, player_position.y - 0.2f), glm::vec3(player_position.x, -0.05f, player_position.y + 1.f), glm::vec3(0.f, 1.f, 0.f));
    glUniformMatrix4fv(mv_matrix_loc, 1, GL_FALSE, glm::value_ptr(mv));
}

void proj_control(int w, int h) {
    GLint pr_matrix_loc = glGetUniformLocation(shaderProgram, "projection");
    glm::mat4 pr = glm::mat4(1.f);
    pr = glm::frustum(-0.5, 0.5, -0.5 * (GLfloat)h / (GLfloat)w, 0.5 * (GLfloat)h / (GLfloat)w, 0.5, 7.0);
    glUniformMatrix4fv(pr_matrix_loc, 1, GL_FALSE, glm::value_ptr(pr));
}

void drawRect(glm::mat4 inn, glm::vec4 color) {
    GLint tr_matrix_loc = glGetUniformLocation(shaderProgram, "transform");
    glm::mat4 tran = glm::mat4(1.0f);
    tran = glm::translate(tran, glm::vec3(0.f, 0.f, 0.2f));
    tran = glm::scale(tran, glm::vec3(0.2f, 0.2f, 0.15f));
    tran = glm::rotate(tran, glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));
    tran = inn * tran;
    glUniformMatrix4fv(tr_matrix_loc, 1, GL_FALSE, glm::value_ptr(tran));

    GLint vertexC = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexC, color.x, color.y, color.z, 1.f);

    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);
}

void determineColor(glm::vec4* player_color, glm::vec4* enemy_color) {
    switch (player.getHP()) {
    case 3:
        *player_color = glm::vec4(0.f, 1.f, 0.f, 1.f);
        break;
    case 2:
        *player_color = glm::vec4(0.2f, 0.8f, 0.8f, 1.f);
        break;
    case 1:
        *player_color = glm::vec4(0.f, 0.f, 1.f, 1.f);
        break;
    default:
        *player_color = glm::vec4(0.f, 0.f, 0.f, 1.f);
        break;
    }

    switch (enemy_list.getIndex()) {
    case 0:
        *enemy_color = glm::vec4(1.f, 1.f, 0.f, 1.f);
        break;
    case 1:
        *enemy_color = glm::vec4(1.f, 0.5f, 0.f, 1.f);
        break;
    case 2:
        *enemy_color = glm::vec4(1.f, 0.f, 0.f, 1.f);
        break;
    case 3:
        *enemy_color = glm::vec4(0.8f, 0.2f, 0.8f, 1.f);
        break;
    case 4:
        *enemy_color = glm::vec4(0.35f, 0.2f, 0.8f, 1.f);
        break;
    default:
        *enemy_color = glm::vec4(0.f, 0.f, 0.f, 1.f);
        break;
    }
}

void isWire() {
    if (line_rendering == HIDING) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
