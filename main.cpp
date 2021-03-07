#include <GL/freeglut.h>
#include <OpenGL/gl.h>
#include <vector>
#include "units.h"

Player player = Player();
std::vector <rectangle> player_bullets;

void init(void){
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  /*
  player.x = 0.01;
  player.y = 0.01;
  player.width = 0.15;
  player.height = 0.18;
  */
}  

void display (void) {
  glClear (GL_COLOR_BUFFER_BIT);

  glColor3f(1.0, 1.0, 1.0);

  triangle player_shape = *player.get_shape();
  glBegin(GL_LINE_LOOP);
    glVertex2f(player_shape.x, player_shape.y);
    glVertex2f(player_shape.x + player_shape.width, player_shape.y);
    glVertex2f(player_shape.x + player_shape.width/2, player_shape.y + player_shape.height);
  glEnd();
  for(int i = 0; i < player_bullets.size(); i++){
    rectangle bullet = player_bullets[i];
    glBegin(GL_LINE_LOOP);
      glVertex2f(bullet.x, bullet.y);
      glVertex2f(bullet.x + bullet.width, bullet.y);
      glVertex2f(bullet.x + bullet.width, bullet.y + bullet.height);
      glVertex2f(bullet.x, bullet.y + bullet.height);
    glEnd();
  }
  glutSwapBuffers ();
}

void reshape (int w, int h) {
 glViewport (0,0,(GLsizei)w, (GLsizei)h);
 glMatrixMode (GL_PROJECTION);
 glLoadIdentity ();
 gluOrtho2D (0, 1, 0, 1);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
}

void moveBullets(){
  for(int i = 0; i < player_bullets.size(); i++){
      player_bullets[i].y += 0.01;
  }
  glutPostRedisplay();
}

void rectangle_draw(){

  rectangle* bullet = &(player_bullets.back());
  glBegin(GL_LINE_LOOP);
      glVertex2f(bullet->x, bullet->y);
      glVertex2f(bullet->x + bullet->width, bullet->y);
      glVertex2f(bullet->x + bullet->width, bullet->y + bullet->height);
      glVertex2f(bullet->x, bullet->y + bullet->height);
  glEnd();

  glutSwapBuffers();
}

void shoot(){
  rectangle bullet;
  triangle player_shape = *player.get_shape();

  bullet.width = 0.03;
  bullet.height = 0.03;
  bullet.x = player_shape.x + player_shape.width/2 - bullet.width/2;
  bullet.y = player_shape.y + player_shape.height;

  player_bullets.push_back(bullet);
}

void keyboard(unsigned char key, int x, int y){

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
    case 32:  //space bar
      shoot();
      break;
  }
  glutPostRedisplay();
}

void specialkeyboard(int key, int x, int y){ 
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



int main (int argc, char **argv) {

  glutInit (&argc, argv); 
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); 
  glutInitWindowSize (500, 500);
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);
  init();

  glutDisplayFunc (display); 
  glutReshapeFunc (reshape); 
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialkeyboard);
    glutIdleFunc(moveBullets);
  glutMainLoop();
  return 0;
}
