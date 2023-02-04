#include <iostream>
#include <vector>
#include <string>

#include <sstream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <random>

#pragma comment(lib, "winmm.lib")

using namespace std;
static int g_width;
static int g_height;
static int g_status;
static int g_stack;
static int g_player_index;
static string g_player_name;
static int g_number_of_players;
static bool g_ai_present;
/*
* 0 - Enterance
* 1 - About
* 2 - Playing
* 3 - Paused
*/


#define g_dir "assets\\sprites\\"

#include "./includes/Framework.h"

#include "./includes/Utils.h";
#include"./includes/Point.h"
#include "./includes/Cursor.h";
#include "./includes/Card.h";
#include "./includes/Player.h";
#include "./includes/Element.h";
#include "./includes/AI.h";
#include "./includes/ManageDeck.h";


class MyFramework : public Framework {

public:
	Card * centerCard = new Card;
	Cursor cursor;
	Element background;
	Element table;
	Element* screen = new Element;
	Element* market = new Element;
	Element* btn_endgame = new Element;
	Element* btn_continue = new Element;
	Element* btn_restart = new Element;
	Element* btn_start = new Element;
	Element* btn_about = new Element;
	Element* btn_close_about = new Element;
	Element* btn_onscreen_pause = new Element;
	Element* pop_background = new Element;
	Element* text_about = new Element;
	Element* text_lost = new Element;
	Element* text_won = new Element;

	ManageDeck* MD = new ManageDeck;
	vector<Card*> deck;
	vector<Player*> players;


