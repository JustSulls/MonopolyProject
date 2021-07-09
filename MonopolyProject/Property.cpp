#include "Property.h"
Property::Property() : Spot()
{
	position = -1;
	color = Property::colors::brown;
	Spot::name = "";
	this->spot_type = Spot::SpotType::property;
	is_owned = false;
}
Property::Property(int pr[], 
	int rc[], 
	colors c, 
	std::string n, 
	int l, 
	SpotType type= Spot::SpotType::property) : Spot()
{
	Spot::name = n;
	Spot::position = l;
	Spot::spot_type = type;
	for (int i = 0; i < number_prices; i++)
	{
		prices[i] = pr[i];
	}
	for (int i = 0; i < number_rent_costs; i++)
	{
		rent_costs[i] = rc[i];
	}
	color = c;
	is_owned = false;
}
void Property::set_level(int setter)
{
	//todo: limit this
	if (8 > setter && setter > 0) {
		level l = static_cast<level>(setter);
	}
}