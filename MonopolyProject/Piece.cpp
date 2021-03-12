#include "Piece.h"

Piece::Piece(std::string n)
{
	//put piece on board
	name = n;
	position = 0;
}
Piece::Piece()
{
	//put piece on board
	position = 0;
	name = "default";
}
bool Piece::operator==(const Piece& other)
{
	std::string n = this->name;
	if (n == other.name) return true;
	else return false;
}