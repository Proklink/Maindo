#include "Engine.h"


Engine::Engine() {

	
	//������� ����
	window.create(VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Maindo");

	//����������� ���
	background.create(1280, 720);
	//background.loadFromFile("Images/backgroun.png");
	background.loadFromFile("Images/background2.png");
	
	Background.setTexture(background);
	Background.setPosition(0, 0);
	//Background.setScale(0.5, 0.5);
	//Background.setScale(0.5, 0.5);

	//�������� ��� ���� � ������
	Image pl;
	pl.loadFromFile("Images/playerAnimation.png");
	pl.createMaskFromColor(Color::White);
	Texture* playerTexture = new Texture;
	playerTexture->loadFromImage(pl);

	//�������������� ������
	Vector2f heroSize(38, 88);
	Vector2f heroPosition(50, 50);


	//�������� �������� ������
	activeActor = Kevin(heroSize, heroPosition, playerTexture);

	//������� ������ ��� �����
	activeActor.Weapons.push_back(new Weapon(200, 200, weaponId::pistol));
	activeActor.Weapons.push_back(new Weapon(600, 400, weaponId::rifle));
	activeActor.Weapons.push_back(new Weapon(weaponId::keyboard, 1));


	//������������� ����� ������
	playerCamera.setCenter(activeActor.getBody().getPosition());
	//������������� ������ ������� ���������� � ������
	FloatRect camerabounds(0, 0, CAMERA_SIZE_X, CAMERA_SIZE_Y);
	playerCamera.reset(camerabounds);
	//������������ ���� ������
	playerCamera.setViewport(FloatRect(0, 0, 1, 1));
	playerCamera.setCenter(Vector2f(CAMERA_SIZE_X / 2, CAMERA_SIZE_Y / 2));

	
	//�������������� ������ �������
	level = Map(&activeActor);
	level.PrimaryInit();

	//������ ������� ����
	MainMenu = Menu(&window, &level);

	//�������� ������
	//CyrilicOld.TTF//Gnomoria_rus_Regular.ttf//3//4//6(��� ������� �������)//8(larger size)
	if (!mainFont.loadFromFile("Fonts/Gnomoria_rus_Regular.ttf"))
	{
		cout << "Font loading is faled\n";
	}
}

void Engine::checkWeapons() {

	uint8_t i = activeActor.getSelectedWeaponIndex();
	Weapon *selectedWeapon = activeActor.Weapons[i];

	bool s = (selectedWeapon->getType() == stapler);
	bool p = (selectedWeapon->getType() == pistol);
	bool r = (selectedWeapon->getType() == rifle);

	if (s || p || r)
		level.projectiles.push_back(selectedWeapon->actionForShot(activeActor.getCurrentSight(), activeActor.getCenter() + Vector2f(10, -5)));
	else if (selectedWeapon->getType() == keyboard) {
		activeActor.hit_flag = true;
	}
	else if (selectedWeapon->getType() == mouse)
		cout << endl;

}

Texture Engine::getBackgroundTexture() {
	return background;
}

Dialog *Engine::getDialog() {
	return currentDialog;
}


RenderWindow *Engine::getWindow() {
	return &window;
}

Map *Engine::getLevel() {

	return &level;
}

void Engine::setEventKeyCode(Keyboard::Key key) {
	event.key.code = key;
	event.type = Event::KeyPressed;
}

Kevin *Engine::getActiveActor() {
	return &activeActor;
}

void Engine::input() {


		while (window.pollEvent(event)) {
			//cout << event.type << endl;


			if (event.type == Event::LostFocus)
			{
				activeActor.stopALL();

				MainMenu.pause(playerCamera, activeActor, level);

				clock.restart();
			}

			if (event.type == Event::Closed)
				window.close();

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
					activeActor.stopALL();
					
					MainMenu.pause(playerCamera, activeActor, level);
	
					clock.restart();
				}
				if (event.key.code == Keyboard::I)
				{
					activeActor.stopALL();

					//создать поток

					//направить поток сюда
					map->listenSocket();

					activeActor.inventory->ShowInventory(playerCamera, &window);

					ьфзю

					clock.restart();
				}
				if (event.key.code == Keyboard::E)
				{
						activeActor.interaction_flag = true;
				}
				if (event.key.code == Keyboard::Space)
				{
					checkWeapons();	
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

bool Engine::collisionCheck() {


	float step = activeActor.getSpeed() * (elapsedTime);

	RectangleShape playerBody = activeActor.getBody();
	RectangleShape HeroInNextFrame(activeActor.getBody().getSize());

	vector <vector<gameObject>> *StationaryObjects = level.getStationaryObjects();

	int SegmentNum = level.getSegment(&activeActor.getBody().getPosition());;

	if (SegmentNum == -1) {
		activeActor.setPosition(50, 50);
		return false;
	}

	HeroInNextFrame.setPosition(playerBody.getPosition());


	if (activeActor.leftPressed)
		HeroInNextFrame.move(-step, 0);

	if (activeActor.rightPressed)
		HeroInNextFrame.move(step, 0);

	if (activeActor.upPressed)
		HeroInNextFrame.move(0, -step);

	if (activeActor.downPressed)
		HeroInNextFrame.move(0, step);


	float  ActorRightPoint = playerBody.getGlobalBounds().left + playerBody.getGlobalBounds().width;
	float  ActorBottomPoint = playerBody.getGlobalBounds().top + playerBody.getGlobalBounds().height;
	float  ActortLeftPoint = playerBody.getGlobalBounds().left;
	float  ActorTopPoint = playerBody.getGlobalBounds().top;

	bool returningFlag = false;

	for (int i = 0; i < (*StationaryObjects)[SegmentNum].size(); i++) {
		RectangleShape ObjectInMap = (*StationaryObjects)[SegmentNum][i].getLowSide();

		float  ObjectRightPoint = ObjectInMap.getGlobalBounds().left + ObjectInMap.getGlobalBounds().width;
		float  ObjectBottomPoint = ObjectInMap.getGlobalBounds().top + ObjectInMap.getGlobalBounds().height;
		float  ObjectLeftPoint = ObjectInMap.getGlobalBounds().left;
		float  ObjectTopPoint = ObjectInMap.getGlobalBounds().top;


		if (HeroInNextFrame.getGlobalBounds().intersects(ObjectInMap.getGlobalBounds())) {

			returningFlag = true;

			if (ActortLeftPoint > ObjectRightPoint) {
				if (activeActor.leftPressed) {
					activeActor.stopLeft();
				}
			}

			if (ActorRightPoint < ObjectLeftPoint) {
				if (activeActor.rightPressed) {
					activeActor.stopRight();
				}
			}

			if (ActorTopPoint > ObjectBottomPoint) {
				if (activeActor.upPressed) {
					activeActor.stopUp();
				}
			}

			if (ActorBottomPoint < ObjectTopPoint) {
				if (activeActor.downPressed) {
					activeActor.stopDown();
				}
			}

		}


	}

	return returningFlag;

}

void Engine::interactionOrDialogue() {

	RectangleShape playerBody = activeActor.getBody();

	//�������� ������ �������� ������
	vector <vector<gameObject>> *StationaryObjects = level.getStationaryObjects();

	//���������� ������� �����, ��� ������������� �����
	int SegmentNum = level.getSegment(&playerBody.getPosition());

	if (SegmentNum == -1) {
		activeActor.setPosition(50, 50);
		return;
	}

	//����: 
	//����������� �� ���� ��������� �� ����� �, ���� � ��� ����� �����������������,
	//������� ������ ���� ����, ������� ����� ��������������� � ����������� �������������,
	//������ ����� ��� ���������. �����, ���� �� ����� � ��� �����������������, �� ��� ������� �
	//���������� ����� �� ��������
	//���: � ������, ����� ��� �������, � �������� ����� �����������������, ������������� ���� � ������,
	//�������������� �������� ������ � �����. �� �� ���� ��� ���������� � �� ����
	for (int i = 0; i < (*StationaryObjects)[SegmentNum].size(); i++) {

		int Objecttype = (*StationaryObjects)[SegmentNum][i].getType();

		if ((Objecttype != humantype) && (Objecttype != itemtype) && (Objecttype != flowertype))
			continue;

		RectangleShape ObjectInMap = (*StationaryObjects)[SegmentNum][i].getBody();


		Vector2f ObjectGBPosition(ObjectInMap.getGlobalBounds().left, ObjectInMap.getGlobalBounds().top);
		Vector2f ObjectGBSize(ObjectInMap.getGlobalBounds().width, ObjectInMap.getGlobalBounds().height);

		RectangleShape interactionZone;

		interactionZone.setSize(ObjectGBSize * 1.5f);
		interactionZone.setPosition(ObjectGBPosition - ObjectGBSize / 4.f);
		/*interactionZone.setFillColor(Color(255, 255, 255, 200));
		window.draw(interactionZone);*/

		bool isCollision = playerBody.getGlobalBounds().intersects(interactionZone.getGlobalBounds());

		if (isCollision) {

			RectangleShape msg;
			msg.setSize(Vector2f(ObjectInMap.getSize().x / 2, 5));
			msg.setPosition(Vector2f(ObjectInMap.getPosition() + Vector2f(ObjectInMap.getSize().x / 4, -10)));
			msg.setFillColor(Color(Color::White));

			Text hint;

			/////////////////////////////////////////////////////////////////
			//������� ��������� ��������
			hint.setFont(mainFont);
			String str = "Enter E for interaction";
			hint.setString(String::fromUtf8(str.begin(), str.end()));
			hint.setCharacterSize(5);
			hint.setFillColor(Color(0, 0, 0));
			hint.setPosition(msg.getPosition() + Vector2f(1.f, 1.f));
			/////////////////////////////////////////////////////////////////

			window.draw(msg);
			window.draw(hint);
			activeActor.msg_displayed = true;


			if (activeActor.interaction_flag) {
				if (Objecttype == itemtype) {		//��������������

					if (ObjectInMap.getFillColor() == Color::Green)
						(*StationaryObjects)[SegmentNum][i].setColor(Color(Color::Black));
					else
						(*StationaryObjects)[SegmentNum][i].setColor(Color(Color::Green));
					activeActor.interaction_flag = false;
				}
				else if (Objecttype == flowertype) {//������ � ���������
					gameObject *temp = &(*StationaryObjects)[SegmentNum][i];//��������� �� ������ �� ������� �������� �� �����

					bool addFlag = activeActor.inventory->addItem(temp);
					if (addFlag) {
						(*StationaryObjects)[SegmentNum].erase((*StationaryObjects)[SegmentNum].begin() + i);
						i--;
					}


				}
				else {
					if (!isDialogNow) {
						isDialogNow = true;
						Vector2f center = playerCamera.getCenter();
						string name;
						if ((ObjectGBPosition.x == 382) && (ObjectGBPosition.y == 30))
							name = "Dialogs/Dialog4.txt";

						else
							name = "Dialogs/Dialog3.txt";
						currentDialog = new Dialog(name, center, mainFont);
					}
				}
				
			}
		}

	}
}

void Engine::KeyboardStrike(Clock& timeForKeyboard) {

	//�������� ���� �� ������� � �����
	//���� ����, ��������� ������ ��� ��������, ��������� ����, ���������, ��� ������ ���������� ����
	//���� ���� ����������, ������������ ������, ������������ �������� � �������� ��������
	if (activeActor.hit_flag) {
		activeActor.hit_flag = false;
		activeActor.isHitting = true;
		timeForKeyboard.restart();
	}
	else
		if (!activeActor.isHitting)
			return;

	if (timeForKeyboard.getElapsedTime().asSeconds() >= 0.1) {
		activeActor.isHitting = false;
		return;
	}

	FloatRect actorBody = activeActor.getBody().getGlobalBounds();
	Vector2f curSig = activeActor.getCurrentSight();
	RectangleShape StrikeZone = activeActor.Weapons[activeActor.getSelectedWeaponIndex()]->actionForKeyboard(actorBody, curSig);

	window.draw(StrikeZone);


	//� ����������, ����� ��������� �� ������������ �� ���� ����� � ������� ���������� �����


	//�������� ������ �������� ������
	vector <vector<gameObject>> *StationaryObjects = level.getStationaryObjects();

	//���������� ������� �����, ��� ������������� �����
	int SegmentNum = level.getSegment(&activeActor.getBody().getPosition());

	if (SegmentNum == -1) {
		activeActor.getBody().setPosition(50, 50);
		return;
	}


	for (int i = 0; i < (*StationaryObjects)[SegmentNum].size(); i++) {

		if ((*StationaryObjects)[SegmentNum][i].getType() != humantype)
			continue;

		RectangleShape ObjectInMap = (*StationaryObjects)[SegmentNum][i].getBody();

		bool isCollision = ObjectInMap.getGlobalBounds().intersects(StrikeZone.getGlobalBounds());

		if (isCollision) {
			(*StationaryObjects)[SegmentNum].erase((*StationaryObjects)[SegmentNum].begin() + i);
			i--;
		}

	}

}

void Engine::checkCameraCollision() {

	//������ ����� ������ ���, ����� ������ ������� �� �������
	playerCamera.setCenter(activeActor.getCenter());

	float RightPoint = (playerCamera.getCenter() + playerCamera.getSize() / 2.f).x;
	float LeftPoint = (playerCamera.getCenter() - playerCamera.getSize() / 2.f).x;
	float TopPoint = (playerCamera.getCenter() - playerCamera.getSize() / 2.f).y;
	float DownPoint = (playerCamera.getCenter() + playerCamera.getSize() / 2.f).y;

	if (RightPoint > WINDOW_SIZE_X)
	{
		if (TopPoint < 0)
			playerCamera.setCenter(Vector2f(WINDOW_SIZE_X - CAMERA_SIZE_X / 2, WINDOW_SIZE_Y / 2 - CAMERA_SIZE_Y / 2));
		else if (DownPoint > WINDOW_SIZE_Y)
			playerCamera.setCenter(Vector2f(WINDOW_SIZE_X - CAMERA_SIZE_X / 2, WINDOW_SIZE_Y - CAMERA_SIZE_Y / 2));
		else
			playerCamera.setCenter(Vector2f(WINDOW_SIZE_X - CAMERA_SIZE_X / 2, activeActor.getCenter().y));

	}
	else if (LeftPoint < 0)
	{
		if (TopPoint < 0)
			playerCamera.setCenter(Vector2f(CAMERA_SIZE_X / 2, CAMERA_SIZE_Y / 2));
		else if (DownPoint > WINDOW_SIZE_Y)
			playerCamera.setCenter(Vector2f(WINDOW_SIZE_X / 2 - CAMERA_SIZE_X / 2, WINDOW_SIZE_Y - CAMERA_SIZE_Y / 2));
		else
			playerCamera.setCenter(Vector2f(WINDOW_SIZE_X / 2 - CAMERA_SIZE_X / 2, activeActor.getCenter().y));

	}
	else
	{
		if (TopPoint < 0)
			playerCamera.setCenter(Vector2f(activeActor.getCenter().x, CAMERA_SIZE_Y / 2));
		else if (DownPoint > WINDOW_SIZE_Y)
			playerCamera.setCenter(Vector2f(activeActor.getCenter().x, WINDOW_SIZE_Y - CAMERA_SIZE_Y / 2));

	}
}

void Engine::inputInDialog() {

	Event event;

	while (window.pollEvent(event)) {
		//cout << event.type << endl;

		if (event.type == Event::Closed)
			window.close();


		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::E)
			{
				activeActor.interaction_flag = true;
			}
			if (event.key.code == Keyboard::Escape)
			{
				MainMenu.pause(playerCamera, activeActor, level);
			}
		}

		if (event.type == Event::KeyReleased) {

			if (event.key.code == Keyboard::E)
				activeActor.interaction_flag = false;

		}
	}

}

void Engine::gameLoop() {


	//����� ��� �������� ����� �����������
	Clock timeForKeyboard;

	//������� ����
	while (window.isOpen()) {

		//cout << activeActor.interaction_flag << endl;
		//cout << activeActor.getBody().getPosition().x << " " << activeActor.getBody().getPosition().y << endl;
		//cout << activeActor.interaction_flag << endl;

		activeActor.interaction_flag = false;

		//����� ��� ��������
		elapsedTime = clock.getElapsedTime().asSeconds();
		clock.restart();

		if (!isDialogNow)
			input();
		else
			inputInDialog();

		//������� ���������� ����
		window.clear();

		window.draw(Background);

		//��������� ��������
		collisionCheck();

		level.checkCollisionProjectiles();

		interactionOrDialogue();

		KeyboardStrike(timeForKeyboard);

		//��������� ��������� ������������ ������
		activeActor.update(&elapsedTime);

		activeActor.updateAnimation(&elapsedTime);

		level.updateProjectailes(&elapsedTime);

		checkCameraCollision();

		//����������� �������� - ��������� ���� ��� �������
		window.setView(playerCamera);

		//������ ����� ��������� ������
		window.draw(activeActor.getBody());

		level.drawObjects(window);

		if (isDialogNow) {
			isDialogNow = currentDialog->update(activeActor.interaction_flag);
			currentDialog->draw(window);
		}

		//������������ ����� ��������� ������
		window.display();

	}
}