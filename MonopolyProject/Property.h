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
};
