#ifndef ENEMY_H
#define ENEMY_H
#include "./object.h"
#include "./bullet.h"
#include "./item.h"

class Enemy : public Object{
private:
    int hp; // health point of enemy
    bool isRight;
    int level;

public:
    Enemy(int hp_, int _level = 0) {
        hp = hp_;
        isRight = true;
        level = _level;
        position.x = 0.5f;
        position.y = 0.85f;
    };
    int getHP() { return hp; }
    bool decrease_hp() {
        if (mode == ALLPASS) hp = 0;
        else hp--;
        if (hp <= 0) return false;
        else return true;
    }
    void increase_level() { level++; }
    void move(int idx) {
        if (idx == 0) {
            if (position.x > 0.8) isRight = false;
            else if (position.x < 0.2 - PLAYER_WIDTH) isRight = true;
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
    void shoot() {
        std::vector <BulletType> bullet_types;
        switch (level){
            case 0:
                bullet_types.clear();
                bullet_types.push_back(NORMAL_DOWN);
                break;
            case 1:
                bullet_types.clear();
                bullet_types.push_back(NORMAL_DOWNRIGHT);
                bullet_types.push_back(NORMAL_DOWNLEFT);
                break;
            case 3:
                bullet_types.clear();
                bullet_types.push_back(NORMAL_DOWN);
                bullet_types.push_back(NORMAL_DOWNRIGHT);
                bullet_types.push_back(NORMAL_DOWNLEFT);
                break;
            default:
                bullet_types.clear();
                bullet_types.push_back(NORMAL_DOWN);
                bullet_types.push_back(NORMAL_DOWNRIGHT);
                bullet_types.push_back(NORMAL_DOWNLEFT);
                break;
        }
        enemy_bullets.shoot(bullet_types, position);
    }
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
            enemy_list.push_back(Enemy(i + 1, i));
        }
    }
    Enemy getEnemy() { return enemy_list[index]; }
    int getIndex() { return index; }
    void move() { enemy_list[index].move(index); }
    void move_2() { enemy_list[index].move_2(index); }
    void decrease_hp() {
        if (enemy_list[index].decrease_hp() == false){
            if (index + 1 == total_num) {
                over = 1;
                return;
            }
            item_list.create_item(enemy_list[index].get_position());
            index++;    
        }
    }
};

extern EnemyList enemy_list;
#endif