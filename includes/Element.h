#pragma once
class Element {
private:
	Point current;
public:
	Sprite* sprite;
	int width;
	int height;
	bool clicked = false;

	/*
	* create an element sprite
	* @param point is the point in the screen to create the card.
	* @param filename is the filename of the card to create.
	*/
	Sprite* CreateElement(Point point, string filename)
	{
		this->sprite = createSprite((g_dir + filename).c_str());

		setSpriteSize(this->sprite, this->width, this->height);

		current = point;
		return this->sprite;

	}

	Point& GetCurrent()
	{
		return current;
	}


	/*
	* Check if the element is clicked
	* @param cursor the pointer of the cursor
	*/
	void CheckClicked(Point cursor) {

		//cout << centerCard->shape << " " << centerCard->number << " Points: " << centerCard->GetCurrent() << endl;
		//check for hitting of the block in x axis
		if (this->GetCurrent().GetX() <= cursor.GetX() && (this->GetCurrent().GetX() + this->width) >= cursor.GetX()) {
			//check for hitting of the blocks in y axis
			if (this->GetCurrent().GetY() <= cursor.GetY() && (this->GetCurrent().GetY() + this->height) >= cursor.GetY()) {
				this->clicked = true;				
				//cout << "Clicked" << endl;
			}
		}
	}


	/*
	* draw the Element sprite to the screen
	*/
	void DrawElement()
	{
		drawSprite(sprite, current.GetX(), current.GetY());
	}

	/*
	* draw the Element sprite to the screen
	* @param point the point in the screen to draw the Element
	* 
	*/
	void DrawElement(Point point)
	{
		current = point;
		drawSprite(sprite, current.GetX(), current.GetY());
	}

	/*
	* destructor of the Element class
	*/
	virtual ~Element() {
		destroySprite(sprite);
	}
};