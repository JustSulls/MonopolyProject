#include "Piece.h"

Piece::Piece()
{
	position = 0;
	piece = static_cast<pieces>(0);
}

Piece::Piece(int type)
{
	//put piece on board
	position = 0;

	//TODO: range check
	piece = static_cast<pieces>(type);
}

Piece::Piece(std::string s)
{
	name = s;
}

bool Piece::operator==(const Piece& p)
{
	if (p.name == name)
	{
		return true;
	}
	else return false;
}
