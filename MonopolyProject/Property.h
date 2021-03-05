#pragma once
#include <string>
class Property
{
public:
	enum class colors {
		brown,
		light_blue,
		pink,
		orange,
		red,
		yellow,
		green,
		dark_blue
	};
	enum class level {
		alone,
		monopoly,
		with_1_house,
		with_2_houses,
		with_3_houses,
		with_4_houses,
		with_hotel,
		with_skyscraper
	};
	Property();
	Property(int prices[],
		int rent_costs[],
		colors c,
		std::string name,
		int location);
	const static int number_prices = 3;
	const static int number_rent_costs = 8;
	std::string name;
	colors color;
	int prices[number_prices] = { 0,0,0 };
	int rent_costs[number_rent_costs] = { 0,0,0,0,0,0,0,0 };
	int position;
	int rent_cost = 0;
	//todo:change this to enum
	level current_level = level::alone;
	void set_level(int setter);
};
