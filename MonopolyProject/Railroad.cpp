#include "Railroad.h"
Railroad::Railroad()
{
	railroad_type = railroad_types::B_0_Railroad;
	position = 0;
}
Railroad::Railroad(std::string name)
{

    if (name == "B_0_Railroad") {
        position = 25;
    }
    else if (name == "Pennsylvania_Railroad") {
        position = 15;
    }
    else if ("Reading_Railroad") {
        position = 5;
    }
    else{
        position = 35;
    }
}
int Railroad::get_landed_cost()
{
	//TODO: fix
	return 1;
}