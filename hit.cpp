#include "hit.h"

void check_hit() {
  std::vector<Position> player_bullet_positions = player_bullets.get_bullet_positions();
  std::vector<Position> enemy_bullet_positions = enemy_bullets.get_bullet_positions();
  Position player_position = player.get_position();
  Position enemy_position = enemy_list.getEnemy().get_position();

  bool player_hit_flag = false;
  bool enemy_hit_flag = false;

  for (int i = 0; i < player_bullets.get_size(); i++){
    if (is_in_hitbox(player_bullet_positions[i], enemy_position, DOWN) == true){
      enemy_hit_flag = true;
      player_bullets.erase_bullet(i);
      break;
    }
  }

  for (int i = 0; i < enemy_bullets.get_size(); i++){
    if (is_in_hitbox(enemy_bullet_positions[i], player_position, UP) == true)
      player_hit_flag = true;
      enemy_bullets.erase_bullet(i);
      break;
  }

  if (player_hit_flag == true) {
    player.decrease_hp();
  }

  if (enemy_hit_flag == true) {
    enemy_list.decrease_hp();
  }

}

bool is_in_hitbox(Position bullet_position, Position plane_position, Direction plane_direction) {
  
  bool result = false;

  float bx = bullet_position.x;
  float by = bullet_position.y;

  float tx = plane_position.x;
  float ty = plane_position.y;

  if (plane_direction == UP &&
      bx - BULLET_RADIUS <= tx + 2.8 * 0.05 && bx + BULLET_RADIUS >= tx - 2.8 * 0.05 && 
      by - BULLET_RADIUS <= ty && by + BULLET_RADIUS >= ty - 2 * 0.05)
      result = true;
  
  else if (plane_direction == DOWN &&
      bx - BULLET_RADIUS <= tx + 2.8 * 0.05 && bx + BULLET_RADIUS >= tx - 2.8 * 0.05 && 
      by + BULLET_RADIUS >= ty && by - BULLET_RADIUS >= ty + 2 * 0.05)
      result = true;
  
  return result;

}