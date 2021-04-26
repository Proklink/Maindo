#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"
//#include "Kevin.h"
//#include "Menu.h"
//#include "Map.h"
//#include "Dialog.h"
#include "Engine.h"
 

using namespace std;
using namespace sf;


#define WINDOW_SIZE_X 1280
#define WINDOW_SIZE_Y 720
#define CAMERA_SIZE_X WINDOW_SIZE_X / 2
#define CAMERA_SIZE_Y WINDOW_SIZE_Y / 2

Font font;

void checkCameraCollision(View& alternativeView, Actor& activeActor) {

	float RightPoint = (alternativeView.getCenter() + alternativeView.getSize() / 2.f).x;
	float LeftPoint = (alternativeView.getCenter() - alternativeView.getSize() / 2.f).x;
	float TopPoint = (alternativeView.getCenter() - alternativeView.getSize() / 2.f).y;
	float DownPoint = (alternativeView.getCenter() + alternativeView.getSize() / 2.f).y;

	if (RightPoint > WINDOW_SIZE_X)
	{
		if (TopPoint < 0)
			alternativeView.setCenter(Vector2f(WINDOW_SIZE_X - CAMERA_SIZE_X / 2, WINDOW_SIZE_Y / 2 - CAMERA_SIZE_Y / 2));
		else if (DownPoint > WINDOW_SIZE_Y)
			alternativeView.setCenter(Vector2f(WINDOW_SIZE_X - CAMERA_SIZE_X / 2, WINDOW_SIZE_Y - CAMERA_SIZE_Y / 2));
		else
			alternativeView.setCenter(Vector2f(WINDOW_SIZE_X - CAMERA_SIZE_X / 2, activeActor.getCenter().y));

	}
	else if (LeftPoint < 0)
	{
		if (TopPoint < 0)
			alternativeView.setCenter(Vector2f(CAMERA_SIZE_X / 2, CAMERA_SIZE_Y / 2));
		else if (DownPoint > WINDOW_SIZE_Y)
			alternativeView.setCenter(Vector2f(WINDOW_SIZE_X / 2 - CAMERA_SIZE_X / 2, WINDOW_SIZE_Y - CAMERA_SIZE_Y / 2));
		else
			alternativeView.setCenter(Vector2f(WINDOW_SIZE_X / 2 - CAMERA_SIZE_X / 2, activeActor.getCenter().y));

	}
	else
	{
		if (TopPoint < 0)
			alternativeView.setCenter(Vector2f(activeActor.getCenter().x, CAMERA_SIZE_Y / 2));
		else if (DownPoint > WINDOW_SIZE_Y)
			alternativeView.setCenter(Vector2f(activeActor.getCenter().x, WINDOW_SIZE_Y - CAMERA_SIZE_Y / 2));

	}
}

void input_v3(RenderWindow *window, Kevin &activeActor, Map *level, View* camera, Menu& menu) {

	Event event;

	while (window->pollEvent(event)) {
		cout << event.type << endl;

		//fix нужно поработать с временем и продолжением движения
		//if (event.type == Event::LostFocus)
		//{
		//	bool lostFocus = true;
		//	while (window.pollEvent(event) or lostFocus)
		//	{
		//		if (event.type == Event::GainedFocus) {
		//			lostFocus = false;
		//			//cout << Event::GainedFocus << endl;
		//		}
		//	}
		//}

		if (event.type == Event::Closed)
			window->close();

		if (Keyboard::isKeyPressed(Keyboard::A))
			activeActor.moveLeft();

		if (Keyboard::isKeyPressed(Keyboard::D))
 			activeActor.moveRight();

		if (Keyboard::isKeyPressed(Keyboard::S))
			activeActor.moveDown();

		if (Keyboard::isKeyPressed(Keyboard::W))
			activeActor.moveUp();

		if (Keyboard::isKeyPressed(Keyboard::LShift))
			activeActor.setFastSpeed();

		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
			{
				menu.pause(*camera, activeActor, *level);
			}
			if (event.key.code == Keyboard::E)
			{
				activeActor.interaction_flag = true;
			}
			if (event.key.code == Keyboard::Space)
			{
				//изменил илюшин код
				uint8_t i = activeActor.getSelectedWeaponIndex();
				Weapon *selectedWeapon = activeActor.Weapons[i];
				bool s = (selectedWeapon->getType() == stapler);
				bool p = (selectedWeapon->getType() == pistol);
				bool r = (selectedWeapon->getType() == rifle);
				if (s || p || r)
					level->projectiles.push_back(selectedWeapon->actionForShot(activeActor.getCurrentSight(), activeActor.getCenter() + Vector2f(10, -5)));
				else if (selectedWeapon->getType() == keyboard) {
					activeActor.hit_flag = true;
				}
				else if (selectedWeapon->getType() == mouse)
					cout << endl;
			}
			if (event.key.code == Keyboard::R)
			{
				uint8_t current_weapon = activeActor.getSelectedWeaponIndex();

				if (!activeActor.Weapons.empty())
					activeActor.setWeapon((current_weapon + 1) % activeActor.Weapons.size());
			}
		}

		if (event.type == Event::KeyReleased) {
			if (event.key.code == Keyboard::A)
				activeActor.stopLeft();
	
			if (event.key.code == Keyboard::D)
				activeActor.stopRight();
	
			if (event.key.code == Keyboard::S)
				activeActor.stopDown();
	
			if (event.key.code == Keyboard::W)
				activeActor.stopUp();

			if (event.key.code == Keyboard::E)
				activeActor.interaction_flag = false;

			if (event.key.code == Keyboard::LShift)
				activeActor.setBaseSpeed();
		}
	}

}