	Point centerCardPoint = Point(300, 200);
	Point *myCardPoint = new Point(40, 480);

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = g_width;
		height = g_height;
		fullscreen = false;
	}

	virtual bool Init() {
		Point bPoint = Point(0, 0);
		background.height = g_height;
		background.width = g_width;
		table.height = g_height;
		table.width = g_width;
		market->height = 101;
		market->width = 75;

		btn_continue->height = 60;
		btn_continue->width = 200;
		btn_endgame->height = 60;
		btn_endgame->width = 200;
		btn_restart->height = 60;
		btn_restart->width = 200;
		btn_start->height = 60;
		btn_start->width = 200;
		btn_about->height = 60;
		btn_about->width = 200;
		btn_onscreen_pause->height = 50;
		btn_onscreen_pause->width = 50;
		btn_close_about->height = 50;
		btn_close_about->width = 50;
		screen->height = g_height;
		screen->width = g_width;
		text_about->width = g_width;
		text_about->height = g_height;
		pop_background->width = g_width;
		pop_background->height = g_height;
		text_won->width = g_width;
		text_won->height = g_height;
		text_lost->width = g_width;
		text_lost->height = g_height;
		background.CreateElement(bPoint, "table_top.png");
		//table.CreateElement(bPoint, "table_top.png");
		bPoint = Point(400, 200);
		market->CreateElement(bPoint, "whot_back.png");
		btn_onscreen_pause->CreateElement(Point(700, 20), "onscreen_pause.png");
		//reset the deck and players in case the init function was called from reset button
		deck.clear();
		players.clear();

		
		using namespace std::this_thread; // sleep_for, sleep_until
		using namespace std::chrono; // nanoseconds, system_clock, seconds

		//for the host player
		for (size_t i = 0; i < g_number_of_players; i++)
		{
			Player* player;
			if (i == g_player_index) {
				player = new Player;
				player->index = i;
				player->name = "Host Name";
				player->myTurn = true;
			}

			if (g_ai_present && i == 1) {				
				player = new AI;
				player->index = i;
				player->name = "AI";
			}
			players.push_back(player);
		}
		bool includeWhat = false;
		int cardsTotal;
		cardsTotal = includeWhat ? 54 : 49;
		MD->loadCards(deck, cardsTotal);



		MD->shuffle(deck);
		//MD->print(deck);
		//cout << "Last : " << deck.back()->shape << deck.back()->number << endl;
		try {
			MD->Share(deck, players,g_stack);
		}
		catch (invalid_argument e) {
			std::cout << "Invalid argument exception: " <<  e.what() << std::endl;
			MD->Share(deck, players, 5);
		} 
		catch(std::exception& e) {
			//Other errors
			std::cout << "Error occured: " << e.what() << std::endl;
		}



		for (auto player : players) {
			cout << "Player name: "<< player->name<<endl;
			for (auto card : player->myCards) {
				cout << card->shape <<" "<< card->number<<endl;
			}
		}
		/*cout << "\n\nNEW DECK \n\n";
		MD->print(deck);*/



		centerCard = deck[0];
		centerCard->CreateCard(centerCardPoint);


		/*int i = 1;
		for (auto card : players[g_player_index]->myCards) {
			if (i > 1) {
				*myCardPoint = *myCardPoint + Point(80, 0);
			}
			cout << card->shape << " " << card->number << " Points: " << myCardPoint << endl;
			card->CreateCard(*myCardPoint);
			i++;
		}*/



		/*int k = 0; int i = 0;
		for (auto card : players[g_player_index]->myCards) {

			int j = i + 1;
			k += 1;
			int perRow = g_width / card->width;
			int row = 1 + int(j / perRow);
			if (j % perRow == 0) {
				row = j / perRow;
			}

			Point point;
			point = Point((((k - 1) * card->width) + k + 10), (((row - 1) * card->height) + row + 10));
			cout << i << "." << point << endl;
			card->CreateCard(point);


			if (j % perRow == 0) {
				k = 0;
			}
			i++;
		}*/

		//Host Player
		/*int k = 0; int i = 0;
		for (auto card : players[g_player_index]->myCards) {

			int j = i + 1;
			k += 1;
			int perRow = g_width / card->width;
			int row = 1 + int(j / perRow);
			if (j % perRow == 0) {
				row = j / perRow;
			}

			Point point;
			move the second row and above higher from the bottom
			int addY = row == 1 ? 1 : -10;
			point = Point((((k - 1) * card->width) + k + 10), ( row + addY + 480 - ((row - 1) * card->height)));
			cout << i << " - " << row << "." << point << endl;
			card->CreateCard(point);


			if (j % perRow == 0) {
				k = 0;
			}
			i++;
		}*/

		//create and position the player Card
		MD->rePositionCard(players, g_player_index,false);
		for (auto player : players) {
			//cout << player->index << ". " << player->name << " " << player->myTurn << endl;
			if (player->name == "AI") {
				AI* ai = dynamic_cast<AI*>(player);
				ai->play(players, deck);
				ai->rePositionCard(false);
				/*for (auto card : ai->myCards) {
					
				}*/
			}
		}


		screen->CreateElement(Point(0, 0), "pause_background.png");
		pop_background->CreateElement(Point(0, 0), "pop_background.png");
		btn_start->CreateElement(Point(300, 200), "btn_start_game.png");
		btn_about->CreateElement(Point(300, 270), "btn_about_game.png");
		btn_continue->CreateElement(Point(300, 200), "btn_continue.png");
		btn_endgame->CreateElement(Point(300, 270),"btn_quit_game.png");
		btn_restart->CreateElement(Point(300, 340), "btn_reset_game.png");
		btn_close_about->CreateElement(Point(g_width/2, g_height - 60), "btn_cancel.png");
		text_about->CreateElement(Point(0, 0), "text_about.png");
		text_lost->CreateElement(Point(0, 0), "text_lost.png");
		text_won->CreateElement(Point(0, 0), "text_won.png");
		return true;
	}

	virtual void Close() {
		cout << "\n\nByeeee :)\n\n";
	}
	
	virtual bool Tick() {
		//show main game screen
		if (g_status == 2) {

			background.DrawElement();
			market->DrawElement();
			//cout << "Draw Center Card 1" << endl;
			centerCard->DrawCard();
			btn_onscreen_pause->DrawElement();

			/*for (size_t i = 0; i < g_number_of_players; i++)
			{
				Player* player = new Player;
				if (i == g_player_index) {
					player->index = i;
					player->name = "Host Name";
				}
				if (g_ai_present && i == 1) {
					player->index = i;
					player->name = "AI";
				}
				players.push_back(player);
			}*/

			//for (auto player : players) {
			/*Point point;
			point = Point(40, 480);
			int i = 1;
			for (auto card : players[g_player_index]->myCards) {
				if (i > 1) {
					point = point + Point(40*i,480);
				}
				card->CreateCard(point);
				i++;
			}*/



			int c = 0;
			//MD->print(players[g_player_index]->myCards);
			for (auto card : players[g_player_index]->myCards) {
				/*cout << "Hello \n";
				MD->print(players[g_player_index]->myCards);*/
				//cout << "\n -" << card->shape << endl;
				//cout << "Draw Card 1" << endl;
				card->DrawCard();
				if (card->clicked && players[g_player_index]->myTurn) {
					//cout << c << endl;
					//players[g_player_index]->myCards.pop_back();

					deck.insert(deck.begin(), card);
					players[g_player_index]->myCards.erase(players[g_player_index]->myCards.begin() + c);

					centerCard = deck[0];
					centerCard->CreateCard(centerCardPoint);
					cout << "Draw Center Card 2" << endl;
					centerCard->DrawCard();
					MD->rePositionCard(players, g_player_index);

					//cout << card->shape << " " << card->number << " Points: " << card->GetCurrent() << endl;


					//set the next player turn if the card played is not 1,2 or 14
					if (card->number != 1 && card->number != 2 && card->number != 14) {
						players[g_player_index]->myTurn = false;
						if (players.size() - 1 == g_player_index) {
							players[0]->myTurn = true;
						}
						else {
							players[g_player_index + 1]->myTurn = true;
						}
					}

					/*blocks.erase(blocks.begin() + block->index - 1);
					cout << card->shape << " " << card->number << " Points: " << card->GetCurrent() << endl;*/
				}
				//cout << card->shape << " Points: " << card->GetCurrent() << endl;
				c++;
				if (c == players[g_player_index]->myCards.size()) {
					c = 1;
				}

				if (market->clicked && players[g_player_index]->myTurn) {
					players[g_player_index]->recieveCard(deck.back());
					deck.pop_back();
					market->clicked = false;
					//cout << "Done" << endl; 
					//*myCardPoint = *myCardPoint + Point(80, 0);
					players[g_player_index]->myCards.back()->CreateCard(centerCardPoint);
					//MD->print(deck);
					MD->rePositionCard(players, g_player_index);

					//set the next player turn
					players[g_player_index]->myTurn = false;
					if (players.size() - 1 == g_player_index) {
						players[0]->myTurn = true;
					}
					else {
						players[g_player_index + 1]->myTurn = true;
					}
				}
			}

			for (auto player : players) {
				//cout << player->index << ". " << player->name << " " << player->myTurn << endl;
				if (player->name == "AI") {
					//Point_3. RTII to make a cast runtime so that the AI player can access AI object properties
					AI* ai = dynamic_cast<AI*>(player);
					if (player->myTurn) {
						ai->play(players, deck);
						//ai->rePositionCard()
						//redraw center card after AI played
						centerCard = deck[0];
						centerCard->CreateCard(centerCardPoint);
						cout << "Draw Center Card 3" << endl;
						centerCard->DrawCard();
					}
					
					for (auto card : ai->myCards) {
						card->DrawCard();
					}
					//cout << " " << ai->ai << endl;
				}
			}
			/*card->shape = "star";
			card->number = 5;*/
		}

		//show default screen
		if (g_status == 0) {
			screen->DrawElement(Point(0, 0));
			btn_start->DrawElement();
			btn_about->DrawElement();
		}
		//show about screen
		if (g_status == 1) {
			screen->DrawElement(Point(0, 0));
			btn_close_about->DrawElement();
			text_about->DrawElement();
		}
		
		//show pause screen
		if (g_status == 3) {
			screen->DrawElement(Point(0, 0));
			btn_continue->DrawElement();
			btn_endgame->DrawElement();
			btn_restart->DrawElement();
		}
		//show win screen
		if (g_status == 4) {
			pop_background->DrawElement(Point(0, 0));
			btn_restart->DrawElement(Point(70, 270));
			btn_endgame->DrawElement(Point(70, 340));
			text_won->DrawElement();
		}

		//show lost screen
		if (g_status == 5) {
			pop_background->DrawElement(Point(0, 0));
			btn_restart->DrawElement(Point(70, 270));
			btn_endgame->DrawElement(Point(70, 340));
			text_lost->DrawElement();
		}

		
		//activate continue game
		if (btn_continue->clicked) {
			screen->DrawElement(Point(g_width * 2, g_height * 2));
			g_status = 2;
			btn_continue->clicked = false;
		}
		//activate close about screen
		if (btn_close_about->clicked) {
			g_status = 0;
			btn_close_about->clicked = false;
		}
		//activate open about screen
		if (btn_about->clicked) {
			g_status = 1;
			btn_about->clicked = false;
		}
		//activate start game
		if (btn_start->clicked) {
			g_status = 2;
			btn_start->clicked = false;
		}
		//activate pause game
		if (btn_onscreen_pause->clicked) {
			g_status = 3;
			btn_onscreen_pause->clicked = false;
		}
		//End game
		if (btn_endgame->clicked) {
			exit(0);		
		}

		//activate reset game
		if (btn_restart->clicked) {
			g_status = 0;
			Init();
			
			btn_restart->clicked = false;
		}
		
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		//cursor tracks and saves the mouse movement
		cursor.MoveCursor(Point(x, y));
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		
		if (button == FRMouseButton::LEFT && isReleased)
		{
			//make sure the clicks are in proper screen
			if (g_status == 2) {
				for (auto card : players[g_player_index]->myCards) {
					//cout << "\n -" << card->shape << endl;
					card->CheckClicked(cursor.GetCurrent(), deck[0]);
					//cout << card->shape << " Points: " << card->GetCurrent() << endl;
				}
				market->CheckClicked(cursor.GetCurrent());
			}
			if (g_status == 0) {
				btn_about->CheckClicked(cursor.GetCurrent());
				btn_start->CheckClicked(cursor.GetCurrent());
			}
			if (g_status == 1) {
				btn_close_about->CheckClicked(cursor.GetCurrent());
			}
			if (g_status == 2) {
				btn_onscreen_pause->CheckClicked(cursor.GetCurrent());
			}
			if (g_status == 3) {
				btn_continue->CheckClicked(cursor.GetCurrent());
				btn_endgame->CheckClicked(cursor.GetCurrent());
				btn_restart->CheckClicked(cursor.GetCurrent());
			}
			if (g_status == 4 || g_status == 5) {
				btn_endgame->CheckClicked(cursor.GetCurrent());
				btn_restart->CheckClicked(cursor.GetCurrent());
			}
			
		}
		if (button == FRMouseButton::MIDDLE && isReleased)
		{
			cout << "Cursor: " << cursor.GetCurrent() << endl;
			for (auto player : players) {
				cout << player->index << ". " << player->name << " " << player->myTurn << endl;
				if (player->name == "AI") {
					AI* ai = dynamic_cast<AI*>(player);
					cout << "   " << ai->ai << endl;
				}
			}
			//MD->print(deck);
		}
	}

	virtual void onKeyPressed(FRKey k) {
		//moving the platform on keyboard press and release

		switch (k)
		{
			case FRKey::DOWN:
			{
				g_status = g_status == 2?3:2;
			}
			break;
			case FRKey::LEFT:
			{
				//cout << "left ";
				//screen1->DrawScreen();
				/*key_l = k;
				inertia_l = true;
				platform.MovePlatform(Point(-power_l, 0));
				power_l += g_platform_increase;*/

			}
			break;
		}


	}

	virtual void onKeyReleased(FRKey k) {
	}

	virtual const char* GetTitle() override
	{
		return "Naija Whot";
	}
};

int main(int argc, char* argv[])
{
	Utils util;

	struct Switches mySwitch;
	mySwitch = util.permuation(argc, argv);

	srand(time(NULL));

	g_stack = mySwitch.stack;
	g_width = mySwitch.screen_width;
	g_height = mySwitch.screen_height;

	//cout << "STACK: "<< g_stack << endl;
	g_player_index = 0;
	g_player_name = "";
	g_number_of_players = 2;
	g_ai_present = true;
	g_status = 4;
	return run(new MyFramework);
}

/*
* Card->owner is used to know who owns the card. So if a player recieve a card from deck the ownership will change to his index;
* at default owner is 0;
* If a user press revert and the last card in deck are his card he will recieve it and the (center playing card) will be updated 
*/