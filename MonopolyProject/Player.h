#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Piece.h"
#include "Property.h"
#include "Utility.h"
#include "Railroad.h"
class Player
{
public:
	Player();
	Player(std::string n);
	Piece piece;
	std::string name;
	int money;
	bool has_get_out_of_jail_card = false;
	bool in_jail = false;
	int number_of_houses = 0;
	int number_of_hotels = 0;

	std::vector<Property>properties_owned;
	std::vector<Utility>utilities_owned;
	std::vector<Railroad>railroads_owned;

	void collect(int amount);
	void pay(int amount);
	int throw_die();
	//void assign_ownership(Property property);
	int decide_buy_or_pass(Property property);
	bool operator==(const Player& other);
};
