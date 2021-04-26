#pragma once
#include "gameObject.h"

using namespace std;

#ifndef GAMEOBJECTMOBILE_H
#define GAMEOBJECTMOBILE_H
//класс передвигащихс¤ по карте сущностей (в будущем - абстрактный)
class gameObjectMobile : public gameObject {
protected:
	//флаги дл¤ передвижени¤
	bool leftPressed;
	bool rightPressed;
	bool upPressed;
	bool downPressed;

	float speed;

	bool isMoving;

	Vector2f currentDirection;
	Vector2f currentSight;
public:

	gameObjectMobile(Vector2f& size, Vector2f& position, ObjectType t, Texture* texture, float speed);

	gameObjectMobile();

	// ?л¤ движени¤ 
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	// ѕрекращение движени¤
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

	void stopALL();

	void shiftPosition(float x, float y);

	//возвращает информацию о направлении движени¤
	Vector2f& getDirection();

	Vector2f getMovingButtons();

	//метод дл¤ обновлени¤ полей дл¤ каждой интерации игрового цикла
	//с учетом времени
	void update(float *elapsedTime);

	//метод дл¤ обновлени¤ полей дл¤ каждой интерации игрового цикла
	//без учета времени
	void update();

	bool collisionCheck(RectangleShape *mapBounds, float *time);

	void setCurrentSight(Vector2f& cs);

	Vector2f getCurrentSight();
};

#endif GAMEOBJECTMOBILE_H