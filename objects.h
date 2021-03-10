#ifndef UNITS_H
#define UNITS_H
#define PLAYER_WIDTH 0.15
#define PLAYER_HEIGHT 0.18
#define BULLET_WIDTH 0.03
#define BULLET_HEIGHT 0.03
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

enum Direction {
  UP,
  DOWN,
  RIGHT,
  LEFT
};

template <typename T> //triangle, rectangle?
class Object {

  protected:
    T shape; //defines shape of the unit. ex) width and height.

  public:
    T* get_shape() {return &shape;}; 
    float move_up(float d) { if (shape.y + d < 1) shape.y += d; return shape.y; }; 
    float move_down(float d) { if (shape.y - d > 0) shape.y -= d; return shape.y; };
    float move_right(float d) { if (shape.x + d < 1) shape.x += d; return shape.x; };
    float move_left(float d) { if (shape.x - d > 0) shape.x -= d; return shape.x; };
};

class Player: public Object<triangle> {
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

class Enemy: public Object<triangle> {
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

class Bullet: public Object<rectangle> {
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

extern Player player;
extern Enemy enemy;

class BulletList {
  private:
    std::vector <Bullet> bullet_list;

  public:
    void shoot() {
      triangle player_shape = *player.get_shape();

      float x = player_shape.x + player_shape.width/2 - BULLET_WIDTH/2;
      float y = player_shape.y + player_shape.height;

      Bullet bullet = Bullet(x, y);

      bullet_list.push_back(bullet);
    }

    void move_bullets(Direction d) {
      for (int i = 0; i < bullet_list.size(); i++) {
        if (d == UP) bullet_list[i].move_up(0.01);
        else if (d == DOWN) bullet_list[i].move_down(0.01);
      }
    }

    std::vector <rectangle> get_bullet_shapes() {
      std::vector <rectangle> shapes;
      for (int i = 0; i < bullet_list.size(); i++) {
        shapes.push_back(*bullet_list[i].get_shape());
      }
      return shapes;
    }
};

extern BulletList player_bullets;
extern BulletList enemy_bullets;
#endif