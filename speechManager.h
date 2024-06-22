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
	vector<int> v1;//12������

	vector<int> v2;//6������

	vector<int> vVictory;//3������

	map<int, Speaker> m_Speaker;//����Լ���Ӧ�ľ���ѡ��

	int m_Index;//��������


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

	map<int, vector<string>> m_Record;//�����¼

	void showRecord();

	void clearRecord();

	void exitSystem();

	
};