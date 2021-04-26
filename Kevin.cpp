#include "Kevin.h"

using namespace std;
using namespace sf;

Kevin::Kevin(Vector2f& size, Vector2f& position, Texture* texture, Texture *animation) : 
	Actor(size, position, 100, texture, animation) {
	type = humantype;
	selectedWeaponIndex = 0;
}

Kevin::Kevin(Vector2f& size, Vector2f& position, Texture* texture) :
	Actor(size, position, 100, texture, NULL) {
	type = humantype;
	selectedWeaponIndex = 0;
	inventory = new Inventory(8);
}

Kevin::Kevin() {
	body.setSize(Vector2f(22, 54));
	body.setPosition(Vector2f(50, 50));
	body.setFillColor(Color(255, 255, 255, 255));
	type = humantype;
	selectedWeaponIndex = 0;
	inventory = new Inventory();
}

void Kevin::setWeapon(int w) {
	selectedWeaponIndex = w;
}

int Kevin::getSelectedWeaponIndex() {
	return selectedWeaponIndex;
}

