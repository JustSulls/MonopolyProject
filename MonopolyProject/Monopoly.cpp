#include "Monopoly.h"

void Monopoly::init_properties()
{
	std::fstream myfile;
	try {
		myfile.open("C:/Users/jsul2/Documents/monopoly_properties.csv"); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
	std::string value;
	std::vector<std::string> holding;

	while (myfile.good())
	{
		std::getline(myfile, value); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
		//std::cout << std::string(value) << std::endl; // display value removing the first and the last character from it
		holding.push_back(value);
	}
	std::vector<std::string> result;
	//get property info in substr, frmt into result vector
	for (unsigned int i = 0; i < holding.size(); i++)
	{
		std::stringstream s_stream(holding.at(i));
		while (s_stream.good()) {
			std::string substr;
			std::getline(s_stream, substr, ',');
			result.push_back(substr);
		}
	}
	const int num_properties = 22;
	const int num_elements_in_property = 14;
	//Generate property info and create property obj (excluding utilities)
	for (int n = 1; n < num_properties + 1; n++) //1 to skip first row in csv where titles are, +1 to adjust for that
	{
		int m = num_elements_in_property * n;
		std::string property_name = result.at(m + 0);
		int alone = std::stoi(result.at(m + 1));
		int monopoly = std::stoi(result.at(m + 2));
		int  with_1_house = std::stoi(result.at(m + 3));
		int  with_2_house = std::stoi(result.at(m + 4));
		int with_3_house = std::stoi(result.at(m + 5));
		int with_4_house = std::stoi(result.at(m + 6));
		int  with_hotel = std::stoi(result.at(m + 7));
		int  printed_price = std::stoi(result.at(m + 8));
		int  mortgage_value = std::stoi(result.at(m + 9));
		int  building_costs = std::stoi(result.at(m + 10));
		int  with_skyscraper = std::stoi(result.at(m + 11));
		std::string color = result.at(m + 12);
		int location = std::stoi(result.at(m + 13));
		//setup the parameters for the constructor for the property to be created
		//these constants are in Property.h
		int prices[3];
		prices[0] = printed_price;
		prices[1] = mortgage_value;
		prices[2] = building_costs;
		int rent_costs[8];
		rent_costs[0] = alone;
		rent_costs[1] = monopoly;
		rent_costs[2] = with_1_house;
		rent_costs[3] = with_2_house;
		rent_costs[4] = with_3_house;
		rent_costs[5] = with_4_house;
		rent_costs[6] = with_hotel;
		rent_costs[7] = with_skyscraper;
		//stupid color transformer replace this
		Property::colors the_color = Property::colors::brown;
		switch (color.at(0)) {
		case ('b'):
			the_color = Property::colors::brown;
			break;
		case('l'):
			the_color = Property::colors::light_blue;
			break;
		case('p'):
			the_color = Property::colors::pink;
			break;
		case('o'):
			the_color = Property::colors::orange;
			break;
		case('r'):
			the_color = Property::colors::red;
			break;
		case('y'):
			the_color = Property::colors::yellow;
			break;
		case('g'):
			the_color = Property::colors::green;
			break;
		case('d'):
			the_color = Property::colors::dark_blue;
			break;
		}
		//create the property
		Property the_property(prices, rent_costs, the_color, property_name, location, Spot::SpotType::property);
		//place properties in maps
		properties.push_back(the_property);
	}
}

void Monopoly::init_railroads()
{
	for (unsigned int i = 0; i < railroad_names.size(); i++)
	{
		std::string rn = railroad_names.at(i);
		nrails::Railroad r(rn);
		railroads.push_back(r);
	}
}

void Monopoly::init_utilities()
{
	for (int i = 0; i < 2; i++)
	{
		int pos = utility_positions[i];
		Utility the_utility(pos, utility_names[i]);
		utilities.push_back(the_utility);
		map_utility[utility_names[i]] = the_utility;
	}
}

void Monopoly::init_cards()
{
	std::fstream myfile;
	myfile.open("C:/Users/jsul2/Documents/monopoly_cards.csv"); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
	std::string value;
	std::vector<std::string> holding;
	while (myfile.good())
	{
		std::getline(myfile, value); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
		//std::cout << std::string(value) << std::endl; // display value removing the first and the last character from it
		holding.push_back(value);
	}
	std::vector<std::string> result;
	for (unsigned int i = 0; i < holding.size(); i++)
	{
		std::stringstream s_stream(holding.at(i));
		while (s_stream.good()) {
			std::string substr;
			std::getline(s_stream, substr, ',');
			result.push_back(substr);
		}
	}
	const int num_chance_cards = 16;
	const int num_community_chest = 17;
	const int num_elements_in_card = 3;

	for (int i = 1; i < num_chance_cards + num_community_chest + 1; i++)
	{
		int m = num_elements_in_card * i;
		int card_id = std::stoi(result.at(m));
		std::string card_text = result.at(m + 1);
		std::string card_type = result.at(m + 2);

		//construct object here
		Card::card_type the_type;
		if (card_type == "chance") {
			the_type = Card::card_type::Chance;
		}
		else {
			the_type = Card::card_type::Community_Chest;
		}

		Card the_card(card_text, the_type, card_id);
		//Split cards into two decks
		if (the_type == Card::card_type::Chance) chance_cards.push_back(the_card);
		else community_cards.push_back(the_card);
		//All cards go here
		cards.push_back(the_card);
	}
	//shuffle deck here
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(cards), std::end(cards), rng);
}

