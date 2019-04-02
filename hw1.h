#ifndef TICTACTOE
#define TICTACTOE

/**
 prints tic tac toe board
 @param input_board takes in vector input for contents of board
 */
void printboard(std::vector<std::string>const input_board);

/**
 updates the board after player input by marking either an x or an o
 @param input_board the vector input for the contents of the board
 @param mark either an x or o that will show up on board depending on which player just went
 */
void changeboard(std::vector<std::string>& input_board, const char mark);

/**
 removes all the current marks and resets the board to blank
 @param input_board the tic tac toe board
 */
void resetboard(std::vector<std::string>& input_board);

/**
 checks whether a player has won
 @param input_board the board with the marks
 @param winnerid- either x or o, indicating whether a player has won
 returns true if there is a line of x's or o's and false if there isn't
 */
bool checkwin(std::vector<std::string>const input_board, char& winnerid);

/**
 checks whether the board is full but there is no winner
 @param input_board the board that the function is checking
 returns true if the board is full but there is no winner and false otherwise
 */
bool checktie(std::vector<std::string>const input_board);


class Player{
public:
	/**
	 returns name of the player
	 */
	std::string get_name() const;
	
	/**
	 sets the name of player based on user input
	 @param input_name the user inputted name
	 */
	void set_name(std::string input_name);
	
	/**
	 returns number of wins that this player has
	 */
	int get_wins() const;
	/**
	 adds 1 to the number of wins that the player has 
	 */
	void add_win();
private:
	std::string name;
	int total_wins;
};
#endif
