#ifndef UNITS_H
#define UNITS_H
#define PLAYER_WIDTH 0.15
#define PLAYER_HEIGHT 0.15
#define BULLET_WIDTH 0.03
#define BULLET_HEIGHT 0.03
#include <vector>
#include "mode.h"
#include <random>

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

extern int over;

template <typename T> //triangle, rectangle?
class Object {

protected:
    T shape; //defines shape of the unit. ex) width and height.

public:
    T* get_shape() { return &shape; };
    float move_up(float d) { if (shape.y + d < 0.98) shape.y += d; return shape.y; };
    float move_down(float d) { if (shape.y - d > 0) shape.y -= d; return shape.y; };
    float move_right(float d) { if (shape.x + d + PLAYER_WIDTH < 1) shape.x += d; return shape.x; };
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
        else if (mode == ALLPASS);
        else hp--;

        if (hp == 0) over = 2;
    }

private:
    int hp = 3; // health point of player
};

class Enemy : public Object<triangle> {
public:
    Enemy(int hp_) {
        triangle tmp = {
          0.5 - PLAYER_WIDTH / 2, //x
          0.98, //y
          PLAYER_WIDTH, //width
          -PLAYER_HEIGHT, //height
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
    void move(int idx) {
        if (idx == 0) {
            if (shape.x > 0.8) isRight = false;
            else if (shape.x < 0.2 - PLAYER_WIDTH) isRight = true;
        }

        if (isRight) move_right(0.001);
        else move_left(0.001);
    }
    void move_2(int idx) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 999);
        int k = dis(gen);

        switch (idx) {
        case 1:
            if (k % 2 == 0) isRight = false;
            else if (k % 2 == 1) isRight = true;
            break;
        case 2:
            if (k % 3 == 1) isRight = false;
            else if (k % 3 == 0 || k % 3 == 2) isRight = true;
            break;
        case 3:
            if (k % 3 == 0 || k % 3 == 2) isRight = false;
            else if (k % 3 == 1) isRight = true;
            break;
        case 4:
            if (k % 2 == 0) isRight = true;
            else if (k % 2 == 1) isRight = false;
            break;
        }
    }

private:
    int hp; // health point of enemy
    bool isRight = true;
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
    void move() { enemy_list[index].move(index); }
    void move_2() { enemy_list[index].move_2(index); }
    void hit() {
        if (enemy_list[index].hit() == false) {
            if (index + 1 == total_num) {
                over = 1;
                return;
            }
            index++;
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
        float x, y;

        if (isPlayer) {
            shape = *player.get_shape();
            x = shape.x + PLAYER_WIDTH / 2 - BULLET_WIDTH / 2;
            y = shape.y + PLAYER_HEIGHT;
        }
        else {
            shape = *enemy_list.getEnemy().get_shape();
            x = shape.x + PLAYER_WIDTH / 2 + BULLET_WIDTH / 2;
            y = shape.y - PLAYER_HEIGHT;
        }

        if (isPlayer == false || mode != ALLFAIL)
            bullet_list.push_back(Bullet(x, y));
    }

    void move_bullets(Direction d) {
        for (int i = 0; i < bullet_list.size(); i++) {
            if (d == UP) {
                bullet_list[i].move_up(0.01);
                if (bullet_list[i].get_shape()->y + 0.01 >= 0.98) {
                    bullet_list.erase(bullet_list.begin() + i);
                    return;
                }

                triangle enemy_shape = *enemy_list.getEnemy().get_shape();
                rectangle bullet_shape = *bullet_list[i].get_shape();

                if (isHit(bullet_shape.x, bullet_shape.y, enemy_shape.x, enemy_shape.y, true)) {
                    enemy_list.hit();
                    bullet_list.erase(bullet_list.begin() + i);
                }
            }
            else if (d == DOWN) {
                bullet_list[i].move_down(0.01);
                if (bullet_list[i].get_shape()->y - 0.01 <= 0) {
                    bullet_list.erase(bullet_list.begin() + i);
                    return;
                }
                rectangle bullet_shape = *bullet_list[i].get_shape();
                triangle player_shape = *player.get_shape();

                if (isHit(bullet_shape.x, bullet_shape.y, player_shape.x, player_shape.y, false)) {
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

    bool isHit(float bx, float by, float tx, float ty, bool isPlayer) {
        int i = -1;
        if (isPlayer) i = 1;

        return (((bx + i * BULLET_WIDTH / 2 > tx + PLAYER_WIDTH / 10) &&
            (bx + i * BULLET_WIDTH / 2 < tx + 9 * PLAYER_WIDTH / 10) &&
            (i * by + BULLET_HEIGHT / 2 < i * ty) &&
            (i * by + BULLET_HEIGHT / 2 > i * ty - PLAYER_HEIGHT / 10)) ||
            ((bx + i * BULLET_WIDTH / 2 > tx + 2 * PLAYER_WIDTH / 5) &&
                (bx + i * BULLET_WIDTH / 2 < tx + 3 * PLAYER_WIDTH / 5) &&
                (i * by + BULLET_HEIGHT / 2 < i * ty - PLAYER_HEIGHT / 10) &&
                (i * by + BULLET_HEIGHT / 2 > i * ty - 4 * PLAYER_HEIGHT / 5)));
    }
};

extern BulletList player_bullets;
extern BulletList enemy_bullets;
#endif