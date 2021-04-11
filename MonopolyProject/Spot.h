#pragma once
class Spot
{
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
	Spot(SpotType s);
	
};

