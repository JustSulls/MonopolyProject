#pragma once
#include <string>
#include "Spot.h"
#include <stdexcept>
#include <algorithm>

class Property: public Spot
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
		int location,
		Spot::SpotType type);
	Property& operator=(const Property& other);
	const static int number_prices = 3;
	const static int number_rent_costs = 8;
	colors color;
	colors get_color();
	const int posUpgradeCost = 2;
	int prices[number_prices] = { 0,0,0 };//{cost to purchase and own property, 
																				//	mortgage value, 
																				//	cost to upgrade building(house or skyscraper}
	int rent_costs[number_rent_costs] = { 0,0,0,0,0,0,0,0 };
	int get_rent();
	int get_upgrade_cost();
	level current_level = level::alone;
	std::string getCurrentLevel();
	void set_level(int setter);
	void set_level(Property::level level);
	bool is_owned;	
};
