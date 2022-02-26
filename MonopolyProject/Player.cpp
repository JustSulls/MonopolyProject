#include "Player.h"
Player::Player()
{
	name = "default";
	money = 1500;
}
Player::Player(std::string n)
{
	name = n;
	money = 1500;
}
void Player::collect(int amount)
{
	money += amount;
	std::cout << name << " collects " << amount << ".\n";
}
void Player::pay(int amount)
{
	money -= amount;
	std::cout << name << " pays " << amount << ".\n";
}
void Player::do_street_repairs()
{
	//Pay $40 per houseand $115 per hotel you own.
	unsigned int num_houses = 0;
	unsigned int num_hotels = 0;
	for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
	{
		int l = static_cast<int>(properties_owned[i]->current_level);
		if (l > 1)
		{
			num_houses += l - 1;//check property level enum 1!=1
			if (l == 6)//hotel 
			{
				num_hotels += 1;
			}
		}
	}
	unsigned int payment = ((40 * num_houses) + (115 * num_hotels));
	pay(payment);
}
void Player::do_general_repairs()
{
	//make repairs, for each house pay 25 for each hotel pay 100
	unsigned int num_houses = 0;
	unsigned int num_hotels = 0;
	for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
	{
		int l = static_cast<int>(properties_owned[i]->current_level);
		if (l > 1)
		{
			num_houses += l - 1;//check property level enum 1!=1
			if (l == 6)//hotel 
			{
				num_hotels += 1;
			}
		}
	}
	int payment = (25 * num_houses) + (100 * num_hotels);
}
bool Player::buy_property(Property* prop)
{
	try {
		if (prop->is_owned)
		{
			std::cout << prop->name << " already owned. Cannot purchase.\n";
			return false;
		}
		pay(prop->prices[0]);//printed price is prices[0]
		prop->is_owned = true;
		properties_owned.push_back(prop);
		std::cout << name << " now owns " << prop->name << ".\n";
		return true;
	}
	catch (const std::invalid_argument& ia) {
		std::cerr << "Invalid argument error: " << ia.what() << '\n';
	}
	return false;
}
bool Player::buy_railroad(Railroad* rail)
{
	try {
		if (rail->is_owned)
		{
			std::cout << rail->name << " already owned. Cannot purchase.\n";
			return false;
		}
		pay(rail->cost);//printed price is prices[0]
		railroads_owned.push_back(rail);
		std::cout << name << " now owns " << rail->name << ".\n";
		rail->is_owned = true;
		return true;
	}
	catch (const std::invalid_argument& ia) {
		std::cerr << "Invalid argument error: " << ia.what() << '\n';
	}
	return false;
}
bool Player::buy_utility(Utility* utility)
{
	try {
		if (utility->is_owned)
		{
			std::cout << utility->name << " already owned. Cannot purchase.\n";
			return false;
		}
		pay(utility->cost);//printed price is prices[0]
		utilities_owned.push_back(utility);
		utility->is_owned = true;
		return true;
	}
	catch (const std::invalid_argument& ia) {
		std::cerr << "Invalid argument error: " << ia.what() << '\n';
	}
	return false;
}
std::vector<Property*> Player::property_upgrades_available()
{
	std::vector<Property*>return_properties;
	if (!properties_owned.empty())
	{
		std::vector<Property::colors> vColorHolder;
		for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
		{
			if (properties_owned[i]->current_level < Property::level::with_skyscraper)	//if not already maxxed
			{
				vColorHolder.push_back(properties_owned[i]->color);
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
			for (unsigned int i = 0; i < vColorHolder.size() - 1; i++)
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
				for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i]->color == Property::colors::brown)	//if not already maxxed
					{
						return_properties.push_back(properties_owned[i]);
					}
				}
			}
			if (lightblue == ColorCount.maxLightBlue)
			{
				for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i]->color == Property::colors::light_blue)	//if not already maxxed
					{
						return_properties.push_back(properties_owned[i]);
					}
				}
			}
			if (pink== ColorCount.maxPink)
			{
				for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i]->color == Property::colors::pink)	//if not already maxxed
					{
						return_properties.push_back(properties_owned[i]);
					}
				}
			}
			if (orange== ColorCount.maxOrange)
			{
				for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i]->color == Property::colors::orange)	//if not already maxxed
					{
						return_properties.push_back(properties_owned[i]);
					}
				}
			}
			if (red == ColorCount.maxRed)
			{
				for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i]->color == Property::colors::red)	//if not already maxxed
					{
						return_properties.push_back(properties_owned[i]);
					}
				}
			}
			if (yellow== ColorCount.maxYellow)
			{
				for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i]->color == Property::colors::yellow)	//if not already maxxed
					{
						return_properties.push_back(properties_owned[i]);
					}
				}
			}
			if (green == ColorCount.maxGreen)
			{
				for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i]->color == Property::colors::green)	//if not already maxxed
					{
						return_properties.push_back(properties_owned[i]);
					}
				}
			}
			if (darkblue== ColorCount.maxDarkBlue)
			{
				for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i]->color == Property::colors::dark_blue)	//if not already maxxed
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
	std::cout << name << " rolled a " << ran << "." << std::endl;
	return ran;
}
bool Player::operator==(const Player& other)
{
	std::string n = other.name;
	if (n == other.name) return true;
	else return false;
}
bool Player::operator!=(const Player& other)
{
	std::string n = other.name;
	if (n != other.name) return true;	//todo:elaborate
	return false;
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
void Player::get_piece(Piece* p)
{
	this->piece = p;
}
