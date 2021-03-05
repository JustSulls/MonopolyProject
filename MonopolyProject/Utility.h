#pragma once
#include<string>

class Utility
{
public:
	enum class utility_type {
		Electric_Company,
		Water_Works
	};
	Utility();
	Utility(int pos, std::string un);

	//
	//member variables
	std::string utility_names[2] = { "Electric_Company", "Water_Works" };
	utility_type utility_type;
	int position;
	const static short cost = 150;
	bool is_owned;
	//todo: make sure two players can't have the same name
	std::string owner_name;
	//
	//member functions
	int get_landed_cost();
};

