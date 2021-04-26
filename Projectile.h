#pragma once
#include "gameObjectMobile.h"

#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile : public gameObjectMobile
{
public:
	friend class Weapon;
	float range;
	Vector2f currentPosition;
	Vector2f startPosition;

	Projectile(Vector2f currentDirection, Vector2f currentPosition, float range, float speed, Vector2f& size, Vector2f& position,
																		Color& color, Texture* texture);
	
	void update(float *time);
};

#endif PROJECTILE_H