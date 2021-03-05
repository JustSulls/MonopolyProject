#pragma once
#include <string>
class Piece
{
public:
	Piece();
	Piece(std::string name);
	std::string name;
	int position;
	bool operator==(const Piece& other);
};

