#ifndef PLAYER_H
#define PLAYER_H
#include "./bullet.h"

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

    void hit() {
        if (mode == ALLPASS);
        else {
            Position player_position = get_position();
            for (int i = 0; i < enemy_bullets.get_size(); i++) {
                Position enemy_bullet_position = enemy_bullets.get_bullet(i).get_position();
                if (isHit(enemy_bullet_position.x, enemy_bullet_position.y, player_position.x, player_position.y, ENEMY)) {
                        if (mode == ALLFAIL) hp = 0;
                        else hp--;
                        if (hp == 0) over = 2;
                        enemy_bullets.erase_bullet(i);
                    }
            }
        }        
    }

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
                break;
        }
        player_bullets.shoot(bullet_types, position);
    }
};

extern Player player;

#endif