void Monopoly::init_board()
{
	//put properties railroads utilities etc. in board as spots
	Spot spot_go(Spot::SpotType::go, 0, "go");
	spots.push_back(spot_go);
	Spot spot_cChest1(Spot::SpotType::community_chest, 2, "community chest 1");
	spots.push_back(spot_cChest1);
	Spot spot_cChest2(Spot::SpotType::community_chest, 17, "community chest 2");
	spots.push_back(spot_cChest2);
	Spot spot_cChest3(Spot::SpotType::community_chest, 33, "community chest 3");
	spots.push_back(spot_cChest3);
	Spot spot_chance1(Spot::SpotType::chance, 7, "chance 1");
	spots.push_back(spot_chance1);
	Spot spot_chance2(Spot::SpotType::chance, 22, "chance 2");
	spots.push_back(spot_chance2);
	Spot spot_chance3(Spot::SpotType::chance, 36, "chance 3");
	spots.push_back(spot_chance3);
	Spot spot_jail(Spot::SpotType::jail, 10, "jail or just visiting");
	spots.push_back(spot_jail);
	Spot spot_free_parking(Spot::SpotType::free_parking, 20, "free parking");
	spots.push_back(spot_free_parking);
	Spot spot_go_to_jail(Spot::SpotType::go_to_jail, 30, "go to jail");
	spots.push_back(spot_go_to_jail);
	Spot tax_income(Spot::SpotType::taxes, 4, "income tax");
	spots.push_back(tax_income);
	Spot utility_electric(Spot::SpotType::utilities, 12, "electic company");
	spots.push_back(utility_electric);
	Spot utility_water(Spot::SpotType::utilities, 28, "water works");
	spots.push_back(utility_water);
	Spot tax_luxury(Spot::SpotType::taxes, 38, "luxury tax");
	spots.push_back(tax_luxury);
}

void Monopoly::init_pieces()
{
	for (int i = 0; i < npiece::NUMBER_PIECES; i++)
	{
		pieces.push_back(Piece(i));
	}
}

void Monopoly::init_players(int num)
{
	//todo:this array isn't being used atm
	Player** array = new Player * [num];
	for (int i = 0; i < num; i++)
	{
		players.push_back(new Player(std::to_string(i+1)));
	}
}

void Monopoly::give_active_players_pieces()
{
	for (int i = 0; i < players.size(); i++)
	{
		players.at(i)->get_piece(&pieces.at(i));
	}
}

