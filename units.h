#ifndef UNITS_H
#define UNITS_H
#define PLAYER_WIDTH 0.15
#define PLAYER_HEIGHT 0.18
#define BULLET_WIDTH 0.03
#define BULLET_HEIGHT 0.03

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

template <typename T> //triangle, rectangle?
class Unit {

  protected:
    T shape; //defines shape of the unit. ex) width and height.

  public:
    T* get_shape() {return &shape;}; 
    void move_up(float d) { if (shape.y + d < 1 - PLAYER_HEIGHT) shape.y += d; };
    void move_down(float d) { if (shape.y - d > 0) shape.y -= d; };
    void move_right(float d) { if (shape.x + d < 1 - PLAYER_HEIGHT) shape.x += d; };
    void move_left(float d) { if (shape.x - d > 0) shape.x -= d; };
};

class Player: public Unit<triangle> {
  public:
    Player() {
      triangle tmp = {
        0.5 - PLAYER_WIDTH/2, //x
        0.02, //y
        PLAYER_WIDTH, //width
        PLAYER_HEIGHT, //height
      };
      shape = tmp;
    };
};

class Enemy: public Unit<triangle> {
  public:
    Enemy() {
      triangle tmp = {
        0.5 - PLAYER_WIDTH/2, //x
        0.7, //y
        0.15, //width
        0.18, //height
      };
      shape = tmp;
    };
};

class Bullet: public Unit<rectangle> {
  public:
    Bullet(float _x, float _y) {
      rectangle tmp = {
        _x, //x
        _y, //y
        BULLET_WIDTH, //width
        BULLET_HEIGHT, //height
      };
      shape = tmp;
    };
};
#endif
