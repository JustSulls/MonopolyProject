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
        property_map[property_name] = the_property;

    }
}

void Monopoly::init_railroads()
{
    for (unsigned int i = 0; i < railroad_names.size(); i++)
    {
        std::string rn = railroad_names.at(i);
        Railroad r(rn);
        railroads.push_back(r);
        railroad_map[railroad_names[i]] = r;
    }
}

void Monopoly::init_utilities()
{
    for (int i = 0; i < 2; i++)
    {
        int pos = utility_positions[i];
        Utility the_utility(pos, utility_names[i]);
        utilities.push_back(the_utility);
        utility_map[utility_names[i]] = the_utility;
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
}

void Monopoly::init_pieces(int num, std::vector<std::string> names)
{
    Piece** array = new Piece * [num];
    for (int i = 0; i < num; i++)
    {
        array[i] = new Piece(names[i]);
    }
}

void Monopoly::init_board()
{
    //TODO:put properties railroads utilities etc. in board as spots

}

void Monopoly::move_piece(Player player, int die_cast)
{
    int board_location_new_spot = player.piece.position + die_cast;
    //get position type (board/railroad etc.)
    //use board position to return spot
    //TODO: need a way to get board spot(type varies) from int position
    Spot = 
}

void Monopoly::move_piece(Player player, Utility utility)
{
    // capture current position of piece
    int old_position = player.piece.position;
    // move piece to new property
    int new_position = utility.position;
    //check if pass go and pay.
    player.piece.position = new_position;
    if (passes_go(player.piece, new_position - old_position))
    {
        //make monopoly function to get player from piece?

    }
}

void Monopoly::move_piece(Player player, Property property)
{
    // capture current position of piece
    int old_position = player.piece.position;
    // move piece to new property
    int new_position = property.position;
    //check if pass go and pay.
    player.piece.position = new_position;
    if (passes_go(player.piece, new_position - old_position))
    {
        //make monopoly function to get player from piece?

    }
}

void Monopoly::move_piece(Player player, Railroad railroad)
{

}

bool Monopoly::passes_go(Piece piece, int n)
{
    //TODO::confirm this 
    // if moved past go, give player 200.
    if ((piece.position + n) > board.LAST_BOARD_POSITION){
    return true; }
    else return false;
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
        move_piece(player, property_map["Illinois Avenue"]);
        break;
    case 3:
        move_piece(player, property_map["St. Charles Place"]);
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
            //get player that owns utility and pay him dice roll *10
            for (unsigned int i = 0; i < players.size(); i++)
            {
                if (players.at(i)->name == util.owner_name) {//find player using name
                    players.at(i)->collect(cost); //set player owner to local variable
                }
                //TODO: might be better to use a map of player to player name instead of this vector so we dont go through everytime 
            }
        }
        else
        {
            //?no offer player to buy that utility
            if (decide_buy_or_pass(util, player)) {
                player.pay(util.cost);
                //add utility to player's utilities
                player.utilities_owned.push_back(util);
                util.is_owned = true;
            };
            //
        }
        break;
    case 5:
        //Advance token to the nearest Railroad and pay owner 
        railroad = advance_to_nearest_railroad(player.piece);
        if (railroad.is_owned)
        {
            //?yes player throw dice and pay owner total 
            //twice the rental to which he is otherwise entitled. 
            int rent_cost = get_railroad_rent(railroad);
            rent_cost *= 2;
        }
        else 
        {  
            if (decide_buy_or_pass(railroad, player))//offer player buy from bank
            {
                player.pay(railroad.cost);
                player.railroads_owned.push_back(railroad);
                railroad.is_owned = true;
            }
        }
        break;
    case 6:
        //Bank pays you dividend of $50.
        player.pay(50);
        break;
    case 7:
        //get out of jail card
        player.has_get_out_of_jail_card = true;
        //todo:fix
        break;
    case 8:
        //go back 3 spaces
        player.piece.position -= 3;
        //todo:
        //do an action at this new position
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
        move_piece(player, railroad_map["Reading Railroad"]);
        break;
    }
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

void Monopoly::init_players(int num, std::vector<std::string> names)
{
    //TODO:this can't be declared here or it ceases to exist after function concludes
    //also can't just move it to header file because you need a num...
    //Player** array = new Player * [num];
    for (int i = 0; i < num; i++)
    {
        //array[i] = new Player(names[i]);
        //TODO:check this is possible solution to above todo
        players.push_back(new Player(names[i]));
    }
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

Monopoly::Monopoly()
{
    init_properties();
    init_railroads();
    init_utilities();
    init_cards();
}

Spot Monopoly::get_spot(int position)
{
    for (int i = 0; i < )
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
        else if(shortest_difference > differences[i])
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
    int differences[num_railroads] = { 0, 0, 0, 0};
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

int Monopoly::get_railroad_rent(Railroad rail)
{
    //todo:
    return 0;
}

void Monopoly::send_to_jail(Player player)
{
    player.piece.position = 10; //jail location
    player.in_jail = true;
}

void Monopoly::do_general_repairs(Player player)
{
    //make repairs, for each house pay 25 for each hotel pay 100
    int payment = (25 * player.number_of_houses) + (100 * player.number_of_hotels);
    player.pay(payment);
}

void Monopoly::play_game(int num_players)
{
    //create num players
    for (short i = 0; i < num_players; i++)
    {
        auto s = std::to_string(i);
        Player* p = new Player(s);
        players.push_back(p);
    }
    //loop 
    for (int i = 0; i < players.size(); i++)
    {
        //wait for player roll
        Player activePlayer = *players.at(i);
        //playern rolls 
        int dieRoll = activePlayer.throw_die();
        //playern moves based on roll
        //TODO:call move piece (figure out which ones to get rid of) 
    }
    //playern reacts to landing
    //  --choose buy or pass
    //  --draw_card()
    //  --pay_rent(player, property)
    //  --send_to_jail(player)
    //  --passes go (captured in move())
    //  --upgrade_property(property)
    //end loop

}

void Monopoly::pay_rent(Player player, Property property)
{
    //TODO: get real rent to pay from property
    int payment = property.rent_costs[0];
    player.pay(payment);
    //TODO: get player owner of property from property somehow
    Player owner = property_player_map[property.name];
    owner.collect(payment);
}

void Monopoly::upgrade_property(Property property)
{
    //todo:
    //get player owner
    //TODO: get player owner of property from property somehow
    Player owner = property_player_map[property.name];
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
