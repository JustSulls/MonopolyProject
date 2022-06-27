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
Property::colors Property::get_color()
{
	return color;
}
int Property::get_rent()
{
	int rent = 0;
	switch (current_level)
	{
	case level::alone:
		rent = rent_costs[0];
		break;
	case level::monopoly:
		rent = rent_costs[1];
		break;
	case level::with_1_house:
		rent = rent_costs[2];
		break;
	case level::with_2_houses:
		rent = rent_costs[3];
		break;
	case level::with_3_houses:
		rent = rent_costs[4];
		break;
	case level::with_4_houses:
		rent = rent_costs[5];
		break;
	case level::with_hotel:
		rent = rent_costs[6];
		break;
	case level::with_skyscraper:
		rent = rent_costs[7];
		break;
	}
	return rent;
}
std::string Property::getCurrentLevel()
{
	std::string returnStr;
	switch (current_level)
	{
	case level::alone:
		returnStr = "alone";
		break;
	case level::monopoly:
		returnStr = "monopoly";
		break;
	case level::with_1_house:
		returnStr = "with_1_house";
		break;
	case level::with_2_houses:
		returnStr = "with_2_houses";
		break;
	case level::with_3_houses:
		returnStr = "with_3_houses";
		break;
	case level::with_4_houses:
		returnStr = "with_4_houses";
		break;
	case level::with_hotel:
		returnStr = "with_hotel";
		break;
	case level::with_skyscraper:
		returnStr = "with_skyscraper";
		break;
	}
	return returnStr;
}
void Property::set_level(int setter)
{
	//todo: limit this
	if ((setter < 8) && (setter > 0)) {
		level l = static_cast<level>(setter);
		current_level = l;
	}
}

void Property::set_level(Property::level level)
{
	current_level = level;
}
