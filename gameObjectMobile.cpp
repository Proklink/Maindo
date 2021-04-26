#include "gameObjectMobile.h"



using namespace std;

gameObjectMobile::gameObjectMobile(Vector2f& size, Vector2f& position, ObjectType t, Texture* texture, float speed)
	: gameObject(size, position, t, texture) {

	currentSight = Vector2f(1, 0);

	body.setOutlineThickness(0);

	isMoving = false;

	leftPressed = false;
	rightPressed = false;
	upPressed = false;
	downPressed = false;

	this->speed = speed;
}

gameObjectMobile::gameObjectMobile() {

	currentDirection = Vector2f(1, 0);

	body.setOutlineThickness(0);

	isMoving = false;

	leftPressed = false;
	rightPressed = false;
	upPressed = false;
	downPressed = false;
}

void gameObjectMobile::stopALL() {
	 leftPressed = false;
	 rightPressed = false;
	 upPressed = false;
	 downPressed = false;
}

// Для движения 
void gameObjectMobile::moveLeft() {
	leftPressed = true;
}

void gameObjectMobile::moveRight() {
	rightPressed = true;
}

void gameObjectMobile::moveUp() {
	upPressed = true;
}

void gameObjectMobile::moveDown() {
	downPressed = true;
}

// Прекращение движения
void gameObjectMobile::stopLeft() {
	leftPressed = false;
}

void gameObjectMobile::stopRight() {
	rightPressed = false;
}

void gameObjectMobile::stopUp() {
	upPressed = false;
}

void gameObjectMobile::stopDown() {
	downPressed = false;
}

//возвращает информацию о направлении движения
Vector2f& gameObjectMobile::getDirection() {
	return currentDirection;
}

Vector2f gameObjectMobile::getMovingButtons() {
	float x = 0, y = 0;

	if (upPressed)
		y--;
	if (downPressed)
		y++;
	if (rightPressed)
		x++;
	if (leftPressed)
		x--;

	return Vector2f(x, y);
}

void gameObjectMobile::setCurrentSight(Vector2f& cs) {
	currentSight = cs;
}

Vector2f gameObjectMobile::getCurrentSight() {
	return currentSight;
}

//метод для обновления полей для каждой интерации игрового цикла
//с учетом времени
void gameObjectMobile::update(float *elapsedTime) {
	float x = 0, y = 0;
	
	if (upPressed)
		y--;
	if (downPressed)
		y++;
	if (rightPressed)
		x++;
	if (leftPressed)
		x--;

	currentDirection.x = x;
	currentDirection.y = y;
	
	if (currentDirection != Vector2f(0, 0))
	{
		currentSight = currentDirection;
	}

	if (leftPressed) {
		body.move(-speed * *elapsedTime, 0);

	}
	if (rightPressed) {
		body.move(speed * *elapsedTime, 0);

	}

	if (upPressed) {
		body.move(0, -speed * *elapsedTime);

	}

	if (downPressed) {
		body.move(0, speed * *elapsedTime);

	}
}

void gameObjectMobile::shiftPosition(float x, float y) {
	body.move(x, y);
}

//bool gameObjectMobile::collisionCheck(RectangleShape *ObjectInMap, float *time) {
//
//	float step = speed * (*time);
//	RectangleShape HeroInNextFrame(body.getSize());
//	HeroInNextFrame.setPosition(body.getPosition());
//
//
//	if (leftPressed) {
//		HeroInNextFrame.move(-step, 0);
//	}
//
//	if (rightPressed) {
//		HeroInNextFrame.move(step, 0);
//	}
//
//	if (upPressed) {
//		HeroInNextFrame.move(0, -step);
//	}
//
//	if (downPressed) {
//		HeroInNextFrame.move(0, step);
//	}
//
//
//	float  ActorRightPoint = body.getGlobalBounds().left + body.getGlobalBounds().width;
//	float  ActorBottomPoint = body.getGlobalBounds().top + body.getGlobalBounds().height;
//	float  ActortLeftPoint = body.getGlobalBounds().left;
//	float  ActorTopPoint = body.getGlobalBounds().top;
//
//	float  ObjectRightPoint = ObjectInMap->getGlobalBounds().left + ObjectInMap->getGlobalBounds().width;
//	float  ObjectBottomPoint = ObjectInMap->getGlobalBounds().top + ObjectInMap->getGlobalBounds().height;
//	float  ObjectLeftPoint = ObjectInMap->getGlobalBounds().left;
//	float  ObjectTopPoint = ObjectInMap->getGlobalBounds().top;
//
//
//	if (HeroInNextFrame.getGlobalBounds().intersects(ObjectInMap->getGlobalBounds())) {
//		if (this->type == ObjectType::projectiletype)
//			return true;
//
//		if (ActortLeftPoint > ObjectRightPoint) {
//			if (leftPressed) {
//				this->stopLeft();
//			}
//		}
//
//		if (ActorRightPoint < ObjectLeftPoint) {
//			if (rightPressed) {
//				this->stopRight();
//			}
//		}
//
//		if (ActorTopPoint > ObjectBottomPoint) {
//			if (upPressed) {
//				this->stopUp();
//			}
//		}
//
//		if (ActorBottomPoint < ObjectTopPoint) {
//			if (downPressed) {
//				this->stopDown();
//			}
//		}
//
//
//	}
//}

