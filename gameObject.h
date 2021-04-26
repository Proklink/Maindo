#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


using namespace std;
using namespace sf;

#define WINDOW_SIZE_X 1280
#define WINDOW_SIZE_Y 720
#define CAMERA_SIZE_X WINDOW_SIZE_X / 2
#define CAMERA_SIZE_Y WINDOW_SIZE_Y / 2

//смещение между адресов родительского объекта типа parent_type и адресом его поля member
#define offsetof(parent_type, member) ((size_t)&((parent_type *)0)->member)

#define container_of(ptr, type, member) ({
	void *_mptr = (void *)(ptr);
	((type *)(_mptr - offsetof(type, member)));	})


enum ObjectType {

	humantype = 0,
	robottype,
	weapontype,
	itemtype,
	projectiletype,
	walltype,
	msgtype, 
	flowertype
};

class gameObject {
protected:

	ObjectType type;
	RectangleShape body;
	RectangleShape lowSide;

public:
	gameObject();

	gameObject(Vector2f& size, Vector2f& position, ObjectType t, Texture* texture = NULL);
	gameObject(RectangleShape& recSh, ObjectType t, Texture* texture = NULL);

	RectangleShape getBody();

	RectangleShape getLowSide();

	Vector2f getCenter();

	ObjectType getType();

	void setColor(Color color);
};