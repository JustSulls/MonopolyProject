#include "Monopoly.h"

void Monopoly::init_properties()
{
	std::fstream myfile;
	myfile.open("C:/Users/jsul2/Documents/monopoly_properties.csv"); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
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
		map_property[property_name] = the_property;

	}
}

void Monopoly::init_railroads()
{
	for (unsigned int i = 0; i < railroad_names.size(); i++)
	{
		std::string rn = railroad_names.at(i);
		Railroad r(rn);
		railroads.push_back(r);
		map_railroad[railroad_names[i]] = r;
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
	//TODO: make csv file of cards and create objects here
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
	Spot spot_cChest1(Spot::SpotType::community_chest, 2, "community chest 1");
	Spot spot_cChest2(Spot::SpotType::community_chest, 17, "community chest 2");
	Spot spot_cChest3(Spot::SpotType::community_chest, 33, "community chest 3");
	Spot spot_chance1(Spot::SpotType::chance, 7, "chance 1");
	Spot spot_chance2(Spot::SpotType::chance, 22, "chance 2");
	Spot spot_chance3(Spot::SpotType::chance, 36, "chance 3");
	Spot spot_jail(Spot::SpotType::jail, 10, "jail or just visiting");
	Spot spot_free_parking(Spot::SpotType::free_parking, 20, "free parking");
	Spot spot_go_to_jail(Spot::SpotType::go_to_jail, 30, "go to jail");
	Spot tax_income(Spot::SpotType::taxes_utilities, 4, "income tax");
	Spot utility_electric(Spot::SpotType::taxes_utilities, 12, "electic company");
	Spot utility_water(Spot::SpotType::taxes_utilities, 28, "water works");
	Spot tax_luxury(Spot::SpotType::taxes_utilities, 38, "luxury tax");
	mapPositionGetSpot[0] = spot_go;
	mapPositionGetSpot[1] = map_property["mediterranean avenue"];
	mapPositionGetSpot[2] = spot_cChest1;
	mapPositionGetSpot[3] = map_property["baltic avenue"];
	mapPositionGetSpot[4] = tax_income;
	mapPositionGetSpot[5] = map_railroad["B_0_Railroad"];
	mapPositionGetSpot[6] = map_property["oriental avenue"];
	mapPositionGetSpot[7] = spot_chance1;
	mapPositionGetSpot[8] = map_property["vermont avenue"];
	mapPositionGetSpot[9] = map_property["connecticut avenue"];
	mapPositionGetSpot[10] = spot_jail;
	mapPositionGetSpot[11] = map_property["st. charles place"];
	mapPositionGetSpot[12] = utility_electric;
	mapPositionGetSpot[13] = map_property["states avenue"];
	mapPositionGetSpot[14] = map_property["virginia avenue"];
	mapPositionGetSpot[15] = map_railroad["Pennsylvania_Railroad"];
	mapPositionGetSpot[16] = map_property["st. james place"];
	mapPositionGetSpot[17] = spot_cChest2;
	mapPositionGetSpot[18] = map_property["tennessee avenue"];
	mapPositionGetSpot[19] = map_property["new york avenue"];
	mapPositionGetSpot[20] = spot_free_parking;
	mapPositionGetSpot[21] = map_property["kentucky avenue"];
	mapPositionGetSpot[22] = spot_chance2;
	mapPositionGetSpot[23] = map_property["indiana avenue"];
	mapPositionGetSpot[24] = map_property["illinois avenue"];
	mapPositionGetSpot[25] = map_railroad["Reading_Railroad"];
	mapPositionGetSpot[26] = map_property["atlantic avenue"];
	mapPositionGetSpot[27] = map_property["ventnor avenue"];
	mapPositionGetSpot[28] = utility_water;
	mapPositionGetSpot[29] = map_property["marvin gardens"];
	mapPositionGetSpot[30] = spot_go_to_jail;
	mapPositionGetSpot[31] = map_property["pacific avenue"];
	mapPositionGetSpot[32] = map_property["north carolina avenue"];
	mapPositionGetSpot[33] = spot_cChest2;
	mapPositionGetSpot[34] = map_property["pennyslvania avenue"];
	mapPositionGetSpot[35] = map_railroad["Short_Line"];
	mapPositionGetSpot[36] = spot_chance3;
	mapPositionGetSpot[37] = map_property["park place"];
	mapPositionGetSpot[38] = tax_luxury;
	mapPositionGetSpot[39] = map_property["boardwalk"];
}

void Monopoly::init_pieces(int num, std::vector<std::string> names)
{
	Piece** array = new Piece * [num];
	for (int i = 0; i < num; i++)
	{
		array[i] = new Piece(names[i]);
	}
}

void Monopoly::init_players(int num)
{
	//TODO:this can't be declared here or it ceases to exist after function concludes
	//also can't just move it to header file because you need a num...
	//Player** array = new Player * [num];
	for (int i = 0; i < num; i++)
	{
		//array[i] = new Player(names[i]);
		//TODO:check this is possible solution to above todo
		players.push_back(new Player);
	}
}

int Monopoly::pick_piece(Player player)
{
	int answer = player.pick_piece();
	Piece p(answer);
	pieces.push_back(p);
	return answer;
}

int Monopoly::die_roll(Player player)
{
	return player.throw_die();
}

Spot Monopoly::get_spot(int position)
{
	return mapPositionGetSpot[position];
}

Utility Monopoly::advance_to_nearest_utility(Piece piece)
{
	// get piece position
	int piece_position = piece.position;
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
	piece.position = utilities.at(which_pos_was_shortest).position;
	//will add rest of card here
	return utilities.at(which_pos_was_shortest);
	//TODO:test this
}

Railroad Monopoly::advance_to_nearest_railroad(Piece piece)
{
	// get piece position
	int piece_position = piece.position;
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

	//advance token to that utility (no mention of passing go $$)
	piece.position = railroads.at(which_pos_was_shortest).position;
	//will add rest of card here
	return railroads.at(which_pos_was_shortest);
	//TODO:test this
}

Card Monopoly::draw_community()
{
	Card the_card = community_cards.at(community_cards.size() - 1);
	community_cards.pop_back();
	return the_card;
}

Card Monopoly::draw_chance()
{
	Card the_card = chance_cards.at(chance_cards.size() - 1);
	chance_cards.pop_back();
	return the_card;
}

int Monopoly::get_railroad_rent(Railroad rail)
{
	//todo:
	return 0;
}

bool Monopoly::decide_buy_or_pass(Property prop, Player player)
{
	//TODO:
	//Present option to player
	//
	int answer = player.decide_buy_or_pass(prop);
	if (answer == 0)
	{
		return false;
	}
	else return true;
}

bool Monopoly::decide_buy_or_pass(Utility util, Player player)
{
	//TODO:
	return false;
}

bool Monopoly::decide_buy_or_pass(Railroad rail, Player player)
{// todo:
	return false;
}

bool Monopoly::decide_upgrade(Property prop, Player player)
{
	//TODO:
	//present options
	int answer = player.decide_upgrade(prop);
	//decide what to return
	return false;
}

bool Monopoly::passes_go(Piece piece, int n)
{
	//TODO::confirm this 
	if ((piece.position + n) > board.LAST_BOARD_POSITION)
	{
		return true;
	}
	else return false;
}

void Monopoly::do_general_repairs(Player player)
{
	//make repairs, for each house pay 25 for each hotel pay 100
	int payment = (25 * player.number_of_houses) + (100 * player.number_of_hotels);
	player.pay(payment);
}

void Monopoly::play_game()
{
	
	//loop 
	while (!game_over)
	{
		for (unsigned int i = 0; i < players.size(); i++)
		{
			//wait for player roll
			Player activePlayer = *players.at(i);
			//decide upgrade logic
			std::vector<Property> potential_upgrades = activePlayer.property_upgrades_available();
			if (!potential_upgrades.empty())
			{
				for (unsigned int i = 0; i < potential_upgrades.size() - 1; i++)
				{
					activePlayer.decide_upgrade(potential_upgrades[i]);
				}
			}
			//playern rolls 
			int dieRoll = activePlayer.throw_die();
			//playern moves based on roll
			move_piece(activePlayer, dieRoll);
			//TODO:call move piece (figure out which ones to get rid of) 
			Spot the_spot = get_spot(activePlayer.piece.position);
			do_spot_action(the_spot, activePlayer);
		}
	}
}

void Monopoly::pay_rent(Player player, Property property)
{
	try {
		//TODO: get real rent to pay from property
		int payment = property.rent_costs[0];
		player.pay(payment);
		//TODO: make sure a player owns this first
		Player owner = mapSpotNameGetOwner[property.name];
		owner.collect(payment);
	}
	catch (const std::invalid_argument& ia) {
		std::cerr << "Invalid argument error: " << ia.what() << '\n';
	}
}

void Monopoly::pay_rent(Player player, Railroad railroad)
{
	try {
		int rent = railroad.get_landed_cost();
		player.pay(rent);
		Player owner = mapSpotNameGetOwner[railroad.name];
		owner.collect(rent);
	}
	catch (const std::invalid_argument& ia) {
		std::cerr << "Invalid argument error: " << ia.what() << '\n';
	}
}

void Monopoly::pay_utilities(Player player, Utility utility)
{
	try {
		int payment = utility.get_landed_cost();
		player.pay(payment);
		Player owner = mapSpotNameGetOwner[utility.name];
		owner.collect(payment);
	}
	catch (const std::invalid_argument& ia) {
		std::cerr << "Invalid argument error: " << ia.what() << '\n';
	}
}

void Monopoly::send_to_jail(Player player)
{
	player.piece.position = 10; //jail location
	player.in_jail = true;
}

void Monopoly::upgrade_property(Property property)
{
	//TODO: make sure a player owns this first
	Player owner = mapSpotNameGetOwner[property.name];
	int price = property.prices[0];
	//owner pays upgrade price
	owner.pay(price);
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

void Monopoly::do_card_action(Card c, Player player)
{
	Utility util;
	Railroad railroad;
	switch (c.id) {
	case 1:
		//Advance to GO. (Collect $200)
		player.collect(200);
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
		util = advance_to_nearest_utility(player.piece);
		//TODO:
		//check if owned
		if (util.is_owned)
		{
			//?yes player throw dice and pay owner total 10 times.
			int die_cast = player.throw_die();
			int cost = die_cast * 10;
			player.pay(cost);
			//get player that owns utility and pay 
			//him dice roll *10
			Player owner = mapSpotNameGetOwner[util.name];
			owner.collect(cost);
		}
		else
		{
			//?no offer player to buy that utility
			if (decide_buy_or_pass(util, player)) {
				player.pay(util.cost);
				//add utility to player's utilities
				player.utilities_owned.push_back(util);
				util.is_owned = true;
				mapSpotNameGetOwner[util.name] = player;
			};
		}
		break;
	case 5:
		/*Advance token to the nearest Railroadand pay owner
		twice the rental to which he is otherwise entitled.
		If Railroad is unowned you may buy it from the Bank*/
		railroad = advance_to_nearest_railroad(player.piece);
		if (railroad.is_owned)
		{
			int rent_cost = get_railroad_rent(railroad);
			Player the_owner = mapSpotNameGetOwner[railroad.name];
			the_owner.collect(2 * rent_cost);
		}
		else
		{
			if (decide_buy_or_pass(railroad, player))//offer player buy from bank
			{
				player.pay(railroad.cost);
				player.railroads_owned.push_back(railroad);
				railroad.is_owned = true;
				//set mapSpotNameGetOwner to new owner
				mapSpotNameGetOwner[railroad.name] = player;
			}
		}
		break;
	case 6:
		//Bank pays you dividend of $50.
		player.collect(50);
		break;
	case 7:
		//get out of jail card
		player.has_get_out_of_jail_card = true;
		break;
	case 8:
		//go back 3 spaces
		player.piece.position -= 3;
		//todo:
		//do an action at this new position

		//check own then offer_player_buy_prop or pay rent
		break;
	case 9:
		//go to jail, directly, do not collect 200 if pass go
		send_to_jail(player);
		break;
	case 10:
		//make repairs, for each house pay 25 for each hotel pay 100
		do_general_repairs(player);
		break;
	case 11:
		//pay poor tax of 15
		player.pay(15);
		break;
	case 12:
		//go to reading railroad, if pass go collect 200
		move_piece(player, map_railroad["Reading Railroad"]);
		break;
	}
}

void Monopoly::do_spot_action(Spot theSpot, Player activePlayer)
{
	if (theSpot.spot_type == Spot::SpotType::chance)
	{
		Card c = draw_chance();
		//do card action
		do_card_action(c, activePlayer);
	}
	else if (theSpot.spot_type == Spot::SpotType::community_chest)
	{
		Card c = draw_community();
		//do card action
		do_card_action(c, activePlayer);
	}
	else if (theSpot.spot_type == Spot::SpotType::free_parking)
	{
		//do nothing 
		//free parking
	}
	else if (theSpot.spot_type == Spot::SpotType::go)
	{
		// do nothing
		// go collect money handled at move function
		// todo:confirm this is best
	}
	else if (theSpot.spot_type == Spot::SpotType::go_to_jail)
	{
		send_player_to_jail(activePlayer);
	}
	else if (theSpot.spot_type == Spot::SpotType::jail)
	{
		//do nothing
		//just visiting
	}
	else if (theSpot.spot_type == Spot::SpotType::property)
	{
		//property handle
		//if owned, pay owner
		//if unowned present option to buy property
		Property prop = get_property(theSpot.position);
		if (prop.is_owned)
		{
			//pay rent
			pay_rent(activePlayer, prop);
		}
		else
		{
			if (decide_buy_or_pass(prop, activePlayer))
			{
				activePlayer.buy_property(prop);
			}
			//TODO:else auction off property, currently nothing
		}
	}
	else if (theSpot.spot_type == Spot::SpotType::railroad)
	{
		//railroad handle
		//if owned, pay owner
		//if unowned present option to buy property
		Railroad railroad = map_railroad[theSpot.name];
		if (railroad.is_owned)
		{
			//pay rent
			pay_rent(activePlayer, railroad);
		}
		else
		{
			if (decide_buy_or_pass(railroad, activePlayer))
			{
				activePlayer.buy_railroad(railroad);
				//TODO: check if this returns true or false
			}
			//else pass because railroad
		}
	}
	else if (theSpot.spot_type == Spot::SpotType::taxes_utilities)
	{
		//taxes utilities handle
		//if utility owned, pay owner
		//if utility unowned present option to buy utility
		Utility utility = map_utility[theSpot.name];
		if (utility.is_owned)
		{
			pay_utilities(activePlayer, utility);
		}
		else
		{
			if (decide_buy_or_pass(utility, activePlayer))
			{
				activePlayer.buy_utility(utility);
				//TODO: check if this returns true or false
			}
			//else pass because railroad
		}
	}
}

void Monopoly::send_player_to_jail(Player p)
{
	//go to jail
	p.in_jail = true;
	p.piece.position = position_jail;
}

void Monopoly::move_piece(Player player, int die_cast)
{
	int old_position = player.piece.position;
	int new_position = player.piece.position + die_cast;
	if (new_position > 39)
	{
		new_position = new_position - 39;
	}
	//get position type (board/railroad etc.)
	//use board position to return spot
	Spot the_spot = mapPositionGetSpot[new_position];
	//set spot's piece to the piece
	//move piece to new spot
	player.piece.position = new_position;
	//check if pass go and pay.
	if (passes_go(player.piece, new_position - old_position))
	{
		player.collect(200);
	}
}

void Monopoly::move_piece(Player player, Spot pSpot)
{
	// capture current position of piece
	int old_position = player.piece.position;
	// move piece to new property
	int new_position = pSpot.position;
	//check if pass go and pay.
	player.piece.position = new_position;
	if (passes_go(player.piece, new_position - old_position))
	{
		player.collect(200);
	}
}

Property Monopoly::get_property(int pos)
{
	for (unsigned int i = 0; i < properties.size() - 1; i++)
	{
		try {
			if (properties[i].position == pos)
			{
				return properties[i];
			}
		}
		catch (const std::out_of_range& oor) {
			std::cerr << "Out of range error: " << oor.what() << '\n';
		}
	}
}

Monopoly::Monopoly(int number_players)
{
	init_properties();
	init_railroads();
	init_utilities();
	init_cards();
	init_board();
	init_players(number_players);
}
