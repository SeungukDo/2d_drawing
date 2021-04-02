mode.h
	: 일반 모드, 올 패스, 올 페일 모드에 관한 정의가 있다.

objects.h
	: 기본적인 triangle과 rectangle를 정의하였다.
	ojbect들이 움직일땐 이들을 이용한다.
	Triangle을 이용하여 Player, Enemy class를 정의하였고 관련 method들을 추가하였다.
	Enemy들을 담은 vector를 위한 EnemyList class를 정의하였다.
	Rectangle을 이용한 Bullet을 정의하였고 Bullet을 담은 vector를 위한 BulletList를 정의하였다.
	각 class들은 총알에 비행체가 맞거나 체력이 깎여 죽는 상황을 담은 method를 지니고 있다.

main.cpp
	: 본격적으로 화면에 표현하는 파일이다.

키보드
	: 위 화살표 : 플레이어가 위로 이동
	i : 플레이어가 위로 이동
	아래 화살표 : 플레이어가 아래로 이동
	m : 플레이어가 아래로 이동
	왼쪽 화살표 : 플레이어가 왼쪽으로 이동
	j : 플레이어가 왼쪽으로 이동
	오른쪽 화살표 : 플레이어가 오른쪽으로 이동
	k : 플레이어가 오른쪽으로 이동
	스페이스바 : 플레이어의 총알 발사
	c : 올패스 모드
	f : 올페일 모드