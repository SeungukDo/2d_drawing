#ifndef UNITS_H
#define UNITS_H

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
    int hp; //구현바람

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

      hp = 3;
    };
};

#endif
