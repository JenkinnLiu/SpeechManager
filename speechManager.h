#pragma once
#include "speaker.h"
#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<deque>
#include<numeric>
#include<fstream>
#include<cstdlib>
#include<ctime>
using namespace std;
class SpeechManager {
public:
	vector<int> v1;//12人容器

	vector<int> v2;//6人容器

	vector<int> vVictory;//3人容器

	map<int, Speaker> m_Speaker;//编号以及对应的具体选手

	int m_Index;//比赛轮数


	SpeechManager();

	~SpeechManager();

	void Show_Menu();

	void initSpeech();

	void createSpeaker();
	
	void startSpeech();

	void speechDraw();

	void speechContest();

	void showScore();

	void saveRecord();

	void loadRecord();

	bool fileIsEmpty;

	map<int, vector<string>> m_Record;//往届记录

	void showRecord();

	void clearRecord();

	void exitSystem();

	
};