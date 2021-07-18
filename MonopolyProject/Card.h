#pragma once
#include <vector>
#include <string>

class Card
{
public:
	std::string text;
	enum class card_type {
		Community_Chest,
		Chance
	};
	short id;
	card_type type;
	Card(std::string txt, card_type ct, short i);
	Card();
};

