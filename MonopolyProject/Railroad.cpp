#include "Railroad.h"
Railroad::Railroad() : Spot()
{
	railroad_type = railroad_types::B_0_Railroad;
	position = 0;
    is_owned = false;
    this->spot_type = SpotType::railroad;
}
Railroad::Railroad(std::string name) : Spot()
{

    if (name == "B_0_Railroad") {
        position = 25;
        railroad_type = railroad_types::B_0_Railroad;
    }
    else if (name == "Pennsylvania_Railroad") {
        position = 15;
        railroad_type = railroad_types::Pennsylvania_Railroad;
    }
    else if ("Reading_Railroad") {
        position = 5;
        railroad_type = railroad_types::Reading_Railroad;
    }
    else{
        position = 35;
        railroad_type = railroad_types::Short_Line;
    }
    is_owned = false;
    this->spot_type = SpotType::railroad;
}
int Railroad::get_landed_cost()
{
	//TODO: fix
	return 1;
}