#ifndef UNITS_H
#define UNITS_H
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
    void move_up(float d) {shape.y += d;};
    void move_down(float d) {shape.y -= d;};
    void move_right(float d) {shape.x += d;};
    void move_left(float d) {shape.x -= d;};

};

class Player: public Unit<triangle> {
  public:
    Player() {
      triangle tmp = {
        0.01, //x
        0.01, //y
        0.15, //width
        0.18, //height
      };
      shape = tmp;
    };
};

class Enemy: public Unit<triangle> {
  public:
    Enemy() {
      triangle tmp = {
        0.01, //x
        0.9, //y
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
