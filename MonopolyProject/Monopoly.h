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
#include "Property.h"
#include "Railroad.h"
#include "Utility.h"
#include "Card.h"
#include "Player.h"
#include "Piece.h"
#include "Board.h"
#include "Spot.h"
#include "Piece.h"
#include <algorithm>
#include <random>

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
	int turnCounter = 0;
	bool test = true;

public:
	Monopoly(int number_players = 2);
	Board board;
	void give_active_players_pieces();
	void make_next_player_active();
	int	die_roll;
	int pick_piece(Player& player);
	int throw_die(Player player);	

	//member get functions
	Player* get_active_player();
	Utility* advance_to_nearest_utility(Piece* piece);
	nrails::Railroad* advance_to_nearest_railroad(Piece* piece);
	Spot* get_spot(int position);
	Player* get_player(Piece p);
	Utility* get_utility(int position);
	int	get_utility_cost_multiplier(Player& owner);
	Player* get_owner(std::string spot_name);
	Property* get_property(int pos);
	nrails::Railroad* get_railroad(int pos);
	nrails::Railroad* get_nearest_railroad(Player& player);
	int	get_railroad_rent(Player player);
	
	//receive cards
	Card draw_community();
	Card draw_chance();

	//pass go
	bool passes_go(Piece* p, int n);
	
	//game over
	bool game_over = false;
	bool check_game_over();
	
	//decide buy or pass
	bool decide_buy_or_pass(Property prop, Player player);
	bool decide_buy_or_pass(Utility util, Player player);
	bool decide_buy_or_pass(nrails::Railroad rail, Player player);
	
	//decide upgrade
	bool decide_upgrade(Property prop, Player player);
	
	//play game
	void play_game();

	//move
	void move_piece(Player* player, int die_cast);
	void move_piece(Player* player, Spot pSpot);

	//pay rent
	void pay_rent(Player& player, Property property);
	void pay_rent(Player& player, nrails::Railroad railroad);
	void pay_utilities(Player& player, Utility& utility);

	//upgrade property
	void upgrade_property(Property& property);

	//do card action
	void do_card_action(Card c, Player* p, bool testing=false);
	
	//do spot action
	void do_spot_action(Spot* the_spot, Player* activePlayer);
	void send_player_to_jail(Player& p);
	void player_throw_die_pay_owner(Player& p, Utility& the_utility);

	//vectors
	std::vector<nrails::Railroad>	railroads;
	std::vector<Utility>			utilities;
	std::vector<Card>				cards;
	std::vector<Card>				chance_cards;
	std::vector<Card>				community_cards;
	std::vector<Player*>			players;
	std::vector<Property>			properties;
	std::vector<Piece>				pieces;
	std::vector<Spot>				spots;

	//maps for properties and utilities
	std::map<std::string, Property> map_property;	//do need, used
	std::map<std::string, Utility> map_utility;		//may not need, no references to date
	
	//constants
	const std::vector<std::string> railroad_names = {
		"Reading_Railroad",
		"Pennsylvania_Railroad",
		"B_0_Railroad",
		"Short_Line"
	};
	const std::string utility_names[2] = { "Electric_Company",
		"Water_Works" };
	const int utility_positions[2] = { 12, 28 };
	const int position_jail = 10;
};
