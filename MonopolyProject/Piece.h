#pragma once
#include <string>
#include <map>
#include "Logger.h"

namespace npiece
{
	static const uint16_t NUMBER_PIECES = 6;
	const std::string enum_str[NUMBER_PIECES] =
	{
		"Battleship",
		"Boot",
		"Cannon",
		"Thimble",
		"TopHat",
		"Iron"
	};
}
class Piece
{
public:
	Piece(int which = 0);
	enum class pieces {
		Battleship,
		Boot,
		Cannon,
		Thimble,
		TopHat,
		Iron
	}piece;
	int getPosition();
	void advancePosition(int numSpaces);
	void movePosition(int new_position);
	std::string str();
	static void presentPieceOptions();
	bool operator ==(const Piece& p);

private:
	std::string name;
	int _position;
	std::map<pieces, std::string> piece_map{
		{pieces::Battleship, "Battleship" },
		{pieces::Boot, "Boot"},
		{pieces::Cannon, "Cannon"},
		{pieces::Thimble, "Thimble"},
		{pieces::TopHat, "TopHat"},
		{pieces::Iron, "Iron"}
	};
};

