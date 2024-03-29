#include "Monopoly.h"

void Monopoly::init_properties()
{
  std::fstream myfile;
  try {
    myfile.open("C:/Users/jsul2/source/repos/MonopolyProject/MonopolyProject/CSV/monopoly_properties.csv"); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
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
    int prices[3]
    {
      printed_price,	//cost to purchase and own property
      mortgage_value,	//cost to mortgage property
      building_costs	//cost to upgrade with a building (house/skyscraper)
    };
    /*prices[0] = printed_price;
    prices[1] = mortgage_value;
    prices[2] = building_costs;*/
    int rent_costs[8]{};
    rent_costs[0] = alone;
    rent_costs[1] = monopoly;
    rent_costs[2] = with_1_house;
    rent_costs[3] = with_2_house;
    rent_costs[4] = with_3_house;
    rent_costs[5] = with_4_house;
    rent_costs[6] = with_hotel;
    rent_costs[7] = with_skyscraper;
    //stupid color transformer replace this
    colors the_color = colors::brown;
    switch (color.at(0)) {
    case ('b'):
      the_color = colors::brown;
      break;
    case('l'):
      the_color = colors::light_blue;
      break;
    case('p'):
      the_color = colors::pink;
      break;
    case('o'):
      the_color = colors::orange;
      break;
    case('r'):
      the_color = colors::red;
      break;
    case('y'):
      the_color = colors::yellow;
      break;
    case('g'):
      the_color = colors::green;
      break;
    case('d'):
      the_color = colors::dark_blue;
      break;
    }
    //create the property
    Property* the_property = new Property(prices, rent_costs, the_color, property_name, location, SpotType::property);
    //place properties in maps
    properties.push_back(the_property);
    //add to map of properties
    map_property[the_property->name] = the_property;
  }
}

void Monopoly::init_railroads()
{
  for (unsigned int i = 0; i < nrails::railroad_names.size(); i++)
  {
    std::string rn = nrails::railroad_names.at(i);
    nrails::Railroad r(rn);
    railroads.push_back(r);
  }
}

void Monopoly::init_utilities()
{
  for (int i = 0; i < 2; i++)
  {
    int pos = utility_positions[i];
    util::Utility the_utility(pos, util::utility_names[i]);
    utilities.push_back(the_utility);
    map_utility[util::utility_names[i]] = the_utility;
  }
}

