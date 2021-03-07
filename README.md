# 2d_drawing
postech graphics assignment#1

## 1. Data Structure
class를 이용해 게임 내 유닛들을 나타내었다. 
이때 각각의 유닛을 나타내는 class들은 모두 하나의 클래스(Unit)으로 부터 inherit한 class이다.

### Unit
#### 특성
- ***shape***: 해당 unit의 모양, 크기와 위치를 나타낸다. shape의 data type이 모양(사각형, 삼각형)을 결정하며, shape이 저장하고 있는 값(x, y좌표, width, height)이 위치와 크기를 나타낸다. 
#### Interface
- ***get_shape***: 해당 unit의 shape를 가리키는 포인터를 return
- ***move_up***: float형 값을 인자로 받아, 그 크기만큼 unit을 위로 이동 (move_down, move_right, move_left는 방향을 제외한 효과는 같다.)

### Player
#### 특성
- ***hp*** (구현 예정)
#### Interface

### Enemy
#### 특성
- ***hp*** (구현 예정)
#### Interface
- ***hp*** (구현 예정)

### Bullet
#### 특성
#### Interface
