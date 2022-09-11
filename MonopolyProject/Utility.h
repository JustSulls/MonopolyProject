#pragma once
#include<string>
#include "Spot.h"

namespace utility
{
	const std::string utility_names[2] = { "Electric_Company", "Water_Works" };
	enum class utility_type {
		Electric_Company,
		Water_Works
	};

	class Utility : public Spot
	{
	public:

		Utility();
		Utility(int pos, std::string un);

		//member variables
		utility_type utility_type;
		int position;
		const static short cost = 150;
		bool is_owned;
		std::string owner_name;
	};
}
