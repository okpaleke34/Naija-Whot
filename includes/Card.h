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
	Card() {

	}
	Card(string s,int n) {
		this->number = n;
		this->shape = s;
	}*/

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

	Sprite* CreateCard(Point point, string filename = "card_")
	{
		filename += this->shape + "_" + std::to_string(this->number) + ".png";
		this->sprite = createSprite((g_dir + filename).c_str());

		setSpriteSize(this->sprite, this->width, this->height);

		current = point;
		return this->sprite;
	}
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
	void destroyCard() {
		destroySprite(sprite);
	}
	void DrawCard()
	{
		drawSprite(sprite, current.GetX(), current.GetY());
	}

	virtual ~Card() {
		destroySprite(sprite);
	}
};

