#pragma once
#include <vector>
#include <string>
class Railroad
{

public:
	enum class railroad_types {
		Reading_Railroad,
		Pennsylvania_Railroad,
		B_0_Railroad,
		Short_Line
	};
	//constructors
	Railroad();
	Railroad(std::string name);
	//member variables
	const static short cost = 200;
	railroad_types railroad_type;
	int position;
	bool is_owned;
	//member functions
	int get_landed_cost();
};

