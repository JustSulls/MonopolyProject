#include "Spot.h"
Spot::Spot()
{
	spot_type = SpotType::property;
	name = "";
	position = -1;
}
Spot::Spot(SpotType s= SpotType::property, 
	int p=-1, 
	std::string n="")
{
	spot_type = s;
	name = n;
	position = p;
}