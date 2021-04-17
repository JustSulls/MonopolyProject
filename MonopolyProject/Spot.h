#pragma once
#include <string>
class Spot
{
public:
	enum class SpotType {
		property,
		taxes_utilities,
		railroad,
		free_parking,
		chance,
		community_chest,
		jail,
		go,
		go_to_jail
	};
	SpotType spot_type;
	Spot(SpotType s, short p, std::string n);
	Spot();
	std::string name;
	short position;
};
