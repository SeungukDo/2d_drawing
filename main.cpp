#include <GL/freeglut.h>
#include <OpenGL/gl.h>
#include <vector>

typedef struct triangle {
  float x;
  float y;
  float width;
  float height;
} triangle;

 typedef struct rectangle {
    float x;
    float y;
    float width;
    float height;
} rectangle;

triangle player;
std::vector <rectangle> player_bullets;

void init(void){
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  player.x = 0.01;
  player.y = 0.01;
  player.width = 0.15;
  player.height = 0.18;
}

void display (void) {
  glClear (GL_COLOR_BUFFER_BIT);

  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_LINE_LOOP);
    glVertex2f(player.x, player.y);
    glVertex2f(player.x + player.width, player.y);
    glVertex2f(player.x + player.width/2, player.y + player.height);
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
  bullet.width = 0.03;
  bullet.height = 0.03;
  bullet.x = player.x + player.width/2 - bullet.width/2;
  bullet.y = player.y + player.height;

  player_bullets.push_back(bullet);
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
    case 'i':
      player.y += 0.005;
      break;
    case 'm':
      player.y -= 0.005;
      break;
    case 'k':
      player.x += 0.005;
      break;
    case 'j':
      player.x -= 0.005;
      break;
    case 32:  //space bar
      shoot();
      break;
  }
  glutPostRedisplay();
}

void specialkeyboard(int key, int x, int y){
  switch (key) {
    case GLUT_KEY_UP:
      player.y += 0.005;
      break;
    case GLUT_KEY_DOWN:
      player.y -= 0.005;
      break;
    case GLUT_KEY_RIGHT:
      player.x += 0.005;
      break;
    case GLUT_KEY_LEFT:
      player.x -= 0.005;
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
