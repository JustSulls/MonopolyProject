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
		nrails::Railroad* r = &m.railroads[0];
		m.players[0]->buy_railroad(r);
		EXPECT_EQ("Reading_Railroad", m.players[0]->railroads_owned[0]->name);
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
		EXPECT_EQ(p->piece->getPosition(), 1);
		m.move_piece(p, 1);
		EXPECT_EQ(p->piece->getPosition(), 2);
		m.move_piece(p, 37);
		EXPECT_EQ(p->piece->getPosition(), 39);
		m.move_piece(p, 1);
		EXPECT_EQ(p->piece->getPosition(), 0);
		p = m.players[1];
		p->get_piece(&m.pieces[0]);
		EXPECT_EQ(p->piece->getPosition(), 0);
	}

	//todo:pay rent test case
	TEST(UserInput, DecideToBuy)
	{
		Monopoly m;
		Player* p = m.players[0];
		p->get_piece(&m.pieces[0]);
		nrails::Railroad r = m.railroads[0];

		bool answer = m.decide_buy_or_pass(r, *p);
		EXPECT_EQ(answer, true);
	}

	TEST(PieceCase, PiecePosition)
	{
		Piece piece;
		EXPECT_EQ(piece.getPosition(), 0);
		Player player;
		piece.movePosition(1);
		player.get_piece(&piece);
		EXPECT_EQ(player.piece->getPosition(), 1);
	}

	TEST(MonopolyCase, PlayGame)
	{
		Monopoly m;
		/*Player* activePlayer = m.players[0];
		Spot* theSpot = m.get_spot(m.board.LAST_BOARD_POSITION);
		activePlayer->piece->movePosition(m.board.LAST_BOARD_POSITION);
		m.do_spot_action(theSpot, activePlayer);*/
		m.play_game();
	}
	TEST(LoggerCase, Log)
	{
		/*std::string msg = "log message 'msg'";
		CLogger::GetLogger()->Log("message to be logged.");
		CLogger::GetLogger()->Log(msg);
		LOGGER->Log("Message is:%s Number is:%d", msg.c_str(), 4);*/
	}
	TEST(JailCase, JailTurn)
	{
		Monopoly m;
		Player* activePlayer = m.players[0];
		activePlayer->get_out_of_jail_cards.push_back(true);
		m.send_player_to_jail(*activePlayer);
		EXPECT_EQ(activePlayer->in_jail, true);
		m.handle_jail_turn(activePlayer);
		m.handle_jail_turn(activePlayer);
		m.handle_jail_turn(activePlayer);
		EXPECT_EQ(activePlayer->in_jail, false);
 	}
}
