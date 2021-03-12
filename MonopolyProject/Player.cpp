#include "Player.h"
Player::Player()
{
	name = "";
	money = 0;
}
Player::Player(std::string n)
{
	name = n;
	money = 0;
}
void Player::collect(int amount)
{
	money += amount;
}
void Player::pay(int amount)
{
	money -= amount;
}
int Player::throw_die()
{
	int ran;
	srand(time(NULL));
	ran = rand() % 6 + 1;
	std::cout << "You rolled a " << ran << "." << std::endl;
	return ran;
}
bool Player::operator==(const Player& other)
{
	std::string n = other.name;
	if (n == other.name) return true;
	else return false;
}
int Player::decide_buy_or_pass(Property property)
{
	//TODO:
	//present option to player
	//[0] no [1] yes
	//for now just return 0
	std::cout << "Decide buy or pass: [0] no, [1] yes" << property.name << "?\n";
	return 0;
}
