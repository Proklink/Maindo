#include "Actor.h"


 
using namespace std;
using namespace sf;

Actor::Actor(Vector2f& size, Vector2f& position, float speed, Texture* texture, Texture* animation)
	: gameObjectMobile(size, position, humantype, texture, speed) 
{
	currentDirection = Vector2f(1, 0);
	interaction_flag = false;
	msg_displayed = false;
	isHitting = false;
	hit_flag = false;
	animationSet = animation;
}

Actor::Actor() {
	currentDirection = Vector2f(1, 0);
	interaction_flag = false;
	msg_displayed = false;
	isHitting = false;
	hit_flag = false;

}

void Actor::updateAnimation(float *ElapsedTime) {
	currentFrame += 7 * (*ElapsedTime);
	if (currentFrame > 7)
		currentFrame = 2;

	int size;
	int start;

	if ((int)currentFrame == 0) {
		start = 3;
		size = 38;
	}
	else if ((int)currentFrame == 1) {
		start = 45;
		size = 38;
	}
	else if ((int)currentFrame == 2) {
		start = 84;
		size = 38;
	}
	else if ((int)currentFrame == 3) {
		start = 123;
		size = 38;
	}
	else if ((int)currentFrame == 4) {
		start = 172;
		size = 38;
	}
	else if ((int)currentFrame == 5) {
		start = 211;
		size = 38;
	}
	else if ((int)currentFrame == 6) {
		start = 251;
		size = 38;
	}
	else if ((int)currentFrame == 7) {
		start = 296;
		size = 38;
	}

	if (currentDirection.x == 1 ) {
		body.setTextureRect(IntRect(start, 3, size, 88));
		
	}
	else if (currentDirection.x == -1) {

		body.setTextureRect(IntRect(3 + 35, 3, -35, 88));
		
	}
	else if (currentDirection == Vector2f(0, 1)) {
		
		body.setTextureRect(IntRect(6, 141, 33, 88));
	}
	else if (currentDirection == Vector2f(0, -1)) {
		
		body.setTextureRect(IntRect(2, 271, 36, 88));
	}
	else if (currentDirection == Vector2f(0, 0)) {
		currentFrame = 0;
		body.setTextureRect(IntRect(6, 141, 33, 88));
	}
}

