#include "Map.h"


using namespace std;


Map::Map( ) {
	Image  anyaImg;
	anyaImg.loadFromFile("Images/anya.PNG");
	anyaImg.createMaskFromColor(Color::White);
	npc1Tex = new Texture();
	npc1Tex->loadFromImage(anyaImg);


	FlowerTex = new Texture();
	FlowerTex->loadFromFile("Images/flower.png");
}

Map::Map(gameObject *k) : Map() {
	kevin = k;
}


//инициализатор для дебага(в релизе его не будет(наверно))
void Map::PrimaryInit() {

	//создаем объект прямоугольной фигуры и в конструктор кладём размер в виде пары значений по x и по y: Vector2f(x, y)
	RectangleShape mapObject2(Vector2f(50, 50));
	mapObject2.setPosition(200, 200);									//утсанавливаем позицию прямоугольника
	mapObject2.setFillColor(Color(0, 0, 0));							//устанавливаем цвет пряугольника
	mapObject2.setOutlineThickness(4);									//толщина контура
	mapObject2.setOutlineColor(Color(14, 0, 255));						//цвет контура
	gameObject gameObject2(mapObject2, ObjectType::itemtype);			//всё помещаем в внутриигровой объект
	

	RectangleShape mapObject1;
	mapObject1.setPosition(200, 250);
	mapObject1.setSize(Vector2f(50, 50));
	mapObject1.setFillColor(Color(0, 0, 0));
	mapObject1.setOutlineThickness(4);
	mapObject1.setOutlineColor(Color(14, 0, 255));
	gameObject gameObject1(mapObject1, ObjectType::itemtype);

	RectangleShape mapObject7;
	mapObject7.setPosition(600, 100);
	mapObject7.setSize(Vector2f(33, 80));
	//mapObject7.setFillColor(Color(0, 0, 0, 0));
	
	mapObject7.setTexture(npc1Tex);
	gameObject npc1(mapObject7, ObjectType::humantype, npc1Tex);

	RectangleShape mapObject8;
	mapObject8.setPosition(382, 30);//ATENTION
	mapObject8.setSize(Vector2f(82, 111));
	mapObject8.setFillColor(Color(255, 255, 255, 0));

	gameObject npc2(mapObject8, ObjectType::humantype, NULL);

	RectangleShape mapObject3(Vector2f(10, 10));
	mapObject3.setPosition(800, 200);
	mapObject3.setFillColor(Color(0, 0, 0, 0));
	mapObject3.setOutlineThickness(4);
	mapObject3.setOutlineColor(Color(0, 255, 0));
	gameObject gameObject3(mapObject3, ObjectType::itemtype);

	
	Vector2f size11(28, 32);
	Vector2f pos11(400, 400);
	gameObject gameObject11(size11, pos11, ObjectType::flowertype, FlowerTex);

	Vector2f size12(28, 32);
	Vector2f pos12(600, 400);
	gameObject gameObject12(size12, pos12, ObjectType::flowertype, FlowerTex);

	RectangleShape mapObject4(Vector2f(10, 10));
	mapObject4.setPosition(820, 200);
	mapObject4.setFillColor(Color(0, 0, 0, 0));
	mapObject4.setOutlineThickness(4);
	mapObject4.setOutlineColor(Color(0, 255, 0));
	gameObject gameObject4(mapObject4, ObjectType::itemtype);

	RectangleShape mapObject5(Vector2f(10, 10));
	mapObject5.setPosition(820, 230);
	mapObject5.setFillColor(Color(0, 0, 0, 0));
	mapObject5.setOutlineThickness(4);
	mapObject5.setOutlineColor(Color(0, 255, 0));
	gameObject gameObject5(mapObject5, ObjectType::itemtype);

	RectangleShape mapLine1(Vector2f(WINDOW_SIZE_X, 3));
	mapLine1.setPosition(Vector2f(1, 1));
	mapLine1.setFillColor(Color(255, 0, 0));
	gameObject gameObject6(mapLine1, ObjectType::walltype);

	RectangleShape mapLine2(Vector2f(3, WINDOW_SIZE_Y));
	mapLine2.setPosition(Vector2f(1, 1));
	mapLine2.setFillColor(Color(0, 255, 0));
	//mapLine2.rotate(180);
	gameObject gameObject7(mapLine2, ObjectType::walltype);

	RectangleShape mapLine3(Vector2f(WINDOW_SIZE_X, 3));
	mapLine3.setPosition(Vector2f(1, WINDOW_SIZE_Y - 3));
	mapLine3.setFillColor(Color(0, 0, 255));
	gameObject gameObject8(mapLine3, ObjectType::walltype);

	RectangleShape mapLine4(Vector2f(3, WINDOW_SIZE_Y));
	mapLine4.setPosition(Vector2f(WINDOW_SIZE_X - 3, 1));
	mapLine4.setFillColor(Color(255, 0, 255));
	mapLine2.rotate(-90);
	gameObject gameObject9(mapLine4, ObjectType::walltype);

	//заполняем объектами контенеры карты
	StationaryObjects.push_back({ gameObject1, gameObject2, gameObject6, gameObject7, gameObject8, gameObject9, npc1, npc2, gameObject11, gameObject12 });
	MapSegmentSize segm1 = { 0, 640, 0, 720 };
	StationaryObjects.push_back({ gameObject3, gameObject4, gameObject5, gameObject6, gameObject7, gameObject8, gameObject9 });
	MapSegmentSize segm2 = { 640, 1280, 0, 720 };
	Segments.push_back(segm1);
	Segments.push_back(segm2);

}

