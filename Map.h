#pragma once
#include <iostream>
#include <vector>
#include  <SFML/Graphics.hpp>

#include "Projectile.h"


using namespace std;

#define WINDOW_SIZE_X 1280
#define WINDOW_SIZE_Y 720

#ifndef MAP_H
#define MAP_H

struct MapSegmentSize {
	float Xmin, Xmax;
	float Ymin, Ymax;
};

class Map {

private:
	vector <vector<gameObject>> StationaryObjects;
	vector <MapSegmentSize> Segments;

	Texture *npc1Tex;
	Texture *FlowerTex;

	gameObject *kevin;
	
public:

	Map(gameObject *k);

	vector <Projectile> projectiles;

	Map( );

	void PrimaryInit();

	void Create_New_Set_Objects_On_Level(vector<gameObject> &objects);

	bool Add_Object_On_Level(gameObject &object, int segm);

	bool Add_Object_On_Level(gameObject &object);

	bool Clear_NonWallObjects(int segm);

	void LoadFromFile(vector <vector<gameObject>> *StationaryObjects, vector <MapSegmentSize> *Segments);

	vector <vector<gameObject>> *getStationaryObjects();

	vector <MapSegmentSize> *getSegments();

	void drawObjects(RenderWindow& window);

	void checkCollisionProjectiles_v2();

	int getSegment(const Vector2f *gOPos);

	void checkCollisionProjectiles();

	void updateProjectailes(float *time);
};

#endif MAP_H