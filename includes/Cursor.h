#pragma once
/*
* This class just save the loaction of the mouse cursor. It is used in the begining of the game to know where to shoot the first ball
*/
class Cursor
{
private:
	Point current;
public:
	/*
	* get the current point cordinate of the cursor
	* @returns current Point cordinates at the moment of calling
	*/
	Point& GetCurrent()
	{
		return current;
	}
	/*
	* Move the pointer cordinate to a new one
	*/
	void MoveCursor(Point current)
	{
		this->current = current;
	}

	virtual ~Cursor() {
		//destroySprite(sprite); 
	}
};
