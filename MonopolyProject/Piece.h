#pragma once
#include <string>
class Piece
{
public:
	Piece();
	Piece(std::string name);
	std::string name;
	unsigned short position;
	bool operator==(const Piece& other);
};

