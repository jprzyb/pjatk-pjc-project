#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>
#include <windows.h>
#include <string>
#include <conio.h>
#include "Monster.h"
#include "Player.h"
#include <chrono>
#include <random>

using std::string; using std::cout; using std::cin; using std::endl; using std::vector;
using std::ifstream; using std::ofstream; using std::getline;

static string monsterPath = "monsters.txt";
static string playerPath = "player.txt";
static string enemyPath = "enemy.txt";

static bool gameLoaded;
static bool playerTurn;

static int iPlayerMonster;
static int iEnemyMonster;

Player player;
Player enemy;

static vector<Monster> monsters;
static vector<Monster> playerMonsters;
static vector<Monster> enemyMonsters;

void wait() {
	Sleep(1000);
	cout << "\nPress any button to continue";
	getchar(); getchar();
	system("cls");
}
double attackEffectivity(string playerType, string monsterType) {
	if (playerType == "WATER") {
		if (monsterType == "WATER") return 0.7;
		if (monsterType == "EARTH" || monsterType == "FIRE") return 1.3;
	}
	else if (playerType == "EARTH") {
		if (monsterType == "WIND") return 0.7;
		if (monsterType == "ICE" || monsterType == "FIRE" || monsterType == "STEEL") return 1.3;
	}
	else if (playerType == "AIR") {
		if (monsterType == "EARTH" || monsterType == "STEEL") return 0.7;
		if (monsterType == "ICE") return 1.3;
	}
	else if (playerType == "FIRE") {
		if (monsterType == "EARTH" || monsterType == "WATER") return 0.7;
		if (monsterType == "STEEL" || monsterType == "ICE") return 1.3;
	}
	else if (playerType == "ICE") {
		if (monsterType == "FIRE" || monsterType == "WATER" || monsterType == "ICE") return 0.7;
		if (monsterType == "EARTH") return 1.3;
	}
	else if (playerType == "STEEL") {
		if (monsterType == "AIR" || monsterType == "WATER") return 0.7;
		if (monsterType == "STEEL" || monsterType == "FIRE") return 1.3;
	}

	return 1.0;
}
void save() {
	// enemy
	ofstream enemyOut(enemyPath);

	enemyOut << enemy.getName() << endl;
	enemyOut << enemy.getWins();

	enemyOut.close();

	// player
	ofstream playerOut(playerPath);

	playerOut << player.getName() << endl;
	playerOut << player.getWins();

	playerOut.close();

	//monsters

	if (gameLoaded) {
		monsters.clear();
		for (int i = 0; i < 6; i++) {
			monsters.push_back(playerMonsters[i]);
			monsters.push_back(enemyMonsters[i]);
		}
		for (int i = 0; i < 3; i++) {
			Monster tempMonster;
			monsters.push_back(tempMonster);
		}
	}
	ofstream monsterOut(monsterPath);

	for (int i = 0; i < 15; i++) {
		monsterOut << monsters[i].getName() << endl;
		monsterOut << monsters[i].getType() << endl;
		monsterOut << monsters[i].getHp() << endl;
		monsterOut << monsters[i].getStrenght() << endl;
		monsterOut << monsters[i].getAgility() << endl;			
		monsterOut << monsters[i].getID() << endl;
		monsterOut << monsters[i].getCurrentExp() << endl;
		monsterOut << monsters[i].getEvolveExpRange() << endl;
		monsterOut << monsters[i].getIsDead() << endl;
	}
	monsterOut.close();
}
int formateA(int a, int range) {
	while (a > range) a /= 2;
	return a;
}
int getRandomNumber(int minimum, int maximum) {
	/*
	* zamiast podstawowej funkcji random() użyłem alternatywnej wersji
	* użyłem tego rozwiązania ponieważ dostawałem błąd o utracie danych oraz losowane były dwie takie same liczby per każdy monster
	* mimo wykorzystania srand(time(NULL))
	*/
	std::default_random_engine RandomGenerator(std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> distribution(minimum, maximum);
	return distribution(RandomGenerator);
}
int  pickIenemyMonster() {
	for (int i = 0; i < 6; i++) {
		if (!enemyMonsters[i].getIsDead()) return i;
	}
	return -1;
}
void pickIplayerMonster() {
	cout << "Which of your monsters you want to choose to battle?\n\nON\tNAME\tTYPE\tHP\tSTRENGHT\tAGILITY\tEXP\tIS ALIVE\n";
	for (int i = 0; i < 6; i++) {
		if (!playerMonsters[i].getIsDead()) {
			cout << i << ".\t";
			playerMonsters[i].showMonsterInLine();
		}
	}
	cout << "\nPICK: "; cin >> iPlayerMonster;
	iPlayerMonster = formateA(iPlayerMonster, 5);
}
string getSkillNameBasedOnYype(string type) {
	if (type == "WATER") {
		int n = getRandomNumber(0, 4);
		switch (n) {
		case 0: return "Aqua Ring";
		case 1: return "Water prison";
		case 2: return "Muddy Watter";
		case 3: return "Scald";
		case 4: return "Soak";
		default: return "Water Gun";
		}
	}
	else if (type == "EARTH") {
		int n = getRandomNumber(0, 4);
		switch (n) {
		case 0: return "Dig";
		case 1: return "Fissure";
		case 2: return "Spikes";
		case 3: return "Sand Tomb";
		case 4: return "Drill Run";
		default: return "Bone Club";
		}
	}
	else if (type == "AIR") {
		int n = getRandomNumber(0, 4);
		switch (n) {
		case 0: return "Acrobatics";
		case 1: return "Air Cutter";
		case 2: return "Air Slash";
		case 3: return "Sky Attack";
		case 4: return "Sky Drop";
		default: return "Tailwind";
		}
	}
	else if (type == "AIR") {
		int n = getRandomNumber(0, 4);
		switch (n) {
		case 0: return "Acrobatics";
		case 1: return "Air Cutter";
		case 2: return "Air Slash";
		case 3: return "Sky Attack";
		case 4: return "Sky Drop";
		default: return "Tailwind";
		}
	}
	else if (type == "STEEL") {
		int n = getRandomNumber(0, 4);
		switch (n) {
		case 0: return "Bullet Punch";
		case 1: return "Doom Desire";
		case 2: return "Gyro Ball";
		case 3: return "Iron Defense";
		case 4: return "Iron Head";
		default: return "Metal Claw";
		}
	}
	else if (type == "FIRE") {
		int n = getRandomNumber(0, 4);
		switch (n) {
		case 0: return "Blast Burn";
		case 1: return "Burn Up";
		case 2: return "Ember";
		case 3: return "Fusion Flare";
		case 4: return "Inferno";
		default: return "Will-O-Wisp";
		}
	}
	else if (type == "ICE") {
		int n = getRandomNumber(0, 4);
		switch (n) {
		case 0: return "Glaciate";
		case 1: return "Ice Beam";
		case 2: return "Sheer Cold";
		case 3: return "Ice Hammer";
		case 4: return "Hail";
		default: return "Mist";
		}
	}
	else return "Big Bang";
}
bool agilityChance(int agility) {
	return agility <= getRandomNumber(0, 99);
}

void pickMonsters() {

	//picking player monsters
	for (int i = 0; i < 6; i++) {

		//showing
		cout << "\tNAME\tTYPE\tHP\tSTRENGHT\tAGILITY\tCURRENT EXP\tIS ALIVE\n";
		for (int j = 0; j < 15; j++) {
			if (monsters[j].getID() == 0) {
				cout << j << ". "; monsters[j].showMonsterInLine();
			}
		}

		//chosing	
		int a;
		cout << "Choose your monster: "; cin >> a;
		Sleep(500); system("cls");
		a = formateA(a, 15);
		if (monsters[a].getID() != 0) {
			i--;
			cout << "BAD CHOICE TRY ONE MORE TIME!" << endl;
			Sleep(500); system("cls");
		}
		else {
			monsters[a].setID(1);
			playerMonsters.push_back(monsters[a]);
		}
	}

	//picking enemy monsters

	for (int i = 0; i < 15; i++) {
		if (monsters[i].getID() == 0) {
			monsters[i].setID(2);
			enemyMonsters.push_back(monsters[i]);
		}
	}

	save();

}
void makeFiles() {

	//clearing
	monsters.clear();
	playerMonsters.clear();
	enemyMonsters.clear();

	//mosters
	ofstream monsterOut(monsterPath);

	for (int i = 0; i < 15; i++) {
		Monster tempMonster;
		monsters.push_back(tempMonster);
	}

	for (int i = 0; i < 15; i++) {
		monsterOut << monsters[i].getName() << endl;
		monsterOut << monsters[i].getType() << endl;
		monsterOut << monsters[i].getHp() << endl;
		monsterOut << monsters[i].getStrenght() << endl;
		monsterOut << monsters[i].getAgility() << endl;
		monsterOut << monsters[i].getID() << endl;
		monsterOut << monsters[i].getCurrentExp() << endl;
		monsterOut << monsters[i].getEvolveExpRange() << endl;
		monsterOut << monsters[i].getIsDead() << endl;
	}
	monsterOut.close();

	// enemy

	Player ene;

	ofstream enemyOut(enemyPath);

	enemyOut << ene.getName() << endl;
	enemyOut << ene.getWins();

	enemy = ene;

	enemyOut.close();

	// player

	string playerName;

	cout << "Insert your nick: "; cin >> playerName;

	Player pla(playerName);

	player = pla;

	ofstream playerOut(playerPath);

	playerOut << pla.getName() << endl;
	playerOut << pla.getWins();

	playerOut.close();



}
void newGame() {
	system("cls");
	makeFiles();
	system("cls");
	pickMonsters();
	gameLoaded = true;
	system("cls");
}
void loadGame() {

	gameLoaded = true;

	string name;
	int wins;

	//getting player
	ifstream playerIn(playerPath);

	playerIn >> name >> wins;
	player.setName(name);
	player.setWins(wins);

	playerIn.close();

	//getting enemy
	ifstream enemyIn(enemyPath);

	enemyIn >> name >> wins;
	enemy.setName(name);
	enemy.setWins(wins);

	enemyIn.close();

	//getting monsters

	string mName, type;
	int strenght, hp, agility, id, currentExp, evolveExpRange;
	bool mIsDead;

	ifstream monsterIn(monsterPath);

	monsters.clear();



	for (int i = 0; i < 15; i++) {
		monsterIn >> mName >> type >> hp >> strenght >> agility >> id >> currentExp >> evolveExpRange >> mIsDead;
		Monster tempMonster(mName, type, hp, strenght, agility, id, currentExp, evolveExpRange, mIsDead);
		monsters.push_back(tempMonster);
	}

	//setting player monsters

	for (int i = 0; i < 15; i++) {
		if (monsters[i].getID() == 1) playerMonsters.push_back(monsters[i]);
	}

	//setting player monsters

	for (int i = 0; i < 15; i++) {
		if (monsters[i].getID() == 2) enemyMonsters.push_back(monsters[i]);
	}

	monsterIn.close();

	system("cls");
	cout << "Succesully loaded the game!\n";
	wait();
}
void gameNotLoaded() {
	bool goodPick = true;
	while (goodPick) {
		system("cls");
		int n;
		cout << "Your game hasn't been loaded.\nWould you try to load game or make a new one?\n\t1. Load Game\n\t2. New Game\nPICK: "; cin >> n;
		switch (n) {
		case 1: {
			goodPick = false;
			loadGame();
			break;
		}
		case 2: {
			goodPick = false;
			newGame();
			break;
		}
		default: {
			system("cls");
			cout << "Bad pick try one more time!";
			Sleep(1000);
		}
		}

	}
}	

void showInstruction() {
	ifstream in("instruction.txt");
	string line;
	while (getline(in, line)) {
		cout << line << endl;
	}
	in.close();
}

void playerWon() {
	system("cls");
	cout << "YOU HAVE WON\nCONGRATULATIONS!\n\nThe game will be automaticaly saved and reloaded.\n";

	player.addWin();
	
	for (int i = 0; i < 6; i++) { // adding additional exp for win
		playerMonsters[i].addExp(20);
	}

	for (int i = 0; i < 6; i++) { // setting monsters
		playerMonsters[i].resetStats();
		enemyMonsters[i].resetStats();
	}

	//game balance
	int randomEvolveIterator = getRandomNumber(0, 4);
	enemyMonsters[randomEvolveIterator].evolve();
	enemyMonsters[randomEvolveIterator+1].evolve();
	
	wait();

	save();
	loadGame();

}
void enemyWon() {
	system("cls");
	cout << "YOU HAVE LOST\nNext time will be better!\n\nThe game will be automaticaly saved and reloaded.\n";

	enemy.addWin();

	for (int i = 0; i < 6; i++) { // setting monsters
		playerMonsters[i].resetStats();
		enemyMonsters[i].resetStats();
	}

	//game balance
	int randomEvolveIterator = getRandomNumber(1, 5);
	enemyMonsters[randomEvolveIterator].unEvolve();
	enemyMonsters[randomEvolveIterator-1].unEvolve();

	wait();

	save();
	loadGame();
}
int showBattleMenu() {
	int n;
	cout << "\t\tNAME\tTYPE\tHP\tSTRENGHT\tAGILITY\tEXP\tIS ALIVE\n";
	cout << "Your Monster:\t"; playerMonsters[iPlayerMonster].showMonsterInLine();
	cout << "Enemy Monster:\t";  enemyMonsters[iEnemyMonster].showMonsterInLine(); cout << endl;
	cout << "\n### CHOOSE MOVE ###\n\t1. Attack\n\t2. Special attack\t(costs 15 EXP)\n\t3. Switch monster\n\t4. Evolve Monster\n\t5. Quit\t(all progress will be lost)\nPICK: ";
	cin>>n;
	return n;

}
void enemyTurn() {

	if (enemyMonsters[iEnemyMonster].getCurrentExp() >= enemyMonsters[iEnemyMonster].getEvolveExpRange()) enemyMonsters[iEnemyMonster].evolve();
	else{
		int n = getRandomNumber(0, 99);
		if (n < 50 && enemyMonsters[iEnemyMonster].getCurrentExp() >= 15) { //specjal attack

			if (agilityChance(playerMonsters[iPlayerMonster].getAgility())) {
				int enemyDamage = enemyMonsters[iEnemyMonster].getStrenght() * attackEffectivity(enemyMonsters[iEnemyMonster].getType(), playerMonsters[iPlayerMonster].getType()) * 2;
				// damage = strenght * arrackEffectifity(playerMonsterType , enemyMonsterType) * 2
				cout << enemy.getName() << " attacked you with " << enemyMonsters[iEnemyMonster].getName() << "'s special skill " << getSkillNameBasedOnYype(enemyMonsters[iEnemyMonster].getType()) << " and took you " << enemyDamage << " DMG !\n\n";
				playerMonsters[iPlayerMonster].setHp(playerMonsters[iPlayerMonster].getHp() - enemyDamage); // damage taking
				enemyMonsters[iEnemyMonster].addExp(-15); // exp removing
				if (playerMonsters[iPlayerMonster].getHp() <= 0) playerMonsters[iPlayerMonster].setIsDead(true); // making monster dead
			}
			else {
				cout << "Your monster avoided the attack!\n";
			}
		}
		else { // attack

			if (agilityChance(playerMonsters[iPlayerMonster].getAgility())) {
				int enemyDamage = enemyMonsters[iEnemyMonster].getStrenght() * attackEffectivity(enemyMonsters[iEnemyMonster].getType(), playerMonsters[iPlayerMonster].getType());
				// damage = strenght * arrackEffectifity(playerMonsterType , enemyMonsterType)
				cout << "Enemy " << enemy.getName() << " attacked you with " << enemyMonsters[iEnemyMonster].getName() << " and took you " << enemyDamage << " DMG !\n\n";
				playerMonsters[iPlayerMonster].setHp(playerMonsters[iPlayerMonster].getHp() - enemyDamage); // damage taking
				enemyMonsters[iEnemyMonster].addExp(10); // exp adding
				if (playerMonsters[iPlayerMonster].getHp() <= 0) playerMonsters[iPlayerMonster].setIsDead(true); // making monster dead
			}
			else {
				cout << "Your monster avoided the attack!\n";
			}
		}
	}
}
int attack() { // 0 -> no win ; 1 -> player win ; 2 -> enemy win
	system("cls");

//player turn
	if (agilityChance(enemyMonsters[iEnemyMonster].getAgility())) {
		int playerDamage = playerMonsters[iPlayerMonster].getStrenght() * attackEffectivity(playerMonsters[iPlayerMonster].getType(), enemyMonsters[iEnemyMonster].getType());
		// damage = strenght * arrackEffectifity(playerMonsterType , enemyMonsterType)
		cout << "You attacked " << enemy.getName() << "'s " << enemyMonsters[iEnemyMonster].getName() << " with " << playerDamage << " DMG !\n\n";
		enemyMonsters[iEnemyMonster].setHp(enemyMonsters[iEnemyMonster].getHp() - playerDamage); // damage taking
		playerMonsters[iPlayerMonster].addExp(10); // exp adding
		if (enemyMonsters[iEnemyMonster].getHp() <= 0) enemyMonsters[iEnemyMonster].setIsDead(true); // making monster dead
	}
	else {
		cout << "Opponent dodged your attack!\n";
	}

// checking if player killed and won
	//won
	if (enemyMonsters[0].getIsDead() && enemyMonsters[1].getIsDead() && enemyMonsters[2].getIsDead() && enemyMonsters[3].getIsDead() && enemyMonsters[4].getIsDead() && enemyMonsters[5].getIsDead()) return 1;
	//killed
	if (enemyMonsters[iEnemyMonster].getIsDead() ) {
		cout << "\nYou knocked of enemy monster!\nGood Job!\n";
		iEnemyMonster = pickIenemyMonster();
		}
//enemy turn
		enemyTurn();

// showing turn stats
		cout << "\t\tNAME\tTYPE\tHP\tSTRENGHT\tAGILITY\tEXP\tIS ALIVE\n";
		cout << "Your monster:\t"; playerMonsters[iPlayerMonster].showMonsterInLine();
		cout << "Enemy monster:\t"; enemyMonsters[iEnemyMonster].showMonsterInLine();
		wait();

// checking if enemy killed and won
		//won
		if (playerMonsters[0].getIsDead() && playerMonsters[1].getIsDead() && playerMonsters[2].getIsDead() && playerMonsters[3].getIsDead() && playerMonsters[4].getIsDead() && playerMonsters[5].getIsDead()) return 2;
		// killed
		if (playerMonsters[iPlayerMonster].getIsDead()) {
			playerMonsters[iPlayerMonster].setIsDead(true);
			cout << enemy.getName() << " knocked of your " << playerMonsters[iPlayerMonster].getName() << "\n ### Pick next monster ###\n";
			pickIplayerMonster();
		}

		return 0;
}
int specialAttack() { // 0 -> no win ; 1 -> player win ; 2 -> enemy win
	system("cls");

//player turn
	if (agilityChance(enemyMonsters[iEnemyMonster].getAgility())) {
		int playerDamage = playerMonsters[iPlayerMonster].getStrenght() * attackEffectivity(playerMonsters[iPlayerMonster].getType(), enemyMonsters[iEnemyMonster].getType()) * 2;
		// damage = strenght * attackEffectifity * 2
		cout << "You attacked " << enemy.getName() << "'s " << enemyMonsters[iEnemyMonster].getName() << " with specjal attack " << getSkillNameBasedOnYype(playerMonsters[iPlayerMonster].getType()) << " and took him " << playerDamage << " DMG !\n\n";
		enemyMonsters[iEnemyMonster].setHp(enemyMonsters[iEnemyMonster].getHp() - playerDamage); // damage taking
		playerMonsters[iPlayerMonster].addExp(-15); // exp removing
		if (enemyMonsters[iEnemyMonster].getHp() <= 0) enemyMonsters[iEnemyMonster].setIsDead(true); // making monster dead
	}
	else {
		cout << "Opponent dodged your attack!\n";
	}

// checking if player killed and won
			//won
	if (enemyMonsters[0].getIsDead() && enemyMonsters[1].getIsDead() && enemyMonsters[2].getIsDead() && enemyMonsters[3].getIsDead() && enemyMonsters[4].getIsDead() && enemyMonsters[5].getIsDead()) return 1;
	//killed
	if (enemyMonsters[iEnemyMonster].getIsDead()) { // killed
		cout << "\nYou knocked of enemy monster!\nGood Job!\n";
		iEnemyMonster = pickIenemyMonster();
	}
//enemy turn
	enemyTurn();

// showing turn stats
	cout << "\t\tNAME\tTYPE\tHP\tSTRENGHT\tAGILITY\tEXP\tIS ALIVE\n";
	cout << "Your monster:\t"; playerMonsters[iPlayerMonster].showMonsterInLine();
	cout << "Enemy monster:\t"; enemyMonsters[iEnemyMonster].showMonsterInLine();
	wait();

// checking if enemy killed and won
	//won
	if (playerMonsters[0].getIsDead() && playerMonsters[1].getIsDead() && playerMonsters[2].getIsDead() && playerMonsters[3].getIsDead() && playerMonsters[4].getIsDead() && playerMonsters[5].getIsDead()) return 2;
	// killed
	if (playerMonsters[iPlayerMonster].getIsDead()) {
		cout << enemy.getName() << " knocked of your " << playerMonsters[iPlayerMonster].getName() << "\n ### Pick next monster ###\n";
		pickIplayerMonster();
	}

	return 0;
}
void battle() {
		//battle menu
		int n;
		int won=0;

		cout << "### Battle starts! ###\n\n";

		while (won == 0) {
			n = showBattleMenu();
			switch (n) {
			case 1: { // attack
				won = attack();
				break;
			}
			case 2: { // special attack
				if (playerMonsters[iPlayerMonster].getCurrentExp() >= 15)specialAttack();
				else {
					system("cls");
					cout << "You can't do that move!\nYour current exp is " << playerMonsters[iPlayerMonster].getCurrentExp() << ".\nYou need at least 15 EXP to use special attack.\n";
					wait();
				}
				break;
			}
			case 3: { // choosing another monster
				system("cls");
				pickIplayerMonster();
				enemyTurn();
				break;
			}
			case 4: { // evolve
				if (playerMonsters[iPlayerMonster].getCurrentExp() >= playerMonsters[iPlayerMonster].getEvolveExpRange()) {
					playerMonsters[iPlayerMonster].evolve();
					enemyTurn();
				}
				else {
					system("cls");
					cout << "You can't do that move!\nYour current exp is " << playerMonsters[iPlayerMonster].getCurrentExp() << ".\nYou need at least "<< playerMonsters[iPlayerMonster].getEvolveExpRange() << " EXP to evolve your monster.\n";
					wait();
				}
				break;
			}
			case 5: {
				system("cls");
				return;
			}
			default: {
				system("cls");
				cout << "Wrong choise! Try one more time!";
				Sleep(2000);
				system("cls");
			}
			}
			system("cls");
		}

		//logika wygranej
		if (won == 1) playerWon();
		if (won == 2) enemyWon();
	}
void game() {
	if (!gameLoaded) gameNotLoaded();
	playerTurn = true;

	system("cls");
	cout << "Your game is beningin!\n";

	pickIplayerMonster();

	iEnemyMonster = pickIenemyMonster();

	system("cls");
	battle();

}

void welcomeScreen() {

	cout << "### MAIN MENU ###\n\t1. Start Game\n\t2. Load Game\n\t3. New Game\n\t4. Show me\n\t5. Show enemy\n\t6. Instruction\n\t7. Save and exit\n\n";
	cout << "Your pick: ";

	int a; cin >> a;

	switch (a) {
	case 1: { // start game
		system("cls");
		game();
		break;
	}
	case 2: { // load game
		system("cls");
		loadGame();
		break;
	}

	case 3: { // new game
		system("cls");
		newGame();
		system("cls");
		game();
		system("cls");
		break;
	}

	case 4: { // show me
		system("cls");
		
		if (gameLoaded) {
			player.showPlayer();
			cout << "\nMONSTERS:\n";
			cout << "\tNAME\tTYPE\tHP\tSTRENGHT\tAGILITY\tEXP\tIS ALIVE\n";
			for (int i = 0; i < 6; i++) {
				cout << "\t";
				playerMonsters[i].showMonsterInLine();
			}
		}
		else {
			cout << "You can't do that!\nThe game hasn't been loaded!\n";
		}
		wait();
		system("cls");

		break;
	}
	case 5: { // show enemy
		system("cls");

		if (gameLoaded) {
			enemy.showPlayer();
			cout << "\nMONSTERS:\n";
			cout << "\tNAME\tTYPE\tHP\tSTRENGHT\tAGILITY\tEXP\tIS ALIVE\n";
			for (int i = 0; i < 6; i++) {
				cout << "\t";
				enemyMonsters[i].showMonsterInLine();
			}
		}
		else {
			cout << "You can't do that!\nThe game hasn't been loaded!\n";
		}

		wait();
		system("cls");

		break;
	}
	case 6: { // instruction
		system("cls");
		showInstruction();
		wait();
		system("cls");
		break;
	}
	case 7: { // exit
		system("cls");
		save();
		cout << "\t\t\tTHANKS FOR GAME!\n\t\t\tSEE YOU SOON!\n";
		Sleep(2000);
		system("cls");
		cout << "PRESS ANY BUTTON TO LEAVE\n";
		exit(0);
		break;
	}
	default: {
		system("cls");
		cout << "Wrong pick! Try One more time :)";
		wait();
		system("cls");
		return;
	}
	}

}

int main()
{
	gameLoaded = false;

	cout << "Hi,\nWelcome to my game!\nChoose what u want to do:\t\t(to choose option just pick a number (e.g. [1]) and click ENTER\n\n";

	for (; ;) {
		welcomeScreen();
	}
}
