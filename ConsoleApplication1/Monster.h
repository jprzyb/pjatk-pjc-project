#include <iostream>

using std::string;

class Monster
{
private:

	int strenght;
	int MAXstrenght;
	int hp;
	int MAXhp;
	int agility;
	int MAXagility;
	int playerId;
	int currentExp;
	int evolveExpRange;

	string name;
	string type;

	bool isDead;

	int getAgilityBasedOnType();
	int getStrenghtBasedOnType();
	int getHpBasedOnType();
	int getRandomNumber(int minimum, int maximum);

	string getRandomMonsterType();
	string getRandomMonsterName();

public:
	int getStrenght();
	int getHp();
	int getAgility();
	string getName();
	string getType();
	bool getIsDead();
	int getID();
	int getCurrentExp();
	int getEvolveExpRange();

	void setStrenght(int strenght);
	void setHp(int hp);
	void setAgility(int agility);
	void setName(string name);
	void setType(string type);
	void setIsDead(bool isDead);
	void setID(int id);
	void setCurrentExp(int currentExp);
	void setEvolveExpRange(int evolveExpRange);

	void evolve();
	void unEvolve();
	void addExp(int exp);
	void resetStats();

	void showMonster();
	void showMonsterInLine();

	Monster();
	Monster(string name, string type, int hp, int strenght, int agility, int id, int currentExp, int evolveExpRange, bool isDead);

};