int Monopoly::pick_piece(Player& player)
{
	//present options to player, bounds check answer, return it
	int answer = -1;
	while (answer > npiece::NUMBER_PIECES - 1 || answer < 0)
	{
		std::cout << "Pick piece: \n";
		Piece::presentPieceOptions();
		std::cin >> answer;
	}
	player.get_piece(&pieces.at(answer));
	return answer;
}

int Monopoly::throw_die(Player player)
{
	die_roll = player.throw_die();
	return die_roll;
}

Spot* Monopoly::get_spot(int position)
{
	for (unsigned int i = 0; i < spots.size(); i++)
	{
		if (spots[i].position == position)
		{
			return &spots[i];
		}
	}
	for (unsigned int i = 0; i < properties.size(); i++)
	{
		if (properties[i].position == position)
		{
			return &properties[i];
		}
	}
	for (unsigned int i = 0; i < utilities.size(); i++)
	{
		if (utilities[i].position == position)
		{
			return &utilities[i];
		}
	}
	for (unsigned int i = 0; i < railroads.size(); i++)
	{
		if (railroads[i].position == position)
		{
			return &railroads[i];
		}
	}
}

Utility* Monopoly::get_utility(int position)
{
	for (unsigned int i = 0; i < utilities.size(); i++)
	{
		if (utilities[i].position == position)
		{
			return &utilities[i];
		}
	}
	return nullptr;
}

Utility* Monopoly::advance_to_nearest_utility(Piece* piece)
{
	// get piece position
	int piece_position = piece->getPosition();
	static const int num_utilities = 2;
	int differences[num_utilities] = { 0, 0 };
	int shortest_difference = 0;
	//get utility positions
	for (int i = 0; i < num_utilities; i++)
	{
		differences[i] = utilities.at(i).position - piece_position;
	}
	//find shortest positive distance (utility - piece) && (delta >=1 )
	int which_pos_was_shortest;
	for (int i = 0; i < num_utilities; i++)
	{
		if (shortest_difference == 0)
		{
			shortest_difference = differences[i];
			which_pos_was_shortest = i;
		}
		else if (shortest_difference > differences[i])
		{
			shortest_difference = differences[i];
			which_pos_was_shortest = i;
		}
	}

	//advance token to that utility (no mention of passing go $$)
	piece->movePosition(utilities.at(which_pos_was_shortest).position);
	std::cout << piece->str() << " moved to " << utilities.at(which_pos_was_shortest).name << ".\n";
	//piece.getPosition() = utilities.at(which_pos_was_shortest).position;

	//will add rest of card here
	try {
		return &utilities.at(which_pos_was_shortest);
	}
	catch (std::exception e)
	{
		std::cerr << "Invalid argument error: " << e.what() << '\n';
	}
}

nrails::Railroad* Monopoly::advance_to_nearest_railroad(Piece* piece)
{
	Player* player_ptr = get_player(*piece);
	nrails::Railroad* rail_ptr = get_nearest_railroad(*player_ptr);
	move_piece(player_ptr, *rail_ptr);
	return rail_ptr;
	//todo:test this
}

nrails::Railroad* Monopoly::get_nearest_railroad(Player& player)
{
	// get piece position
	int piece_position = player.piece->getPosition();
	static const int num_railroads = 4;
	int differences[num_railroads] = { 0, 0, 0, 0 };
	int shortest_difference = 0;
	//get railroad positions
	for (int i = 0; i < num_railroads; i++)
	{
		differences[i] = railroads.at(i).position - piece_position;
	}
	//find shortest positive distance (railroad - piece) && (delta >=1 )
	int which_pos_was_shortest;
	for (int i = 0; i < num_railroads; i++)
	{
		if (shortest_difference == 0)
		{
			shortest_difference = differences[i];
			which_pos_was_shortest = i;
		}
		else if (shortest_difference > differences[i])
		{
			shortest_difference = differences[i];
			which_pos_was_shortest = i;
		}
	}
	nrails::Railroad* rail_ptr = new nrails::Railroad();
	rail_ptr = &railroads.at(which_pos_was_shortest);
	return rail_ptr;
}

