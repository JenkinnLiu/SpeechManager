#include<iostream>
#include "speechManager.h";
using namespace std;

int main() {
	SpeechManager sm;
	/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
		cout << "ѡ�ֱ�ţ�" << it->first
			<< " ������" << it->second.m_Name
			<< " �ɼ���" << it->second.m_Score[0] << endl;
	}*/
	int choice = 0;
	while (true) {
		sm.Show_Menu();
		cout << "����������ѡ��" << endl;
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