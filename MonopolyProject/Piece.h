#pragma once
#include <string>
#include <map>
class Piece
{
public:
	Piece(int which=0);
	enum class pieces{
		Battleship,
		Boot,
		Cannon,
		Thimble,
		TopHat,
		Iron
	}piece;
	int position();
	void movePosition(int new_position);
	std::string str();

private:
	std::map<pieces, std::string> piece_map{
		{pieces::Battleship, "Battleship" },
		{pieces::Boot, "Boot"},
		{pieces::Cannon, "Cannon"},
		{pieces::Thimble, "Thimble"},
		{pieces::TopHat, "TopHat"},
		{pieces::Iron, "Iron"}
	};
	int _position;
};