Player* Monopoly::get_owner(std::string spot_name)
{
	for (unsigned int i = 0; i < players.size(); i++)
	{
		for (unsigned int j = 0; j < players[i]->properties_owned.size(); j++)
		{
			if (players[i]->properties_owned[j]->name == spot_name)
			{
				return players[i];
			}
		}
		for (unsigned int j = 0; j < players[i]->railroads_owned.size(); j++)
		{
			if (players[i]->railroads_owned[j]->name == spot_name)
			{
				return players[i];
			}
		}
		for (unsigned int j = 0; j < players[i]->utilities_owned.size(); j++)
		{
			if (players[i]->utilities_owned[j]->name == spot_name)
			{
				return players[i];
			}
		}
	}
	//todo:get rid of this shou ld never happen
	return nullptr;
}

Card Monopoly::draw_community()
{
	try {
		Card the_card = community_cards.back();	//todo:getting out of range exception here when community_cards has capacity 19 but cant see each card
		community_cards.pop_back();
		return the_card;
	}
	catch ([[maybe_unused]]const std::exception& e) {
		//todo: get rid of blank card
		Card c;
		return c;
	}
	
}

Card Monopoly::draw_chance()
{
	try {
		Card the_card = chance_cards.back();
		chance_cards.pop_back();
		return the_card;
	}
	catch ([[maybe_unused]]const std::exception& e) {
		//todo: get rid of blank card
		Card c;
		return c;
	}
}

int Monopoly::get_railroad_rent(Player player)
{
	/*1 Railroad Owned: $25
	2 Railroads Owned : $50
	3 Railroads Owned : $100
	4 Railroads Owned : $200.*/
	//TODO: fix
	int rails_owned = 0;
	for (unsigned int i = 0; i < player.railroads_owned.size(); i++)
	{
		rails_owned += 1;
	}
	int rent_owed = 0;
	if (rails_owned == 1) rent_owed = 25;
	if (rails_owned == 2) rent_owed = 50;
	if (rails_owned == 3) rent_owed = 100;
	if (rails_owned == 4) rent_owed = 200;
	return rent_owed;
}

Player* Monopoly::get_player(Piece p)
{
	for (int i = 0; i < players.size(); i++)
	{
		if (*players.at(i)->piece == p)
		{
			return players.at(i);
		}
	}
	return nullptr;
}

bool Monopoly::decide_buy_or_pass(Property prop, Player player)
{
	//present options to player, bounds check answer, return it	
	int answer = -1;
	while (answer > 1 || answer < 0)
	{
		std::cout << player.name << " decide to buy or pass " << prop.name << " for " <<
			prop.prices[0] << " [0] no, [1] yes?\n";
		std::cin >> answer;
	}
	if (answer == 0)
	{
		return false;
	}
	else return true;
}

bool Monopoly::decide_buy_or_pass(Utility util, Player player, bool testing)
{
	if (testing)
	{
		return true;
	}
	else {
		int answer = -1;
		std::cin >> answer;
		while (answer > 1 || answer < 0)
		{
			std::cout << player.name << " decide to buy or pass " << util.name << " for " <<
				util.cost << " [0] no, [1] yes?\n";
			std::cin >> answer;
		}
		if (answer == 0)
		{
			return false;
		}
		else return true;
	}
}

bool Monopoly::decide_buy_or_pass(nrails::Railroad rail, Player player, int answer)
{
	while (answer > 1 || answer < 0)
	{
		std::cout << player.name << " decide to buy or pass " << rail.name << " for " <<
			rail.cost << " [0] no, [1] yes?\n";
		std::cin >> answer;
	}
	if (answer == 0)
	{
		return false;
	}
	else return true;
}

bool Monopoly::decide_upgrade(Property prop, Player player)
{
	//TODO:
	//present options
	int answer = player.decide_upgrade(prop);
	//decide what to return
	return false;
}

