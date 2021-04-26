#pragma once
#include "Dialog.h"
#include "Kevin.h"
#include "Menu.h"
#include "Inventory.h"


using namespace std;
using namespace sf;



#ifndef ENGINE_H
#define ENGINE_H

class Engine {
private:
	friend class UnitTests;
	friend class Inventory;

	Kevin activeActor;

	Map level;

	View playerCamera;

	Menu MainMenu;

	Font mainFont;

	Dialog *currentDialog;

	Texture background;
	Sprite Background;

	RenderWindow window;

	Texture *npc1Tex;

	Event event;

	//время для движения
	Clock clock;

	float elapsedTime;

public:

	bool isDialogNow = false;

	Engine();

	void input();

	void drawAndDisplay();

	Texture getBackgroundTexture();

	Dialog *getDialog();

	RenderWindow *getWindow();

	Kevin *getActiveActor();

	Map *getLevel();

	bool collisionCheck();

	void KeyboardStrike(Clock& timeForKeyboard);

	void checkCameraCollision();

	void interactionOrDialogue();

	void inputInDialog();

	void checkWeapons();

	void updateAll();

	void gameLoop();

	void setEventKeyCode(Keyboard::Key key);

	bool moveFromInvToMap();

};

#endif ENGINE_H