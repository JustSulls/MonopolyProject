#pragma once
#include <vector>
#include <string>
#include "Spot.h"

class Railroad: public Spot
{

public:
	enum class railroad_types {
		Reading_Railroad,
		Pennsylvania_Railroad,
		B_0_Railroad,
		Short_Line
	};
	//constructors
	Railroad();
	Railroad(std::string name);
	//member variables
	const static short cost = 200;
	railroad_types railroad_type;
	bool is_owned;
	//member functions
	int get_landed_cost();
	int railroad_positions[4] = { 5, 15, 25, 35 };
};

