#pragma once
#include  <SFML/Graphics.hpp>

#include "Projectile.h"

using namespace std;
using namespace sf;

enum weaponId {
	keyboard = 0,
	mouse,
	stapler,
	staple,//скоба
	pistol,
	rifle
};

class Weapon : public gameObject 
{
	friend class Kevin;
private:
	weaponId weaponType;

public:

	Weapon();

	Weapon(float range, float projectileSpeed, weaponId weaponType, Texture* projectileTexture = NULL, float fireRate = 0, float damage = 0);

	Weapon(weaponId weaponType, float damage);

	Projectile actionForShot(Vector2f shotDirection, Vector2f shotPosition);

	RectangleShape actionForKeyboard(FloatRect& actorBody, Vector2f& currentSight);


	Texture* projectileTexture;
	float range;			//uint16_t damageDistance;
	float damage;			//uint8_t damage;
	float fireRate;
	float projectileSpeed;

	int getType() { return weaponType; }
};