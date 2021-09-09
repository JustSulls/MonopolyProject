#pragma once
#include <string>

class Spot
{
public:
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

	//member variables
	SpotType spot_type;
	std::string name;
	int position;

	//constructors
	Spot(SpotType s, int p, std::string n);
	Spot();
};