bool Monopoly::passes_go(Piece* piece, int n)
{
	//TODO::confirm this 
	if ((piece->getPosition() + n) > board.LAST_BOARD_POSITION)
	{
		return true;
	}
	else return false;
}

void Monopoly::play_game()
{
	std::cout << "Game started." <<std::endl;
	//loop 
	while (!game_over)
	{
		for (unsigned int i = 0; i < players.size(); i++)
		{
			//wait for player roll
			Player* activePlayer = players.at(i);
			//decide upgrade logic
			std::vector<Property*> potential_upgrades = activePlayer->property_upgrades_available();
			if (!potential_upgrades.empty())
			{
				for (unsigned int i = 0; i < potential_upgrades.size() - 1; i++)
				{
					activePlayer->decide_upgrade(*potential_upgrades[i]);
				}
			}
			//playern rolls 
			throw_die(*activePlayer);
			//playern moves based on roll
			move_piece(activePlayer, die_roll);
			//TODO:call move piece (figure out which ones to get rid of) 
			Spot* the_spot = get_spot(activePlayer->piece->getPosition());
			do_spot_action(the_spot, activePlayer);
		}
	}
	//todo:game over now handle that

}

void Monopoly::pay_rent(Player& player, Property property)
{
	try {
		//TODO: get real rent to pay from property
		int payment = property.rent_costs[0];
		player.pay(payment);
		//TODO: make sure a player owns this first
		Player* owner = get_owner(property.name);
		owner->collect(payment);
	}
	catch (const std::invalid_argument& ia) {
		std::cerr << "Invalid argument error: " << ia.what() << '\n';
	}
}

void Monopoly::pay_rent(Player& player, nrails::Railroad railroad)
{
	try {
		Player* owner = get_owner(railroad.name);
		int rent = get_railroad_rent(*owner);
		player.pay(rent);
		owner->collect(rent);
	}
	catch (const std::invalid_argument& ia) {
		std::cerr << "Invalid argument error: " << ia.what() << '\n';
	}
}

void Monopoly::pay_utilities(Player& player, Utility& utility)
{
	try {
		player_throw_die_pay_owner(player, utility);
	}
	catch (const std::invalid_argument& ia) {
		std::cerr << "Invalid argument error: " << ia.what() << '\n';
	}
}

void Monopoly::send_player_to_jail(Player& p)
{
	//go to jail
	p.in_jail = true;
	p.piece->movePosition(position_jail);//jail location 10 
	std::cout << p.name << " is now in jail.\n";
}

void Monopoly::upgrade_property(Property& property)
{
	//TODO: make sure a player owns this first
	Player* owner = get_owner(property.name);
	int price = property.prices[0];
	//owner pays upgrade price
	owner->pay(price);
	//upgrade property
	//todo:fix this, overload operator??
	int current_l = static_cast<int>(property.current_level);
	int next_l = 0;
	if (current_l < 7)
	{
		next_l += current_l + 1;
	}
	property.set_level(next_l);
}

