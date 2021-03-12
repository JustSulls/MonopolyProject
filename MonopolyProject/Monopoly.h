#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> 
#include <cstdlib>
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

class Monopoly
{
public:
	const std::vector<std::string> railroad_names = {
		"B_0_Railroad",
		"Pennsylvania_Railroad",
		"Reading_Railroad",
		"Short_Line"
	};
	std::string utility_names[2] = { "Electric_Company", "Water_Works" };
	int utility_positions[2] = { 12, 28};
	
	Monopoly();
	//init
	void init_properties();
	void init_railroads();
	void init_utilities();
	void init_cards();
	void init_pieces(int num, std::vector<std::string> names);
	void init_players(int num, std::vector<std::string> names);
	
	//void actions
	void do_general_repairs(Player player);
	void play_game(int num_players);
	void pay_rent(Player player, Property property);
	void send_to_jail(Player player);
	void upgrade_property(Property property);
	void do_card_action(Card c, Player p);
	
	Board board;
	//maps for properties and utilities
	std::map<std::string, Property> property_map;
	std::map<std::string, Utility> utility_map;
	std::map<std::string, Railroad> railroad_map;
	std::map<std::string, Player> property_player_map;
	//vectors
	std::vector<Railroad> railroads;
	std::vector<Utility> utilities;
	std::vector<Card> cards;
	std::vector<Card> chance_cards;
	std::vector<Card> community_cards;
	std::vector<Player*> players;
	std::vector<Property> properties;

	// What are commands the player should be able to enter?
	//int roll_die(); //put this in the player methods
	void move_piece(int n, Piece piece);
	void move_piece(Player player, Property property);	
	void move_piece(Player player, Railroad railroad);
	void move_piece(Player player, Utility utility);

	//member functions which return
	Utility advance_to_nearest_utility(Piece piece);
	Railroad advance_to_nearest_railroad(Piece piece);
	//Player get_player_owner_from_utility(Utility util);
	int get_railroad_rent(Railroad rail);
	// decide to buy or pass property
	bool decide_buy_or_pass(Property prop, Player player);
	bool decide_buy_or_pass(Utility util, Player player);
	bool decide_buy_or_pass(Railroad rail, Player player);
	// receive cards
	Card draw_community();
	Card draw_chance();
	// collect and pay money
	bool passes_go(Piece p, int n);
	//void get_money_from(Player player, int amount);	//might be able to just use the player methods.
	//void give_money_to(Player player, int amount);	
};

