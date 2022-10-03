#pragma once
#include <string>

//const enum
const enum class SpotType {
	property,
	utilities,
	railroad,
	free_parking,
	chance,
	community_chest,
	jail,
	go,
	go_to_jail,
	taxes
};

class Spot
{
public:

	//constructors
	Spot(SpotType s, int p, std::string n);
	Spot();

	//member variables
	std::string name;
	SpotType spot_type;
	int position;
};
