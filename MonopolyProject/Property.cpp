#include "Property.h"
Property::Property() : Spot()
{
	position = -1;
	color = colors::brown;
	Spot::name = "";
	this->spot_type = SpotType::property;
	is_owned = false;
}
Property::Property(int pr[], 
	int rc[], 
	colors c, 
	std::string n, 
	int l, 
	SpotType type= SpotType::property) : Spot()
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
Property& Property::operator=(const Property& other)
{
	std::copy(std::begin(other.prices), std::end(other.prices), std::begin(prices));
	std::copy(std::begin(other.rent_costs), std::end(other.rent_costs), std::begin(rent_costs));
	current_level = other.current_level;
	color = other.color;
	is_owned = other.is_owned;
	return *this;
}
std::string Property::get_color()
{
	std::string theColor = "";
	switch (color)
	{
	case colors::brown:
		theColor = "brown";
		break;
	case colors::light_blue:
		theColor = "light blue";
		break;
	case colors::pink:
		theColor = "light pink";
		break;
	case colors::orange:
		theColor = "orange";
		break;
	case colors::red:
		theColor = "red";
		break;
	case colors::yellow:
		theColor = "yellow";
		break;
	case colors::green:
		theColor = "green";
		break;
	case colors::dark_blue:
		theColor = "dark blue";
		break;
	}
	return theColor;
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
int Property::get_upgrade_cost()
{
	return prices[posUpgradeCost];
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
	else {
		throw std::out_of_range("property level out of range");
	}
}
void Property::set_level(level level)
{
	current_level = level;
}
