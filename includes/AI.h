#pragma once
//Point_2. C++ Inheritance 
class AI:public Player{

public:
	string ai = "AI is working...";
	/*
	* Checks if it is the AI turn to play. If so and the AI does not have any matching card at hand, 
	* it will take a card from the deck and if it the AI has played it will pass the turn to the next player in index
	* @param players is the vector of all players available as a reference
	* @param deck is the vector of all the cards in the deck as a reference
	*/
	void play(vector<Player*>& players, vector<Card*>& deck) {

		this->printCards();
		int c = 0;
		for (auto card : myCards) {
			if (card->shape == deck[0]->shape || card->number == deck[0]->number) {
				//cehcking to know if it is the best option to play
				deck.insert(deck.begin(), card);
				//this->myCards.erase(this->myCards.begin() + c);

				/*myCards.erase(
					std::remove_if(
						myCards.begin(),
						myCards.end(),
						[deck](Card const* card) { return card->shape == deck[0]->shape || card->number == deck[0]->number; }
					),
					myCards.end()
				);*/
				/*myCards.erase(
					std::remove_if(
						myCards.begin(),
						myCards.end(),
						[deck](Card const* card) { return card->shape == deck[0]->shape && card->number == deck[0]->number; }
					),
					myCards.end()
				);*/
				this->removeCard(card);
				this->rePositionCard(true);



				if (card->number != 1 && card->number != 2 && card->number != 14) {
					this->myTurn = false;
					break;
				}

				//this->clicked = true;
				//cout << "Valid: "<< card->shape +" " << card->number << endl;
				
			}
			else {
				//cout << "Invalid: " << card->shape + " " << card->number << endl;
			}
			c++;
		}

		//if any of the choice wasnt good or available it will take from the market 
		if (this->myTurn) {
			this->recieveCard(deck.back());
			deck.pop_back();
			this->myTurn = false;
			this->rePositionCard(false);
		}
		//set the next player turn
		if (players.size() - 1 == this->index) {
			players[0]->myTurn = true;
		}
		else {
			players[this->index + 1]->myTurn = true;
		}

		//this->printCards();	

	}

	void rePositionCard(bool isUpdate = true) {
		int k = 0; int i = 0;
		for (auto card : myCards) {

			int j = i + 1;
			k += 1;
			int start = 0;
			int perRow = g_width / card->width;
			//if the card will contian in first row calculate the  sum of all widths then dive it by 2 so that you will position the card at the middle of the screen
			if (myCards.size() < perRow) {
				start = (g_width - (myCards.size() * (card->width + 10))) / 2;
			}
			int row = 1 + int(j / perRow);
			if (j % perRow == 0) {
				row = j / perRow;
			}

			Point point;
			//move the second row and above higher from the bottom
			int addY = row == 1 ? 1 : 10;
			int addX = i == 0 ? start : start;
			point = Point((((k - 1) * card->width) + k + 10 + start), (row + addY + 10 - ((row - 1) * card->height)));
			//cout << i << " - " << row << "." << point << endl;
			if (isUpdate) {
				card->SetCurrent(point);
			}
			else {
				//card->SetCurrent(point);
				card->CreateCard(point,"whot_back.png",true);
			}


			if (j % perRow == 0) {
				k = 0;
			}
			i++;
		}
	}
	/*
	* Print the AI availble cards
	*/
	void printCards() {
		cout << endl<< "== AI CARDS ==" << endl;
		for (auto card : myCards) {
			cout << card->shape << " " << card->number << endl;
		}
		cout << endl << endl;
	}

};