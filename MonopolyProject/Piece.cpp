#include "Piece.h"

Piece::Piece(std::string n)
{
	name = n;
	position = 0;
}
Piece::Piece()
{
	position = 0;
	name = "default";
}
bool Piece::operator==(const Piece& other)
{
	if (this->name == other.name) return true;
	else return false;
}