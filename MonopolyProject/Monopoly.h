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
#include "Spot.h"
#include "Piece.h"

#include <algorithm>
#include <random>

class Monopoly
{
private:
	//init
	void init_properties();
	void init_railroads();
	void init_utilities();
	void init_cards();
	void init_board();
	void init_pieces(int num, std::vector<std::string> names);
	void init_players(int num);
public:
	Monopoly(int number_players = 2);
	//game commands from player's perspective:
	//todo: check what you need to return from these game moving command functions
	//pick piece
	int pick_piece(Player& player);
	//start game
	//roll die
	int die_roll(Player player);
	//decide buy or pass
	bool decide_buy_or_pass(Property prop, Player player);
	bool decide_buy_or_pass(Utility util, Player player);
	bool decide_buy_or_pass(Railroad rail, Player player);
	//decide upgrade
	bool decide_upgrade(Property prop, Player player);
	//constants
	const std::vector<std::string> railroad_names = {
		"B_0_Railroad",
		"Pennsylvania_Railroad",
		"Reading_Railroad",
		"Short_Line"
	};
	const std::string utility_names[2] = { "Electric_Company", 
		"Water_Works" };
	const int utility_positions[2] = { 12, 28};
	const int position_jail = 20;
	//the board
	Board board;
	//member functions which return
	Spot* get_spot(int position);
	Utility* advance_to_nearest_utility(Piece& piece);
	Railroad* advance_to_nearest_railroad(Piece& piece);
	Player* get_owner(std::string property_name);
	//receive cards
	Card draw_community();
	Card draw_chance();
	int get_railroad_rent(Railroad rail);
	//pass go
	bool passes_go(Piece p, int n);
	//game over
	bool game_over = false;
	//void actions
	//play game
	void play_game();
	//pay rent
	void pay_rent(Player& player, Property property);
	void pay_rent(Player& player, Railroad railroad);
	void pay_utilities(Player& player, Utility utility);
	//send to jail
	void send_to_jail(Player& player);
	//upgrade property
	void upgrade_property(Property& property);
	//do card action
	void do_card_action(Card c, Player& p);
	//do spot action
	void do_spot_action(Spot* the_spot, Player& activePlayer);
	void send_player_to_jail(Player& p);
	//move
	void move_piece(Player& player, int die_cast);
	void move_piece(Player& player, Spot pSpot);
	Property* get_property(int pos);
	Railroad* get_railroad(int pos);
	//vectors
	std::vector<Railroad> railroads;
	std::vector<Utility> utilities;
	std::vector<Card> cards;
	std::vector<Card> chance_cards;
	std::vector<Card> community_cards;
	std::vector<Player*> players;
	std::vector<Property> properties;
	std::vector<Piece> pieces;
	std::vector<Spot> spots;
	//maps for properties and utilities
	std::map<std::string, Property> map_property;
	std::map<std::string, Utility> map_utility;
	//std::map<std::string, Railroad> map_railroad;
	//std::map<std::string, Player> mapSpotNameGetOwner;
	//std::map<Piece, Player> mapPiecePlayer;
	//std::map<uint16_t, Spot> mapPositionGetSpot;
};
