#include "Spot.h"
Spot::Spot()
{
	this->spot_type = SpotType::property;
}
Spot::Spot(SpotType s,  short p, std::string n)
{
	spot_type = s;
	position = p;
	name = n;
}