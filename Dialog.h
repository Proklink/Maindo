#pragma once
#include "gameObject.h"
#include <iostream>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

class Dialog {
private:
	queue<string> Speeches;
	RectangleShape DialogsBackgr;
	RectangleShape SpeakerNameBackgr;
	Text speech;
	Text SpeakerName;

	void SplitSpeech(int lastLetterInLine, vector<String> *partsOfSpeech);

public:

	Dialog(string dialogName, Vector2f& cameraPos, Font& font);


	bool update(bool isInteraction);

	void draw(RenderWindow& window);
};