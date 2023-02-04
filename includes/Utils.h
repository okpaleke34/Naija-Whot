#pragma once

struct Switches
{
	int screen_width = 800;
	int screen_height = 600;
	int stack = 5;
	bool help = false;
};



class Utils {
public:
    //Point_1. C++ Templeting 
    //because 1. To make the function resuable for other vector types 2.the Utils Header have to be imported before Card header so Card object cannot be passed as a parameter 
    template < typename T>
    //(Card* newCard)

	/*
	* Generate a random number from minimum passed in the parameters to the maximum
	* @param min the min number in the range
	* @param max the maximum number in the range
	* @returns integer within the range passed in the parameter
	*/
    std::pair<bool, int > findInVector(const std::vector<T*>& vecOfElements, const T *element)
    {
        std::pair<bool, int > result;
        // Find given element in vector
        auto it = std::find(vecOfElements.begin(), vecOfElements.end(), element);
        if (it != vecOfElements.end())
        {
            result.second = distance(vecOfElements.begin(), it);
            result.first = true;
        }
        else
        {
            result.first = false;
            result.second = -1;
        }
        return result;
    }


	/*
	* converts a string of separated char to a vector
	* @param str the string to convert to vector
	* @param delimeter the delimeter to explode
	* @returns a vector separated by the delimeter of the str
	*/
	vector<string> str2vec(string str, char delimeter) {
		vector<string> vect;
		//Point_5. C++ Streams 
		stringstream ss(str);

		while (ss.good()) {
			string substr;
			getline(ss, substr, delimeter);
			vect.push_back(substr);
		}
		return vect;
	}

	/*
	* This handles the permutation of the command line switches since there is no getopt for c++ windows as in linux
	* @param argc is the number of switches passed through the command line
	* @param argv is an array of char passed through the command line
	* @returns it return a Switches struct containing the different values passed through the command line for easy reading
	*/
	struct Switches permuation(int argc, char** argv)
	{
		Switches mySwitch;
		if (argc == 1)
		{
			mySwitch.help = true;
		}
		for (int i = 0; i < argc; i++)
		{

			if (i != 0)
			{
				string prevSwitch = argv[i - 1];
				string currSwitch = argv[i];
				if (currSwitch == "-h")
				{
					mySwitch.help = true;
				}
				else if (prevSwitch == "-window")
				{
					vector<string> window = str2vec(argv[i], 'x');
					mySwitch.screen_width = stoi(window[0]);
					mySwitch.screen_height = stoi(window[1]);
				}
				else if (prevSwitch == "-stack")
				{
					mySwitch.stack = stoi(argv[i]);
				}
			}
		}
		if (mySwitch.help) {
			cout << "   \n\nNAIJA WHOT TUTORIAL \n\n\
			\n *Use the command line switch eg '-window 800x600 -stack 5 -h' \
			\n*-Where 800 is the width and 600 is the height of the display screen \
			\n*-Where -stack is the number of cards to be shared in the begining it should be less than 25 and greater than 0 \
			\n*-If you have -h it will print the help. It will also print it if there is no arguments passed in the commandline. \
			\n*\
			\n* There is a winner when a player card is finished.  \
			\n* A player can put a card on top of number 1,2 and 14 to continue the game.\
			\n* If it does not have a matching shape the player will take 1 card from the deck.\
			\n* If the opponent plays card 14 the other opponent will take a card from the deck.\
			\n* If the opponent plays card 2 the other opponent will take two cards the deck.\
			\n*\
			\n*Controls\
			\n*- Click the down button to pause the game and click again when paused to continue the game\n\n\
			";
		}
		return mySwitch;
	}
};
