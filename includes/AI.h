#pragma once
//Point_2. C++ Inheritance 
class AI:public Player{

public:
	string ai = "AI is working...";
	void play(vector<Player*>& players, vector<Card*>& deck) {

		this->printCards();
		/*if (this->myTurn) {

		}*/
		//cout << "Emi lokan ooo!! E don reach my turn oooo, Make space for AI wey Sabi"<<endl;
		//cout << 
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



				if (card->number != 1 && card->number != 2 && card->number != 14) {
					this->myTurn = false;
					break;
				}

				//this->clicked = true;
				cout << "Valid: "<< card->shape +" " << card->number << endl;
				
			}
			else {
				cout << "Invalid: " << card->shape + " " << card->number << endl;
			}
			c++;
		}

		//if any of the choice wasnt good or available it will take from the market 
		if (this->myTurn) {
			this->recieveCard(deck.back());
			deck.pop_back();
			this->myTurn = false;
		}
		//set the next player turn
		if (players.size() - 1 == this->index) {
			players[0]->myTurn = true;
		}
		else {
			players[this->index + 1]->myTurn = true;
		}

		this->printCards();
	

	}
	//Print Available Cards
	void printCards() {
		cout << endl<< "== AI CARDS ==" << endl;
		for (auto card : myCards) {
			cout << card->shape << " " << card->number << endl;
		}
		cout << endl << endl;
	}

};