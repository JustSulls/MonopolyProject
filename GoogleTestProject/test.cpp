#include "pch.h"

namespace testNamespace 
{
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

	TEST(PlayerTestCase, PlayerBuyRailroad) {
		Monopoly m;
		Railroad* r = &m.railroads[0];
		m.players[0]->buy_railroad(r);
		EXPECT_EQ("B_0_Railroad", m.players[0]->railroads_owned[0]->name);
		EXPECT_FALSE(m.players[1]->buy_railroad(r));
	}

	TEST(PlayerTestCase, PlayerBuyUtility)
	{
		Monopoly m;
		Utility* u = &m.utilities[0];
		m.players[0]->buy_utility(u);
		EXPECT_EQ("Electric_Company", m.players[0]->utilities_owned[0]->name);
		EXPECT_FALSE(m.players[1]->buy_utility(u));
	}

	TEST(PlayerTestCase, PlayerMovement)
	{
		Monopoly m;
		Player* p = m.players[0];
		p->get_piece(&m.pieces[0]);
		m.move_piece(p, 1);
		EXPECT_EQ(p->piece->position(), 1);
		m.move_piece(p, 1);
		EXPECT_EQ(p->piece->position(), 2);
		m.move_piece(p, 37);
		EXPECT_EQ(p->piece->position(), 39);
		m.move_piece(p, 1);
		EXPECT_EQ(p->piece->position(), 0);
		p = m.players[1];
		p->get_piece(&m.pieces[1]);
		EXPECT_EQ(p->piece->position(), 0);
	}

	TEST(CardTestCase, GoToJail)
	{
		Monopoly m;
		Player* p = m.players[0];
		p->get_piece(&m.pieces[0]);
		Card c = m.cards[9];

		EXPECT_EQ(p->in_jail, false);
		EXPECT_EQ(p->piece->position(), 0);

		m.do_card_action(c, p);
		EXPECT_EQ(p->in_jail, true);
		EXPECT_EQ(p->piece->position(), 10);
	}

	TEST(CardTestCase, AdvanceToGo)
	{
		Monopoly m;
		Player* p = m.players[0];
		p->get_piece(&m.pieces[0]);
		Card c = m.cards[1];	//Advance to GO. (Collect $200)

		EXPECT_EQ(p->money, 1500);
		EXPECT_EQ(p->piece->position(), 0);

		m.do_card_action(c, p);

		EXPECT_EQ(p->money, 1700);
		EXPECT_EQ(p->piece->position(), 0);
	}

	TEST(CardTestCase, Inherit100)
	{
		Monopoly m;
		Player* p = m.players[0];
		p->get_piece(&m.pieces[0]);
		Card c = m.cards[0];	//Inherit 100

		EXPECT_EQ(p->money, 1500);
		EXPECT_EQ(p->piece->position(), 0);

		m.do_card_action(c, p);

		EXPECT_EQ(p->money, 1600);
		EXPECT_EQ(p->piece->position(), 0);
	}

	TEST(CardTestCase, AdvanceToUtility)
	{
		/*Advance token to nearest Utility.
		If unowned  you may buy it from the Bank.
		If owned throw diceand pay owner a total 10
		times the amount thrown.*/

		Monopoly m;
		Player* p = m.players[0];
		p->get_piece(&m.pieces[0]);
		Card c = m.cards[2];
		const int startingMoney = 1500;

<<<<<<< HEAD
		EXPECT_EQ(p->money, 1500);
		EXPECT_EQ(p->piece->position(), 0);
=======
		EXPECT_EQ(p->money, startingMoney);
		EXPECT_EQ(p->piece.position, 0);
>>>>>>> e451bcd7094dd92f902527cbbb8c83b1cb3e4fe3

		m.do_card_action(c, p, true);//pass true to have player 'choose' to buy when presented with option

<<<<<<< HEAD
		//EXPECT_EQ(p->piece->position(), 12);	//Electric Company
=======
		EXPECT_EQ(p->piece.position, 12);	//Electric Company
		//took players money for buying electric company
		int moneyAfterBuy = startingMoney - m.utilities.at(0).cost;
		EXPECT_EQ(p->money, moneyAfterBuy);
>>>>>>> e451bcd7094dd92f902527cbbb8c83b1cb3e4fe3

		//make sure next player has to pay first player when landing on now owned electric company
		//p = m.players[1];
		//m.move_piece(p, 12);//todo:moving piece to bought electric company does not trigger paying player owner
		//Spot* the_spot = m.get_spot(12);
		//m.do_spot_action(the_spot, p);
	}
	//todo:pay rent test case
	TEST(UserInput, DecideToBuy)
	{
		Monopoly m;
		Player* p = m.players[0];
		p->get_piece(&m.pieces[0]);
		Railroad r = m.railroads[0];

		bool answer = m.decide_buy_or_pass(r, *p, 1);
		EXPECT_EQ(answer, true);
	}

	TEST(PieceCase, PiecePosition)
	{
		Piece piece;
		EXPECT_EQ(piece.position(), 0);
		Player player;
		piece.movePosition(1);
		player.get_piece(&piece);
		EXPECT_EQ(player.piece->position(), 1);
	}
}
