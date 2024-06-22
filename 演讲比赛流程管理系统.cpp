#include<iostream>
#include "speechManager.h";
using namespace std;

int main() {
	SpeechManager sm;
	int choice = 0;
	while (true) {
		sm.Show_Menu();
		cout << "ÇëÊäÈëÄúµÄÑ¡Ôñ" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 0:
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}