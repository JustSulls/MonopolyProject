#include "Card.h"
Card::Card(std::string txt, card_type ct, short i)
{
	text = txt;
	type = ct;
	id = i;
}

Card::Card()
{
	text = "";
	type = card_type::Chance;
	id = -1;
}
