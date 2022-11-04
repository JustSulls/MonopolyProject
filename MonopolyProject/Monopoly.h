#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> 
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <exception>
#include <map>
#include <algorithm>
#include <random>
#include "Property.h"
#include "Railroad.h"
#include "Utility.h"
#include "Card.h"
#include "Player.h"
#include "Piece.h"
#include "Board.h"
#include "Spot.h"
#include "Piece.h"
#include "Logger.h"

class Monopoly
{
private:
  void init_properties();
  void init_railroads();
  void init_utilities();
  void init_cards();
  void init_board();
  void init_pieces();
  void init_players(int num);
  int numberOfPlayers;
  unsigned int turnCounter = 0;
  int playerTurnTracker = 0;
  struct PropertyColorMaxNumbers
  {
    int brown = 2;
    int lightblue = 3;
    int pink = 3;
    int orange = 3;
    int red = 3;
    int yellow = 3;
    int green = 3;
    int darkblue = 2;
  }theMaxNumberPropertyColors;
  bool simulatingDiceRolls;

public:
  bool test = true;
  bool jailTest = false;
  //temporary var for testin
  Monopoly(int number_players = 2);
  
  //
  //play game
  //
  void play_game(bool simulate_dice_rolls = false);

  Board board;
  
  struct Dice
  {
    int diceRoll;
    int firstDieRoll;
    int secondDieRoll;
  }dice;
  std::vector<std::vector<int>>dice_roll_log;

  int pick_piece(Player& player);
  int throw_dice(Player player);
  
  //Getters
  Spot*           get_spot(int position);
  Player*         get_player(Piece p);
  Player*         get_owner(std::string spot_name);
  Player*         get_active_player(int& playerTurnTracker);
  util::Utility*  advance_to_nearest_utility(Piece* piece);
  util::Utility*  get_utility(int position);
  Property*       get_property(int pos);
  
  //Get winner
  Player*         get_winner();

  int get_railroad_rent(Player player);
  int get_utility_cost_multiplier(Player& owner);
  

  //railroads
  nrails::Railroad* get_railroad(int pos);
  nrails::Railroad* advance_to_nearest_railroad(Piece* piece);
  nrails::Railroad* get_nearest_railroad(Player& player);
  
  //receive cards
  Card draw_community();
  Card draw_chance();
  void reshuffle_chance();
  void reshuffle_community();

  //pass go, die_roll is die roll
  bool passes_go(Piece* p, int die_roll);
  //game over
  bool game_over = false;
  bool check_game_over(unsigned int& turnCounter);
  //decide buy or pass
  bool decide_buy_or_pass(Property prop, Player player);
  bool decide_buy_or_pass(util::Utility util, Player player);
  bool decide_buy_or_pass(nrails::Railroad rail, Player player);
  //buy property
  void buy_property(Player* player, Property* prop);
  

  //
  // JAIL
  // 
  //get valid jail turn choices based on jail counter turn
  struct JailChoices
  {
    bool rollDoubles = true;//1
    bool useCard = false;   //2
    bool pay = true;        //3
  };
  JailChoices get_valid_jail_choices(Player activePlayer);
  //decide what to do in jail
  unsigned int decide_jail_turn_choice(Player player);
  //handle jail turn
  void handle_jail_turn(Player* active_player);
  //did roll doubles
  bool didRollDoubles();

  //
  // Creating Monopolies
  // 
  //if last property bought completes the set (monopoly)
  bool property_monopoly(Property prop);
  void assign_property_monopoly(Property* prop);
  //upgrade all property of same color to monopoly level
  void upgrade_property_color_set_to_monopoly(std::vector<Property*> set);
  std::vector<Property*> get_all_properties_in_color(colors c);

  //move
  void move_piece(Player* player, int die_cast, bool collectGo = true);
  void move_piece(Player* player, Spot* pSpot, bool collectGo = true);
  int get_reg_distance(int old_position, int new_position);

  //pay rent
  void pay_rent(Player& player, Property property);
  void pay_rent(Player& player, nrails::Railroad railroad);

  //pay utilities
  void pay_utilities(Player& player, util::Utility& utility);

  //upgrade property
  void upgrade_property(Property* property);

  //do card action
  void do_card_action(Card c, Player* p, bool testing=false);
  
  //do spot action
  void do_spot_action(Spot* the_spot, Player* activePlayer);

  //send player to jail
  void send_player_to_jail(Player& p);

  //release player from jail
  void release_player_from_jail(Player& p);

  //player throws die and pays owner of utility based on roll and utilities
  void player_throw_die_pay_owner(Player& p, util::Utility& the_utility);

  //give all players a piece without player choice
  void give_active_players_pieces();

  //make next player active player
  void cycle_player_turn_tracker(int& playerTurnTracker);

  //print results
  void print_results();

  //vectors
  std::vector<nrails::Railroad>	railroads;
  std::vector<util::Utility>	utilities;
  std::vector<Card>				      cards;
  std::vector<Card>				      chance_cards;
  std::vector<Card>				      community_cards;
  std::vector<Player*>			    players;
  std::vector<Property*>			  properties;
  std::vector<Piece>				    pieces;
  std::vector<Spot>				      spots;

  //maps for properties and utilities
  std::map<std::string, Property*> map_property;	//do need, used
  std::map<std::string, util::Utility> map_utility;		//may not need, no references to date
  
  const int utility_positions[2] = { 12, 28 };
  const int position_jail = 10;
};
