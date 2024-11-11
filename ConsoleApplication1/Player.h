#include <iostream>
using std::string;

class Player
{
private:
	string name;	

	int wins;

	int getRandomNumber(int minimum, int maximum);

	string getRandomName();
public:

	string getName();
	int getWins();

	void setName(string name);
	void setWins(int wins);
	void addWin();

	void showPlayer();

	Player();
	Player(string name);

};

