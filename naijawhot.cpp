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
static int g_paused;


#define g_dir "assets\\sprites\\"

#include "./includes/Framework.h"

#include "./includes/Utils.h";
#include"./includes/Point.h"
#include "./includes/Cursor.h";
#include "./includes/Card.h";
#include "./includes/Player.h";
#include "./includes/Element.h";
#include "./includes/AI.h";
#include "./includes/Screen.h";
#include "./includes/ManageDeck.h";


class MyFramework : public Framework {

public:
	Card * centerCard = new Card;
	Cursor cursor;
	Screen *screen1 = new Screen;
	Element background;
	Element table;
	Element* market = new Element;
	Element* btn_endgame = new Element;
	Element* btn_continue = new Element;

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

		btn_continue->height = 40;
		btn_continue->width = 200;
		btn_endgame->height = 40;
		btn_endgame->width = 200;
		background.CreateElement(bPoint, "table_top.png");
		//table.CreateElement(bPoint, "table_top.png");
		bPoint = Point(400, 200);
		market->CreateElement(bPoint, "whot_back.png");

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


		screen1->CreateScreen(Point(0, 0));
		//btn_endgame->CreateElement(bPoint, "whot_back.png");
		btn_continue->CreateElement(Point(300, 300), "btn_continue.png");
		btn_endgame->CreateElement(Point(300, 400),"btn_end_game.png");

		return true;
	}

	virtual void Close() {
		cout << "\n\nByeeee :)\n\n";
	}
	
	virtual bool Tick() {
		//drawTestBackground();
		background.DrawElement();
		market->DrawElement();
		
		centerCard->DrawCard();
		
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
		for (auto card : players[g_player_index]->myCards) {
			//cout << "\n -" << card->shape << endl;
			card->DrawCard();
			if (card->clicked && players[g_player_index]->myTurn) {
				//cout << c << endl;
				//players[g_player_index]->myCards.pop_back();

				deck.insert(deck.begin(), card);
				players[g_player_index]->myCards.erase(players[g_player_index]->myCards.begin() + c);

				centerCard = deck[0];
				centerCard->CreateCard(centerCardPoint);
				centerCard->DrawCard();
				MD->rePositionCard(players,g_player_index);

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
		//}

		for (auto player : players) {
			//cout << player->index << ". " << player->name << " " << player->myTurn << endl;
			if (player->myTurn && player->name == "AI") {
				//Point_3. RTII to make a cast runtime so that the AI player can access AI object properties
				AI* ai = dynamic_cast<AI*>(player);
				ai->play(players,deck);
				//redraw center card after AI played
				centerCard = deck[0];
				centerCard->CreateCard(centerCardPoint);
				centerCard->DrawCard();
				//cout << " " << ai->ai << endl;
			}
		}
		/*card->shape = "star";
		card->number = 5;*/
		if (g_paused == 1) {
			screen1->DrawScreen(Point(0, 0));
			btn_continue->DrawElement();
			btn_endgame->DrawElement();
		}
		if(g_paused == 2) {
			//screen1->destroyScreen();
			screen1->DrawScreen(Point(g_width * 2, g_height * 2));
			g_paused = 0;
		}
		if (btn_continue->clicked) {
			screen1->DrawScreen(Point(g_width * 2, g_height * 2));
			g_paused = 0;
			btn_continue->clicked = false;
		}

		if (btn_endgame->clicked) {
			/*screen1->DrawScreen(Point(g_width * 2, g_height * 2));
			g_paused = 0;
			btn_continue->clicked = false;*/
			exit(0);
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
			for (auto card : players[g_player_index]->myCards) {
				//cout << "\n -" << card->shape << endl;
				card->CheckClicked(cursor.GetCurrent(), deck[0]);
				//cout << card->shape << " Points: " << card->GetCurrent() << endl;
			}
			btn_continue->CheckClicked(cursor.GetCurrent());
			btn_endgame->CheckClicked(cursor.GetCurrent());
			market->CheckClicked(cursor.GetCurrent());
			
			
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
				//screen1->DrawScreen();
				g_paused = g_paused == 1?2:1;
				//if(g_paused)
				/*key_l = k;
				inertia_l = true;
				platform.MovePlatform(Point(-power_l, 0));
				power_l += g_platform_increase;*/

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

	cout << "STACK: "<< g_stack << endl;
	g_player_index = 0;
	g_player_name = "";
	g_number_of_players = 2;
	g_ai_present = true;
	g_paused = false;
	return run(new MyFramework);
}




















int main_() {
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono; // nanoseconds, system_clock, seconds
	ManageDeck *MD = new ManageDeck;
	vector<Card*> deck;
	bool includeWhat = false;
	int cardsTotal;
	cardsTotal = includeWhat ? 54 : 49;
	MD->loadCards(deck, cardsTotal);

	MD->shuffle(deck);
	MD->print(deck);
	cout <<"Last : " << deck.back()->shape<< deck.back()->number;
	/*while (true) {

		cout << "hello world\n";
		sleep_for(seconds(1));
	}*/
	//sleep_until(system_clock::now() + seconds(1));
	return 0;
}
/*
* Card->owner is used to know who owns the card. So if a player recieeve a card from deck the ownership will change to his index;
* at default owner is 0;
* If a user press revert and the last card in deck are his card he will recieve it and the (center playing card) will be updated 
*/