void Monopoly::init_cards()
{
  std::fstream myfile;
  myfile.open("C:/Users/jsul2/source/repos/MonopolyProject/MonopolyProject/CSV/monopoly_cards.csv"); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
  std::string value;
  std::vector<std::string> holding;
  while (myfile.good())
  {
    std::getline(myfile, value); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
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
  shuffle(begin(chance_cards), end(chance_cards), rng);
  shuffle(begin(community_cards), end(community_cards), rng);
}

void Monopoly::init_board()
{
  //put properties railroads utilities etc. in board as spots
  Spot spot_go(SpotType::go, 0, "go");
  spots.push_back(spot_go);
  Spot spot_cChest1(SpotType::community_chest, 2, "community chest 1");
  spots.push_back(spot_cChest1);
  Spot spot_cChest2(SpotType::community_chest, 17, "community chest 2");
  spots.push_back(spot_cChest2);
  Spot spot_cChest3(SpotType::community_chest, 33, "community chest 3");
  spots.push_back(spot_cChest3);
  Spot spot_chance1(SpotType::chance, 7, "chance 1");
  spots.push_back(spot_chance1);
  Spot spot_chance2(SpotType::chance, 22, "chance 2");
  spots.push_back(spot_chance2);
  Spot spot_chance3(SpotType::chance, 36, "chance 3");
  spots.push_back(spot_chance3);
  Spot spot_jail(SpotType::jail, 10, "jail or just visiting");
  spots.push_back(spot_jail);
  Spot spot_free_parking(SpotType::free_parking, 20, "free parking");
  spots.push_back(spot_free_parking);
  Spot spot_go_to_jail(SpotType::go_to_jail, 30, "go to jail");
  spots.push_back(spot_go_to_jail);
  Spot tax_income(SpotType::taxes, 4, "income tax");
  spots.push_back(tax_income);
  //Spot utility_electric(SpotType::utilities, 12, "electic company");
  //spots.push_back(utility_electric);
  //Spot utility_water(SpotType::utilities, 28, "water works");
  //spots.push_back(utility_water);
  Spot tax_luxury(SpotType::taxes, 38, "luxury tax");
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
  numberOfPlayers = num;
  for (int i = 0; i < num; i++)
  {
    std::string playerName = "Player " + std::to_string(i + 1);
    players.push_back(new Player(playerName));
  }
}

void Monopoly::give_active_players_pieces()
{
  for (unsigned int i = 0; i < players.size(); i++)
  {
    players.at(i)->get_piece(&pieces.at(i));
  }
}

void Monopoly::cycle_player_turn_tracker(int&  playerTurnTracker)
{
 if (numberOfPlayers == 2)
  {
    if (playerTurnTracker == 0)
    {
      playerTurnTracker++;
    }
    else if (playerTurnTracker == 1)
    {
      playerTurnTracker = 0;
    }
  }
  else(throw std::invalid_argument("more than two players without way to handle..."));
}

Player* Monopoly::get_active_player(int& playerTurnTracker)
{
  if (numberOfPlayers == 2)
  {
    if (playerTurnTracker == 0)
    {
      return players[0];
    }
    else if (playerTurnTracker == 1)
    {
      return players[1];
    }
  }
  else(throw std::invalid_argument("more than two players without way to handle..."));
}

void Monopoly::print_results()
{
  CLogger::GetLogger()->Log("------------");
  CLogger::GetLogger()->Log("Printing results..."); 
  for (unsigned int i = 0; i < players.size(); i++)
  {
    CLogger::GetLogger()->Log(players[i]->name + " $" + std::to_string(players[i]->money));
    CLogger::GetLogger()->Log(players[i]->name + " total payments made $" + std::to_string(players[i]->get_total_payments_made()));
    CLogger::GetLogger()->Log(players[i]->name + " total payments collected $" + std::to_string(players[i]->get_total_payments_collected()));
    CLogger::GetLogger()->Log(players[i]->name + " total times passed go: " + std::to_string(players[i]->total_passed_go));
    CLogger::GetLogger()->Log("Properties owned: " + std::to_string(players[i]->properties_owned.size()));
    for (const auto the_color : ALL_COLORS)
    {
      for (int j = 0; j < players[i]->properties_owned.size(); j++)
      {
        Property the_property = *players[i]->properties_owned[j];
         if (the_property.color == the_color)
        {
          CLogger::GetLogger()->Log(the_property.name + " : " 
            + the_property.getCurrentLevel() + " : " 
            + the_property.get_color());
        }
      }
    }
    for (unsigned int k = 0; k < players[i]->railroads_owned.size(); k++)
    {
      CLogger::GetLogger()->Log(players[i]->railroads_owned[k]->name);
    }
    for (unsigned int l = 0; l < players[i]->utilities_owned.size(); l++)
    {
      CLogger::GetLogger()->Log(players[i]->utilities_owned[l]->name);
    }
  }
}

int Monopoly::pick_piece(Player& player)
{
  //present options to player, bounds check answer, return it
  int answer = -1;
  while (answer > npiece::NUMBER_PIECES - 1 || answer < 0)
  {
    CLogger::GetLogger()->Log("Pick piece: ");
    Piece::presentPieceOptions();
    std::cin >> answer;
  }
  player.get_piece(&pieces.at(answer));
  return answer;
}

int Monopoly::throw_dice(Player player)
{
  if (simulatingDiceRolls)
  {
    dice.diceRoll = dice_roll_log[turnCounter - 1][0];
    dice.firstDieRoll = dice_roll_log[turnCounter - 1][1];
    dice.secondDieRoll = dice_roll_log[turnCounter - 1][2];

    CLogger::GetLogger()->Log(player.name + " rolled a " + std::to_string(dice.diceRoll) +
      ". (" + std::to_string(dice.firstDieRoll) + " + " +
      std::to_string(dice.secondDieRoll) + ").");
  }
  else//normal dice roll, no simulate
  {
    int first_roll = rand() % 6 + 1;
    int second_roll = rand() % 6 + 1;
    int die_roll = first_roll + second_roll;
    dice.diceRoll = die_roll;
    dice.firstDieRoll = first_roll;
    dice.secondDieRoll = second_roll;

    //Log the dice roll in DiceLog.txt
    CLogger::GetDLogger()->LogDiceRolls(to_string(die_roll));
    CLogger::GetDLogger()->LogDiceRolls(std::to_string(first_roll));
    CLogger::GetDLogger()->LogDiceRolls(std::to_string(second_roll));
    CLogger::GetLogger()->Log(player.name + " rolled a " + std::to_string(die_roll) +
      ". (" + std::to_string(first_roll) + " + "
      + std::to_string(second_roll) + ").");
  }
  return dice.diceRoll;
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
    if (properties[i]->position == position)
    {
      return properties[i];
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

util::Utility* Monopoly::get_utility(int position)
{
  for (unsigned int i = 0; i < utilities.size(); i++)
  {
    if (utilities[i].position == position)
    {
      return &utilities[i];
    }
  }
  return nullptr;//todo: remove this
}

util::Utility* Monopoly::advance_to_nearest_utility(Piece* piece)
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
  CLogger::GetLogger()->Log(piece->str() + " moved to " + utilities.at(which_pos_was_shortest).name + ".");
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
  move_piece(player_ptr, rail_ptr);
  return rail_ptr;
}

Player* Monopoly::get_winner()
{
  for (int i = 0; i < numberOfPlayers; i++)
  {
    if (players[i]->money > 0)
    {
      return players[i];
    }
  }
  return nullptr;
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
    differences[i] = get_reg_distance(piece_position, railroads.at(i).position);
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

std::vector<Property*> Monopoly::get_all_properties_in_color(colors c)
{
  std::vector<Property*> return_properties;
  for (unsigned int i = 0; i < properties.size(); ++i)
  {
    if (properties[i]->color == c)
    {
      return_properties.push_back(properties[i]);//may want to change properties to pointers
    }
  }
  return return_properties;
}

Player* Monopoly::get_owner(std::string spot_name)
{
  Player* returnPlayer = nullptr;
  for (unsigned int i = 0; i < players.size(); i++)
  {
    for (unsigned int j = 0; j < players[i]->properties_owned.size(); j++)
    {
      if (players[i]->properties_owned[j]->name == spot_name)
      {
        returnPlayer = players[i];
      }
    }
    for (unsigned int j = 0; j < players[i]->railroads_owned.size(); j++)
    {
      if (players[i]->railroads_owned[j]->name == spot_name)
      {
        returnPlayer = players[i];
      }
    }
    for (unsigned int j = 0; j < players[i]->utilities_owned.size(); j++)
    {
      if (players[i]->utilities_owned[j]->name == spot_name)
      {
        returnPlayer = players[i];
      }
    }
  }
  assert(returnPlayer != nullptr);
  return returnPlayer;
}

Card Monopoly::draw_community()
{
  Card the_card = community_cards.back();
  community_cards.pop_back();
  return the_card; 
}

Card Monopoly::draw_chance()
{
  Card the_card = chance_cards.back();
  chance_cards.pop_back();
  return the_card;
}

void Monopoly::reshuffle_chance()
{
  //chance cards have been pop_backed() to empty, re-populate from cards, then shuffle
  //if not already empty, make empty to start so we don't add duplicates
  if (!chance_cards.empty())
  {
    chance_cards.clear();
  }
  for (uint32_t i = 0; i < cards.size(); i++)
  {
    if (cards[i].type == Card::card_type::Chance)
    {
      chance_cards.push_back(cards[i]);
    }
  }
  //shuffle deck here
  auto rng = std::default_random_engine{};
  std::shuffle(std::begin(chance_cards), std::end(chance_cards), rng);
}

void Monopoly::reshuffle_community()
{
  //chance cards have been pop_backed() to empty, re-populate from cards, then shuffle
  //if not already empty, make empty to start so we don't add duplicates
  if (!community_cards.empty())
  {
    community_cards.clear();
  }
  for (uint32_t i = 0; i < cards.size(); i++)
  {
    if (cards[i].type == Card::card_type::Community_Chest)
    {
      community_cards.push_back(cards[i]);
    }
  }
  //shuffle deck here
  auto rng = std::default_random_engine{};
  std::shuffle(std::begin(community_cards), std::end(community_cards), rng);
}

int Monopoly::get_railroad_rent(Player player)
{
  /*1 Railroad Owned: $25
  2 Railroads Owned : $50
  3 Railroads Owned : $100
  4 Railroads Owned : $200.*/
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
  Player* thePlayer = nullptr;
  for (unsigned int i = 0; i < players.size(); i++)
  {
    if (*players.at(i)->piece == p)
    {
      thePlayer = players.at(i);
    }
  }
  assert(thePlayer != nullptr);
  return thePlayer;
}

bool Monopoly::check_game_over(unsigned int& turnCounter)
{
  bool gameIsOver = false;
  if (turnCounter > 1000) {
    gameIsOver = true;
  };//todo:remove when done testing
  //FOR NOW check if any player has 0 or less money. (TODO: this is not technically game over, the player can sell property etc.)
  for (unsigned int i = 0; i < players.size(); i++)
  {
    if (players.at(i)->money <= 0)
    {
      gameIsOver = true;
    }
  }
  return gameIsOver;
}

bool Monopoly::decide_buy_or_pass(Property prop, Player player)
{
  CLogger::GetLogger()->Log(player.name + " decide to buy or pass " + prop.name + " for $" +
    std::to_string(prop.prices[0]) + ":\n($" + std::to_string(player.money) + " in bank)" + 
    ":\n[0] no [1] yes");
  bool decidedYes = false;
  //present options to player(unless testing), bounds check answer, return it	
  if (allAutomated)//TEST
  {
    //Make sure player has enough money to buy
    if (player.money >= prop.prices[0])
    {
      decidedYes = true;
    }
    else
    {
      //Player not enough money to buy property
      CLogger::GetLogger()->Log(player.name + " can't afford to buy " + prop.name + 
        " for $" + std::to_string(prop.prices[0]) + "(has only $" + 
        std::to_string(player.money) +  "). ");
        decidedYes = false;
    }
  }
  else if (manualInputPlayer1)
  {
    //if player one manual input
    if (player.name == "Player 1")
    {
      int answer = -1;
      while (answer > 1 || answer < 0)
      {
        std::cin >> answer;
      }
      if (answer == 0)
      {
        decidedYes = false;
      }
      else
      {
        decidedYes = true;
      }
    }
    else//Automate for player 2
    {
      //Make sure player has enough money to buy
      if (player.money >= prop.prices[0])
      {
        decidedYes = true;
      }
      else
      {
        //Player not enough money to buy property
        CLogger::GetLogger()->Log(player.name + " can't afford to buy " + prop.name +
          " for $" + std::to_string(prop.prices[0]) + "(has only $" +
          std::to_string(player.money) + "). ");
        decidedYes = false;
      }
    }
  }
  else//Neither testing bool is true
  {
    int answer = -1;
    while (answer > 1 || answer < 0)
    {
      
      std::cin >> answer;
    }
    if (answer == 0)
    {
      decidedYes = false;
    }
    else
    {
      decidedYes = true;
    }
  }

  if (decidedYes)
  {
    CLogger::GetLogger()->Log(player.name + " decides to buy " + prop.name +
      " for $" + std::to_string(prop.prices[0]) + ". ");
  }
  else
  {
    CLogger::GetLogger()->Log(player.name + " decides not to buy " + prop.name +
      " for $" + std::to_string(prop.prices[0]) + ". ");
  }
  return decidedYes;
}

bool Monopoly::decide_buy_or_pass(util::Utility util, Player player)
{
  CLogger::GetLogger()->Log(player.name + " decide to buy or pass " + util.name + " for $" +
    std::to_string(util.cost) + ":\n($" + to_string(player.money) + " in bank)" +
    ":\n[0] no [1] yes");
  bool decidedYes = false;
  if (allAutomated)
  {
    if (player.money >= util.cost)
    {
      decidedYes = true;
    }
    else
    {
      //Player not enough money to buy utility
      CLogger::GetLogger()->Log(player.name + " can't afford to buy " + util.name +
        " for $" + std::to_string(util.cost) + "(has only $" +
        std::to_string(player.money) + "). ");
      decidedYes = false;
    }
  }
  else if (manualInputPlayer1)
  {
    //if player one manual input
    if (player.name == "Player 1")
    {
      int answer = -1;
      while (answer > 1 || answer < 0)
      {
        std::cin >> answer;
      }
      if (answer == 0)
      {
        decidedYes = false;
      }
      else
      {
        decidedYes = true;
      }
    }
    else//Automate for player 2
    {
      //Make sure player has enough money to buy
      if (player.money >= util.cost)
      {
        decidedYes = true;
      }
      else
      {
        //Player not enough money to buy property
        CLogger::GetLogger()->Log(player.name + " can't afford to buy " + util.name +
          " for $" + std::to_string(util.cost) + "(has only $" +
          std::to_string(player.money) + "). ");
        decidedYes = false;
      }
    }
  }
  else {
    int answer = -1;
    std::cin >> answer;
    while (answer > 1 || answer < 0)
    {
      std::cin >> answer;
    }
    if (answer == 0)
    {
      decidedYes = false;
    }
    else
    {
      decidedYes = true;
    }
  }

  if (decidedYes)
  {
    CLogger::GetLogger()->Log(player.name + " decides to buy " + util.name +
      " for $" + std::to_string(util.cost) + ". ");
  }
  else
  {
    CLogger::GetLogger()->Log(player.name + " decides not to buy " + util.name +
      " for $" + std::to_string(util.cost) + ". ");
  }
  return decidedYes;
}

bool Monopoly::decide_buy_or_pass(nrails::Railroad rail, Player player)
{
  CLogger::GetLogger()->Log(player.name + " decide to buy or pass " + rail.name + " for $" +
    std::to_string(rail.cost) + ":\n($" + to_string(player.money) + " in bank)" + 
    ":\n[0] no [1] yes");
  bool decidedYes = false;
  if (allAutomated)
  {
    if (player.money >= rail.cost)
    {
      decidedYes = true;
    }
    else
    {
      //Player not enough money to buy railroad
      CLogger::GetLogger()->Log(player.name + " can't afford to buy " + rail.name + 
        " for $" + std::to_string(rail.cost) +"(has only $" +
        std::to_string(player.money) + "). ");
      decidedYes = false;
    }
  }
  else if (manualInputPlayer1)
  {
    //if player one manual input
    if (player.name == "Player 1")
    {
      int answer = -1;
      while (answer > 1 || answer < 0)
      {
        std::cin >> answer;
      }
      if (answer == 0)
      {
        decidedYes = false;
      }
      else
      {
        decidedYes = true;
      }
    }
    else//Automate for player 2
    {
      //Make sure player has enough money to buy
      if (player.money >= rail.cost)
      {
        decidedYes = true;
      }
      else
      {
        //Player not enough money to buy property
        CLogger::GetLogger()->Log(player.name + " can't afford to buy " + rail.name +
          " for $" + std::to_string(rail.cost) + "(has only $" +
          std::to_string(player.money) + "). ");
        decidedYes = false;
      }
    }
  }
  else
  {
    int answer = -1;
    while (answer > 1 || answer < 0)
    {
      std::cin >> answer;
    }
    if (answer == 0)
    {
      decidedYes = false;
    }
    else
    {
      decidedYes = true;
    }
  }
  if (decidedYes)
  {
    CLogger::GetLogger()->Log(player.name + " decides to buy " + rail.name +
    " for $" + std::to_string(rail.cost) + ". ");
  }
  else
  {
    CLogger::GetLogger()->Log(player.name + " decides not to buy " + rail.name +
      " for $" + std::to_string(rail.cost) + ". ");
  }
  return decidedYes;
}

void Monopoly::buy_property(Player* player, Property* prop)
{
  if (prop->is_owned)
  {
    CLogger::GetLogger()->Log(prop->name + " already owned. Cannot purchase.");
  }
  else
  {
    player->pay(prop->prices[0]);//printed price is prices[0]
    prop->is_owned = true;
    player->properties_owned.push_back(prop);
    //if player now has the correct number of same colored properties
    if (property_monopoly(*prop))
    {
      CLogger::GetLogger()->Log("Property monopoly achieved in " + prop->get_color() + "!");
      //assign property monopoly
      assign_property_monopoly(prop);
    }
    //upgrade property level from alone to monopoly
    CLogger::GetLogger()->Log(player->name + " now owns " + prop->name);
  }
}

void Monopoly::upgrade_property(Property* property)
{
  Player* owner = get_owner(property->name);
  int price = property->prices[0];
  //owner pays upgrade price
  owner->pay(price);
  //upgrade property
  int current_l = static_cast<int>(property->current_level);
  int next_l = 0;
  if (current_l < 7)
  {
    next_l += current_l + 1;
  }
  property->set_level(next_l);
  CLogger::GetLogger()->Log(owner->name + " upgrades " + property->name + " to " + property->getCurrentLevel());
}

Monopoly::JailChoices Monopoly::get_valid_jail_choices(Player activePlayer)
{
  //--
  //--Pseudo code English
  //----
  //if jail_turn_counter >= 3
  JailChoices returnChoices;
  if (activePlayer.jailTurnCounter > 2)
  {
    //elminate options 2 (use card) & 3 (pay)
    returnChoices.useCard = false;
    returnChoices.pay = false;
  }
  if (!activePlayer.has_get_out_of_jail_card())
  {
    //no get out of jail card, eliminate option 2
    returnChoices.useCard = false;
  }
  return returnChoices;
}

unsigned int Monopoly::decide_jail_turn_choice(Player player)
{
  unsigned int answer = -1;
  if (jailTest)
  {
    //always choose roll for doubles
    answer = 0;
  }
  else
  {
    //find and eliminate invalid choices
    JailChoices validChoices = get_valid_jail_choices(player);
    bool answerValid = false;
    while (!answerValid)
    {
      CLogger::GetLogger()->Log(player.name + " decides what to do in jail.");
      if (validChoices.rollDoubles)
      {
        CLogger::GetLogger()->Log("choice [0]: Roll for doubles, if hit move forward roll.");
      }
      if (validChoices.useCard) {
        CLogger::GetLogger()->Log("choice [1]: Use get out of jail card.");
      }
      if (validChoices.pay)
      {
        CLogger::GetLogger()->Log("choice [2]: Pay $50 before 1st or 2nd jail turn.");
      }
      if (manualInputPlayer1)
      {
        if (player.name == "Player 1")
        {
          std::cin >> answer;
          //if player chose option 0 and its an invalid choice answer is invalid
          if (validChoices.rollDoubles && answer == 0)
          {
            answerValid = true;
          }
          if (validChoices.useCard && answer == 1)
          {
            answerValid = true;
          }
          if (validChoices.pay && answer == 2)
          {
            answerValid = true;
          }
        }
      }
      else//automated 
      {
        //Always automate 0 roll for doubles
        answer = 0;
        answerValid = true;//to get out of while loop
      }
    }
  }
  return answer;
}

void Monopoly::handle_jail_turn(Player* active_player)
{
  //You cannot stay in Jail as long as you like. 
  //You must pay the fine, use Get Out of Jail Free card or try to roll doubles.
  //A player gets out of Jail "early" by:
  //	>Rolling Doubles on any of that player's next three turns in Jail. If a player succeeds in doing this, he or she 
  //	immediately moves forward the number of spaces shown by the throw. 
  //		Even if doubles are rolled, the player does NOT take another turn.
  //	>Using a "GET OUT OF JAIL FREE" card(possibly by purchasing from another player, at a price agreeable to both).
  //	>Paying a $50 fine to the Bank BEFORE throwing the dice for either the first turn or the second turn in Jail.
  //A player MAY NOT remain in Jail after his third turn(i.e., not longer than having three turns to play after being sent to Jail).
  //Immediately after throwing the dice for his third turn, if the player does not roll Doubles, he or she must pay the $50 fine. 
  //He then comes out and moves forward from Jail the number of spaces shown by his roll.
  if (active_player->in_jail)
  {
    active_player->jailTurnCounter++;
    std::string jailTurnCounterString;
    if (active_player->jailTurnCounter == 1) jailTurnCounterString = "1st";
    else if (active_player->jailTurnCounter == 2) jailTurnCounterString = "2nd";
    else if (active_player->jailTurnCounter == 3) jailTurnCounterString = "3rd";
    CLogger::GetLogger()->Log(active_player->name + "'s [" + jailTurnCounterString + "] turn in jail.");
    unsigned int answer = decide_jail_turn_choice(*active_player);//TODO:bug hereinfinite loop
    switch (answer)
    {
    case 0:
      //roll for doubles
      active_player->tryRollDoublesCounter++;// roll for doubles counter up
      CLogger::GetLogger()->Log(active_player->name + " attempts [" + to_string(active_player->tryRollDoublesCounter) + 
        "] roll for doubles to get out of jail.");
      throw_dice(*active_player);
      if (didRollDoubles())
      {
        //Leave jail
        //move forward roll
        CLogger::GetLogger()->Log(active_player->name + " successfully rolled doubles.");
        release_player_from_jail(*active_player);
        CLogger::GetLogger()->Log(active_player->name + " released from jail.");
        CLogger::GetLogger()->Log("Moving piece amount rolled.");
        move_piece(active_player, dice.diceRoll);
        do_spot_action(get_spot(active_player->piece->getPosition()), active_player);
      }
      else
      {
        //Roll failed, stay in jail (unless it's third turn and roll doubles failed)
        //If rolled doubles on third jail turn and it failed, pay $50,
        //then release from jail and move spaces rolled.
        if (active_player->jailTurnCounter >= 3)
        {
          CLogger::GetLogger()->Log(active_player->name + "'s time in jail is up, pays to get out of jail. Roll's to move.");
          //TODO: handle if can't pay //if (active_player.cant_pay(amount)offer_alternative();
          active_player->pay(50);
          release_player_from_jail(*active_player);
          move_piece(active_player, dice.diceRoll);
          do_spot_action(get_spot(active_player->piece->getPosition()), active_player);
        }
        else {
          CLogger::GetLogger()->Log(active_player->name + " fails to roll doubles.");
        }
      }
      break;
    case 1:
      //Use get out of jail card
      try {
        active_player->use_get_out_of_jail_card();
        release_player_from_jail(*active_player);
        CLogger::GetLogger()->Log(active_player->name + " uses get out of jail card.");
      }
      catch (std::exception& e)
      {
        std::cout << e.what() << std::endl;
      }
      break;
    case 2:
      //Pay $50 before 1st or 2nd jail turn (no roll?)
      if (active_player->jailTurnCounter < 3)
      {
        CLogger::GetLogger()->Log(active_player->name + " pays to get out of jail.");
        active_player->pay(50);
        release_player_from_jail(*active_player);
      }
      break;
    }
  }
}

bool Monopoly::didRollDoubles()
{
  if (dice.firstDieRoll == dice.secondDieRoll) return true;
  else return false;
}

bool Monopoly::passes_go(Piece* piece, int die_roll)
{
  //piece has already moved
  int fromPosition = piece->getPosition() - die_roll;
  int toPosition = piece->getPosition();
  if (toPosition - fromPosition < 0)
  {
    return true;
  }
  else return false;
}

void Monopoly::play_game(bool simulate_dice_rolls)
{
  simulatingDiceRolls = simulate_dice_rolls;
  CLogger::GetLogger()->Log("Game started.");
  if (simulate_dice_rolls)CLogger::GetLogger()->Log("Simulating dice rolls.");
  Player* activePlayer = nullptr;
  Property* activeProperty = nullptr;
  
  while (!game_over)
  {
    //Turn counter increment
    turnCounter++;
    CLogger::GetLogger()->Log("--Starting turn " + std::to_string(turnCounter) + "--");
    
    //Get active player (based on player turn tracker)
    activePlayer = get_active_player(playerTurnTracker);

    //First, confirm player not in jail
    if (!activePlayer->in_jail)
    {
      //Get any properties that can be upgraded
      std::vector<Property*> potential_upgrades = get_active_player(playerTurnTracker)->property_upgrades_available();

      //If any properties with potential upgrades were returned
      if (!potential_upgrades.empty())
      {
        CLogger::GetLogger()->Log("Decide whether to upgrade property.");
        for (unsigned int i = 0; i < potential_upgrades.size(); i++)
        {
          //Player decides whether to upgrade properties
          int answer = activePlayer->decide_upgrade(*potential_upgrades[i]);
          if (answer == 0)
          {
            //Decided no upgrade
            CLogger::GetLogger()->Log(activePlayer->name + " decides not to upgrade any property.");
            break;
          }
          else//answer == 1
          {
            CLogger::GetLogger()->Log(activePlayer->name + " decides to upgrade property.");
            //Decided yes upgrade
            //Already validated that we can do upgrade during player.propertyupgradesavailable()
            //Do upgrade (except monopoly that should be one automatically)
            //TODO: make answer the selection of which property to upgrade not just a yes or no
            upgrade_property(potential_upgrades[i]);
          }
        }
      }
      
      //Player rolls
      throw_dice(*activePlayer);

      //check if passed go done inside move_piece()
      move_piece(get_active_player(playerTurnTracker), dice.diceRoll);
      
      Spot* the_spot = get_spot(get_active_player(playerTurnTracker)->piece->getPosition());
      do_spot_action(the_spot, get_active_player(playerTurnTracker));
    }
    else//player is in jail, offer a way out
    {
      handle_jail_turn(activePlayer);
    }
    //turn over, check if game over 
    if (check_game_over(turnCounter)) {
      game_over = true;
      //get winner
      Player* winner = nullptr;
      winner = get_winner();
      CLogger::GetLogger()->Log("Game over.");
      if (winner != nullptr)
      {
        CLogger::GetLogger()->Log(winner->name + " wins.");
      }
      else//no winner, assuming 1000+ turns reached and false win declared for testing sake
      {
        CLogger::GetLogger()->Log("no winner, assuming 1000+ turns reached and false win declared for testing sake");
      }
      print_results();
    }
    ////If player 2 sleep for reading
    //if (activePlayer->name == "Player 2") {
    //  std::this_thread::sleep_for(std::chrono::milliseconds(4000));
    //}
    //increment turn counter to set next player active
    cycle_player_turn_tracker(playerTurnTracker);
  }
  //Throw logged dice rolls into a txt file to save after program execution completes
}

void Monopoly::pay_rent(Player& player, Property property)
{
  //No need to assert payment >= 0 here, need that to confirm game over elsewhere
  //Check which rent is owed.
  //rent_costs[0] = alone;
  //rent_costs[1] = monopoly;
  //rent_costs[2] = with_1_house;
  //rent_costs[3] = with_2_house;
  //rent_costs[4] = with_3_house;
  //rent_costs[5] = with_4_house;
  //rent_costs[6] = with_hotel;
  //rent_costs[7] = with_skyscraper;
  //Check property level
  int payment_owed = 0;
  switch (property.current_level)
  {
  case level::alone:
    payment_owed = property.rent_costs[0];
    break;
  case level::monopoly:
    payment_owed = property.rent_costs[1];
    break;
  case level::with_1_house:
    payment_owed = property.rent_costs[2];
    break;
  case level::with_2_houses:
    payment_owed = property.rent_costs[3];
    break;
  case level::with_3_houses:
    payment_owed = property.rent_costs[4];
    break;
  case level::with_4_houses:
    payment_owed = property.rent_costs[5];
    break;
  case level::with_hotel:
    payment_owed = property.rent_costs[6];
    break;
  case level::with_skyscraper:
    payment_owed = property.rent_costs[7];
    break;
  }
  player.pay(payment_owed);
  Player* owner = get_owner(property.name);
  owner->collect(payment_owed);
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

bool Monopoly::property_monopoly(Property prop)
{
  bool answer = false;
  //get owner
  Player* owner = get_owner(prop.name);
  colors theColor = prop.color;
  int colorNumber = 0;
  int maxColorNeeded = 0;
  for (int i = 0; i < owner->properties_owned.size(); i++)
  {
    if (owner->properties_owned[i]->color == theColor)
    {
      colorNumber++;
    }
  }
  //figure out if this color number is correct for max color number
  switch (theColor)
  {
  case colors::brown:
    if (colorNumber == theMaxNumberPropertyColors.brown)
    {
      answer = true;
    }
    break;
  case colors::light_blue:
    if (colorNumber == theMaxNumberPropertyColors.lightblue)
    {
      answer = true;
    }
    break;
  case colors::pink:
    if (colorNumber == theMaxNumberPropertyColors.pink)
    {
      answer = true;
    }
    break;
  case colors::orange:
    if (colorNumber == theMaxNumberPropertyColors.orange)
    {
      answer = true;
    }
    break;
  case colors::red:
    if (colorNumber == theMaxNumberPropertyColors.red)
    {
      answer = true;
    }
    break;
  case colors::yellow:
    if (colorNumber == theMaxNumberPropertyColors.yellow)
    {
      answer = true;
    }
    break;
  case colors::green:
    if (colorNumber == theMaxNumberPropertyColors.green)
    {
      answer = true;
    }
    break;
  case colors::dark_blue:
    if (colorNumber == theMaxNumberPropertyColors.darkblue)
    {
      answer = true;
    }
    break;
  default:
    break;
  }
  return answer;
}

void Monopoly::assign_property_monopoly(Property* prop)
{
  std::vector<Property*> the_set = get_all_properties_in_color(prop->color);
  upgrade_property_color_set_to_monopoly(the_set);
}

void Monopoly::pay_utilities(Player& player, util::Utility& utility)
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
  CLogger::GetLogger()->Log(p.name + " is now in jail.");
}

void Monopoly::release_player_from_jail(Player& p)
{
  p.in_jail = false;
  p.jailTurnCounter = 0;
  p.tryRollDoublesCounter = 0;
}

void Monopoly::upgrade_property_color_set_to_monopoly(std::vector<Property*> set)
{
  //Does not confirm this is a set of the same color, that's done outside as of now ...
  for (unsigned int i = 0; i < set.size(); i++)
  {
    set[i]->set_level(1);//1 is property::level monopoly
    CLogger::GetLogger()->Log(set[i]->name + " upgraded to a Monopoly.");
  }
}

void Monopoly::do_card_action(Card c, Player* player, bool testing)
{
  CLogger::GetLogger()->Log(player->name + " draws \"" + c.text + "\".");
  nrails::Railroad* railroad;	
  Property* theProperty;
  Spot* s;
  //todo: is card id always 14?
  switch (c.id) {
  case 1:
    //Advance to GO. (Collect $200)
    player->collect(200);
    break;
  case 2:
    //Advance to Illinois Avenue. If you pass GO  collect $200.
    theProperty = map_property["Illinois Avenue"];
    move_piece(player, theProperty);
    break;
  case 3:
    //Advance to St. Charles Place. If you pass GO  collect $200.
    theProperty = map_property["St. Charles Place"];
    move_piece(player, theProperty);
    break;
  case 4:
    //Advance token to nearest Utility. If unowned 
    //you may buy it from the Bank. If owned throw 
    //dice and pay owner a total 10 times the amount thrown.
    util::Utility * util;
    util = advance_to_nearest_utility(player->piece);
    //check if owned
    if (util->is_owned)
    {        
      if (util->owner_name != player->name)
      {
        //player throw dice and pay owner cost multiplier.
        player_throw_die_pay_owner(*player, *util);
      }
      else
      {
        //do nothing, player owns it already
        CLogger::GetLogger()->Log(player->name + " already owns " + util->name +
        ". No further action. ");
      }
    }
    else
    {
      if (testing)
      {
        decide_buy_or_pass(*util, *player);//returns true 
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
      if (decide_buy_or_pass(*railroad, *player))//offer player buy from bank//testing so always enter yes to buy
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
    s = get_spot(5);
    move_piece(player, s);	//reading railroad position
    break;
  case 13:
    //take a walk on the boardwalk. advance token to boardwalk.
    //TODO: this causes failure, fix
    theProperty = map_property["Boardwalk"];
    move_piece(player, theProperty);
    break;
  case 14:
    //you have been elected chariman of the board. pay each player $50		
    for (unsigned int i = 0; i < players.size(); i++)
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
    move_piece(player, s);
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
    for (unsigned int i = 0; i < players.size(); i++)
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
  if (theSpot->spot_type == SpotType::chance)
  {
    if (chance_cards.empty())
    {
      //Reshuffle
      CLogger::GetLogger()->Log("Chance card pile empty. Reshuffling.");
      reshuffle_chance();
      //Then proceed to draw as normal
    }
    Card c = draw_chance();
    //do card action
    do_card_action(c, activePlayer);
  }
  else if (theSpot->spot_type == SpotType::community_chest)
  {
    if (community_cards.empty())
    {
      //Reshuffle
      CLogger::GetLogger()->Log("Community chest card pile empty. Reshuffling.");
      reshuffle_community();
      //Then proceed to draw as normal
    }
    Card c = draw_community();
    //do card action
    do_card_action(c, activePlayer);
  }
  else if (theSpot->spot_type == SpotType::free_parking)
  {
    //do nothing 
    //free parking
  }
  else if (theSpot->spot_type == SpotType::go)
  {
    // do nothing
    // go collect money handled at move function
  }
  else if (theSpot->spot_type == SpotType::go_to_jail)
  {
    send_player_to_jail(*activePlayer);
  }
  else if (theSpot->spot_type == SpotType::jail)
  {
    //do nothing
    //just visiting
  }
  else if (theSpot->spot_type == SpotType::property)
  {
    //property handle
    //if owned, pay owner
    //if unowned present option to buy property
    Property* prop = get_property(theSpot->position);
    if (prop->is_owned)
    {
      //First confirm this is not your own property so you don't pay yourself
      Player* owner = get_owner(prop->name);
      if (owner != activePlayer)
      {
        //pay rent
        pay_rent(*activePlayer, *prop);
      }
      else
      {
        CLogger::GetLogger()->Log(activePlayer->name + " already owns " + prop->name + ". ");
      }
    }
    else
    {
      //If player decides to buy property
      if (decide_buy_or_pass(*prop, *activePlayer))
      {
        //If player buys property successfully
        //if (activePlayer->buy_property(prop))
        buy_property(activePlayer, prop);
      }
      //TODO:else auction off property, currently nothing
    }
  }
  else if (theSpot->spot_type == SpotType::railroad)
  {
    //railroad handle
    //if owned, pay owner
    //if unowned present option to buy property
    nrails::Railroad* railroad = get_railroad(theSpot->position);
    if (railroad->is_owned)
    {
      Player* owner = get_owner(railroad->name);
      if (owner != activePlayer)
      {
        //pay rent
        pay_rent(*activePlayer, *railroad);
      }
      else
      {
        CLogger::GetLogger()->Log(activePlayer->name + " already owns " + railroad->name + ". ");
      }
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
  else if (theSpot->spot_type == SpotType::utilities)
  {
    //taxes utilities handle
    //if utility owned, pay owner
    //if utility unowned present option to buy utility
    util::Utility* utility = get_utility(theSpot->position);
    if (utility->is_owned)
    {
      Player* owner = get_owner(utility->name);
      if (owner != activePlayer)
      {
        //pay utility
        pay_utilities(*activePlayer, *utility);
      }
      else
      {
        CLogger::GetLogger()->Log(activePlayer->name + " already owns " + utility->name + ". ");
      }
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
  else if (theSpot->spot_type == SpotType::taxes)
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

void Monopoly::player_throw_die_pay_owner(Player& p, util::Utility& the_utility)
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
  CLogger::GetLogger()->Log(p.name + " owns one utility, cost multiplier is " + 
    std::to_string(cost_multiplier) + ". ");
  CLogger::GetLogger()->Log(p.name + " throws die and pays owner (" + the_owner->name
    +") a total of (" + std::to_string(cost_multiplier) + ") times the amount rolled.");
  throw_dice(p);
  int cost = dice.diceRoll * cost_multiplier;
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

void Monopoly::move_piece(Player* player, int die_cast, bool collectGo)
{
  int old_position = player->piece->getPosition();
  int new_position = player->piece->getPosition() + die_cast;
  if (new_position > 39)
  {
    new_position = new_position - 40;		//wrap around to 0 then continue
    CLogger::GetLogger()->Log(player->name + " passed go.");
    //TODO: put pass go check here because it seems like this is the best place to capture when player passes go reliably
    if (collectGo)
    {
      player->collect(200);
      player->total_passed_go++;
    }
  }
  //get position type (board/railroad etc.)
  //use board position to return spot
  Spot* the_spot = get_spot(new_position);	//returns correct spot
  //set spot's piece to the piece
  //move piece to new spot
  player->piece->movePosition(new_position);

  CLogger::GetLogger()->Log(player->name + "'s piece landed on " + "[" + std::to_string(new_position) + "]" + the_spot->name + ".");
}

void Monopoly::move_piece(Player* player, Spot* pSpot, bool collectGo)
{
  //Get distance between spots, as if it were a dice roll ie. 5, 20, any positive number 
  //(hopefully less than board size 40)
  int fake_dice_roll = get_reg_distance(player->piece->getPosition(), pSpot->position);
  //Call other normal move piece which checks for collect go
  move_piece(player, fake_dice_roll, true);
}

int Monopoly::get_reg_distance(int old_position, int new_position)
{
  //gets fake dice roll or number of spots traversed
  //will use in move with spot param
  int counter = 0;
  int increment = old_position;
  while (increment != new_position)
  {
    increment++;
    counter++;
    if (increment == 40)//last position on board is 39 so 40 rolls over to 0 (go)
    {
      increment = 0;
    }
  }
  return counter;//distance traveled
}

Property* Monopoly::get_property(int pos) 
{
  for (unsigned int i = 0; i < properties.size(); i++)
  {
    if (properties[i]->position == pos)
    {
      assert(properties[i] != nullptr);
      return properties[i];
    }
  }
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
  srand(time(NULL));
  init_properties();
  init_railroads();
  init_utilities();
  init_cards();
  init_board();
  init_pieces();
  init_players(number_players);
  give_active_players_pieces();//TODO:remove when giving players choice of piece
  simulatingDiceRolls = false;
  
  //Populate dice roll log vector with dice rolls from DiceLog.txt
  string line;
  ifstream myfile("DiceLog.txt");
  int counter = 0;
  if (myfile.is_open())
  {
    cout << "Reading dice casts from DiceLog.txt\n";
    vector<int> tempDice;
    while (getline(myfile, line))
    {
      //cout << line << '\n';
      int i{ std::stoi(line) };
      tempDice.push_back(i);
      if (counter == 2)
      {
        dice_roll_log.push_back(tempDice);
        tempDice.clear();
        counter = 0;
      }
      else counter++;
    }
    cout << "Finished reading from DiceLog.txt\n";
    myfile.close();
  }
  else cout << "Unable to open file.\n";
}
