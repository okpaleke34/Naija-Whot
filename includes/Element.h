#pragma once
class Element {
private:
	Point current;
public:
	Sprite* sprite;
	int width;
	int height;
	bool clicked = false;

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

	void CheckClicked(Point cursor) {

		//cout << centerCard->shape << " " << centerCard->number << " Points: " << centerCard->GetCurrent() << endl;
		//check for hitting of the block in x axis
		if (this->GetCurrent().GetX() <= cursor.GetX() && (this->GetCurrent().GetX() + this->width) >= cursor.GetX()) {
			//check for hitting of the blocks in y axis
			if (this->GetCurrent().GetY() <= cursor.GetY() && (this->GetCurrent().GetY() + this->height) >= cursor.GetY()) {
				this->clicked = true;				
				cout << "Clicked" << endl;
			}
		}
	}
	void DrawElement()
	{
		drawSprite(sprite, current.GetX(), current.GetY());
	}

	virtual ~Element() {
		destroySprite(sprite);
	}
};