#include "gameObject.h"

using namespace std;



gameObject::gameObject(Vector2f& size, Vector2f& position, ObjectType t, Texture* texture) {
	body.setSize(size);
	body.setPosition(position);
	body.setFillColor(Color(255, 255, 255, 255));
	body.setTexture(texture);
	type = t;

	if (t == ObjectType::walltype)
		lowSide = body;
	else {

		Vector2f size(body.getGlobalBounds().width, body.getGlobalBounds().height / 2);
		Vector2f pos(body.getGlobalBounds().left, body.getGlobalBounds().top + body.getGlobalBounds().height / 2);
		lowSide.setSize(size);
		lowSide.setPosition(pos);
	}
}

gameObject::gameObject(RectangleShape& recSh, ObjectType t, Texture* texture) {
	body = recSh;
	body.setTexture(texture);
	type = t;


	//в конструкторе выше есть такая же конструкция
	if (t == ObjectType::walltype)
		lowSide = body;
	else {

		Vector2f size(body.getGlobalBounds().width, body.getGlobalBounds().height / 2);
		Vector2f pos(body.getGlobalBounds().left, body.getGlobalBounds().top + body.getGlobalBounds().height / 2);
		lowSide.setSize(size);
		lowSide.setPosition(pos);
	}
}

gameObject::gameObject() {}

RectangleShape gameObject::getBody() { return body; }

RectangleShape gameObject::getLowSide() { return lowSide; }

Vector2f gameObject::getCenter() {
	return body.getPosition() + body.getSize() / 2.f;
}

ObjectType gameObject::getType() { return type; }

void gameObject::setColor(Color color) {

	body.setFillColor(color);
}