int main() {
	/*//игровое окно
	RenderWindow window(VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Maindo");
	
	Image backg;
	backg.loadFromFile("Images/background.png");
	backg.createMaskFromColor(Color(255, 255, 255));

	Texture background;
	background.create(1280, 720);
	background.loadFromImage(backg);

	Sprite Background;
	Background.setTexture(background);
	Background.setPosition(0, 0);
	Background.setScale(0.60, 0.38);

	//текстуры для пуль и игрока
	Texture* playerTexture = new Texture;
	playerTexture->loadFromFile("Images/player1.png");
	
	//характеристики актора
	Vector2f heroSize(22, 54);
	Vector2f heroPosition(50, 50);

	//создание сущности игрока
	Kevin activeActor(heroSize, heroPosition, playerTexture);

	activeActor.Weapons.push_back(new Weapon(200, 200, weaponId::pistol));
	activeActor.Weapons.push_back(new Weapon(600, 400, weaponId::rifle));
	activeActor.Weapons.push_back(new Weapon(weaponId::keyboard, 1));

	//вид камеры 
	View alternativeView;
	//устанавливаем центр камеры
	alternativeView.setCenter(activeActor.getBody().getPosition());
	//устанавливаем размер области попадающей в камеру
	FloatRect camerabounds(0, 0, CAMERA_SIZE_X, CAMERA_SIZE_Y);
	alternativeView.reset(camerabounds);
	//расположение окна камеры
	alternativeView.setViewport(FloatRect(0, 0, 1, 1));
	alternativeView.setCenter(Vector2f(CAMERA_SIZE_X / 2, CAMERA_SIZE_Y / 2));


	//инициализируем первый уровень
	Map level1;
	level1.PrimaryInit();

	//создаём главное меню
	Menu MainMenu(&window, &level1);

	//время для движения
	Clock clock;
	//время для анимации удара клавиатурой
	Clock timeForKeyboard;


	//vector<Font> testFonts;
	//vector<Text> testText;
	for (int i = 0; i < 11; i++) {
		if (!testFonts[i].loadFromFile("Fonts/FontTest/" + (string)".ttf"))
		{
			cout << "Font loading is faled\n";
		}
	}
	
	if (!font.loadFromFile("Fonts/Gnomoria_rus_Regular.ttf"))//CyrilicOld.TTF//Gnomoria_rus_Regular.ttf
	{
		cout << "Font loading is faled\n";
	}

	Text text;
	text.setFont(font);
	text.setCharacterSize(24);

	text.setFillColor(Color::Red);

	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.setPosition(50, 50);


	Dialog d("Dialogs/Dialog1.txt");

	//игровой цикл
	while (window.isOpen()) {
		
		//cout << activeActor.getBody().getPosition().x << " " << activeActor.getBody().getPosition().y << endl;
		//cout << activeActor.interaction_flag << endl;

		//время для движения
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();


		if (!activeActor.isDialogNow)
			input_v3(&window, activeActor, &level1, &alternativeView, MainMenu);
		else
			//activeActor.inputInDialog();

		//очищаем предыдущий кадр
		window.clear();

		window.draw(Background);

		//проверяем коллизии
		activeActor.collisionCheck(&level1, &time, window);
		level1.checkCollisionProjectiles();

		activeActor.interactionOrDialogue(&level1, &time, window, font);

		activeActor.KeyboardStrike(level1, window, timeForKeyboard);

		//обновляем состояние действующего актора
		activeActor.update(&time);

		level1.updateProjectailes(&time);

		//ставим центр камеры так, чтобы камера следила за игроком
		alternativeView.setCenter(activeActor.getCenter());
		
		checkCameraCollision(alternativeView, activeActor);

		//обязаельное действие: установка вида как текущее
		window.setView(alternativeView);
		

		//создаём новое состояние экрана
		window.draw(activeActor.getBody());

		level1.drawObjects(window);
		
		String line = "Что";
		
		text.setString(String::fromUtf8(d.speech.begin(), d.speech.end()));
		text.setString(String::fromUtf8(line.begin(), line.end()));
		
		window.draw(text);
		
		//отрисовываем новое состояние экрана
		window.display();

	}*/

	Engine engine;
	engine.gameLoop();


	return 0;
}