#pragma once
#include <vector>
#include "gameObject.h"

using namespace std;


#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory {

private:
	vector<gameObject> objectsCollection;
	uint8_t capacity;

	//RenderWindow* window;

	Image windowImage;
	Texture windowTexture;
	Sprite windowSprite;

	RectangleShape background;

	RectangleShape outline;

	RectangleShape InvBody;

	void runStateMachine();

	void drawInv(Vector2f *cameraCenter, RenderWindow *window);

public:
	bool isInventory;
	bool ePressed;
	bool spacePressed;
	bool moveDown;
	bool moveUp;
	bool moveRight;
	bool moveLeft;
	int state;

	Inventory();

	void input(RenderWindow *window);

	Inventory(uint8_t cap);

	bool addItem(gameObject *item);

	bool removeItem(uint8_t index);

	void ShowInventory(View& camera, RenderWindow *window);

	bool DropItem(int cell);

	
};
#endif INVENTORY_H