# 2d_drawing
postech graphics assignment#1

## 1. Introduction

## 2. 실행 방법

## 2. Data Structure
class를 이용해 게임 내 물체들을 나타내었다. 
이때 각각의 물체를 나타내는 class들은 모두 하나의 클래스(Object)으로 부터 inherit한 class이다.

### Object
#### Features
- ***shape***: 해당 object의 모양, 크기와 위치를 나타낸다. shape의 data type이 모양(사각형, 삼각형)을 결정하며, shape이 저장하고 있는 값(x, y좌표, width, height)이 위치와 크기를 나타낸다. 
#### Interface
- ***get_shape***: 해당 unit의 shape를 가리키는 포인터를 return
- ***move_up***: float형 값을 인자로 받아, 그 크기만큼 unit을 위로 이동한 후, 이동 후 위치를 return한다. 만약 이동 예정 위치가 경계를 벗어날 경우, 그 작업을 시행하지 않는다. (move_down, move_right, move_left는 방향을 제외한 효과는 같다.)

### Player
#### Features
- ***hp***: 플레이어의 체력을 나타낸다. 생성 시, 3으로 초기화된다.
#### Interface
- ***getHP***: 플레이어의 체력을 return.
- ***hit***: 플레이어가 총알에 맞았을 경우 실행된다. 게임모드(NORMAL, ALLPASS, ALLFAIL)에 따라 다른 효과가 실행된다. 
  - NORMAL: hp를 1 감소시킨다.
  - ALLPASS: 아무런 동작을 실행하지 않는다.
  - ALLFAIL: hp를 0으로 설정한다. 

### Enemy
#### Features
- ***hp***: 적의 체력을 나타낸다.
#### Interface
- ***getHP***: 적의 체력을 return.
- ***hit***: 적이 총알에 맞았을 경우 실행된다. 게임모드(NORMAL, ALLPASS, ALLFAIL)에 따라 다른 효과가 실행된다. 
  - NORMAL: hp를 1 감소시킨다.
  - ALLPASS: hp를 1로 설정한다.
  - ALLFAIL: hp를 1 감소시킨다.
   
  해당 효과 실행 후, 체력이 0 이하가 되었을 경우 false 그렇지 않다면 true를 return 한다.
  
### EnemyList
#### Features
- ***enemy_list***: Enemy object들의 vector
- ***index***: 현재 Enemy의 index
- ***total_num***: Enemy들의 총 개수
#### Interface
- ***getEnemy***: 현재 index가 가리키는 Enemy를 return.
- ***getIndex***: 현재 index를 return.
- ***hit***: 현재 index가 가리키는 Enemy의 hit()함수를 호출하여 hp를 감소시킨다. 만약 그 enemy의 체력이 0이 되었을 경우(false를 return) index를 1 추가시킨다. index가 total_num과 같아졌을 경우 ***구현 예정***

### Bullet
#### Features
#### Interface

### BulletList
#### Features
- ***bullet_list***: bullet들의 vector
#### Interface
- ***shoot***: bullet_list에 bullet object를 하나 만들어서 추가. 플레이어의 bullet인지에 대한 여부를 인자로 받아, player 혹은 enemy의 위치를 받아온다. 이를 바탕으로 bullet object를 생성하여 bullet_list에 추가한다.
- ***move_bullets***: direction을 인자로 받아, 해당하는 방향으로 bullet_list의 모든 bullet을 이동시킨다. 만약 적 혹은 플레이어의 boundary 안에 총알이 위치할 경우, enemy_list.hit 혹은 player.hit을 호출한다.
- ***get_bullet_shapes***: 모든 bullet의 shape를 vector에 저장한 후, return한다.
