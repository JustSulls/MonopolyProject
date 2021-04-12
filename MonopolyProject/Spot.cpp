#include "Spot.h"
Spot::Spot()
{
	this->spot_type = SpotType::property;
}
Spot::Spot(SpotType s)
{
	this->spot_type = s;
}