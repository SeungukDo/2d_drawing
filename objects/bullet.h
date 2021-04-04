#ifndef BULLET_H
#define BULLET_H
#include "./object.h"

enum BulletType {
    NORMAL_UP,
    NORMAL_DOWN,
    NORMAL_RIGHT,
    NORMAL_LEFT,
    NORMAL_UPRIGHT,
    NORMAL_UPRIGHT15,
    NORMAL_UPLEFT,
    NORMAL_UPLEFT15,
    NORMAL_DOWNRIGHT,
    NORMAL_DOWNRIGHT15,
    NORMAL_DOWNLEFT,
    NORMAL_DOWNLEFT15,
};

class Bullet : public Object{
private:
    BulletType bullet_type;
public:
    Bullet(Position _position, BulletType _bullet_type) {
        position = _position;
        bullet_type = _bullet_type;
    };

    BulletType get_bullet_type() {
        return bullet_type;
    }
};

class BulletList {
private:
    std::vector <Bullet> bullet_list;
    Owner owner;

public:
    BulletList(Owner _owner) {owner = _owner;}

    int get_size() { return bullet_list.size(); }
    Bullet get_bullet(int i) { return bullet_list[i]; }
    void erase_bullet(int i) { bullet_list.erase(bullet_list.begin() + i);}
    void shoot(std::vector<BulletType> bullet_types, Position position) {
        for (int i = 0; i < bullet_types.size(); i++) {
            bullet_list.push_back(Bullet(position, bullet_types[i]));
        }
    }

