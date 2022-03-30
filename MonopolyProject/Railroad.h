#pragma once
#include <vector>
#include <string>
#include "Spot.h"

namespace nrails
{
	const int railroad_positions[4] = { 5, 15, 25, 35 };
	const enum class railroad_types {
		Reading_Railroad,
		Pennsylvania_Railroad,
		B_0_Railroad,
		Short_Line
	};
	class Railroad : public Spot
	{
	public:
		//constructors
		Railroad();
		Railroad(std::string name);
		//member variables
		const static short cost = 200;
		railroad_types railroad_type;
		bool is_owned;
		//member functions
	};
}

