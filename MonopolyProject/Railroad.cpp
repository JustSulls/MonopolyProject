#include "Railroad.h"
Railroad::Railroad() : Spot()
{
	railroad_type = railroad_types::B_0_Railroad;
	position = 0;
    is_owned = false;
    Spot::spot_type = SpotType::railroad;
}
Railroad::Railroad(std::string name) : Spot()
{

    if (name == "B_0_Railroad") {
        position = position = railroad_positions[2];
        railroad_type = railroad_types::B_0_Railroad;
    }
    else if (name == "Pennsylvania_Railroad") {
        position = position = railroad_positions[1];
        railroad_type = railroad_types::Pennsylvania_Railroad;
    }
    else if ("Reading_Railroad") {
        position = railroad_positions[0];
        railroad_type = railroad_types::Reading_Railroad;
    }
    else{
        position = railroad_positions[3];
        railroad_type = railroad_types::Short_Line;
    }
    is_owned = false;
    Spot::spot_type = SpotType::railroad;
    Spot::name = name;
    Spot::position = position;
}
int Railroad::get_landed_cost()
{
	//TODO: fix
	return 1;
}