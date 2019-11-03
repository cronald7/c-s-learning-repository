#include<iostream>
#include<iomanip>
#include<string>
#include <cstring> 
using namespace std;

const int num = 5, testdata = 100;//������ʿ���͵�������Ԥ����������ݵ������������պ��޸ġ�
string weaponName[3] = { "sword","bomb","arrow" };
//��Ų�������
int iniElem_Wr[testdata][num] = { 0 }, iniForce_Wr[testdata][num] = { 0 }, arrowForce[testdata] = { 0 };
int lionLoyl[testdata] = { 0 };
int stop;//�Ƿ�����Ӫ��ռ��
class CWarrior; class CDragon; class CNinjia; class CIceman; class CLion; class CWolf;
class CHeadquarter {
	int color;
	string colorName;
	int index = 0;
	int round;
	int site;//��������
	int countEnemy = 0; int record = 0;//record������¼�ִﱾ��Ӫ��enemy������û�иı�
	CWarrior *army[200] = { NULL };
	int warriorCode = 0;
	static int warriorCreatSqueue[2][5];
public:
	int element;
	CWarrior *enemyWr[2] = { NULL };//���ֵĵо�
	CWarrior *wp = NULL;//�ҷ��ճ�������ʿ
	CHeadquarter(int color_, int elem_, int round_, int site_, string colorNm) :color(color_), element(elem_), round(round_), site(site_), colorName(colorNm) {}
	~CHeadquarter();
	friend class CWarrior; friend class CCity; friend class CLion;
	void printCommanSituation(int time);//���������������ʿ��Ϣ���������������
	void produceWr(int time_);//������ʿ
	void pritenemy(int time);//����о����ֵ����
	void pritElem(int time)//�����Ӫ������Ԫ
	{
		cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
		cout << element << " elements in " << colorName << " headquarter" << endl;
	}
};
class CCity {
public:
	int site;
	int element;
	int flag;
	int last_winner = 2;//�ϴ�ս��ʤ������Ӫ��0����죬1��������2��������
	int num_warrior;
	CWarrior *victorWr = NULL;//������ʤ��
	CWarrior *wr[2] = { NULL };//�����е���ʿ
	CCity(int code_, int flag_, int elem_ = 0, int num_ = 0) :site(code_), flag(flag_), element(elem_), num_warrior(num_)
	{
		CWarrior *wr[2] = { NULL };
		victorWr = NULL;
	}
	void elementPlus() { element += 10; victorWr = NULL; }
	void transferElem(CHeadquarter & headquarter, int time, int color = 0);
	void pritWarrior(int time_);
	void shootWr(int time_, CCity *nextCity, int color);
	void bomb(int time);
	friend class CWarrior; friend class CDragon; friend class CNinjia; friend class CIceman; friend class CLion; friend class CWolf;
};
class CWeapon {
	string name;
	int force;
	int useTime = 3;
public:
	CWeapon(string name_, int force_ = 0) :name(name_), force(force_) {}
	friend class CWarrior; friend class CDragon; friend class CNinjia; friend class CIceman; friend class CLion; friend class CWolf;
};
class CWarrior {
public:
	string name;
	int color;
	string colorName;
	int force;
	int element;
	int code;
	int site;//���ڳ��б��
	int tmpElem;//��¼��սǰ������Ԫ������lion
	CWeapon *wp[3] = { NULL };
	CWarrior(string name_, int force_, int elem_, int color_, int code_, int site_, string colorNm) :force(force_), element(elem_), color(color_), code(code_), site(site_), colorName(colorNm)
	{
		name = name_;
	}
	virtual ~CWarrior()
	{
		for (int i = 0; i < 3; i++)
		{
			if (wp[i])
				delete wp[i];
		}
	}
	virtual void attack(CWarrior & enemy, CCity & city, int time);
	virtual void fightback(CWarrior & enemy, CCity & city, int time);
	void rewardElem(CHeadquarter & headquarter)//����Ӫ������ʤ��ʿ
	{
		if (headquarter.element >= 8)
		{
			element += 8;
			headquarter.element -= 8;
		}
		else
		{
			element += headquarter.element;
			headquarter.element = 0;
		}
	}
	virtual void victor(CCity & city, int time);
	virtual void defeat(CCity & city);//˫���������¼�
	virtual void death(CWarrior & enemy, CCity &city, int time);
	virtual void moveforward(CCity *city[], int N, CHeadquarter *headquarter[], int time);//ǰ������
	virtual void shoot(CWarrior *enemy, int time);
	virtual int escape(int time_, CHeadquarter &headquarter, CCity &city) { return 0; }//����lion������
	int calDamage();//ʹ��sword�����
	int estimateForce();//Ԥ���˺�ֵ
	void pritAttack(CWarrior & enemy, CCity & city, int time);
	void pritWeapon(int time);
	virtual void getWeapon(CWarrior & enemy) {}//����wolf�ɻ�����
};
class CDragon :public CWarrior {
	double morale;
public:
	CDragon(string name_, int force_, int elem_, int color_, int code_, double morale_, int arrowforce_, int site_, string colorname) :CWarrior(name_, force_, elem_, color_, code_, site_, colorname)
	{
		morale = morale_;
		switch (code % 3)
		{
		case 0:if ((force / 5) != 0) wp[0] = new CWeapon("sword", force / 5); break;
		case 1:wp[1] = new CWeapon("bomb"); break;
		case 2:wp[2] = new CWeapon("arrow", arrowforce_); break;
		}
	}
	void attack(CWarrior & enemy, CCity & city, int time);
	void fightback(CWarrior & enemy, CCity & city, int time);
	void defeat(CCity & city) { city.last_winner = 2; };
	void victor(CCity & city, int time);
	void pritYell(CCity & city, int time);
};
class CNinjia :public CWarrior {
public:
	CNinjia(string name_, int force_, int elem_, int color_, int code_, int arrowforce_, int site_, string colorname) :CWarrior(name_, force_, elem_, color_, code_, site_, colorname)
	{
		switch (code % 3)
		{
		case 0: {if ((force / 5) != 0) wp[0] = new CWeapon("sword", force / 5); wp[1] = new CWeapon("bomb"); break; }
		case 1: {wp[1] = new CWeapon("bomb"); wp[2] = new CWeapon("arrow", arrowforce_); break; }
		case 2: {wp[2] = new CWeapon("arrow", arrowforce_); if (force / 5 != 0) wp[0] = new CWeapon("sword", force / 5);  break; }
		}
	}
	void fightback(CWarrior & enemy, CCity & city, int time)
	{
		defeat(city);
		enemy.defeat(city);
	}
};
class CIceman :public CWarrior {
	int countStep = 0;
public:
	CIceman(string name_, int force_, int elem_, int color_, int code_, int arrowforce_, int site_, string colorname) :CWarrior(name_, force_, elem_, color_, code_, site_, colorname)
	{
		switch (code % 3)
		{
		case 0:if ((force / 5) != 0) wp[0] = new CWeapon("sword", force / 5); break;
		case 1:wp[1] = new CWeapon("bomb"); break;
		case 2:wp[2] = new CWeapon("arrow", arrowforce_); break;
		}
	}
	void moveforward(CCity *city[], int N, CHeadquarter *headquarter[], int time);
};
class CLion :public CWarrior {
	int loyalty;
	int K;//ÿ���½����ҳ�
public:
	CLion(string name_, int force_, int elem_, int color_, int code_, int arrowforce_, int loyalty_, int K_, int site_, string colorname) :CWarrior(name_, force_, elem_, color_, code_, site_, colorname)
	{
		loyalty = loyalty_;
		K = K_;
	}
	void attack(CWarrior & enemy, CCity & city, int time);
	void fightback(CWarrior & enemy, CCity & city, int time);
	void death(CWarrior & enemy, CCity & city, int time);
	int escape(int time_, CHeadquarter &headquarter, CCity & city);
};
class CWolf :public CWarrior {
public:
	CWolf(string name_, int force_, int elem_, int color_, int code_, int arrowforce_, int site_, string colorname) :CWarrior(name_, force_, elem_, color_, code_, site_, colorname) {}
	void getWeapon(CWarrior & enemy);
};
CHeadquarter::~CHeadquarter()
{
	for (int i = 0; i < warriorCode; i++)
		if (army[i])
			delete army[i];
}
void CHeadquarter::printCommanSituation(int time)
{
	cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
	cout << colorName << " " << army[warriorCode]->name << " " << warriorCode + 1 << " born" << endl;
}
void CHeadquarter::produceWr(int time_)
{
	switch (warriorCreatSqueue[color][index])
	{
	case 0:
	{
		if (iniElem_Wr[round][0] <= element)
		{
			element -= iniElem_Wr[round][0];
			army[warriorCode] = new CDragon("dragon", iniForce_Wr[round][0], iniElem_Wr[round][0], color, warriorCode + 1, double(element) / iniElem_Wr[round][0], arrowForce[round], site, colorName);
			wp = army[warriorCode];
			printCommanSituation(time_);
			cout << "Its morale is " << setiosflags(ios::fixed) << setprecision(2) << double(element) / iniElem_Wr[round][0] << endl;
			warriorCode++; index++;
			if (index == 5) index = 0;
		}
		break;
	}
	case 1:
	{
		if (iniElem_Wr[round][1] <= element)
		{
			element -= iniElem_Wr[round][1];
			army[warriorCode] = new CNinjia("ninja", iniForce_Wr[round][1], iniElem_Wr[round][1], color, warriorCode + 1, arrowForce[round], site, colorName);
			wp = army[warriorCode];
			printCommanSituation(time_);
			warriorCode++; index++;
			if (index == 5) index = 0;
		}
		break;
	}
	case 2:
	{
		if (iniElem_Wr[round][2] <= element)
		{
			element -= iniElem_Wr[round][2];
			army[warriorCode] = new CIceman("iceman", iniForce_Wr[round][2], iniElem_Wr[round][2], color, warriorCode + 1, arrowForce[round], site, colorName);
			wp = army[warriorCode];
			printCommanSituation(time_);
			warriorCode++; index++;
			if (index == 5) index = 0;
		}
		break;
	}
	case 3:
	{
		if (iniElem_Wr[round][3] <= element)
		{
			element -= iniElem_Wr[round][3];
			army[warriorCode] = new CLion("lion", iniForce_Wr[round][3], iniElem_Wr[round][3], color, warriorCode + 1, arrowForce[round], element, lionLoyl[round], site, colorName);
			wp = army[warriorCode];
			printCommanSituation(time_);
			cout << "Its loyalty is " << element << endl;
			warriorCode++; index++;
			if (index == 5) index = 0;
		}
		break;
	}
	case 4:
	{
		if (iniElem_Wr[round][4] <= element)
		{
			element -= iniElem_Wr[round][4];
			army[warriorCode] = new CWolf("wolf", iniForce_Wr[round][4], iniElem_Wr[round][4], color, warriorCode + 1, arrowForce[round], site, colorName);
			wp = army[warriorCode];
			printCommanSituation(time_);
			warriorCode++; index++;
			if (index == 5) index = 0;
		}
		break;
	}
	}
}
void CHeadquarter::pritenemy(int time)
{
	if (record == countEnemy)
		return;
	else
	{
		switch (countEnemy)
		{
		case 0: break;
		case 1: {
			cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
			cout << enemyWr[0]->colorName << " " << enemyWr[0]->name << " " << enemyWr[0]->code << " reached " << colorName << " headquarter with " << enemyWr[0]->element << " elements and force " << enemyWr[0]->force << endl;
			record = 1; break;
		}
		case 2:
		{
			cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
			cout << enemyWr[1]->colorName << " " << enemyWr[1]->name << " " << enemyWr[1]->code << " reached " << colorName << " headquarter with " << enemyWr[1]->element << " elements and force " << enemyWr[1]->force << endl;
			cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
			cout << colorName << " headquarter was taken" << endl;
			stop = 1; record = 2; break;
		}
		}
	}
}
int CHeadquarter::warriorCreatSqueue[2][5] = { { 2,3,4,1,0 },{ 3,0,1,2,4 } };
void CCity::pritWarrior(int time_)
{
	if (wr[0])
	{
		cout << setfill('0') << setw(3) << time_ / 60 << ":" << setfill('0') << setw(2) << time_ % 60 << " ";
		cout << "red " << wr[0]->name << " " << wr[0]->code << " marched to city " << site << " with " << wr[0]->element << " elements and force " << wr[0]->force << endl;
	}
	if (wr[1])
	{
		cout << setfill('0') << setw(3) << time_ / 60 << ":" << setfill('0') << setw(2) << time_ % 60 << " ";
		cout << "blue " << wr[1]->name << " " << wr[1]->code << " marched to city " << site << " with " << wr[1]->element << " elements and force " << wr[1]->force << endl;
	}
}
void CCity::bomb(int time)
{
	if (num_warrior == 2)
	{
		if ((wr[0]->element > 0)&(wr[1]->element > 0))
		{
			for (int i = 0; i < 2; i++)
			{
				if (wr[i]->wp[1] != NULL)
				{
					if ((flag == i) || ((flag == 2)&(site % 2 == 1 - i)))
					{
						if (wr[1 - i]->element > (wr[i]->force + wr[i]->estimateForce()))
						{
							if (wr[1 - i]->name != "ninja")
							{
								if (wr[i]->element <= (wr[1 - i]->force / 2 + wr[1 - i]->estimateForce()))
								{
									cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
									cout << wr[i]->colorName << " " << wr[i]->name << " " << wr[i]->code << " used a bomb and killed " << wr[1 - i]->colorName << " " << wr[1 - i]->name << " " << wr[1 - i]->code << endl;
									wr[1 - i] = NULL; wr[i] = NULL;
									num_warrior = 0;
									break;
								}
							}
						}
					}
					else
					{
						if (wr[i]->element <= (wr[1 - i]->force + wr[1 - i]->estimateForce()))
						{
							cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
							cout << wr[i]->colorName << " " << wr[i]->name << " " << wr[i]->code << " used a bomb and killed " << wr[1 - i]->colorName << " " << wr[1 - i]->name << " " << wr[1 - i]->code << endl;
							wr[1 - i] = NULL; wr[i] = NULL;
							num_warrior = 0; break;
						}
					}
				}
			}
		}
	}
}
void  CCity::shootWr(int time_, CCity *nextCity, int color)
{
	if ((wr[color] != NULL)&(nextCity->wr[1 - color] != NULL))
	{
		wr[color]->shoot(nextCity->wr[1 - color], time_);
	}
}
void CCity::transferElem(CHeadquarter & headquarter, int time, int color)
{
	headquarter.element += element;
	cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
	cout << wr[color]->colorName << " " << wr[color]->name << " " << wr[color]->code << " earned " << element << " elements for his headquarter" << endl;
	element = 0;
}
void CWarrior::attack(CWarrior & enemy, CCity & city, int time)//�������ڳ���
{
	if (enemy.name == "lion")
		enemy.tmpElem = enemy.element;
	enemy.element = enemy.element - force - calDamage();
	pritAttack(enemy, city, time);
	if (enemy.element <= 0)
	{
		getWeapon(enemy);
		enemy.death(*this, city, time);
		city.victorWr = this;//���б��ʤ��
		victor(city, time);
	}
	else
		enemy.fightback(*this, city, time);
}
void CWarrior::fightback(CWarrior & enemy, CCity & city, int time)
{
	enemy.element = enemy.element - force / 2 - calDamage();
	cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
	cout << colorName << " " << name << " " << code << " fought back against " << enemy.colorName << " " << enemy.name << " " << enemy.code << " in city " << city.site << endl;
	if (enemy.element <= 0)
	{
		getWeapon(enemy);
		enemy.death(*this, city, time);
		city.victorWr = this;//���б��ʤ��
		victor(city, time);
	}
	else
	{
		defeat(city);
		enemy.defeat(city);
	}
}
void CWarrior::victor(CCity & city, int time)//�������ڳ���
{
	cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
	cout << colorName << " " << name << " " << code << " earned " << city.element << " elements for his headquarter" << endl;
	if ((city.flag != color)&(city.last_winner == color))
	{
		city.flag = color;
		cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
		cout << colorName << " flag raised in city " << city.site << endl;
	}
	else
		city.last_winner = color;
}
void CWarrior::defeat(CCity & city)
{
	city.last_winner = 2;
}
void CWarrior::death(CWarrior & enemy, CCity &city, int time)
{
	cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
	cout << colorName << " " << name << " " << code << " was killed in city " << city.site << endl;
	city.num_warrior--;
	city.wr[color] = NULL;
}
void CWarrior::moveforward(CCity *city[], int N, CHeadquarter *headquarter[], int time)//����������飬��������
{
	//���������е���ʿ������һ��Ȼ���ƶ�����һ�����У�������һ�����е���ʿ������һ��ͬʱ�������е���ʿָ��ָ���Լ���
	if (color == 0)
	{
		if (site != 0)
		{
			city[site]->num_warrior--;
			city[site]->wr[color] = NULL;
		}
		site++;
		if (site == N + 1)
		{
			headquarter[1]->enemyWr[headquarter[1]->countEnemy] = this;
			headquarter[1]->countEnemy++;
		}
		else
		{
			city[site]->num_warrior++;
			city[site]->wr[color] = this;
		}
	}
	if (color == 1)
	{
		if (site != N + 1)
		{
			city[site]->num_warrior--;
			city[site]->wr[color] = NULL;
		}
		site--;
		if (site == 0)
		{
			headquarter[0]->enemyWr[headquarter[0]->countEnemy] = this;
			headquarter[0]->countEnemy++;
		}
		else
		{
			city[site]->num_warrior++;
			city[site]->wr[color] = this;
		}
	}
}
void CWarrior::shoot(CWarrior *enemy, int time)
{
	if (wp[2])
	{
		enemy->element -= wp[2]->force;
		cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
		if (enemy->element <= 0)
			cout << colorName << " " << name << " " << code << " shot and killed " << enemy->colorName << " " << enemy->name << " " << enemy->code << endl;
		else
			cout << colorName << " " << name << " " << code << " shot" << endl;
		wp[2]->useTime--;
		if (wp[2]->useTime == 0)
		{
			delete wp[2]; wp[2] = NULL;
		}
	}
}
int  CWarrior::calDamage()
{
	if (wp[0])
	{
		int tmp = wp[0]->force;
		wp[0]->force = int(wp[0]->force* 0.8);
		if (wp[0]->force == 0)
		{
			delete wp[0]; wp[0] = NULL;
		}
		return tmp;
	}
	else
		return 0;
}
void CWarrior::pritAttack(CWarrior & enemy, CCity & city, int time)
{
	cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
	cout << colorName << " " << name << " " << code << " attacked " << enemy.colorName << " " << enemy.name << " " << enemy.code << " in city " << city.site << " with " << element << " elements and force " << force << endl;
}
void CWarrior::pritWeapon(int time)
{
	cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
	cout << colorName << " " << name << " " << code << " has ";
	if (wp[2])
	{
		cout << "arrow(" << wp[2]->useTime << ")";
		if (wp[1] || wp[0])
			cout << ",";
		else cout << endl;
	}
	if (wp[1])
	{
		cout << "bomb";
		if (wp[0]) cout << ",";
		else cout << endl;
	}
	if (wp[0])
		cout << "sword(" << wp[0]->force << ")" << endl;
	else if ((wp[0] == NULL)&(wp[1] == NULL)&(wp[2] == NULL))
		cout << "no weapon" << endl;
}
int CWarrior::estimateForce()
{
	if (wp[0])
		return wp[0]->force;
	else return 0;
}
void CDragon::attack(CWarrior & enemy, CCity & city, int time)
{
	if (enemy.name == "lion")
		enemy.tmpElem = enemy.element;
	enemy.element = enemy.element - force - calDamage();
	pritAttack(enemy, city, time);
	if (enemy.element <= 0)
	{
		enemy.death(*this, city, time);
		city.victorWr = this;//���б��ʤ��
		victor(city, time);
	}
	else
	{
		morale -= 0.2;
		enemy.fightback(*this, city, time);
		if ((morale > 0.8)&(element > 0))
			pritYell(city, time);
	}
}
void CDragon::fightback(CWarrior & enemy, CCity & city, int time)
{
	enemy.element = enemy.element - force / 2 - calDamage();
	cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
	cout << colorName << " " << name << " " << code << " fought back against " << enemy.colorName << " " << enemy.name << " " << enemy.code << " in city " << city.site << endl;
	if (enemy.element <= 0)
	{
		enemy.death(*this, city, time);
		city.victorWr = this;//���б��ʤ��
		victor(city, time);
	}
	else
	{
		morale -= 0.2;
		defeat(city);
		enemy.defeat(city);
	}
}
void CDragon::victor(CCity & city, int time)
{
	morale += 0.2;
	if ((city.flag == color) || (city.site % 2 == (1 - color)&(city.flag == 2)))
		if (morale > 0.8)
			pritYell(city, time);
	CWarrior::victor(city, time);
}
void  CDragon::pritYell(CCity & city, int time)
{
	cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
	cout << colorName << " dragon " << code << " yelled in city " << city.site << endl;
}
void CIceman::moveforward(CCity *city[], int N, CHeadquarter *headquarter[], int time)
{
	countStep++;
	if (countStep == 2)
	{
		if (element > 9)
			element -= 9;
		else
			element = 1;
		force += 20;
		countStep = 0;
	}
	CWarrior::moveforward(city, N, headquarter, time);
}
void CLion::attack(CWarrior & enemy, CCity & city, int time)
{
	tmpElem = element;
	if (enemy.name == "lion")
		enemy.tmpElem = enemy.element;
	enemy.element -= force;
	pritAttack(enemy, city, time);
	if (enemy.element <= 0)
	{
		enemy.death(*this, city, time);
		city.victorWr = this;//���б��ʤ��
		victor(city, time);
	}
	else
	{
		loyalty -= K;
		enemy.fightback(*this, city, time);
	}
}
void CLion::fightback(CWarrior & enemy, CCity & city, int time)
{
	enemy.element = enemy.element - force / 2 - calDamage();
	cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
	cout << colorName << " " << name << " " << code << " fought back against " << enemy.colorName << " " << enemy.name << " " << enemy.code << " in city " << city.site << endl;
	if (enemy.element <= 0)
	{
		getWeapon(enemy);
		enemy.death(*this, city, time);
		city.victorWr = this;//���б��ʤ��
		victor(city, time);
	}
	else
	{
		loyalty -= K;
		defeat(city);
		enemy.defeat(city);
	}
}
void CLion::death(CWarrior & enemy, CCity& city, int time)
{
	cout << setfill('0') << setw(3) << time / 60 << ":" << setfill('0') << setw(2) << time % 60 << " ";
	cout << colorName << " lion " << code << " was killed in city " << city.site << endl;
	enemy.element += tmpElem; city.num_warrior--;
	city.wr[color] = NULL;
}
int CLion::escape(int time_, CHeadquarter &headquarter, CCity & city)
{
	if (loyalty <= 0)
	{
		cout << setfill('0') << setw(3) << time_ / 60 << ":" << setfill('0') << setw(2) << time_ % 60 << " ";
		cout << colorName << " lion " << code << " ran away" << endl;
		return 1;
	}
	else return 0;
}
void CWolf::getWeapon(CWarrior & enemy)
{
	for (int i = 0; i < 3; i++)
		if ((wp[i] == NULL)&(enemy.wp[i] != NULL))
			wp[i] = new CWeapon(*enemy.wp[i]);
}
int main()
{
	int test;
	cin >> test;
	int iniElem_Hedqr[testdata] = { 0 }, num_City[testdata] = { 0 }, T[testdata] = { 0 };
	for (int i = 0; i < test; i++)//�������в�������
	{
		cin >> iniElem_Hedqr[i] >> num_City[i] >> arrowForce[i] >> lionLoyl[i] >> T[i];
		for (int j = 0; j < num; j++)
			cin >> iniElem_Wr[i][j];
		for (int j = 0; j < num; j++)
			cin >> iniForce_Wr[i][j];
	}
	for (int i = 0; i < test; i++)//��ʼ��Ϸ
	{
		int time = 0;
		CHeadquarter *headquater[2];
		CCity*city[25] = { NULL };
		headquater[0] = new CHeadquarter(0, iniElem_Hedqr[i], i, 0, "red");
		headquater[1] = new CHeadquarter(1, iniElem_Hedqr[i], i, num_City[i] + 1, "blue");
		for (int j = 1; j < num_City[i] + 1; j++)
		{
			city[j] = new CCity(j, 2);
			city[j]->site = j;
		}
		cout << "Case " << i + 1 << ":" << endl;
		while (stop != 1)
		{
			//������ʿ
			headquater[0]->produceWr(time);
			headquater[1]->produceWr(time);
			time += 5; if (time > T[i]) break;//��5���ӣ������򶫣��ж�lion�Ƿ�����
			if (headquater[0]->wp)
				if (headquater[0]->wp->escape(time, *headquater[0], *city[1]) == 1)
					headquater[0]->wp = NULL;
			for (int j = 1; j < num_City[i] + 1; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					if (city[j]->wr[k])
					{
						if (city[j]->wr[k]->escape(time, *headquater[k], *city[j]) == 1)
						{
							city[j]->wr[k] = NULL;
							city[j]->num_warrior--;
						}
					}
				}
			}
			if (headquater[1]->wp)
				if (headquater[1]->wp->escape(time, *headquater[1], *city[1]) == 1)
					headquater[1]->wp = NULL;
			time += 5; if (time > T[i]) break;//��10���ӣ����ָ�벻Ϊ�գ���ôָ��ָ�����ʿǰ��
			for (int j = num_City[i]; j > 0; j--)
				if (city[j]->wr[0])
					city[j]->wr[0]->moveforward(city, num_City[i], headquater, time);
			if (headquater[0]->wp)
			{
				headquater[0]->wp->moveforward(city, num_City[i], headquater, time);
				headquater[0]->wp = NULL;
			}
			for (int j = 1; j < num_City[i] + 1; j++)
				if (city[j]->wr[1])
					city[j]->wr[1]->moveforward(city, num_City[i], headquater, time);
			if (headquater[1]->wp)
			{
				headquater[1]->wp->moveforward(city, num_City[i], headquater, time);
				headquater[1]->wp = NULL;
			}
			headquater[0]->pritenemy(time);//��ӡ��ʿǰ�������
			for (int j = 1; j < num_City[i] + 1; j++)
				city[j]->pritWarrior(time);
			headquater[1]->pritenemy(time);
			if (stop != 1)
			{
				time += 10; if (time > T[i]) break;//��20���ӣ���������10��element
				for (int j = 1; j < num_City[i] + 1; j++)
					city[j]->elementPlus();
				time += 10; if (time > T[i]) break;//��30���ӣ��������ֻ��һ����ʿ����ô��ʿȡ��element
				for (int j = 1; j < num_City[i] + 1; j++)
				{
					if ((city[j]->wr[0] == NULL)&(city[j]->wr[1] != NULL))
						city[j]->transferElem(*headquater[1], time, 1);
					if ((city[j]->wr[0] != NULL)&(city[j]->wr[1] == NULL))
						city[j]->transferElem(*headquater[0], time, 0);
				}
				time += 5; if (time > T[i]) break;//��35���ӣ��ж��Ƿ���arrow�������ڽ������Ƿ��е���
				if (num_City[i] != 1)
				{
					city[1]->shootWr(time, city[2], 0);
					for (int j = 2; j < num_City[i]; j++)
					{
						city[j]->shootWr(time, city[j + 1], 0);
						city[j]->shootWr(time, city[j - 1], 1);
					}
					city[num_City[i]]->shootWr(time, city[num_City[i] - 1], 1);
				}
				time += 3; if (time > T[i]) break;//��38���ӣ�ӵ��bomb����ʿ�ж�
				for (int j = 1; j < num_City[i] + 1; j++)
					city[j]->bomb(time);
				time += 2; if (time > T[i]) break;//��40���ӣ������򶫣�ս����ʼ
				for (int j = 1; j < num_City[i] + 1; j++)
				{
					if (city[j]->num_warrior == 2)
					{
						if ((city[j]->wr[0]->element > 0)&(city[j]->wr[1]->element > 0))
						{
							if ((city[j]->flag == 0) || ((city[j]->flag == 2)&(city[j]->site % 2 == 1)))
								city[j]->wr[0]->attack(*city[j]->wr[1], *city[j], time);
							else
								city[j]->wr[1]->attack(*city[j]->wr[0], *city[j], time);
						}
						else if ((city[j]->wr[1]->element <= 0)&(city[j]->wr[0]->element <= 0))
						{
							city[j]->victorWr = NULL;
							city[j]->num_warrior = 0;
							city[j]->wr[0] = NULL; city[j]->wr[1] = NULL;
						}
						else if ((city[j]->wr[0]->element > 0)&(city[j]->wr[1]->element <= 0))
						{
							city[j]->wr[0]->getWeapon(*city[j]->wr[1]);
							city[j]->wr[0]->victor(*city[j], time);
							city[j]->victorWr = city[j]->wr[0];
							city[j]->wr[1] = NULL; city[j]->num_warrior--;
						}
						else if ((city[j]->wr[0]->element <= 0)&(city[j]->wr[1]->element > 0))
						{
							city[j]->wr[1]->getWeapon(*city[j]->wr[0]);
							city[j]->victorWr = city[j]->wr[1];
							city[j]->wr[1]->victor(*city[j], time);
							city[j]->wr[0] = NULL; city[j]->num_warrior--;
						}
					}
					else if (city[j]->num_warrior == 1)
					{
						if (city[j]->wr[0])
						{
							if (city[j]->wr[0]->element <= 0)
							{
								city[j]->wr[0] = NULL;
								city[j]->num_warrior = 0;
							}
						}
						else if (city[j]->wr[1])
						{
							if (city[j]->wr[1]->element <= 0)
							{
								city[j]->wr[1] = NULL;
								city[j]->num_warrior = 0;
							}
						}
					}
				}
				for (int j = 1; j < num_City[i] + 1; j++)//�����򶫣�����Ӫ������ʤ��ʿ
				{
					if (city[j]->victorWr)
						if (city[j]->victorWr->color == 1)
							city[j]->victorWr->rewardElem(*headquater[1]);
				}
				for (int j = num_City[i]; j > 0; j--)//�Զ�����������Ӫ������ʤ��ʿ
				{
					if (city[j]->victorWr)
						if (city[j]->victorWr->color == 0)
							city[j]->victorWr->rewardElem(*headquater[0]);
				}
				for (int j = 1; j < num_City[i] + 1; j++)//ʤ�߻��ճ���element
					if (city[j]->victorWr)
					{
						headquater[city[j]->victorWr->color]->element += city[j]->element;
						city[j]->element = 0;
					}
				time += 10; if (time > T[i]) break;//��50���ӣ���Ӫ����element
				headquater[0]->pritElem(time);
				headquater[1]->pritElem(time);
				time += 5; if (time > T[i]) break;//��55���ӣ���ʿ�����������
				for (int j = 1; j < num_City[i] + 1; j++)
					if (city[j]->wr[0])
						city[j]->wr[0]->pritWeapon(time);
				if (headquater[1]->enemyWr[0])
					headquater[1]->enemyWr[0]->pritWeapon(time);
				if (headquater[0]->enemyWr[0])
					headquater[0]->enemyWr[0]->pritWeapon(time);
				for (int j = 1; j < num_City[i] + 1; j++)
					if (city[j]->wr[1])
						city[j]->wr[1]->pritWeapon(time);
			}
			time += 5;
		}
		delete headquater[0]; delete headquater[1];
		for (int i = 0; i < 25; i++)
			if (city[i])
				delete city[i];
		stop = 0;
	}
	return 0;
}
