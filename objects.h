#ifndef UNITS_H
#define UNITS_H
#define PLAYER_WIDTH 0.15
#define PLAYER_HEIGHT 0.18
#define BULLET_WIDTH 0.03
#define BULLET_HEIGHT 0.03
#include <vector>
#include "mode.h"

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
    T* get_shape() { return &shape; };
    float move_up(float d) { if (shape.y + d < 1) shape.y += d; return shape.y; };
    float move_down(float d) { if (shape.y - d > 0) shape.y -= d; return shape.y; };
    float move_right(float d) { if (shape.x + d < 1) shape.x += d; return shape.x; };
    float move_left(float d) { if (shape.x - d > 0) shape.x -= d; return shape.x; };
};

class Player : public Object<triangle> {
public:
    Player() {
        triangle tmp = {
          0.5 - PLAYER_WIDTH / 2, //x
          0.02, //y
          PLAYER_WIDTH, //width
          PLAYER_HEIGHT, //height
        };
        shape = tmp;
    };
    int getHP() { return hp; }
    void hit() { 
        if (mode == ALLFAIL) hp = 0; 
        else if (mode == ALLPASS) ;
        else hp--;
}

private:
    int hp = 3; // health point of player
};

class Enemy : public Object<triangle> {
public:
    Enemy(int hp_) {
        triangle tmp = {
          0.5 - PLAYER_WIDTH / 2, //x
          0.7, //y
          0.15, //width
          -0.18, //height
        };
        shape = tmp;
        hp = hp_;
    };
    int getHP() { return hp; }
    bool hit() {
        if (mode == ALLPASS) hp = 0;
        else hp--;
        if (hp <= 0) return false;
        else return true;
    }

private:
    int hp; // health point of enemy
};

class EnemyList {
private:
    std::vector <Enemy> enemy_list;
    int index;
    int total_num;

public:
    EnemyList() {
        index = 0;
        total_num = 5;
        for (int i = 0; i < total_num; i++) {
            enemy_list.push_back(Enemy(i + 1));
        }
    }

    Enemy getEnemy() { return enemy_list[index]; }

    int getIndex() { return index; }

    void hit() {
        if (enemy_list[index].hit() == false) {
            index++;
        }

        if (index == total_num) {
            // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@Game Win
        }
    }
};

class Bullet : public Object<rectangle> {
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
extern EnemyList enemy_list;

class BulletList {
private:
    std::vector <Bullet> bullet_list;

public:
    void shoot(bool isPlayer) {
        triangle shape;

        if (isPlayer)
            shape = *player.get_shape();
        else
            shape = *enemy_list.getEnemy().get_shape();

        float x = shape.x + shape.width / 2 - BULLET_WIDTH / 2;
        float y = shape.y + shape.height;

        Bullet bullet = Bullet(x, y);

        if (isPlayer == false || mode != ALLFAIL)
            bullet_list.push_back(bullet);
    }

    void move_bullets(Direction d) {
        for (int i = 0; i < bullet_list.size(); i++) {
            if (d == UP) {
                bullet_list[i].move_up(0.01); 

                triangle enemy_shape = *enemy_list.getEnemy().get_shape();
                rectangle bullet_shape = *bullet_list[i].get_shape();
                if ((bullet_shape.x < enemy_shape.x + enemy_shape.width) &&     // hit box... need to be replaced
                    (bullet_shape.x > enemy_shape.x) &&
                    (bullet_shape.y < enemy_shape.y) &&
                    (bullet_shape.y > enemy_shape.y + enemy_shape.height)) {
                    enemy_list.hit();
                    bullet_list.erase(bullet_list.begin() + i);
                }
            }
            else if (d == DOWN) { 
                bullet_list[i].move_down(0.01); 

                rectangle bullet_shape = *bullet_list[i].get_shape();
                triangle player_shape = *player.get_shape();
                if ((bullet_shape.x < player_shape.x + player_shape.width) &&     // hit box... need to be replaced
                    (bullet_shape.x > player_shape.x) &&
                    (bullet_shape.y > player_shape.y) &&
                    (bullet_shape.y < player_shape.y + player_shape.height)) {
                    player.hit();
                    bullet_list.erase(bullet_list.begin() + i);
                }
            }
        }
    }

    std::vector <rectangle> get_bullet_shapes() {
        std::vector <rectangle> shapes;
        for (int i = 0; i < bullet_list.size(); i++) {
            shapes.push_back(*bullet_list[i].get_shape());
        }
        return shapes;
    }

    bool isHit(rectangle bullet_shape, triangle try_shape) {

    }
};

extern BulletList player_bullets;
extern BulletList enemy_bullets;
#endif