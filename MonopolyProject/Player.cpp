#include "Player.h"
Player::Player()
{
	name = "default";
	money = 1500;
	total_payments_made = 0;
	total_payments_collected = 0;
	total_passed_go = 0;
}
Player::Player(std::string n)
{
	name = n;
	money = 1500;
	total_payments_made = 0;
	total_payments_collected = 0;
	total_passed_go = 0;
}
bool Player::has_get_out_of_jail_card()
{
	bool has = false;
	for (unsigned int i = 0; i < get_out_of_jail_cards.size(); i++)
	{
		if (get_out_of_jail_cards[i] == true)
		{
			has = true;
		}
	}
	return has;
}
void Player::collect(int amount)
{
	money += amount;
	total_payments_collected += amount;
	CLogger::GetLogger()->Log(name + " collects $" + std::to_string(amount) +
		" ($" + std::to_string(money) + " total).");
}
void Player::pay(int amount)
{
	money -= amount;
	total_payments_made += amount;
	CLogger::GetLogger()->Log(name + " pays $" + std::to_string(amount) + 
		" ($" + std::to_string(money) + " total).");
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
int Player::get_general_repair_cost()
{
	int payment = (25 * get_num_houses()) + (100 * get_num_hotels());
	return payment;
}
int Player::get_total_payments_collected()
{
	return total_payments_collected;
}
int Player::get_total_payments_made()
{
	return total_payments_made;
}
void Player::do_general_repairs()
{
	//make repairs, for each house pay 25 for each hotel pay 100
	int payment = get_general_repair_cost();
	this->pay(payment);
}
int Player::get_num_houses()
{
	unsigned int num_houses = 0;
	if (!properties_owned.empty())
	{
		for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
		{
			int l = static_cast<int>(properties_owned[i]->current_level);
			if (l > 1)
			{
				num_houses += l - 1;//check property level enum 1!=1
			}
		}
	}
	return num_houses;
}
int Player::get_num_hotels()
{
	unsigned int num_hotels = 0;
	if (!properties_owned.empty())
	{
		for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
		{
			int l = static_cast<int>(properties_owned[i]->current_level);
			if (l == 6)//hotel 
			{
				num_hotels += 1;
			}
		}
	}
	return num_hotels;
}
void Player::use_get_out_of_jail_card()
{
	if (!get_out_of_jail_cards.empty())
	{
		get_out_of_jail_cards.pop_back();
	}
	else throw std::range_error("Get out of jail cards vector empty.");
}
bool Player::buy_property(Property* prop)
{
	try {
		if (prop->is_owned)
		{
			CLogger::GetLogger()->Log(prop->name + " already owned. Cannot purchase.");
			return false;
		}
		pay(prop->prices[0]);//printed price is prices[0]
		prop->is_owned = true;
		properties_owned.push_back(prop);
		CLogger::GetLogger()->Log(name + " now owns " + prop->name);
		return true;
	}
	catch (const std::invalid_argument& ia) {
		std::cerr << "Invalid argument error: " << ia.what() << '\n';
	}
	return false;
}
bool Player::buy_railroad(nrails::Railroad* rail)
{
	try {
		if (rail->is_owned)
		{
			CLogger::GetLogger()->Log(rail->name + " already owned. Cannot purchase.");
			return false;
		}
		pay(rail->cost);//printed price is prices[0]
		railroads_owned.push_back(rail);
		CLogger::GetLogger()->Log(name + " now owns " + rail->name);
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
			CLogger::GetLogger()->Log(utility->name + " already owned. Cannot purchase.");
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
std::vector<Property> Player::property_upgrades_available()
{
	std::vector<Property>return_properties;
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
						return_properties.push_back(*properties_owned[i]);
					}
				}
			}
			if (lightblue == ColorCount.maxLightBlue)
			{
				for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i]->color == Property::colors::light_blue)	//if not already maxxed
					{
						return_properties.push_back(*properties_owned[i]);
					}
				}
			}
			if (pink== ColorCount.maxPink)
			{
				for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i]->color == Property::colors::pink)	//if not already maxxed
					{
						return_properties.push_back(*properties_owned[i]);
					}
				}
			}
			if (orange== ColorCount.maxOrange)
			{
				for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i]->color == Property::colors::orange)	//if not already maxxed
					{
						return_properties.push_back(*properties_owned[i]);
					}
				}
			}
			if (red == ColorCount.maxRed)
			{
				for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i]->color == Property::colors::red)	//if not already maxxed
					{
						return_properties.push_back(*properties_owned[i]);
					}
				}
			}
			if (yellow== ColorCount.maxYellow)
			{
				for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i]->color == Property::colors::yellow)	//if not already maxxed
					{
						return_properties.push_back(*properties_owned[i]);
					}
				}
			}
			if (green == ColorCount.maxGreen)
			{
				for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i]->color == Property::colors::green)	//if not already maxxed
					{
						return_properties.push_back(*properties_owned[i]);
					}
				}
			}
			if (darkblue== ColorCount.maxDarkBlue)
			{
				for (unsigned int i = 0; i < properties_owned.size() - 1; i++)
				{
					if (properties_owned[i]->color == Property::colors::dark_blue)	//if not already maxxed
					{
						return_properties.push_back(*properties_owned[i]);
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
	CLogger::GetLogger()->Log(name + " rolled a " + std::to_string(ran) + ".");
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
		CLogger::GetLogger()->Log("Decide upgrade " + prop.name + ": [0] no, [1] yes?");
		std::cin >> i;
	}
	return i;
}
void Player::get_piece(Piece* p)
{
	this->piece = p;
}
