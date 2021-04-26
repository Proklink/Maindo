#include "Weapon.h"


Weapon::Weapon()
{
	range = 0;
	damage = 0;
	fireRate = 0;
	projectileSpeed = 0;
	projectileTexture = NULL;
	type = ObjectType::weapontype;
}

Weapon::Weapon(float range, float projectileSpeed, weaponId weaponType, Texture* projectileTexture, float fireRate, float damage)
{
	this->range = range;

	this->projectileSpeed = projectileSpeed;

	this->fireRate = fireRate;

	this->damage = damage;

	if (projectileTexture) {
		this->projectileTexture = projectileTexture;
		this->body.setFillColor(Color::White);
	}

	this->weaponType = weaponType;

	type = ObjectType::weapontype;
}

Weapon::Weapon(weaponId weaponType, float damage) {
	this->weaponType = weaponType;
	type = ObjectType::weapontype;
	this->damage = damage;
}

Projectile Weapon::actionForShot(Vector2f shotDirection, Vector2f shotPosition)
{
	//Vector2f projSize(projectile.body.getTextureRect().width, projectile.body.getTextureRect().height);
	Vector2f size(4, 2);
	Color color = Color::White;
	Projectile projectile(shotDirection, shotPosition, this->range, projectileSpeed,
																				size, shotPosition, color, projectileTexture);
	//cout << shotDirection.x << " " << shotDirection.y << endl;
	projectile.isMoving = true;

	projectile.body.setRotation((float)(atan2(shotDirection.y, shotDirection.x) * 180 / 3.14));
	
	return projectile;
}

RectangleShape Weapon::actionForKeyboard(FloatRect& actorBody, Vector2f& currentSight) {
	
	Vector2f bodySize(actorBody.width, actorBody.height);
	Vector2f bodyPosition(actorBody.left, actorBody.top);

	//коэффициент 1/9 это соотношение длины руки с клавиатурой к моему росту, поэтому чтобы вычислисть дальность удара
	//нужно умножить 1/9 на высоту игрока
	float alwtk = bodySize.y * 5 / 9;		//arm's length with the keyboard

	//рассмотрим рассчет размера и положения зоны поражения для игрока, смотрящего справо:
	//левая крайняя точка зоны поражения это крайняя правая точка игрока
	//верхняя точка зоны поражения равна сдвигу вниз от верхней точки игрока на 1/6(отношение моей головы к росту)
	//умноженное на высоту игрока


	float left = bodyPosition.x + bodySize.x;
	float top = bodyPosition.y + (bodySize.y * 2) / 6 - alwtk; // 2/6  использовал, потому что всё-таки
																					//отношения головы к росту было мало

	if (currentSight == Vector2f(-1, 0))
		left = bodyPosition.x - alwtk;
	else if (currentSight == Vector2f(0, 1)) {
		left = bodyPosition.x - abs(alwtk - bodySize.x) / 2;
		top = bodyPosition.y + (bodySize.y * 3) / 4 - 20;
	}
	else if (currentSight == Vector2f(0, -1)) {
		left = bodyPosition.x - abs(alwtk - bodySize.x) / 2;
		top = bodyPosition.y - (bodySize.y * 3) / 4 + 20;
	}


	RectangleShape StrikeZone(Vector2f(alwtk, 2 * alwtk));
	StrikeZone.setPosition(Vector2f(left, top));
	StrikeZone.setFillColor(Color(255, 255, 255, 100));

	return StrikeZone;

}

