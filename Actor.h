#pragma once
#include  <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"
//#include "gameObjectMobile.h"
#include "Weapon.h"
#include "Map.h"
#include "Dialog.h"




using namespace std;
using namespace sf;

#ifndef ACTOR_H
#define ACTOR_H

class Actor : public gameObjectMobile {
	
private:

	

	uint8_t healthPoints;


	//коэффициент скорости передвижения
	float BaseSpeed = 100;
	float FastSpeed = BaseSpeed * 2;

	Texture *animationSet;

	float currentFrame;

public:

	bool interaction_flag;
	bool msg_displayed;
	bool isHitting;
	bool hit_flag;



	Actor();

	Actor(Vector2f& size, Vector2f& position, float speed, Texture* texture, Texture *animation);


	float getFastSpeed();

	float getSpeed();

	float getBaseSpeed();

	void setFastSpeed();

	void setBaseSpeed();

	void collisionCheck(Map *level, float *time, RenderWindow& window);

	void interactionCheck(Map *level, float *time, RenderWindow& window);

	void updateAnimation(float *ElapsedTime);

	void setPosition(float x, float y);
	
};

#endif ACTOR_H