void Monopoly::do_card_action(Card c, Player* player, bool testing)
{
	std::cout << player->name << " draws \"" << c.text << "\".\n";
	Utility* util;
	//Utility tempUtil;//todo::removing pointer to util above, this partialy complete
	nrails::Railroad* railroad;
	nrails::Railroad tempRailroad;
	Spot* s;
	switch (c.id) {
	case 1:
		//Advance to GO. (Collect $200)
		player->collect(200);
		break;
	case 2:
		//Advance to Illinois Avenue. If you pass GO  collect $200.
		move_piece(player, map_property["Illinois Avenue"]);
		break;
	case 3:
		move_piece(player, map_property["St. Charles Place"]);
		break;
	case 4:
		//Advance token to nearest Utility. If unowned 
		//you may buy it from the Bank. If owned throw 
		//dice and pay owner a total 10 times the amount thrown.
		util = advance_to_nearest_utility(player->piece);
		//check if owned
		if (util->is_owned)//todo: this should trigger but isn't
		{
			//?yes player throw dice and pay owner total 10 times.
			player_throw_die_pay_owner(*player, *util);
		}
		else
		{
			if (testing)
			{
				decide_buy_or_pass(*util, *player, true);//returns true 
				player->pay(util->cost);
				//add utility to player's utilities
				player->utilities_owned.push_back(util);
				util->is_owned = true;//todo:does not update util outside of this func
			}
			else
			{
				//?no offer player to buy that utility
				if (decide_buy_or_pass(*util, *player))
				{
					player->pay(util->cost);
					//add utility to player's utilities
					player->utilities_owned.push_back(util);
					util->is_owned = true;
					//mapSpotNameGetOwner[util.name] = player;
				};
			}
		}
		break;
	case 5:
		/*Advance token to the nearest Railroadand pay owner
		twice the rental to which he is otherwise entitled.
		If Railroad is unowned you may buy it from the Bank*/
		railroad = advance_to_nearest_railroad(player->piece);//todo make this func not return a railroad and add a func to do that separately
		if (railroad->is_owned)
		{
			Player* the_owner = get_owner(railroad->name);
			int rent_cost = get_railroad_rent(*the_owner);
			the_owner->collect(2 * rent_cost);
		}
		else
		{
			if (decide_buy_or_pass(*railroad, *player, 1))//offer player buy from bank//testing so always enter yes to buy
			{
				player->pay(railroad->cost);
				railroad->is_owned = true;
				player->railroads_owned.push_back(railroad);
			}
		}
		break;
	case 6:
		//Bank pays you dividend of $50.
		player->collect(50);
		break;
	case 7:
		//get out of jail card
		player->get_out_of_jail_cards.push_back(true);
		break;
	case 8:
		//go back 3 spaces
		player->piece->advancePosition(-3);
		//todo:
		//do an action at this new position
		s = get_spot(player->piece->getPosition());
		if (!testing)
		{	//skip if testing
			do_spot_action(s, player);
		}
		break;
	case 9:
		//go to jail, directly, do not collect 200 if pass go
		send_player_to_jail(*player);
		break;
	case 10:
		//make repairs, for each house pay 25 for each hotel pay 100
		player->do_general_repairs();
		break;
	case 11:
		//pay poor tax of 15
		player->pay(15);
		break;
	case 12:
		//go to reading railroad, if pass go collect 200
		move_piece(player, 5);	//reading railroad position
		break;
	case 13:
		//take a walk on the boardwalk. advance token to boardwalk.
		move_piece(player, map_property["Boardwalk"]);
		break;
	case 14:
		//you have been elected chariman of the board. pay each player $50		
		for (unsigned int i = 0; i < players.size() - 1; i++)
		{
			if (player != players[i])//if not this player
			{
				player->pay(50);
				players[i]->collect(50);
			}
		}
		break;
	case 15:
		//your building and land matures. collect $150
		player->collect(150);
		break;
	case 16:
		//You have won a crossword competition. Collect $100.
		player->collect(100);
		break;
	case 17:
		//Advance to GO. Collect $200.
		s = get_spot(0);
		move_piece(player, *s);
		break;
	case 18:
		//Bank error in your favor. Collect $200.
		player->collect(200);
		break;
	case 19:
		//Doctor's fees. Pay $50.
		player->pay(50);
		break;
	case 20:
		//From sale of stock you get $50.
		player->collect(50);
		break;
	case 21:
		//Get Out of Jail Free. This card may be kept until needed or sold/traded.
		player->get_out_of_jail_cards.push_back(true);
		break;
	case 22:
		//Go to Jail. Go directly to jail. Do not pass GO. Do not collect $200.
		send_player_to_jail(*player);
		break;
	case 23:
		//Grand Opera Night. Collect $50 from every player for opening night seats.
		for (unsigned int i = 0; i < players.size(); i++)
		{
			if (player != players[i])//if not this player
			{
				players[i]->pay(50);
				player->collect(50);
			}
		}
		break;
	case 24:
		//Holiday fund matures. Receive $100.
		player->collect(100);
		break;
	case 25:
		//Income tax refund. Collect $20.
		player->collect(20);
		break;
	case 26:
		//It is your birthday. Collect $10 from every player.
		for (unsigned int i = 0; i < players.size() - 1; i++)
		{
			if (player != players[i])//if not this player
			{
				players[i]->pay(10);
				player->collect(10);
			}
		}
		break;
	case 27:
		//Life insurance matures. Collect $100
		player->collect(100);
		break;
	case 28:
		//Hospital Fees. Pay $50.
		player->pay(50);
		break;
	case 29:
		//School fees. Pay $50.
		player->pay(50);
		break;
	case 30:
		//Receive $25 consultancy fee.
		player->collect(25);
		break;
	case 31:
		//You are assessed for street repairs: Pay $40 per house and $115 per hotel you own.
		player->do_street_repairs();
		break;
	case 32:
		//You have won second prize in a beauty contest. Collect $10.
		player->collect(10);
		break;
	case 33:
		//You inherit $100.
		player->collect(100);
		break;
	}
}

