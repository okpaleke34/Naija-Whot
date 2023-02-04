#pragma once
class Card {
private:
	Point current;
public:
	string shape;
	int number;
	string owner;
	Sprite* sprite;
	int width = 75;
	int height = 101;
	bool clicked = false;
	

	/*
	* get the current point of the platform
	* @returns the current cordinate points of the platform
	*/
	Point& GetCurrent()
	{
		return current;
	}
	void SetCurrent(Point point)
	{
		this->current =  point;
	}
	/*
	* create a card sprite 
	* @param point is the point in the screen to create the card.
	* @param filename is the filename of the card to create.
	* @param alt is a optional paramater that is false by default, if it is set to true then the filename passed in second parameter will be used to create a the card
	*/
	Sprite* CreateCard(Point point, string filename = "card_", bool alt = false)
	{		
		if (!alt) {
			filename += this->shape + "_" + std::to_string(this->number) + ".png";
		}
		this->sprite = createSprite((g_dir + filename).c_str());

		setSpriteSize(this->sprite, this->width, this->height);
		//cout << point << filename<<endl;
		current = point;
		return this->sprite;
	}
	/*
	* Check if the card is clicked
	* @param cursor the pointer of the cursor
	* @param centerCard that is on the game of play so that it will be used to know if the card cliced on is valid to play
	*/
	void CheckClicked(Point cursor, Card *centerCard) {

		//cout << centerCard->shape << " " << centerCard->number << " Points: " << centerCard->GetCurrent() << endl;
		//check for hitting of the block in x axis
		if (this->GetCurrent().GetX() <= cursor.GetX() && (this->GetCurrent().GetX() + this->width) >= cursor.GetX()) {
			//check for hitting of the blocks in y axis
			if (this->GetCurrent().GetY() <= cursor.GetY() && (this->GetCurrent().GetY() + this->height) >= cursor.GetY()) {
				if (this->shape == centerCard->shape || this->number == centerCard->number) {
					this->clicked = true;
					cout << "Valid" << endl;
				}
				else {
					cout << "Invalid" << endl;
				}
			}
		}
	}
	/*
	* Destroy the card sprite 
	*/
	void destroyCard() {
		destroySprite(sprite);
	}
	/*
	* draw the card sprite to the screen
	*/
	void DrawCard()
	{
		drawSprite(sprite, current.GetX(), current.GetY());
	}
	/*
	* destructor of the card class
	*/
	virtual ~Card() {
		destroySprite(sprite);
	}
};

