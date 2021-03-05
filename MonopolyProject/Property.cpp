#include "Property.h"
Property::Property()
{
	position = 0;
	color = Property::colors::brown;
	name = "";
}
Property::Property(int pr[], int rc[], colors c, std::string n, int l)
{
	for (int i = 0; i < number_prices; i++)
	{
		prices[i] = pr[i];
	}
	for (int i = 0; i < number_rent_costs; i++)
	{
		rent_costs[i] = rc[i];
	}
	color = c;
	name = n;
	position = l;
}