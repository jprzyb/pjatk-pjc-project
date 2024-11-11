#include "Monster.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <chrono>
#include <random>

using std::string; using std::cout; using std::endl;
using std::fstream; using std::ifstream; using std::ofstream; using std::ios;

static double evolveMultiplier = 1.5; // standard evolve multiplier

	void Monster::showMonster() {
		cout << "MONSTER: " << "\n\tName:\t" << name << "\n\tType:\t" << type << "\n\tStrenght:\t" << strenght << "\n\tAgility:\t" << agility << "\n\tHP:\t" << hp<<"\n";
	}
	void Monster::showMonsterInLine() {
		cout << name << "\t" << type << "\t" << hp << "\t" << strenght << "\t\t" << agility << "\t" << currentExp << "\t" << isDead << "\n";
	}

	int Monster::getAgilityBasedOnType() { //water-fire earth-steel wind-ice
		if (type == "FIRE" || type == "WATER") return 10;
		return 2;
	}
	int Monster::getStrenghtBasedOnType() { //water-fire earth-steel wind-ice
		if (type == "WIND" || type == "ICE") return 25;
		return 20;
	}
	int Monster::getHpBasedOnType() { //water-fire earth-steel wind-ice
		if (type == "EARTH" || type == "STEEL") return 120;
		return 100;
	}
	int Monster::getRandomNumber(int minimum, int maximum) {
		/*
		* zamiast podstawowej funkcji random() u¿y³em alternatywnej wersji
		* u¿y³em tego rozwi¹zania poniewa¿ dostawa³em b³¹d o utracie danych oraz losowane by³y dwie takie same liczby per ka¿dy monster
		* mimo wykorzystania srand(time(NULL))
		*/
		std::default_random_engine RandomGenerator(std::chrono::steady_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<int> distribution(minimum, maximum);
		return distribution(RandomGenerator);
	}

	string Monster::getRandomMonsterType() {
		int n = getRandomNumber(0,5);

		//cout << "getRandomMonsterType: " << n << endl;

		switch (n) { //water-fire earth-steel wind-ice 
		case 0: return "WATER"; // +agility
		case 1: return "EARTH"; // +hp
		case 2: return "WIND"; // +strenght
		case 3: return "FIRE"; // +agility
		case 4: return "ICE";  // +strenght
		case 5: return "STEEL"; // +hp
		default: return "WATER";
		}
	}
	string Monster::getRandomMonsterName() {
		int n = getRandomNumber(0, 19);

		//cout << "getRandomMonsterName: " << n << endl;

		switch (n) {
		case 0: return "Vullaby";
		case 1: return "Horesa";
		case 2: return "Drampa";
		case 3: return "Frosla";
		case 4: return "Gooomy";
		case 5: return "Steelix";
		case 6: return "Yamask";
		case 7: return "Mudkip";
		case 8: return "Cursola";
		case 9: return "Slaking";
		case 10: return "Lombre";
		case 12: return "Delin";
		case 13: return "Arbok";
		case 14: return "Vulpix";
		case 15: return "Ho-Oh";
		case 16: return "Mieno";
		case 17: return "Dreepy";
		case 18: return "Aggron";
		case 19: return "Solrock";
		default: return "Huntail";
		}
	}

	int Monster::getStrenght() {
		return strenght;
	}
	int Monster::getHp() {
		return hp;
	}
	int Monster::getAgility() {
		return agility;
	}
	string Monster::getName() {
		return name;
	}
	string Monster::getType() {
		return type;
	}
	bool Monster::getIsDead() {
		return isDead;
	}
	int Monster::getID() {
		return playerId;
	}
	int Monster::getCurrentExp() { 
		return currentExp;
	}
	int Monster::getEvolveExpRange() {
		return evolveExpRange;
	}

	void Monster::setStrenght(int strenght) {
		this->strenght = strenght;
	}
	void Monster::setHp(int hp) {
		this->hp = hp;
	}
	void Monster::setAgility(int agility) {
		this->agility = agility;
	}
	void Monster::setName(string name) {
		this->name = name;
	}
	void Monster::setType(string type) {
		this->type = type;
	}
	void Monster::setIsDead(bool isDead) {
		this->isDead = isDead;
	}
	void Monster::setID(int id) {
		this->playerId = id;
	}
	void Monster::setCurrentExp(int currentExp) {
		this->currentExp = currentExp;
	}
	void Monster::setEvolveExpRange(int evolveExpRange) {
		this->evolveExpRange = evolveExpRange;
	}

	void Monster::addExp(int exp) {
		currentExp += exp;
	}
	void Monster::evolve() {

		strenght *= evolveMultiplier;
		hp *= evolveMultiplier;
		agility *= evolveMultiplier;

		MAXstrenght *= evolveMultiplier;
		MAXhp *= evolveMultiplier;
		MAXagility *= evolveMultiplier;

		currentExp -= evolveExpRange;
		evolveExpRange *= evolveMultiplier;

	}
	void Monster::unEvolve() { // used to decrese enemy stats if player lose
		strenght /= evolveMultiplier;
		hp /= evolveMultiplier;
		agility /= evolveMultiplier;

		MAXstrenght /= evolveMultiplier;
		MAXhp /= evolveMultiplier;
		MAXagility /= evolveMultiplier;

		evolveExpRange /= evolveMultiplier;
	}
	void Monster::resetStats() {
		hp = MAXhp;
		strenght = MAXstrenght;
		agility = MAXagility;
		isDead = false;
	}

	Monster::Monster() {
		
		name = getRandomMonsterName();
		type = getRandomMonsterType();
		hp = getHpBasedOnType();
		MAXhp = hp;
		strenght = getStrenghtBasedOnType();
		MAXstrenght = strenght;
		agility = getAgilityBasedOnType();
		MAXagility = agility;
		playerId = 0;
		currentExp = 0;
		evolveExpRange = 50;
		isDead = false;
	}
	Monster::Monster(string name,string type,int hp,int strenght,int agility,int id,int currentExp,int evolveExpRange,bool isDead) {
		this->name = name;
		this->type = type;
		this->hp = hp;
		MAXhp = hp;
		this->strenght = strenght;
		MAXstrenght = strenght;
		this->agility = agility;
		MAXagility = agility;
		this->playerId = id;
		this->currentExp = currentExp;
		this->evolveExpRange= evolveExpRange;
		this->isDead = isDead;
	}

	/*
	  ========== monsters.txt structure ===========
	
	fieldName					fieldType	ON
	
	firstMonsterName			string		0
	firstMonsterType			string		1
	firstMonsterHp				int			2
	firstMonsterStrenght		int			3
	firstMonsterAgility			int			4
	firstPlayerID				int			5
	firstCurrentExp				int			6
	firstEvolveExpRange			int			7
	firstMonsterIsDead			bool		8
	secondMonsterName			string		9
	secondMonsterType			string		10
	secondMonsterHp				int			11
	secondMonsterStrennght		int			12
	secondMonsterAgility		int			13
	secondPlayerID				int			14
	secondCurrentExp			int			15
	secondEvolveExpRange		int			16
	secondMonsterIsDead			bool		17
	...
	lastMonsterName				string		127
	lastMonsterType				string		128
	lastMonsterHp				int			129
	lastMonsterStrennght		int			130
	lastMonsterAgility			int			131
	LastPlayerID				int			132
	lastCurrentExp				int			133
	lastEvolveExpRange			int			134
	lastMonsterIsDead 			bool		135
	*/
