#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Piece.h"
#include "Property.h"
#include "Utility.h"
#include "Railroad.h"
#include "Logger.h"
class Player
{
public:
  Player();
  Player(std::string n);
  Piece* piece;
  std::string name;
  int money;
  std::vector<bool>get_out_of_jail_cards;
  bool in_jail = false;
  //---TESTing
  //keep only one true OR ELSE
  bool all_automated = false;
  bool player1manualInput = true;
  //---
  int total_passed_go;
  int jailTurnCounter;
  int tryRollDoublesCounter;

  std::vector<Property*>properties_owned;
  std::vector<util::Utility*>utilities_owned;
  std::vector<nrails::Railroad*>railroads_owned;

  void collect(int amount);
  void pay(int amount);
  void do_street_repairs(); 
  void do_general_repairs();
  void use_get_out_of_jail_card();
  bool buy_railroad(nrails::Railroad* rail);
  bool buy_utility(util::Utility* utility);
  
  //Sets in_jail to false
  bool has_get_out_of_jail_card();
  std::vector<Property*>property_upgrades_available();
  int decide_upgrade(Property prop);
  void get_piece(Piece* p);
  int get_num_houses();
  int get_num_hotels();
  int get_general_repair_cost();
  int get_total_payments_collected();
  int get_total_payments_made();
  bool operator==(const Player& other);
  bool operator!=(const Player& other);

private:
  struct maxColorCounts {
    int maxDarkBlue	=	2;
    int maxGreen	  =	3;
    int maxYellow	  =	3;
    int maxRed		  =	3;
    int maxOrange	  =	3;
    int maxPink		  =	3;
    int maxLightBlue=	3;
    int maxBrown	  =	2;
  }ColorCount;
  int total_payments_collected;
  int total_payments_made;
};
