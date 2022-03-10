#pragma once
#include <string>
class Piece
{
public:
	Piece();
	Piece(int);
	Piece(std::string);
	enum class pieces{
		Destroyer,
		Mercedes
	};
	pieces piece;
	unsigned short position;
	std::string name;
	bool operator ==(const Piece& p);
};

