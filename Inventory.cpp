#include "Inventory.h"


Inventory::Inventory() {
	 ePressed = false;
	 spacePressed = false;
	 isInventory = false;
	 moveDown = false;
	 moveUp = false;
	 moveRight = false;
	 moveLeft = false;
	 state = false;

	 background.setSize(Vector2f(WINDOW_SIZE_X, WINDOW_SIZE_Y));
	 background.setFillColor(Color(100, 100, 100, 150));
	 background.setPosition(0, 0);

	 outline.setSize(Vector2f(105, 80));
	 outline.setOutlineThickness(2);
	 outline.setOutlineColor(Color(0, 0, 255));

	 InvBody.setSize(Vector2f(500, 200));
	 InvBody.setFillColor(Color(100, 100, 100, 150));
}

Inventory::Inventory(uint8_t cap) : Inventory() {
	
	if (cap > 0) {
		//objectsCollection.resize(cap);
		capacity = cap;
	}
	
}


bool Inventory::addItem(gameObject *item) {
	int s = objectsCollection.size();
	if (s < capacity) {

		bool isExist = false;
		for (int i = 0; i < objectsCollection.size(); i++) {
			if (objectsCollection[i].getType() != item->getType()) {
				isExist = true;
				break;
			}

		}
		 
		if (!isExist) {
			objectsCollection.push_back(*item);
			return true;
		}
		else
			return false;
		
	}
	return false;
}

bool Inventory::removeItem(uint8_t index) {
	if (!objectsCollection.empty()) {
		objectsCollection.erase(objectsCollection.begin() + index);

		return 1;
	}
	return 0;
}

void MakeScreenShotLikeBackgr(Vector2f& cameraCenter, RenderWindow *window, Texture *windowTexture, Sprite *windowSprite) {

	Vector2u windowSize = window->getSize();

	windowTexture->create(windowSize.x, windowSize.y);
	windowTexture->update(*window);

	windowSprite->setTexture(*windowTexture);
	windowSprite->setScale(0.5, 0.5);
	windowSprite->setPosition(cameraCenter - Vector2f(CAMERA_SIZE_X / 2, CAMERA_SIZE_Y / 2));

}

void Inventory::input(RenderWindow *window) {

	Event event;
	while (window->pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
				isInventory = false;

			if (event.key.code == Keyboard::E)
				ePressed = true;

			if (event.key.code == Keyboard::Space)
				spacePressed = true;
		}

		if (event.type == Event::Closed) {
			isInventory = false;
			window->close();
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
			moveLeft = true;

		if (Keyboard::isKeyPressed(Keyboard::D))
			moveRight = true;

		if (Keyboard::isKeyPressed(Keyboard::S))
			moveDown = true;

		if (Keyboard::isKeyPressed(Keyboard::W))
			moveUp = true;

		if (event.type == Event::KeyReleased) {
			if (event.key.code == Keyboard::A)
				moveLeft = false;

			if (event.key.code == Keyboard::D)
				moveRight = false;

			if (event.key.code == Keyboard::S)
				moveDown = false;

			if (event.key.code == Keyboard::W)
				moveUp = false;

		}
	}
}

bool Inventory::DropItem(int cell) {
	
	int ret = 0;
	//������� �������� �� ������������ cell
	gameObject *ObjFromInv = &objectsCollection[cell];

	objectsCollection.erase(objectsCollection.begin() + cell);

	

	return ret;

}

