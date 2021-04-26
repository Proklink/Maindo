
#include "Dialog.h"


Dialog::Dialog(string dialogName, Vector2f& cameraPos, Font& font) {
	
	ifstream in(dialogName);
	string line;

	if (in.is_open())
	{
		while (getline(in, line))
		{
			
			Speeches.push(line);
		}
	}
	else
		cout << "Openning the file is failed\n";

	in.close();     // закрываем файл

	DialogsBackgr.setSize(Vector2f(CAMERA_SIZE_X / 1.25, 70));
	DialogsBackgr.setPosition(cameraPos.x - (float)(CAMERA_SIZE_X / 2.5), cameraPos.y + 80);
	DialogsBackgr.setFillColor(Color(30, 30, 30, 240));
	DialogsBackgr.setOutlineThickness(1);
	DialogsBackgr.setOutlineColor(Color(0, 52, 134));

	SpeakerNameBackgr.setSize(Vector2f(100, 20));
	SpeakerNameBackgr.setPosition(Vector2f(DialogsBackgr.getPosition().x + DialogsBackgr.getSize().x / 4 - SpeakerNameBackgr.getSize().x / 2, DialogsBackgr.getPosition().y - (SpeakerNameBackgr.getSize().y * 3) / 4));
	SpeakerNameBackgr.setFillColor(Color(30, 30, 30, 240));
	SpeakerNameBackgr.setOutlineThickness(1);
	SpeakerNameBackgr.setOutlineColor(Color(0, 52, 134));

	speech.setFont(font);
	speech.setCharacterSize(8);
	speech.setFillColor(Color::White);
	

	SpeakerName.setFont(font);
	SpeakerName.setCharacterSize(8);
	SpeakerName.setFillColor(Color::White);
	
	


}

vector<String> *SplitLine(String *line) {

	vector<String> *partsOfSpeech = new vector<String>();

	size_t space = line->find(' ');
	int i = 0;
	while (space != -1) {
		partsOfSpeech->push_back(line->substring(i, (space)-i) + " ");
		i = space;
		space = line->find(' ', space + 1);
	}
	if (i == 0)			//если вся реплика - это одно слово, то цикл не отработает и записать понадобится строку с нулевого
		partsOfSpeech->push_back(line->substring(i, line->getSize() - i)); //символа, те i = 0
	else
		partsOfSpeech->push_back(line->substring(i + 1, line->getSize() - (i + 1))); //Если реплика больше одного слова, то i будет ненулевым, те будет указывать на пробел перед последним словом

	return partsOfSpeech;
}

void Dialog::SplitSpeech(int lastLetterInLine, vector<String> *partsOfSpeech) {

	queue<string> temporaryQ;
	String temp = "";

	for (int i = lastLetterInLine; i < (*partsOfSpeech).size(); i++)
		temp += (*partsOfSpeech)[i];
	temporaryQ.push(temp);

	for (int i = 0; i < Speeches.size(); i++) {
		temporaryQ.push(Speeches.front());
		Speeches.pop();
	}
	Speeches = temporaryQ;

}

bool Dialog::update(bool isInteraction) {
	

	//Максимальное кол-во символов текста в длинну для моей рамки - 64
	//высота текста  - 9п при шрифте 8
	//максимальное кол-во строчек  текста  - 
	if (isInteraction) {
		if (!Speeches.empty()) {
			
			//получаем из очереди реплики, переводим в другую кодировку и разбиваем на имена и речь
			String line = String::fromUtf8(Speeches.front().begin(), Speeches.front().end());
			size_t delim = line.find(":");
			String name = line.substring(0, delim);
			String sentence = line.substring(delim + 2, line.getSize() - delim - 2);//если здесь вылетает исключение, то значит в файле с диалогом, после конца последней реплики ещё что то существует. Нужно почистить "пустые строки"

			
			int d = sentence.getSize();
			

			//разбиваем речь на слова
			vector<String> *partsOfSpeech = SplitLine(&sentence);


			//формируем строку, которую выведем на экран
			//будем вести счет символов для каждой строки в прямоугольнике речи
			//чтобы не выйти за ограничение в 64 сивола в строке и 4 строки
			String splitedString = "";
			int count = 0;
			int NumberOfCharacters = 0;
			int lastLetterInLine = 0;

			for (int i = 0; i < partsOfSpeech->size(); i++) {
				if ((NumberOfCharacters + (*partsOfSpeech)[i].getSize()) < 65) {//если новое слово помещается в строку
					splitedString += (*partsOfSpeech)[i];						//добавляем его туда
					NumberOfCharacters += (*partsOfSpeech)[i].getSize();		//и обновляем количество символом в строке
				}
				else {															
					if (count == 3) {											//одновременно считаем не выходим ли мы за лимит строк
						lastLetterInLine = i;									//если вышли, то запоминаем  индекс слова, которое не влезло
						break;
					}
					splitedString.erase(splitedString.getSize() - 1);			//если новое слово не поместилось в строку
					splitedString += "\n";										//рубим строку до нового слова
					count++;													//считаем сколько раз разрубилистроку
					NumberOfCharacters = (*partsOfSpeech)[i].getSize();			//обновляем число символов в новой строке
					splitedString += (*partsOfSpeech)[i];						//добавляем слово в новую строку
				}
				
			}

		
			if (lastLetterInLine > 0) {							//если были слова в строке, которые не влезли 
																//в лимит строк, то из остатком слов формируем новую
				SplitSpeech(lastLetterInLine, partsOfSpeech);	//строку и вставляем в очередь на первое место

			}

			
			//взависимости от того, сколько строк надо вывести, устанавливаем позицию теста речи
			if (count == 0) 
				speech.setPosition(DialogsBackgr.getPosition() + Vector2f(30.f, 30.f));
			else if (count == 1)
				speech.setPosition(DialogsBackgr.getPosition() + Vector2f(30.f, 25.f));
			else if (count == 2)
				speech.setPosition(DialogsBackgr.getPosition() + Vector2f(30.f, 20.f));
			else if (count == 3)
				speech.setPosition(DialogsBackgr.getPosition() + Vector2f(30.f, 12.f));


			//if (speech.getGlobalBounds().left + speech.getGlobalBounds().width > DialogsBackgr.getPosition().x + DialogsBackgr.getSize().x - 30) {
			//	int split = sentence.getSize() / 2;
			//	//cout << sentence.getSize() << endl;
			//	for (int i = split; i < (sentence.getSize() * 3) / 4; i++)
			//		if (sentence[i] == ' ') {
			//			sentence.insert(i, "\n");
			//			break;
			//		}
			//	speech.setString(sentence);
			//}
		
			
			//sentence = (String)splitedString;

			SpeakerName.setString(name);
			speech.setString(splitedString);

			//взависимости от размеров имени говорящего, устанавливаем позицию текста имени
			float Xpos = SpeakerNameBackgr.getPosition().x + SpeakerNameBackgr.getSize().x / 2 - SpeakerName.getGlobalBounds().width / 2;
			float Ypos = SpeakerNameBackgr.getPosition().y + SpeakerNameBackgr.getSize().y / 2 - SpeakerName.getGlobalBounds().height / 2;
			SpeakerName.setPosition(Vector2f(Xpos, Ypos));
			
			Speeches.pop();

		}
		else
			return 0;
	}

	return 1;

}

void Dialog::draw(RenderWindow& window) {

	
	window.draw(DialogsBackgr);
	window.draw(SpeakerNameBackgr);
	window.draw(speech); 
	window.draw(SpeakerName);

}