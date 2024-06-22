#include "speechManager.h"



SpeechManager::SpeechManager() {
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
}

SpeechManager::~SpeechManager() {
}

void SpeechManager::Show_Menu() {
	cout << "********************************************" << endl;
	cout << "*************  欢迎参加演讲比赛 ************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void SpeechManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	this->m_Index = 1;//初始化比赛1轮数
	this->m_Record.clear();
}

void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2; i++) sp.m_Score[i] = 0;//初始化成绩

		this->v1.push_back(i + 10001);

		this->m_Speaker.insert({ i + 10001, sp });
	}
}

void SpeechManager::startSpeech() {
	//第一轮比赛
	//1、抽签
	this->speechDraw();
	//2、比赛
	this->speechContest();
	//3、显示晋级结果
	this->showScore();
	//第二轮比赛
	this->m_Index++;
	//1、抽签
	this->speechDraw();
	//2、比赛
	this->speechContest();
	//3、显示最终结果
	this->showScore();
	//4、保存分数
	this->saveRecord();

	this->initSpeech();

	this->createSpeaker();

	this->loadRecord();

	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::speechDraw() {
	cout << "第 << " << this->m_Index << " >> 轮比赛选手正在抽签" << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "抽签后演讲顺序如下:" << endl;
	if (this->m_Index == 1) {//第一轮
		srand((unsigned int)time(NULL));
		random_shuffle(v1.begin(), v1.end());//打乱顺序
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {//第二轮
		random_shuffle(v2.begin(), v2.end());//打乱顺序
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-----------------------------------------------" << endl;
	system("pause");
	cout << endl;
}

void SpeechManager::speechContest() {
	cout << "第 << " << this->m_Index << " >> 轮比赛正式开始" << endl;
	multimap<double, int, greater<int>> groupScore;//临时容器，保存key分数value选手编号
	//这个multimap会按分数自己排序
	int num = 0;//记录人员数，6个为一组

	vector<int> v_Src;//比赛的人员容器
	if (this->m_Index == 1) v_Src = v1;
	else v_Src = v2;

	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;

		deque<double> d;//10个评委给这个演讲者打分
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f; //600 ~ 1000
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());//打分排序
		d.pop_front();//deque是为了方便去掉最高分
		d.pop_back();//去掉最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f);//累加，保留一位浮点数
		double avg = sum / (double)d.size();//求平均分

		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;//填分数
		groupScore.insert({ avg, *it });
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "编号: " << it->second << " 姓名： " 
					<< this->m_Speaker[it->second].m_Name 
					<< " 成绩： " << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			int count = 0;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count ++) {
				if (this->m_Index == 1) {
					v2.push_back((*it).second);
				}
				else {
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "-----------第 << " << this->m_Index << " >> 轮比赛完毕---------" << endl;
	system("pause");
}

void SpeechManager::showScore() {
	cout << "---------第" << this->m_Index << "轮晋级选手信息如下：-----------" << endl;
	vector<int>v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "选手编号：" << *it << " 姓名： " << m_Speaker[*it].m_Name 
			<< " 得分： " << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->Show_Menu();
}

void SpeechManager::saveRecord() {
	ofstream file;
	file.open("speech.csv", ios::out | ios::app);//用输出的方式打开文件
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		file << *it << "," << m_Speaker[*it].m_Score[1] << ",";//只写入决赛成绩,csv用逗号换下一格
	}
	file << endl;//csv的换行
	file.close();
	cout << "记录已经保存" << endl;
	this->fileIsEmpty = false;
}

void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;//试着读取一个字符
	if (ifs.eof()) {
		cout << "文件为空！" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch);//读取的单个字符放回去

	string data;
	int index = 0;
	while (ifs >> data) {//相当于while(cin>> data)
		vector<string> v;
		int pos = -1;
		int start = 0;
		while (true) {
			pos = data.find(",", start);//从0开始查找逗号，返回逗号的下标
			if (pos == string::npos) break;//找不到逗号，返回
			string tmp = data.substr(start, pos - start);//找到逗号，分割，substr(pos, length)
			v.push_back(tmp);
			start = pos + 1;//继续查找下一个
		}
		this->m_Record.insert({ index, v });//插入记录
		index++;
	}
	ifs.close();
}

void SpeechManager::showRecord() {
	if (this->fileIsEmpty) {
		cout << "文件不存在，或记录为空！" << endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); i++) {
			cout << "第" << i + 1 << "届 " <<
				"冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1] << " "
				"亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3] << " "
				"季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5] << endl;
		}
	}
	
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord() {
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//打开模式 ios::trunc 如果存在删除文件并重新创建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化属性
		this->initSpeech();

		//创建选手
		this->createSpeaker();

		//获取往届记录
		this->loadRecord();


		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}

void SpeechManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
