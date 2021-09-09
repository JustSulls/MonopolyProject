#include "pch.h"


TEST(PlayerTestCase, PlayerMoney) {
	Monopoly m;
	int starting_money = 1500;

	EXPECT_EQ(starting_money, m.players[0]->money);
	m.players[0]->collect(200);
	EXPECT_EQ(1700, m.players[0]->money);
	m.players[0]->pay(200);
	EXPECT_EQ(starting_money, m.players[0]->money);

	EXPECT_EQ(starting_money, m.players[1]->money);
	m.players[1]->collect(200);
	EXPECT_EQ(1700, m.players[1]->money);
	m.players[1]->pay(200);
	EXPECT_EQ(starting_money, m.players[1]->money);
}

TEST(PlayerTestCase, PlayerBuyProperty) {
	Monopoly m;
	Property* p = &m.properties[0];
	m.players[0]->buy_property(p);
	EXPECT_EQ("mediterranean avenue", m.players[0]->properties_owned[0]->name);
	EXPECT_FALSE(m.players[1]->buy_property(p));//already owned
}

TEST(PlayerTestCase, PlayerMovement)
{
	Monopoly m;
	Player* p = m.players[0];
	m.move_piece(p, 1);
	EXPECT_EQ(p->piece.position, 1);
	m.move_piece(p, 1);
	EXPECT_EQ(p->piece.position, 2);
	m.move_piece(p, 37);
	EXPECT_EQ(p->piece.position, 39);
	m.move_piece(p, 1);
	EXPECT_EQ(p->piece.position, 0);
	p = m.players[1];
	EXPECT_EQ(p->piece.position, 0);
}

TEST(CardTestCase, GoToJail)
{
	Monopoly m;
	Player* p = m.players[0];
	Card c = m.cards[9];

	EXPECT_EQ(p->in_jail, false);
	EXPECT_EQ(p->piece.position, 0);

	m.do_card_action(c, p);
	EXPECT_EQ(p->in_jail, true);
	EXPECT_EQ(p->piece.position, 10);
}

TEST(CardTestCase, AdvanceToGo)
{
	Monopoly m;
	Player* p = m.players[0];
	Card c = m.cards[1];	//Advance to GO. (Collect $200)

	EXPECT_EQ(p->money, 1500);
	EXPECT_EQ(p->piece.position, 0);

	m.do_card_action(c, p);

	EXPECT_EQ(p->money, 1700);
	EXPECT_EQ(p->piece.position, 0);
}
