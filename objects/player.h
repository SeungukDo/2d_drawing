#ifndef PLAYER_H
#define PLAYER_H
#include "./bullet.h"
#include "./item.h"

class Player : public Object{
private:
    int item;
    int hp;
public:
    Player() {
        hp = 3;
        item = 0;
        position.x = 0.5;
        position.y = 0.15;
    };

    int getHP() { return hp; }

    void decrease_hp() {
        if (mode == ALLPASS);
        else{
            if (mode == ALLFAIL) hp = 0;
            else hp--;
            if (hp == 0) over = 2;
        }
    }

    void increase_item() { if (item <= 2) item++; }

    void shoot() {
        std::vector <BulletType> bullet_types;
        switch (item){
            case 0:
                bullet_types.clear();
                bullet_types.push_back(NORMAL_UP);
                break;
            case 1:
                bullet_types.clear();
                bullet_types.push_back(NORMAL_UPRIGHT);
                bullet_types.push_back(NORMAL_UPLEFT);
                break;
            case 2:
                bullet_types.clear();
                bullet_types.push_back(NORMAL_UP);
                bullet_types.push_back(NORMAL_UPRIGHT);
                bullet_types.push_back(NORMAL_UPLEFT);
                break;
            default:
                bullet_types.clear();
                bullet_types.push_back(NORMAL_UP);
                bullet_types.push_back(NORMAL_UPRIGHT);
                bullet_types.push_back(NORMAL_UPLEFT);
                break;
        }
        player_bullets.shoot(bullet_types, position);
    }
};

extern Player player;

#endif