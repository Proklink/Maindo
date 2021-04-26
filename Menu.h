#pragma once
#include "Actor.h"


enum Button {
	continue_button,
	new_game_button,
	usage_button,
	sounds_button,
	music_button,
	exit_button
};


class Menu {
private:
	RenderWindow* window;

	Image windowImage;
	Texture windowTexture;
	Sprite windowSprite;

	Sprite SelectedMenu;
	vector<Texture> menuTextures;

	RectangleShape background;

	RectangleShape outline;

	Texture usage;

public:
	bool moveDown;
	bool moveUp;
	bool moveRight;
	bool moveLeft;
	bool enterPressed;
	int state;
	bool isPause;
	bool music;
	bool sounds;

	Menu(RenderWindow *window, Map *level);

	Menu();

	void MakeScreenShotLikeBackgr(Vector2f& cameraCenter);

	void input();

	void pause(View& camera, Actor& activeActor, Map& level);

	void newGame(Actor& activeActor, Map& level);

	void showUsage();

	void runStateMachine(Actor& activeActor, Map& level);

	void drawOutline();

	void changeMusic();

	void changeSounds();
};