#pragma once

class ManageDeck {
public:
	/*
	* The function loads all the cards elements to a card class
	* @param deck is the reference of the vector of all the cards(deck)
	* @param cardstotal is the total cards tpo load
	*/
	void loadCards(vector<Card*>& deck, int cardsTotal) {
		int star[7] = { 1,2,3,4,5,7,8 };
		int cross[9] = { 1,2,3,5,7,10,11,13,14 };
		int block[9] = { 1,2,3,5,7,10,11,13,14 };
		int circle[12] = { 1,2,3,4,5,7,8,10,11,12,13,14 };
		int triangle[12] = { 1,2,3,4,5,7,8,10,11,12,13,14 };
		int whot[5] = { 20,20,20,20,20 };

		int c = 0;

		for (int i = 0; i < cardsTotal; i++) {
			Card* card = new Card;
			if (i >= 0 && i < 7) {
				card->number = star[c];
				card->shape = "star";
			}
			else if (i >= 7 && i < 16) {
				card->number = cross[c];
				card->shape = "cross";
			}
			else if (i >= 16 && i < 25) {
				card->number = block[c];
				card->shape = "block";
			}
			else if (i >= 25 && i < 37) {
				card->number = circle[c];
				card->shape = "circle";
			}
			else if (i >= 37 && i < 49) {
				card->number = triangle[c];
				card->shape = "triangle";
			}
			else {
				card->number = 20;
				card->shape = "whot";
			}
			deck.push_back(card);

			c++;
			if (i == 6 || i == 15 || i == 24 || i == 36 || i == 48) {
				c = 0;
			}
		}

	}
	/*
	* this class shuffles the card to make it random
	* @param deck is the reference of the deck of the cards to shuffle
	*/
	void shuffle(vector<Card*>& deck) {
		std::random_device rd;
		std::shuffle(deck.begin(), deck.end(), rd);
	}

	/*
	* This function shares the card to the available players.
	* @param deck is the deck of card to share to players
	* @param players is the vector of players avaialable to recieve the card
	* @param defStack is the number of card each player will get. it throws exception if the defStack is less than 1 or greater then 25
	*/
	void Share(vector<Card*>& deck, vector<Player*>& players, int defStack = 5) {
		if (defStack > 0 && defStack < 25) {
			for (size_t i = 0; i < defStack; i++)
			{
				for (auto player : players) {
					cout << player->name << endl;
					player->recieveCard(deck.back());
					deck.pop_back();
					/*
					cout << card->shape << " " << card->number << endl;*/
				}
			}
		}
		else {
			//Point_4. C++ Throws an Exception if the amount user want to share by default is less than 0
			throw out_of_range("Each player card  ust be greater than 0");
		}
		

	}
	/*
	* This function repositions the player card to look pretty and standard on the table
	* @param players is teh list of players  playing the game
	* @param playerIndex is the index of the player to rearrange their card
	* @param isUpdate is to check if the card added is new or not
	*/
	void rePositionCard(vector<Player*>& players,int playerIndex,bool isUpdate = true) {
		int k = 0; int i = 0;
		for (auto card : players[playerIndex]->myCards) {

			int j = i + 1;
			k += 1;
			int start = 0;
			int perRow = g_width / card->width;
			//if the card will contian in first row calculate the  sum of all widths then dive it by 2 so that you will position the card at the middle of the screen
			if (players[playerIndex]->myCards.size() < perRow) {
				start = (g_width - (players[playerIndex]->myCards.size() * (card->width + 10))) / 2;
			}
			int row = 1 + int(j / perRow);
			if (j % perRow == 0) {
				row = j / perRow;
			}

			Point point;
			//move the second row and above higher from the bottom
			int addY = row == 1 ? 1 : -10;
			int addX = i == 0 ? start : start;
			point = Point((((k - 1) * card->width) + k + 10 + start), (row + addY + 480 - ((row - 1) * card->height)));
			//cout << i << " - " << row << "." << point << endl;
			if (isUpdate) {
				card->SetCurrent(point);
			}
			else {
				//card->SetCurrent(point);
				card->CreateCard(point);
			}


			if (j % perRow == 0) {
				k = 0;
			}
			i++;
		}

	}

	/*
	* prints the available card to the console
	* @param deck is the vector of cards tobe printed
	*/
	void print(vector<Card*>& deck) {
		int i = 1;
		for (auto card : deck) {
			cout << i << ". " << card->shape << " " << card->number << endl;
			i++;
		}
	}

};