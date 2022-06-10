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
	int turnCounter = 0;
	bool test = true;

public:
	Monopoly(int number_players = 2);
	Board board;
	
	struct Dice
	{
		int diceRoll;
		int firstDieRoll;
		int secondDieRoll;
	}dice;
	int pick_piece(Player& player);
	int throw_die();
	int	get_railroad_rent(Player player);
	int	get_utility_cost_multiplier(Player& owner);
	
	Spot* get_spot(int position);
	Player* get_player(Piece p);
	Player* get_owner(std::string spot_name);
	Player* get_active_player();
	Utility* advance_to_nearest_utility(Piece* piece);
	Utility* get_utility(int position);
	Property* get_property(int pos);
	Player* get_winner();
	
	//railroads
	nrails::Railroad* get_railroad(int pos);
	nrails::Railroad* advance_to_nearest_railroad(Piece* piece);
	nrails::Railroad* get_nearest_railroad(Player& player);
	
	//receive cards
	Card draw_community();
	Card draw_chance();

	//pass go, n is die roll
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
	//get valid jail turn choices based on jail counter turn
	bool* get_valid_jail_choices(Player activePlayer);
	//decide what to do in jail
	unsigned int decide_jail_turn_choice(Player player);
	//JAIL
	//	A player sent to Jail cannot collect $200 salary in that move since, regardless of where his/her piece is or of the path of the board, he/she must move his/her piece DIRECTLY into Jail. A player's turn ends when he is sent to Jail.
	//You may buy and erect housesand /or hotels, sell or buy property, collect rent, mortgage properties, participate in auctionsand deal with other players even though in Jail.
	//If you pass go before landing on chance or community chest and drawing a card that sends you to jail, you still collect your salary.
	
	//handle jail turn
	void handle_jail_turn(Player* active_player);
	
	//did roll doubles
	bool didRollDoubles();
	
	//play game
	void play_game();

	//move
	void move_piece(Player* player, int die_cast);
	void move_piece(Player* player, Spot pSpot);

	//pay rent
	void pay_rent(Player& player, Property property);
	void pay_rent(Player& player, nrails::Railroad railroad);

	//pay utilities
	void pay_utilities(Player& player, Utility& utility);

	//upgrade property
	void upgrade_property(Property& property);

	//do card action
	void do_card_action(Card c, Player* p, bool testing=false);
	
	//do spot action
	void do_spot_action(Spot* the_spot, Player* activePlayer);

	//send player to jail
	void send_player_to_jail(Player& p);

	//release player from jail
	void release_player_from_jail(Player& p);

	//player throws die and pays owner of utility based on roll and utilities
	void player_throw_die_pay_owner(Player& p, Utility& the_utility);

	//give all players a piece
	void give_active_players_pieces();

	//make next player active player
	void make_next_player_active();

	//print results
	void print_results();

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
