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
    int getHP() { return hp; }
    void hit() { hp--; }

  private:
    int hp = 3; // health point of player
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
    int getHP() { return hp; }
    int getRemain() { return remain; }
    void new_hp() { hp = 6 - remain; }
    void hit() { 
        hp--;
        if (hp == 0) {
            remain--;
            new_hp();
        }
    }
    bool getDir() { return right; }
    void changeDir() { right = !right; }

  private:
    int remain = 5; // remain number of enemies
    int hp = 1; // health point of enemy
    bool right = true;
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