void Monopoly::do_spot_action(Spot* theSpot, Player* activePlayer)
{
	if (theSpot->spot_type == Spot::SpotType::chance)
	{
		if (!chance_cards.empty())
		{
			Card c = draw_chance();
			//do card action
			do_card_action(c, activePlayer);
		}
		else std::cout << "Chance card pile empty.\n";
	}
	else if (theSpot->spot_type == Spot::SpotType::community_chest)
	{
		if (!community_cards.empty())
		{
			Card c = draw_community();
			//do card action
			do_card_action(c, activePlayer);
		}
		else std::cout << "Community chest card pile empty.\n";
	}
	else if (theSpot->spot_type == Spot::SpotType::free_parking)
	{
		//do nothing 
		//free parking
	}
	else if (theSpot->spot_type == Spot::SpotType::go)
	{
		// do nothing
		// go collect money handled at move function
		// todo:confirm this is best
	}
	else if (theSpot->spot_type == Spot::SpotType::go_to_jail)
	{
		send_player_to_jail(*activePlayer);
	}
	else if (theSpot->spot_type == Spot::SpotType::jail)
	{
		//do nothing
		//just visiting
	}
	else if (theSpot->spot_type == Spot::SpotType::property)
	{
		//property handle
		//if owned, pay owner
		//if unowned present option to buy property
		Property* prop = get_property(theSpot->position);
		if (prop->is_owned)
		{
			//pay rent
			pay_rent(*activePlayer, *prop);
		}
		else
		{
			if (decide_buy_or_pass(*prop, *activePlayer))
			{
				activePlayer->buy_property(prop);
			}
			//TODO:else auction off property, currently nothing
		}
	}
	else if (theSpot->spot_type == Spot::SpotType::railroad)
	{
		//railroad handle
		//if owned, pay owner
		//if unowned present option to buy property
		nrails::Railroad* railroad = get_railroad(theSpot->position);
		if (railroad->is_owned)
		{
			//pay rent
			pay_rent(*activePlayer, *railroad);
		}
		else
		{
			if (decide_buy_or_pass(*railroad, *activePlayer))
			{
				activePlayer->buy_railroad(railroad);
				//TODO: check if this returns true or false
			}
			//else pass because railroad
		}
	}
	else if (theSpot->spot_type == Spot::SpotType::utilities)
	{
		//taxes utilities handle
		//if utility owned, pay owner
		//if utility unowned present option to buy utility
		Utility* utility = get_utility(theSpot->position);
		if (utility->is_owned)
		{
			pay_utilities(*activePlayer, *utility);
		}
		else
		{
			if (decide_buy_or_pass(*utility, *activePlayer))
			{
				activePlayer->buy_utility(utility);
				//TODO: check if this returns true or false
			}
			//else pass because railroad
		}
	}
	else if (theSpot->spot_type == Spot::SpotType::taxes)
	{
		if (theSpot->position == 4)
		{
			//income tax
			activePlayer->pay(200);
		}
		else if (theSpot->position == 38)
		{
			//luxury tax
			activePlayer->pay(150);
		}
	}
}

