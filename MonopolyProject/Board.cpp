#include "Board.h"
Board::Board()
{
	//Init properties
	//Property()
	for (int i = 0; i < NUMBER_BOARD_POSITIONS; i++)
	{
		//There are 40 spots on the board fill the vector of positions with the likeness
		positions.push_back(i);
	}
}