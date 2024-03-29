#include "pch.h"

TEST(CardCase, ItIsYourBirthday)
{
	Monopoly m;
	Player* p = m.players[0];
	p->get_piece(&m.pieces[0]);
	Card c = m.cards[8];

	m.do_card_action(c, p, true);
	EXPECT_EQ(p->money, 1510);
}
TEST(CardCase, GrandOperaNight)
{
	Monopoly m;
	Player* p = m.players[0];
	p->get_piece(&m.pieces[0]);
	Card c = m.cards[17];

	m.do_card_action(c, p, true);
	EXPECT_EQ(p->money, 1550);
}
TEST(CardCase, GoBackSpaces)
{
	Monopoly m;
	Player* p = m.players[0];
	p->get_piece(&m.pieces[0]);
	Card c = m.cards[26];
	//start
	EXPECT_EQ(p->piece->getPosition(), 0);

	m.do_card_action(c, p, true);
	//after card action moves back 3 spaces then does spot action wherever land this could cause anomalies here?

	EXPECT_EQ(p->piece->getPosition(), 37); //last board position is 39.. 0, 39, 38, 37
}
TEST(CardCase, GoToJail)
{
	Monopoly m;
	Player* p = m.players[0];
	p->get_piece(&m.pieces[0]);
	Card c = m.cards[9];

	EXPECT_EQ(p->in_jail, false);
	EXPECT_EQ(p->piece->getPosition(), 0);

	m.do_card_action(c, p);
	EXPECT_EQ(p->in_jail, true);
	EXPECT_EQ(p->piece->getPosition(), 10);
}
TEST(CardCase, AdvanceToGo)
{
	Monopoly m;
	Player* p = m.players[0];
	p->get_piece(&m.pieces[0]);
	Card c = m.cards[1];	//Advance to GO. (Collect $200)

	EXPECT_EQ(p->money, 1500);
	EXPECT_EQ(p->piece->getPosition(), 0);

	m.do_card_action(c, p);

	EXPECT_EQ(p->money, 1700);
	EXPECT_EQ(p->piece->getPosition(), 0);
}
TEST(CardCase, Inherit100)
{
	Monopoly m;
	Player* p = m.players[0];
	p->get_piece(&m.pieces[0]);
	Card c = m.cards[0];	//Inherit 100

	EXPECT_EQ(p->money, 1500);
	EXPECT_EQ(p->piece->getPosition(), 0);

	m.do_card_action(c, p);

	EXPECT_EQ(p->money, 1600);
	EXPECT_EQ(p->piece->getPosition(), 0);
}
TEST(CardCase, AdvanceToUtility)
{
	/*Advance token to nearest Utility.
	If unowned  you may buy it from the Bank.
	If owned throw diceand pay owner a total 10
	times the amount thrown.*/

	Monopoly m;
	Player* p = m.players[0];
	Card c = m.cards[2];//railroad card
	const int startingMoney = 1500;

	EXPECT_EQ(p->money, startingMoney);
	EXPECT_EQ(p->piece->getPosition(), 0);

	m.do_card_action(c, p, true);//pass true to have player 'choose' to buy when presented with option

	EXPECT_EQ(p->piece->getPosition(), 12);	//Electric Company

	//took players money for buying electric company
	int moneyAfterBuy = startingMoney - m.utilities.at(0).cost;
	EXPECT_EQ(p->money, moneyAfterBuy);

	//make sure next player has to pay first player when landing on now owned electric company
	p = m.players[1];
	m.move_piece(p, 12);//todo:moving piece to bought electric company does not trigger paying player owner
	Spot* the_spot = m.get_spot(12);
	m.do_spot_action(the_spot, p);
	//should be able to see that the second player payed the first
	int cost_multiplier = m.get_utility_cost_multiplier(*m.players[0]);
	int current_utility_cost = m.dice.diceRoll * cost_multiplier;
	EXPECT_EQ(p->money, startingMoney - current_utility_cost);
	EXPECT_EQ(m.players[0]->money, startingMoney - m.utilities.at(0).cost + current_utility_cost);
}
TEST(CardCase, AdvanceToRailroad)
{
	Monopoly m;
	Player* p = m.players[0];
	Card c = m.cards[32];//railroad card
	const int startingMoney = 1500;

	EXPECT_EQ(p->money, startingMoney);
	EXPECT_EQ(p->piece->getPosition(), 0);

	m.do_card_action(c, p, true);//pass true to have player 'choose' to buy when presented with option

	EXPECT_EQ(p->piece->getPosition(), 5);	//Reading railroad

	//took players money for buying electric company
	int moneyAfterBuy = startingMoney - m.railroads.at(0).cost;
	EXPECT_EQ(p->money, moneyAfterBuy);

	//make sure next player has to pay first player when landing on now owned electric company
	p = m.players[1];
	m.move_piece(p, 5);//todo:moving piece to bought electric company does not trigger paying player owner
	Spot* the_spot = m.get_spot(5);
	m.do_spot_action(the_spot, p);
	//should be able to see that the second player payed the first
	int landed_cost = m.get_railroad_rent(*m.players[0]);
	EXPECT_EQ(p->money, startingMoney - landed_cost);
}
TEST(CardCase, BankPays50)
{
	Monopoly m;
	Player* p = m.players[0];
	p->get_piece(&m.pieces[0]);
	Card c = m.cards[27];	//Bank pays you dividend of $50

	EXPECT_EQ(p->money, 1500);
	EXPECT_EQ(p->piece->getPosition(), 0);

	m.do_card_action(c, p);

	EXPECT_EQ(p->money, 1550);
	EXPECT_EQ(p->piece->getPosition(), 0);
}
TEST(CardCase, GetOutOfJailCard)
{
	Monopoly m;
	Player* p = m.players[0];
	p->get_piece(&m.pieces[0]);
	Card c = m.cards[19];	//Get out of jail free
	Card c2 = m.cards[30];

	EXPECT_EQ(p->money, 1500);
	EXPECT_EQ(p->piece->getPosition(), 0);

	m.do_card_action(c, p);

	EXPECT_EQ(p->money, 1500);
	EXPECT_EQ(p->piece->getPosition(), 0);
	EXPECT_EQ(p->has_get_out_of_jail_card(), true);

	m.do_card_action(c2, p);
	EXPECT_EQ(p->money, 1500);
	EXPECT_EQ(p->piece->getPosition(), 0);
	EXPECT_EQ(p->has_get_out_of_jail_card(), true);

	p->use_get_out_of_jail_card();
	//still has one card
	EXPECT_EQ(p->has_get_out_of_jail_card(), true);

	p->use_get_out_of_jail_card();
	//has no cards left
	EXPECT_EQ(p->has_get_out_of_jail_card(), false);
}
TEST(CardCase, DoGeneralRepairs)
{
	Monopoly m;
	Player* p = m.players[0];
	p->get_piece(&m.pieces[0]);
	Card c = m.cards[31];//make general repairs

	EXPECT_EQ(p->money, 1500);
	EXPECT_EQ(p->piece->getPosition(), 0);

	m.do_card_action(c, p);
	
	//because has no properties, no pay
	EXPECT_EQ(p->money, 1500);

	//todo:give properties
	
}
TEST(CardCaseShuffle, Shuffling)
{
	Monopoly m;
	Card cChance		= m.draw_chance();
	Card cCommunity = m.draw_community();
	m.reshuffle_chance();
	m.reshuffle_community();
}