float Actor::getBaseSpeed() {
	return BaseSpeed;
}

	float Actor::getFastSpeed() {
		return FastSpeed;
	}

	float Actor::getSpeed() {
		return speed;
	}

	void Actor::setFastSpeed() {
		speed = FastSpeed;
	}

	void Actor::setBaseSpeed() {
		speed = BaseSpeed;
	}

	void Actor::collisionCheck(Map *level, float *time, RenderWindow& window) {

		float step = speed * (*time);
		RectangleShape HeroInNextFrame(body.getSize());
		vector <vector<gameObject>> *StationaryObjects = level->getStationaryObjects();
		vector <MapSegmentSize> *Segments = level->getSegments();
		int SegmentNum = level->getSegment(&this->body.getPosition());;

		if (SegmentNum == -1) {
			this->body.setPosition(50, 50);
			return;
		}

		HeroInNextFrame.setPosition(body.getPosition());


		if (leftPressed) 
			HeroInNextFrame.move(-step, 0);

		if (rightPressed) 
			HeroInNextFrame.move(step, 0);

		if (upPressed) 
			HeroInNextFrame.move(0, -step);

		if (downPressed) 
			HeroInNextFrame.move(0, step);


		float  ActorRightPoint = body.getGlobalBounds().left + body.getGlobalBounds().width;
		float  ActorBottomPoint = body.getGlobalBounds().top + body.getGlobalBounds().height;
		float  ActortLeftPoint = body.getGlobalBounds().left;
		float  ActorTopPoint = body.getGlobalBounds().top;
		

		
		for (int i = 0; i < (*StationaryObjects)[SegmentNum].size(); i++) {
			RectangleShape ObjectInMap = (*StationaryObjects)[SegmentNum][i].getLowSide();

			float  ObjectRightPoint = ObjectInMap.getGlobalBounds().left + ObjectInMap.getGlobalBounds().width;
			float  ObjectBottomPoint = ObjectInMap.getGlobalBounds().top + ObjectInMap.getGlobalBounds().height;
			float  ObjectLeftPoint = ObjectInMap.getGlobalBounds().left;
			float  ObjectTopPoint = ObjectInMap.getGlobalBounds().top;


			if (HeroInNextFrame.getGlobalBounds().intersects(ObjectInMap.getGlobalBounds())) {

				if (ActortLeftPoint > ObjectRightPoint) {
					if (leftPressed) {
						this->stopLeft();
					}
				}

				if (ActorRightPoint < ObjectLeftPoint) {
					if (rightPressed) {
						this->stopRight();
					}
				}

				if (ActorTopPoint > ObjectBottomPoint) {
					if (upPressed) {
						this->stopUp();
					}
				}

				if (ActorBottomPoint < ObjectTopPoint) {
					if (downPressed) {
						this->stopDown();
					}
				}

			}

			
		}
	}

	//илюшина функция
	void Actor::interactionCheck(Map *level, float *time, RenderWindow& window)
	{
		vector <vector<gameObject>> *StationaryObjects = level->getStationaryObjects();
		vector <MapSegmentSize> *Segments = level->getSegments();
		int SegmentNum = level->getSegment(&this->body.getPosition());

		if (SegmentNum == -1) {
			this->body.setPosition(50, 50);
			return;
		}

		msg_displayed = false;
		for (int i = 0; i < (*StationaryObjects)[SegmentNum].size(); i++) {

			if ((*StationaryObjects)[SegmentNum][i].getType() != humantype)
				continue;

			RectangleShape ObjectInMap = (*StationaryObjects)[SegmentNum][i].getBody();

			RectangleShape interactionZone;

			Vector2f ObjectGBPosition(ObjectInMap.getGlobalBounds().left, ObjectInMap.getGlobalBounds().top);
			Vector2f ObjectGBSize(ObjectInMap.getGlobalBounds().width, ObjectInMap.getGlobalBounds().height);
			
			interactionZone.setSize(ObjectGBSize * 1.5f);
			interactionZone.setPosition(ObjectGBPosition - ObjectGBSize / 4.f);
			interactionZone.setFillColor(Color(255, 255, 255, 200));
			window.draw(interactionZone);
			bool isCollision = this->body.getGlobalBounds().intersects(interactionZone.getGlobalBounds());

			if (isCollision and !msg_displayed)
			{

				if (interaction_flag)
				{
					if (ObjectInMap.getFillColor() == Color::Green)
						(*StationaryObjects)[SegmentNum][i].setColor(Color(Color::Black));
					else
						(*StationaryObjects)[SegmentNum][i].setColor(Color(Color::Green));
					interaction_flag = false;
				}
				else
				{
					RectangleShape msg;
					msg.setSize(Vector2f(this->getBody().getSize().x, 5));
					msg.setPosition(Vector2f(this->getBody().getPosition() + Vector2f(0, -10)));
					msg.setFillColor(Color(Color::White));
					window.draw(msg);
					msg_displayed = true;
				}

			}
		}
	}

	//моя функция. По моему msg_displayed не нужен 
	/*void Actor::interactionOrDialogue(Map *level, float *time, RenderWindow& window, Font& font) {
		
		//получаем список объектов уровня
		vector <vector<gameObject>> *StationaryObjects = level->getStationaryObjects();
		
		//определяем сегмент карты, где располагается игрок
		int SegmentNum = level->getSegment(&body.getPosition());

		if (SegmentNum == -1) {
			this->body.setPosition(50, 50);
			return;
		}

		//суть: 
		//пробегаемся по всем предметам на карте и, если с ним можно взаимодействовать,
		//создаем вокруг него зону, которая будет сигнализировать о возможности ваимодействия,
		//выводя текст над предметом. Далее, если мы хотим с ним взаимодействовать, то при нажатии Е
		//происходит какое то действие
		//баг: в случае, когда два объекта, с которыми можно взаимодействовать, соприкасаются друг с другом,
		//взаимодействие возможно только с одним. Из за чего это происходит я не знаю
		for (int i = 0; i < (*StationaryObjects)[SegmentNum].size(); i++) {

			int Objecttype = (*StationaryObjects)[SegmentNum][i].getType();

			if ((Objecttype != humantype) && (Objecttype != itemtype))
				continue;

			RectangleShape ObjectInMap = (*StationaryObjects)[SegmentNum][i].getBody();


			Vector2f ObjectGBPosition(ObjectInMap.getGlobalBounds().left, ObjectInMap.getGlobalBounds().top);
			Vector2f ObjectGBSize(ObjectInMap.getGlobalBounds().width, ObjectInMap.getGlobalBounds().height);
			RectangleShape interactionZone;

			interactionZone.setSize(ObjectGBSize * 1.5f);
			interactionZone.setPosition(ObjectGBPosition - ObjectGBSize / 4.f);
			//nteractionZone.setFillColor(Color(255, 255, 255, 200));
			//window.draw(interactionZone);

			bool isCollision = this->body.getGlobalBounds().intersects(interactionZone.getGlobalBounds());

			if (isCollision) {

				
				RectangleShape msg;
				msg.setSize(Vector2f(ObjectInMap.getSize().x / 2, 5));
				msg.setPosition(Vector2f(ObjectInMap.getPosition() + Vector2f(ObjectInMap.getSize().x / 4, -10)));
				msg.setFillColor(Color(Color::White));

				Text hint;
				hint.setFont(font);
				String str = "Enter E for interaction";
				hint.setString(String::fromUtf8(str.begin(), str.end()));
				hint.setCharacterSize(5);
				hint.setFillColor(Color(0, 0, 0));
				hint.setPosition(msg.getPosition() + Vector2f(1.f, 1.f));
				
				window.draw(msg);
				window.draw(hint);
				msg_displayed = true;
				

				if (interaction_flag) {
					if (Objecttype == itemtype) {
						if (ObjectInMap.getFillColor() == Color::Green)
							(*StationaryObjects)[SegmentNum][i].setColor(Color(Color::Black));
						else
							(*StationaryObjects)[SegmentNum][i].setColor(Color(Color::Green));
						interaction_flag = false;
					}
					else {
						isDialogNow = true;
						currentDialogue = new Dialog("Dialogs/Dialog1.txt");
					}
				}
			}

		}
	}*/


	void Actor::setPosition(float x, float y) {
		body.setPosition(x, y);
	}