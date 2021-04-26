#include "Menu.h"


Menu::Menu(RenderWindow *window, Map *level) {

	 moveDown = false;
	 moveUp = false;
	 moveRight = false;
	 moveLeft = false;
	 enterPressed = false;
	 music = true;
	 sounds = true;

	 background.setSize(Vector2f((float)window->getSize().x, (float)window->getSize().y));
	 background.setFillColor(Color(100, 100, 100, 150));
	 background.setPosition(0, 0);


	for (int i = 0; i < 4; i++) {
		String file = (String)"Images/Menu_" + to_string(i + 1) + (String)".png";

		Image menuImage;
		menuImage.loadFromFile(file);
		menuImage.createMaskFromColor(Color(255, 255, 255));

		Texture tempTex;
		tempTex.loadFromImage(menuImage);

		menuTextures.push_back(tempTex);
	}

	SelectedMenu.setTexture(menuTextures[0]);

	this->window = (window);

	usage.loadFromFile("Images/usage.png");
}

void Menu::MakeScreenShotLikeBackgr(Vector2f& cameraCenter) {
	
	Vector2u windowSize = window->getSize();

	windowTexture.create(windowSize.x, windowSize.y);
	windowTexture.update(*window);
	
	windowSprite.setTexture(windowTexture);
	windowSprite.setScale(0.5, 0.5);
	windowSprite.setPosition(cameraCenter - Vector2f(CAMERA_SIZE_X / 2, CAMERA_SIZE_Y / 2));

}

Menu::Menu() {}

void Menu::input() {

	Event event;
	while (window->pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
				isPause = false;

			if (event.key.code == Keyboard::Enter)
				enterPressed = true;

			if (event.key.code == Keyboard::Space)
				enterPressed = true;
		}

		if (event.type == Event::Closed) {
			isPause = false;
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

void Menu::newGame(Actor& activeActor, Map& level) {
	Map newLevel;
	newLevel.PrimaryInit();
	level = newLevel;
	activeActor.setPosition(50, 50);
}

void Menu::showUsage() {
	Event event;
	bool ESC = true;
	Sprite Usage;
	Usage.setTexture(usage);
	Vector2f pos = SelectedMenu.getPosition();
	Usage.setPosition(pos);

	window->draw(Usage);
	window->display();

	while (window->pollEvent(event) or ESC)
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
				ESC = false;
		}


	}
}

void Menu::changeMusic() {
	
	if (music && sounds) {
		SelectedMenu.setTexture(menuTextures[2]);
		music = false;
	}
	else if (music && !sounds) {
		SelectedMenu.setTexture(menuTextures[3]);
		music = false;
	}
	else if (!music && sounds) {
		SelectedMenu.setTexture(menuTextures[0]);
		music = true;
	}
	else if (!music && !sounds) {
		SelectedMenu.setTexture(menuTextures[1]);
		music = true;
	}
}

void Menu::changeSounds() {

	if (music && sounds) {
		SelectedMenu.setTexture(menuTextures[1]);
		sounds = false;
	}
	else if (music && !sounds) {
		SelectedMenu.setTexture(menuTextures[0]);
		sounds = true;
	}
	else if (!music && sounds) {
		SelectedMenu.setTexture(menuTextures[3]);
		sounds = false;
	}
	else if (!music && !sounds) {
		SelectedMenu.setTexture(menuTextures[2]);
		sounds = true;
	}
}

void Menu::runStateMachine(Actor& activeActor, Map& level) {

	switch (state)
	{
	case continue_button:
		if (enterPressed) {
			enterPressed = false;
			isPause = false;
		} 
		else if (moveDown) {
			moveDown = false;
			state = new_game_button;
		}
		else if (moveUp) {
			moveUp = false;
			state = exit_button;
		}
		break;

	case new_game_button:
		if (enterPressed) {
			enterPressed = false;
			newGame(activeActor, level);
			isPause = false;
			
		}
		else if (moveUp) {
			moveUp = false;
			state = continue_button;
		}
		else if (moveDown) {
			moveDown = false;
			state = usage_button;
		} 
		
		break;

	case usage_button:
		if (enterPressed) {
			enterPressed = false;
			showUsage();
			
		}
		else if (moveUp) {
			moveUp = false;
			state = new_game_button;
		}
		else if (moveDown) {
			moveDown = false;
			state = exit_button;
		}
		break;

	case exit_button:
		if (enterPressed) {
			enterPressed = false;
			isPause = false;
			window->close();
		}
		else if (moveUp) {
			moveUp = false;
			state = usage_button;
		}
		else if (moveRight) {
			moveRight = false;
			state = sounds_button;
		}
		else if (moveDown) {
			moveDown = false;
			state = continue_button;
		}
		break;

	case sounds_button:
		if (enterPressed) {
			enterPressed = false;
			changeSounds();
			
		}
		else if (moveLeft) {
			moveLeft = false;
			state = exit_button;
		}
		else if (moveRight) {
			moveRight = false;
			state = music_button;
		}
		break;

	case music_button:
		if (enterPressed) {
			enterPressed = false;
			changeMusic();
			
			
		}
		else if (moveLeft) {
			moveLeft = false;
			state = sounds_button;
		}
		break;

	default:
		break;
	}

}

void Menu::drawOutline() {
	
	outline.setFillColor(Color(0, 0, 0, 0));
	outline.setOutlineThickness(1);
	outline.setOutlineColor(Color(0, 0, 0, 255));
	Vector2f menuPos = SelectedMenu.getPosition();


	if (state == continue_button) {
		Vector2f size(86, 14);

		outline.setSize(size);
		outline.setPosition(menuPos.x + 32, menuPos.y + 8);
	}
	if (state == new_game_button) {
		Vector2f size(118, 16);

		outline.setSize(size);
		outline.setPosition(menuPos.x + 16, menuPos.y + 29);
	}
	if (state == usage_button) {
		Vector2f size(88, 15);

		outline.setSize(size);
		outline.setPosition(menuPos.x + 31, menuPos.y + 53);
	}
	if (state == exit_button) {
		Vector2f size(50, 14);

		outline.setSize(size);
		outline.setPosition(menuPos.x + 50, menuPos.y + 77);
	}
	if (state == sounds_button) {
		Vector2f size(18, 17);

		outline.setSize(size);
		outline.setPosition(menuPos.x + 110, menuPos.y + 107);
	}
	if (state == music_button) {
		Vector2f size(16, 17);

		outline.setSize(size);
		outline.setPosition(menuPos.x + 131, menuPos.y + 107);
	}

	
}

void Menu::pause(View& camera, Actor& activeActor, Map& level) {

	const Texture *menuTexture;
	Vector2f cameraCenter = camera.getCenter();
	SelectedMenu.setTexture(menuTextures[0]);
	isPause = true;
	state = continue_button;

	MakeScreenShotLikeBackgr(cameraCenter);

	while (isPause) {

		input();
		window->clear();

		menuTexture = SelectedMenu.getTexture();
		SelectedMenu.setPosition(cameraCenter.x - (menuTexture->getSize().x / 2), cameraCenter.y - (menuTexture->getSize().y / 2));

		drawOutline();
		runStateMachine(activeActor, level);
	
		window->draw(windowSprite);
		window->draw(background);
		window->draw(SelectedMenu);
		window->draw(outline);

		window->display();
	}

}