#include <GL/freeglut.h>
#include <OpenGL/gl.h>
#include <vector>
#include "objects.h"

Player player = Player();
Enemy enemy = Enemy();
BulletList player_bullets;
BulletList enemy_bullets;

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
  triangle enemy_shape = *enemy.get_shape();

  //player
  glBegin(GL_LINE_LOOP);   
    glVertex2f(player_shape.x, player_shape.y);
    glVertex2f(player_shape.x + player_shape.width, player_shape.y);
    glVertex2f(player_shape.x + player_shape.width/2, player_shape.y + player_shape.height);
  glEnd();

  //enemy
  glBegin(GL_LINE_LOOP);  
    glVertex2f(enemy_shape.x, enemy_shape.y);
    glVertex2f(enemy_shape.x + enemy_shape.width, enemy_shape.y);
    glVertex2f(enemy_shape.x + enemy_shape.width/2, enemy_shape.y - enemy_shape.height);
  glEnd();

  //player bullet
  std::vector <rectangle> player_bullet_shapes = player_bullets.get_bullet_shapes();
  for(int i = 0; i < player_bullet_shapes.size(); i++){ 
    rectangle bullet_shape = player_bullet_shapes[i];
    glBegin(GL_LINE_LOOP);
      glVertex2f(bullet_shape.x, bullet_shape.y);
      glVertex2f(bullet_shape.x + bullet_shape.width, bullet_shape.y);
      glVertex2f(bullet_shape.x + bullet_shape.width, bullet_shape.y + bullet_shape.height);
      glVertex2f(bullet_shape.x, bullet_shape.y + bullet_shape.height);
    glEnd();
  }

  //enemy bullet
  std::vector <rectangle> enemy_bullet_shapes = enemy_bullets.get_bullet_shapes();
  for(int i = 0; i < enemy_bullet_shapes.size(); i++){ 
    rectangle bullet_shape = enemy_bullet_shapes[i];
    glBegin(GL_LINE_LOOP);
      glVertex2f(bullet_shape.x, bullet_shape.y);
      glVertex2f(bullet_shape.x + bullet_shape.width, bullet_shape.y);
      glVertex2f(bullet_shape.x + bullet_shape.width, bullet_shape.y + bullet_shape.height);
      glVertex2f(bullet_shape.x, bullet_shape.y + bullet_shape.height);
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
      player_bullets.shoot();
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

void idle_func() {
  player_bullets.move_bullets(UP);
  enemy_bullets.move_bullets(DOWN);

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
  glutIdleFunc(idle_func);
  glutMainLoop();
  return 0;
}