//void Map::Create_New_Set_Objects_On_Level(vector<gameObject> &objects) {
//
//	StationaryObjects.clear();
//
//	for (int i = 0; i < objects.size(); i++) {
//		if (objects[i].getType() == ObjectType::itemtype) {
//
//		}
//	}
//}

bool Map::Add_Object_On_Level(gameObject &object, int segm) {

	if ((segm < 0) || (segm > StationaryObjects.size()))
		return 0;

	gameObject CopyObject = object;

	StationaryObjects[segm].push_back(CopyObject);

	return 1;

}

bool Map::Add_Object_On_Level(gameObject &object) {

	int segm = getSegment(&kevin->getBody().getPosition());

	return Add_Object_On_Level(object, segm);

}

int listenSocket() {

	for () {

		//слушать

	}

}

int killThread( ) {

	

}

vector <vector<gameObject>> *Map::getStationaryObjects() {
	return &StationaryObjects;
}

vector <MapSegmentSize> *Map::getSegments() {
	return &Segments;
}

bool Map::Clear_NonWallObjects(int segm) {
	if ((segm < 0) || (segm > StationaryObjects.size()))
		return 0;

	for (int i = 0; i < StationaryObjects[segm].size(); i++) {
		if (StationaryObjects[segm][i].getType() != walltype) {
			StationaryObjects[segm].erase(StationaryObjects[segm].begin() + i);
			i--;
		}
	}
	return 1;
}


//отрисовываем все объекты на карте
void Map::drawObjects(RenderWindow& window) {
	for (int i = 0; i < StationaryObjects.size(); i++) 
		for (int j = 0; j < StationaryObjects[i].size(); j++)
			window.draw(StationaryObjects[i][j].getBody());

	for (int i = 0; i < projectiles.size(); i++)
		window.draw(projectiles[i].getBody());
}

//суть:
//пробегаемся по всем пулькам на карте, которые мы при нажатии на пробел добавляли в вектор
//затем вычисляем пройденное ими расстояние и сравниваем с пределом для каждого типа оружия
//если расстояние превышено - удаляем пульку из вектора, чтобы её не отрисовывать в конце каждого кадра
//Дальше вычисляем сегмент карты, в котором находится пулька
//итерируемся по всем объектам в данном сегменте и проверяем пересечение пульки и объекта на карте
//если пересечение есть, пульку сразу удаляем; если ещё и объект представляет "убиваемый тип", то удаляем и объект
//чтобы его тоже не отрисовывать после каждого кадра
void Map::checkCollisionProjectiles() {
	
	//перенести в Engine

	for (int i = 0; i < projectiles.size(); i++)
	{
		float Dx = projectiles[i].getBody().getPosition().x - projectiles[i].startPosition.x;
		float Dy = projectiles[i].getBody().getPosition().y - projectiles[i].startPosition.y;
		bool was_erased = false;


		if (sqrt(pow(Dx, 2) + pow(Dy, 2)) < projectiles[i].range)
		{
			//данное выражение позволит знать в каком сегменте карты находится пулька на каждом кадре
			int CurSegm = getSegment(&projectiles[i].getBody().getPosition());


			for (int j = 0; j < StationaryObjects[CurSegm].size(); j++)
			{
				FloatRect ProjectileBounds = projectiles[i].getBody().getGlobalBounds();
				FloatRect ObjectBounds = StationaryObjects[CurSegm][j].getBody().getGlobalBounds();

				if (ProjectileBounds.intersects(ObjectBounds) )
				{
					projectiles.erase(projectiles.begin() + i);
					i--;
					int object_type = StationaryObjects[CurSegm][j].getType();

					if ((object_type == ObjectType::humantype) ||(object_type == ObjectType::robottype))
					{
						StationaryObjects[CurSegm].erase(StationaryObjects[CurSegm].begin() + j);
					}
					was_erased = true;
					break;
				}
			}
			/*if (was_erased)
			{
				continue;
			}*/
		}
		else
		{
       		projectiles.erase(projectiles.begin() + i);
			i--;
		}


	}
}


//суть:
//возвращает сегмент карты, в котором находится объект gO
//если координаты данного объекта не соответсвуют границам ни одного из существующих сегментов,
//то возвращаем -1 как знак неккоректных координат у объекта
int Map::getSegment(const Vector2f *gOPos) {
	for (int i = 0; i < Segments.size(); i++) {
		float xActorPos = gOPos->x;
		float yActorPos = gOPos->y;

		//возможны проблемы с включением краёв в сегменты
		if ((xActorPos > Segments[i].Xmin) && (xActorPos <= Segments[i].Xmax))
			if ((yActorPos > Segments[i].Ymin) && (yActorPos <= Segments[i].Ymax)) 
				return i;
	}
	return -1;
}

//продвигаем пульки дальше по карте
void Map::updateProjectailes(float *time) {

	for (int i = 0; i < projectiles.size(); i++)
		projectiles[i].update(time);
}