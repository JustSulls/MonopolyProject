#include "Utility.h"
utility::Utility::Utility() : Spot()
{
	utility_type = utility_type::Electric_Company;
	position = 0; //bad
	is_owned = false;
	this->spot_type = Spot::SpotType::utilities;
}
utility::Utility::Utility(int pos, std::string un) : Spot()
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
	Spot::spot_type = SpotType::utilities;
	Spot::name = un;
	Spot::position = pos;
}