    void move_bullets() {
        for (int i = 0; i < bullet_list.size(); i++) {
            BulletType d = bullet_list[i].get_bullet_type();

            switch (d){
                case NORMAL_UP:
                    bullet_list[i].move_up(BULLET_SPEED);
                    if (bullet_list[i].get_position().y + BULLET_SPEED >= 0.98) {
                        bullet_list.erase(bullet_list.begin() + i);
                        return;
                    }
                    break;

                case NORMAL_DOWN:
                    bullet_list[i].move_down(BULLET_SPEED);
                    if (bullet_list[i].get_position().y - BULLET_SPEED <= 0) {
                        bullet_list.erase(bullet_list.begin() + i);
                        return;
                    }
                    break;

                case NORMAL_UPRIGHT:
                    bullet_list[i].move_up(BULLET_SPEED * cos(45 * (PI/180)));
                    bullet_list[i].move_right(BULLET_SPEED * cos(45 * (PI/180)));
                    if (bullet_list[i].get_position().y + BULLET_SPEED >= 0.98) {
                        bullet_list.erase(bullet_list.begin() + i);
                        return;
                    }
                    else if (bullet_list[i].get_position().x + BULLET_SPEED >= 0.98) {
                        bullet_list.erase(bullet_list.begin() + i);
                        return;
                    }
                    break;

                case NORMAL_UPRIGHT15:
                    bullet_list[i].move_up(BULLET_SPEED * cos(15 * (PI/180)));
                    bullet_list[i].move_right(BULLET_SPEED * sin(15 * (PI/180)));
                    if (bullet_list[i].get_position().y + BULLET_SPEED >= 0.98) {
                        bullet_list.erase(bullet_list.begin() + i);
                        return;
                    }
                    else if (bullet_list[i].get_position().x + BULLET_SPEED >= 0.98) {
                        bullet_list.erase(bullet_list.begin() + i);
                        return;
                    }
                    break;

                case NORMAL_UPLEFT:
                    bullet_list[i].move_up(BULLET_SPEED * cos(45 * (PI/180)));
                    bullet_list[i].move_left(BULLET_SPEED * cos(45 * (PI/180)));
                    if (bullet_list[i].get_position().y + BULLET_SPEED >= 0.98) {
                        bullet_list.erase(bullet_list.begin() + i);
                        return;
                    }
                    else if (bullet_list[i].get_position().x - BULLET_SPEED <= 0.0) {
                        bullet_list.erase(bullet_list.begin() + i);
                        return;
                    }
                    break;

                case NORMAL_UPLEFT15:
                    bullet_list[i].move_up(BULLET_SPEED * cos(15 * (PI/180)));
                    bullet_list[i].move_left(BULLET_SPEED * sin(15 * (PI/180)));
                    if (bullet_list[i].get_position().y + BULLET_SPEED >= 0.98) {
                        bullet_list.erase(bullet_list.begin() + i);
                        return;
                    }
                    else if (bullet_list[i].get_position().x - BULLET_SPEED <= 0.0) {
                        bullet_list.erase(bullet_list.begin() + i);
                        return;
                    }
                    break;
                
                case NORMAL_DOWNRIGHT:
                    bullet_list[i].move_down(BULLET_SPEED * cos(45 * (PI/180)));
                    bullet_list[i].move_right(BULLET_SPEED * cos(45 * (PI/180)));
                    if (bullet_list[i].get_position().y - BULLET_SPEED <= 0.0) {
                        bullet_list.erase(bullet_list.begin() + i);
                        return;
                    }
                    else if (bullet_list[i].get_position().x + BULLET_SPEED >= 0.98) {
                        bullet_list.erase(bullet_list.begin() + i);
                        return;
                    }
                    break;

                case NORMAL_DOWNRIGHT15:
                    bullet_list[i].move_down(BULLET_SPEED * cos(15 * (PI/180)));
                    bullet_list[i].move_right(BULLET_SPEED * sin(15 * (PI/180)));
                    if (bullet_list[i].get_position().y - BULLET_SPEED <= 0.0) {
                        bullet_list.erase(bullet_list.begin() + i);
                        return;
                    }
                    else if (bullet_list[i].get_position().x + BULLET_SPEED >= 0.98) {
                        bullet_list.erase(bullet_list.begin() + i);
                        return;
                    }
                    break;
                
                case NORMAL_DOWNLEFT:
                    bullet_list[i].move_down(BULLET_SPEED * cos(45 * (PI/180)));
                    bullet_list[i].move_left(BULLET_SPEED * cos(45 * (PI/180)));
                    if (bullet_list[i].get_position().y - BULLET_SPEED <= 0.0) {
                        bullet_list.erase(bullet_list.begin() + i);
                        return;
                    }
                    else if (bullet_list[i].get_position().x + BULLET_SPEED <= 0.0) {
                        bullet_list.erase(bullet_list.begin() + i);
                        return;
                    }
                    break;
                
                case NORMAL_DOWNLEFT15:
                    bullet_list[i].move_down(BULLET_SPEED * cos(15 * (PI/180)));
                    bullet_list[i].move_left(BULLET_SPEED * sin(15 * (PI/180)));
                    if (bullet_list[i].get_position().y - BULLET_SPEED <= 0.0) {
                        bullet_list.erase(bullet_list.begin() + i);
                        return;
                    }
                    else if (bullet_list[i].get_position().x + BULLET_SPEED <= 0.0) {
                        bullet_list.erase(bullet_list.begin() + i);
                        return;
                    }
                    break;

                default:
                    break;
            }
            Position bullet_position = bullet_list[i].get_position();
        }
    }

    std::vector <Position> get_bullet_positions() {
        std::vector <Position> positions;
        for (int i = 0; i < bullet_list.size(); i++) {
            positions.push_back(bullet_list[i].get_position());
        }
        return positions;
    }
};

extern BulletList player_bullets;
extern BulletList enemy_bullets;

bool isHit(float bx, float by, float tx, float ty, Owner owner) {
        int i = -1;
        if (owner == PLAYER) i = 1;

        return (((bx + i * BULLET_RADIUS / 2 > tx + PLAYER_WIDTH / 10) &&
            (bx + i * BULLET_RADIUS / 2 < tx + 9 * PLAYER_WIDTH / 10) &&
            (i * by + BULLET_RADIUS / 2 < i * ty) &&
            (i * by + BULLET_RADIUS / 2 > i * ty - PLAYER_HEIGHT / 10)) ||
            ((bx + i * BULLET_RADIUS / 2 > tx + 2 * PLAYER_WIDTH / 5) &&
                (bx + i * BULLET_RADIUS / 2 < tx + 3 * PLAYER_WIDTH / 5) &&
                (i * by + BULLET_RADIUS / 2 < i * ty - PLAYER_HEIGHT / 10) &&
                (i * by + BULLET_RADIUS / 2 > i * ty - 4 * PLAYER_HEIGHT / 5)));
}

#endif