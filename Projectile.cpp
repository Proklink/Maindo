#pragma once
#include "Projectile.h"

Projectile::Projectile(Vector2f currentDirection, Vector2f currentPosition, float range, float speed, 
									Vector2f& size, Vector2f& position, Color& color, Texture* texture)
	: gameObjectMobile(size, position, ObjectType::projectiletype, texture, speed)
{
	this->range = range;
	this->currentDirection = currentDirection;
	this->currentPosition = currentPosition;
	this->startPosition = currentPosition;
	this->body.setFillColor(color);
}


void Projectile::update(float *time) {
	Vector2f shift = currentDirection * speed * (*time);
	body.move(shift);
}