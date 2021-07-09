#include "Player.h"
Player::Player()
{
	name = "";
	money = 0;
}
Player::Player(std::string n)
{
	name = n;
	money = 0;
}
void Player::collect(int amount)
{
	money += amount;
}
void Player::pay(int amount)
{
	money -= amount;
}
bool Player::buy_property(Property prop)
{
	try {
		this->pay(prop.prices[0]);//printed price is prices[0]
		this->properties_owned.push_back(prop);
		prop.is_owned = true;
		return true;
	}
	catch (const std::invalid_argument& ia) {
		std::cerr << "Invalid argument error: " << ia.what() << '\n';
	}
	return false;
}
bool Player::buy_railroad(Railroad rail)
{
	try {
		this->pay(rail.cost);//printed price is prices[0]
		this->railroads_owned.push_back(rail);
		rail.is_owned = true;
		return true;
	}
	catch (const std::invalid_argument& ia) {
		std::cerr << "Invalid argument error: " << ia.what() << '\n';
	}
	return false;
}
bool Player::buy_utility(Utility utility)
{
	try {
		this->pay(utility.cost);//printed price is prices[0]
		this->utilities_owned.push_back(utility);
		utility.is_owned = true;
		return true;
	}
	catch (const std::invalid_argument& ia) {
		std::cerr << "Invalid argument error: " << ia.what() << '\n';
	}
	return false;
}
std::vector<Property> Player::property_upgrades_available()
{
	std::vector<Property>return_properties;
	if (!properties_owned.empty())
	{
		std::vector<Property::colors> vColorHolder;
		for (int i = 0; i < properties_owned.size() - 1; i++)
		{
			if (properties_owned[i].current_level < Property::level::with_skyscraper)	//if not already maxxed
			{
				vColorHolder.push_back(properties_owned[i].color);
			}
		}
		if (!vColorHolder.empty())
		{
			int brown = 0;
			int lightblue = 0;
			int pink = 0;
			int orange = 0;
			int red = 0;
			int yellow = 0;
			int green = 0;
			int darkblue = 0;
			for (int i = 0; i < vColorHolder.size() - 1; i++)
			{
				if (vColorHolder[i] == Property::colors::brown) brown++;
				else if (vColorHolder[i] == Property::colors::light_blue) lightblue++;
				else if (vColorHolder[i] == Property::colors::pink) pink++;
				else if (vColorHolder[i] == Property::colors::orange) orange++;
				else if (vColorHolder[i] == Property::colors::red) red++;
				else if (vColorHolder[i] == Property::colors::yellow) yellow++;
				else if (vColorHolder[i] == Property::colors::green) green++;
				else if (vColorHolder[i] == Property::colors::dark_blue) darkblue++;
			}
			if (brown == ColorCount.maxBrown)
			{
				for (int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i].color == Property::colors::brown)	//if not already maxxed
					{
						return_properties.push_back(properties_owned[i]);
					}
				}
			}
			if (lightblue == ColorCount.maxLightBlue)
			{
				for (int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i].color == Property::colors::light_blue)	//if not already maxxed
					{
						return_properties.push_back(properties_owned[i]);
					}
				}
			}
			if (pink== ColorCount.maxPink)
			{
				for (int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i].color == Property::colors::pink)	//if not already maxxed
					{
						return_properties.push_back(properties_owned[i]);
					}
				}
			}
			if (orange== ColorCount.maxOrange)
			{
				for (int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i].color == Property::colors::orange)	//if not already maxxed
					{
						return_properties.push_back(properties_owned[i]);
					}
				}
			}
			if (red == ColorCount.maxRed)
			{
				for (int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i].color == Property::colors::red)	//if not already maxxed
					{
						return_properties.push_back(properties_owned[i]);
					}
				}
			}
			if (yellow== ColorCount.maxYellow)
			{
				for (int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i].color == Property::colors::yellow)	//if not already maxxed
					{
						return_properties.push_back(properties_owned[i]);
					}
				}
			}
			if (green == ColorCount.maxGreen)
			{
				for (int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i].color == Property::colors::green)	//if not already maxxed
					{
						return_properties.push_back(properties_owned[i]);
					}
				}
			}
			if (darkblue== ColorCount.maxDarkBlue)
			{
				for (int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i].color == Property::colors::dark_blue)	//if not already maxxed
					{
						return_properties.push_back(properties_owned[i]);
					}
				}
			}
		}
	}
	else
	{
	return return_properties;
 }
}
int Player::throw_die()
{
	int ran;
	srand(time(NULL));
	ran = rand() % 6 + 1;
	std::cout << "You rolled a " << ran << "." << std::endl;
	return ran;
}
bool Player::operator==(const Player& other)
{
	std::string n = other.name;
	if (n == other.name) return true;
	else return false;
}
int Player::decide_buy_or_pass(Property property)
{
	//present options to player, bounds check answer, return it	
	int i = -1;
	while (i > 1 || i < 0)
	{
		std::cout << "Decide to buy or pass" << property.name << ": [0] no, [1] yes?\n";
		std::cin >> i;
	}
	return i;
}

int Player::decide_upgrade(Property prop)
{
	//present options to player, bounds check answer, return it
	int i = -1;
	while (i > 1 || i < 0)
	{
		std::cout << "Decide upgrade " << prop.name << ": [0] no, [1] yes?\n";
		std::cin >> i;
	}
	return i;
}

int Player::pick_piece()
{
	//present options to player, bounds check answer, return it
	int i = -1;
	while (i > 1 || i < 0)
	{
		std::cout << "Pick piece: [0] Destroyer, [1] Mercedes?\n";
		std::cin >> i;
	}
	return i;
}
