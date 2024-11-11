#include <iostream>
#include <vector>
#include "Monster.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <chrono>
#include <random>
#include <string>

using std::string; using std::cout; using std::cin; using std::endl; using std::vector;
using std::ifstream; using std::ofstream;

	int Player::getRandomNumber(int minimum , int maximum) {
		/*
		* zamiast podstawowej funkcji random() u¿y³em alternatywnej wersji
		* u¿y³em tego rozwi¹zania poniewa¿ dostawa³em b³¹d o utracie danych oraz losowane by³y dwie takie same liczby per ka¿dy monster
		* mimo wykorzystania srand(time(NULL))
		*/
		std::default_random_engine RandomGenerator(std::chrono::steady_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<int> distribution(minimum, maximum);
		return distribution(RandomGenerator);
	}

	string Player::getRandomName() {
		int n = getRandomNumber(0, 10);

		switch (n) {
		case 0: return "Andy";
		case 1: return "Bobendy";
		case 2: return "Rick";
		case 3: return "Morty";
		case 4: return "Ariana";
		case 5: return "Caleb";
		case 6: return "Harleen";
		case 7: return "Neyla";
		case 8: return "Natasha";
		case 9: return "Fabiola";
		default: return "Maxwell";
		}
	}

	string Player::getName() {
		return name;
	}
	int Player::getWins() {
		return wins;
	}

	void Player::setName(string name) {
		this->name = name;
	}
	void Player::setWins(int wins) {
		this->wins = wins;
	}
	void Player::addWin() {
		this->wins += 1;
	}

	void Player::showPlayer() {
		cout << "PLAYER:\n\tName: " << name << "\n\tWins: " << wins << endl;
	}

	Player::Player() {
		this->name = getRandomName();
		this->wins = 0;
	}
	Player::Player(string name) {
		this->name = name;
		this->wins = 0;
	}

	/* FILE STRUCTURE FOR THIS CLASS
	* name	string	1
	* wins	int		2
	*/