#include "pch.h"

TEST(CardTestCase, GoToJail)
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

TEST(CardTestCase, AdvanceToGo)
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

TEST(CardTestCase, Inherit100)
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

TEST(CardTestCase, AdvanceToUtility)
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
	int current_utility_cost = m.die_roll * cost_multiplier;
	EXPECT_EQ(p->money, startingMoney - current_utility_cost);
	EXPECT_EQ(m.players[0]->money, startingMoney - m.utilities.at(0).cost + current_utility_cost);
}

TEST(CardTestCase, AdvanceToRailroad)
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