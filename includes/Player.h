#pragma once
class Player {
public:
	int index;
	string name;
	vector<Card*> myCards;
	Utils util;
	bool myTurn = false;
	//a dummy virtual function to make the class polymorphic
	virtual void dummy() {}

	void recieveCards(vector<Card> newCard) {
		//myCards.push_back(newCard);
		//change the ownership to player index
		//myCards.insert(myCards.end(), newCard.begin(), newCard.end());
	}
	/*
	* recieve card from market
	* @param newCard  is the new card to receive to the player deck
	*/
	void recieveCard(Card *newCard) {
		newCard->owner = this->index;
		myCards.push_back(newCard);
		//change the ownership to player index
	}


	/*
	* remove card from player hand
	* @param card is the new card to receive to the player deck
	*/
	void removeCard(Card *card) {
		std::pair<bool, int > result;
		result  = util.findInVector(myCards, card);
		if (result.first) {
			myCards.erase(myCards.begin() + result.second);
		}
		else{
			cout << "Card does not exist in player stack\n";
		}
		//deck.back()->shape << deck.back()->number;
	}
};