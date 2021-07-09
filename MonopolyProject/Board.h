#pragma once
#include <vector>

class Board
{
public:
	const int LAST_BOARD_POSITION = 39;
	//0-39
	const int NUMBER_BOARD_POSITIONS = 40;
	Board();
	std::vector<int> positions;
};