void Inventory::runStateMachine() {

	switch (state)
	{
	case 1:
		if (ePressed) {
			ePressed = false;
		
		}
		if (spacePressed) {
			spacePressed = false;
			DropItem(state);

		}
		else if (moveDown) {
			moveDown = false;
			state = 5;
		}
		else if (moveRight) {
			moveRight = false;
			state = 2;
		}
		else if (moveLeft) {
			moveLeft = false;
			state = 4;
		}
		break;

	case 2:
		if (ePressed) {
			ePressed = false;
			
		}
		else if (moveRight) {
			moveRight = false;
			state = 3;
		}
		else if (moveDown) {
			moveDown = false;
			state = 6;
		}
		else if (moveLeft) {
			moveLeft = false;
			state = 1;
		}

		break;

	case 3:
		if (ePressed) {
			ePressed = false;


		}
		else if (moveRight) {
			moveRight = false;
			state = 4;
		}
		else if (moveLeft) {
			moveLeft = false;
			state = 2;
		}
		else if (moveDown) {
			moveDown = false;
			state = 7;
		}
		break;

	case 4:
		if (ePressed) {
			ePressed = false;
			
		}
		else if (moveRight) {
			moveRight = false;
			state = 1;
		}
		else if (moveLeft) {
			moveLeft = false;
			state = 3;
		}
		else if (moveDown) {
			moveDown = false;
			state = 8;
		}
		break;

	case 5:
		if (ePressed) {
			ePressed = false;
		}
		else if (moveLeft) {
			moveLeft = false;
			state = 8;
		}
		else if (moveRight) {
			moveRight = false;
			state = 6;
		}
		else if (moveUp) {
			moveUp = false;
			state = 1;
		}
		break;

	case 6:
		if (ePressed) {
			ePressed = false;
			
		}
		else if (moveLeft) {
			moveLeft = false;
			state = 5;
		}
		else if (moveRight) {
			moveRight = false;
			state = 7;
		}
		else if (moveUp) {
			moveUp = false;
			state = 2;
		}
		break;
	case 7:
		if (ePressed) {
			ePressed = false;
		}
		else if (moveLeft) {
			moveLeft = false;
			state = 6;
		}
		else if (moveUp) {
			moveUp = false;
			state = 3;
		}
		else if (moveRight) {
			moveRight = false;
			state = 8;
		}
		break;
	case 8:
		if (ePressed) {
			ePressed = false;
			
		}
		else if (moveLeft) {
			moveLeft = false;
			state = 7;
		}
		else if (moveUp) {
			moveUp = false;
			state = 4;
		}
		else if (moveRight) {
			moveRight = false;
			state = 5;
		}
		break;

	default:
		break;
	}

}

void Inventory::drawInv(Vector2f *cameraCenter, RenderWindow *window) {

	int cur_row = 0;
	RectangleShape temp(Vector2f(105, 80));
	for (int i = 0; i < 8; i++) {
		if (i > 3)
			cur_row = 1;

		temp.setPosition(InvBody.getPosition().x + 125 * (i % 4) + 10, InvBody.getPosition().y + 100 * cur_row + 10);
		temp.setFillColor(Color(100, 100, 100));

		window->draw(temp);

		if (i < objectsCollection.size()) {
			if (objectsCollection[i].getType() == flowertype) {
				Texture flowerTex;
				flowerTex.loadFromFile("Images/flower.png");
				Sprite flowerSpr;
				flowerSpr.setTexture(flowerTex);
				flowerSpr.setPosition(temp.getPosition().x + temp.getSize().x / 2 - flowerSpr.getGlobalBounds().width / 2, temp.getPosition().y + temp.getSize().y / 2 - flowerSpr.getGlobalBounds().top / 2);

				window->draw(flowerSpr);
			}
		}
	
		
	}
	
	cur_row = 0;
	if (state > 4)
		cur_row = 1;
	outline.setPosition(InvBody.getPosition().x + 125 * (state % 4) + 10, InvBody.getPosition().y + 100 * cur_row + 10);
	outline.setFillColor(Color(0, 0, 0, 0));
	window->draw(outline);
	
}

void Inventory::ShowInventory(View& camera, RenderWindow *window) {

	
	Vector2f cameraCenter = camera.getCenter();
	
	isInventory = true;
	state = 1;

	MakeScreenShotLikeBackgr(cameraCenter, window, &windowTexture, &windowSprite);
	
	InvBody.setPosition(cameraCenter.x - (InvBody.getSize().x / 2), cameraCenter.y - (InvBody.getSize().y / 2));
	

	while (isInventory) {

		input(window);
		window->clear();

	
		runStateMachine();

		window->draw(windowSprite);
		window->draw(background);
		window->draw(InvBody);
		drawInv(&cameraCenter, window);


		window->display();
	}

}