#pragma once
#include  <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"
#include "Actor.h"
#include "Inventory.h"

using namespace std;
using namespace sf;

#ifndef KEVIN_H
#define KEVIN_H

class Kevin : public Actor {
	friend class Engine;
	friend class UnitTests;
private:

	int selectedWeaponIndex;

	Inventory *inventory;

public:
	vector<Weapon *> Weapons;

	Kevin(Vector2f& size, Vector2f& position, Texture* texture, Texture *animation);

	Kevin(Vector2f& size, Vector2f& position, Texture* texture);

	Kevin();

	void setWeapon(int w);

	int getSelectedWeaponIndex();

	
};
#endif KEVIN_H