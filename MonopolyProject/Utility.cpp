#include "Utility.h"
Utility::Utility()
{
	utility_type = utility_type::Electric_Company;
	position = 0; //bad
	is_owned = false;
	this->spot_type = SpotType::taxes_utilities;
}
Utility::Utility(int pos, std::string un)
{
	if (un == utility_names[0]){
		utility_type = utility_type::Electric_Company;
	} else {
		utility_type = utility_type::Water_Works;
	}
	position = pos;
	is_owned = false;
}

int Utility::get_landed_cost()
{
	return -1;
}
