#include "Property.h"
Property::Property()
{
	position = 0;
	color = Property::colors::brown;
	name = "";
	this->spot_type = SpotType::property;
}
Property::Property(int pr[], int rc[], colors c, std::string n, int l, SpotType type=SpotType::property)
{
	for (int i = 0; i < number_prices; i++)
	{
		prices[i] = pr[i];
	}
	for (int i = 0; i < number_rent_costs; i++)
	{
		rent_costs[i] = rc[i];
	}
	color = c;
	name = n;
	position = l;
	Spot::spot_type = type;
}
void Property::set_level(int setter)
{
	//todo: limit this
	if (8 > setter && setter > 0) {
		level l = static_cast<level>(setter);
	}
}