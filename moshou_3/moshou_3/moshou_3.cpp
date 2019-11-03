#include "pch.h"
#include <iostream>
using namespace std;
// 基类指针变量，指向基类调用基类同名虚函数，指向派生类调用派生类同名虚函数
// 2019.10.22 先完成武士类、武器类、武士和武器类的交互，可以参考魔兽世界二的代码
// 2019.10.25 继续完成武士类中，武士死亡，构造函数，析构函数，武器类
// 2019.10.26 构造函数如何写，析构函数怎么写，完成武器类及武器类
// 2019.10.27 保证类与类之间的交互关系相互独立而不耦合
// 炸弹的使用需要知道对方的生命值和攻击力，这个交互动作需要与城市类交互完成
// 弓箭的使用需要知道下一个城市是否有敌人，这个交互动作需要与城市类交互完成
// 27没有完成武士与武器的交互
// 10.28 有hurt成员函数完成近战中对武器的检测，弓箭攻击和炸弹是城市类中一个特殊的成员函数
// 弓箭和炸弹的使用先放考虑，等城市类完成再考虑
// sword的编号是0,如何给weapon用上多态？
// 2019.10.29 没想清楚sword如何被使用 
// 2019.10.30 时间安排不当
// 要确定武器与武士之间的映射关系，动态的设定封闭类，通过武士类的构造函数来创建武器类对象
// 2019.10.31 时间安排不当，继续思考这个问题，如果周日还没结果就参考网上程序，周末一定过掉这关





class Worrior {
public:
	int lifeValue;
	int power;
	Weapon weapon[3];
	Worrior(int lifeValue_, int power_) : lifeValue(lifeValue_), power(power_) { }
	virtual void Attack(Worrior * pWorrior) { }
	virtual void strikeBack(Worrior * pWorrior) { }
	virtual void Hurt(Worrior * pWorrior) { }
	~Worrior() { }

};

// 龙武士
class Dragon : public Worrior {
public:
	Dragon(int lifeValue_, int power_, int n) : Worrior(lifeValue_, power_) { 
		if (n % 3 == 0) {
			weapon[0].power = power_ * 0.2;
			weapon[0].num = 1;
		}
		else if (n % 3 == 1) {
			weapon[1].power = 1e9;
			weapon[1].num = 1;
		}
		else if (n % 3 == 2) {
			weapon[2].power = power_;
			weapon[2].num = 1;
		}
	}
	virtual void Attack(Worrior * pWorrior);
	virtual void strikeBack(Worrior * pWorrior);
	virtual void Hurt(Worrior * pWorrior);
	~Dragon(){ }
};

void Dragon :: Attack(Worrior * pWorrior) {
	pWorrior->Hurt(this);
	pWorrior->strikeBack(this);
}

void Dragon::strikeBack(Worrior * pWorrior) {
	pWorrior->Hurt(this);
}

void Dragon::Hurt(Worrior * pWorrior) {
	int relife = 0;
	int damageValue = 0;
	if (pWorrior->weapon[0].num != 0) {
		damageValue = pWorrior->power + pWorrior->weapon[0].power;
	}
	relife = lifeValue -damageValue;
	if (relife > 0) lifeValue = relife;
	else this->~Dragon();
}


// 娜迦
class Ninja : public Worrior {
private:
	int weapon1;
	int weapon2;
public:
	Ninja(int lifeValue_, int power_, int n) : Worrior(lifeValue_, power_) {
		weapon1 = n % 3;
		weapon2 = (n + 1) % 3;
	}
	virtual void Attack(Worrior * pWorrior) { }
	virtual void strikeBack(Worrior * pWorrior) { }
	virtual void Hurt(Worrior * pWorrior) { }
	~Ninja() { }

};

void Ninja::Attack(Worrior * pWorrior) {
	pWorrior->Hurt(this);
	pWorrior->strikeBack(this);
}

void Ninja::strikeBack(Worrior * pWorrior) {
	pWorrior->Hurt(this);
}

void Ninja::Hurt(Worrior * pWorrior) {
	int relife = 0;
	relife = lifeValue - pWorrior->lifeValue;
	if (relife > 0) lifeValue = relife;
	else this->~Ninja();
}


// 冰人
class Iceman : public Worrior {
private:
	int weapon;
public:
	Iceman(int lifeValue_, int power_, int n) : Worrior(lifeValue_, power_) { 
		weapon = n % 3;
	}
	virtual void Attack(Worrior * pWorrior) { }
	virtual void strikeBack(Worrior * pWorrior) { }
	virtual void Hurt(Worrior * pWorrior) { }
	~Iceman() { }

};

void Iceman::Attack(Worrior * pWorrior) {
	pWorrior->Hurt(this);
	pWorrior->strikeBack(this);
}

void Iceman::strikeBack(Worrior * pWorrior) {
	pWorrior->Hurt(this);
}

void Iceman::Hurt(Worrior * pWorrior) {
	lifeValue = lifeValue - pWorrior->power;
}

// 狮武士
class Lion : public Worrior {
public:
	Lion(int lifeValue_, int power_) : Worrior(lifeValue_, power_) { }
	virtual void Attack(Worrior * pWorrior) { }
	virtual void strikeBack(Worrior * pWorrior) { }
	virtual void Hurt(Worrior * pWorrior) { }
	~Lion() { }

};

void Lion::Attack(Worrior * pWorrior) {
	pWorrior->Hurt(this);
	pWorrior->strikeBack(this);
}

void Lion::strikeBack(Worrior * pWorrior) {
	pWorrior->Hurt(this);
}

void Lion::Hurt(Worrior * pWorrior) {
	lifeValue = lifeValue - pWorrior->power;
}

// 狼人
class Wolf : public Worrior {
public:
	Wolf(int lifeValue_, int power_) : Worrior(lifeValue_, power_) { }
	virtual void Attack(Worrior * pWorrior) { }
	virtual void strikeBack(Worrior * pWorrior) { }
	virtual void Hurt(Worrior * pWorrior) { }
	~Wolf() { }

};

void Wolf::Attack(Worrior * pWorrior) {
	pWorrior->Hurt(this);
	pWorrior->strikeBack(this);
}

void Wolf::strikeBack(Worrior * pWorrior) {
	pWorrior->Hurt(this);
}

void Wolf::Hurt(Worrior * pWorrior) {
	lifeValue = lifeValue - pWorrior->power;
}

class Weapon {
public:
	int power;
	int num;
	Weapon() { }

};

class Sword {
private:
	int swordPower = 0;
public:
	Sword(Worrior * pWorrior) { }
	void durability() { }

};

Sword::Sword(Worrior * pWorrior) {
	swordPower = 0.2 * pWorrior->power;
}

void Sword::durability() {
	swordPower *= 0.8;
}

class Arrow {
	int R;
	int durability;
public:
	Arrow(int R_, int durability_ = 3) { }
	void Shot(Worrior * pWorrior);

};

void Arrow::Shot(Worrior * pWorrior) {
	pWorrior->Hurt(pWorrior);
}

class Bomb {
public:
	void DiDaLa(Worrior * pWorrior, Worrior * enemy);

};

void Bomb::DiDaLa(Worrior * pWorrior, Worrior * enemy) {
	pWorrior->~Worrior();
	enemy->~Worrior();
}

class Headquarter {


};

class City {


};

int main() {

}