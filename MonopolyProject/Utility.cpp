#include "Utility.h"
Utility::Utility() : Spot()
{
	utility_type = utility_type::Electric_Company;
	position = 0; //bad
	is_owned = false;
	this->spot_type = Spot::SpotType::taxes_utilities;
}
Utility::Utility(int pos, std::string un) : Spot()
{
	if (un == utility_names[0])
	{
		utility_type = utility_type::Electric_Company;
	} else 
	{
		utility_type = utility_type::Water_Works;
	}
	position = pos;
	is_owned = false;
	//parent class members (Spot)
	Spot::spot_type = SpotType::taxes_utilities;
	Spot::name = un;
	Spot::position = pos;
}

int Utility::get_landed_cost()
{
	return -1;
}