void Monopoly::player_throw_die_pay_owner(Player& p, Utility& the_utility)
{
	int cost_multiplier = 0;
	//get utility owner
	Player* the_owner = get_owner(the_utility.name);
	//The cost is dice roll(n) times 4 for one utility, 10 for both
	//e.g. roll is 5 owner owns one utility cost is (5)*4 = 20
	if (the_owner->utilities_owned.size() > 1)//owns 2
	{
		cost_multiplier = 10;
	}
	else if (the_owner->utilities_owned.size() == 1)
	{
		cost_multiplier = 4;
	}
	std::cout << p.name << " throws die and pays owner ("<<the_owner->name 
		<<") a total of (" << cost_multiplier << ")  times.\n";
	throw_die(p);
	int cost = die_roll * cost_multiplier;
	p.pay(cost);
	the_owner->collect(cost);
}

int Monopoly::get_utility_cost_multiplier(Player& owner)
{
	int cost_multiplier = 0;
	if (owner.utilities_owned.size() > 1)//owns 2
	{
		cost_multiplier = 10;
	}
	else if (owner.utilities_owned.size() == 1)
	{
		cost_multiplier = 4;
	}
	return cost_multiplier;
}

void Monopoly::move_piece(Player* player, int die_cast)
{
	int old_position = player->piece->getPosition();
	int new_position = player->piece->getPosition() + die_cast;
	if (new_position > 39)
	{
		new_position = new_position - 40;		//wrap around to 0 then continue
	}
	//get position type (board/railroad etc.)
	//use board position to return spot
	Spot* the_spot = get_spot(new_position);	//returns correct spot
	//set spot's piece to the piece
	//move piece to new spot
	player->piece->movePosition(new_position);
	std::cout << player->name << "'s piece landed on " << the_spot->name << ".\n";
	//check if pass go and pay.
	if (passes_go(player->piece, new_position - old_position))
	{
		player->collect(200);
	}
}

void Monopoly::move_piece(Player* player, Spot pSpot)
{
	// capture current position of piece
	int old_position = player->piece->getPosition();
	// move piece to new property
	int new_position = pSpot.position;
	Spot* the_spot = get_spot(new_position);	//returns correct spot
	std::cout << player->name << "'s piece landed on " << the_spot->name << ".\n";
	//check if pass go and pay.
	player->piece->movePosition(new_position);
	if (passes_go(player->piece, new_position - old_position))
	{
		player->collect(200);
	}
}

Property* Monopoly::get_property(int pos) 
{
	for (unsigned int i = 0; i < properties.size() - 1; i++)
	{
		try {
			if (properties[i].position == pos)
			{
				return &properties[i];
			}
		}
		catch (const std::out_of_range& oor) {
			std::cerr << "Out of range error: " << oor.what() << '\n';
		}
	}
	return nullptr;
}

nrails::Railroad* Monopoly::get_railroad(int pos)
{
	//todo: fix if still need this func
	nrails::Railroad* r;
	for (unsigned int i = 0; i < 4; i++)
	{
		if (railroads[i].position == pos)
		{
			r = &railroads[i];
			return r;
		}
		if (railroads[i].position == pos)
		{
			r = &railroads[i];
			return r;
		}
		if (railroads[i].position == pos)
		{
			r = &railroads[i];
			return r;
		}
		if (railroads[i].position == pos)
		{
			r = &railroads[i];
			return r;
		}
	}
	return nullptr;
}

Monopoly::Monopoly(int number_players)
{
	init_properties();
	init_railroads();
	init_utilities();
	init_cards();
	init_board();
	init_pieces();
	init_players(number_players);
	give_active_players_pieces();//remove when giving players choice of piece
}
