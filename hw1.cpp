#include <iostream>
#include <vector>
#include <string>
#include "hw1.h"

int main()
{
	std::vector <std::string>board = {" 1 2 3","1 | | "," -----","2 | | "," -----","3 | | "};
	
	Player p1;
	Player p2;
	
	std::string p1_name;
	std::string p2_name;
	int rounds;
	
	std::cout <<"This is a Tic Tac Toe game! \nPlease enter the name of player 1: ";
	std::cin>> p1_name;
	p1.set_name(p1_name);
	std::cout <<"Please enter the name of player 2: ";
	std::cin>>p2_name;
	p2.set_name(p2_name);
	std::cout <<"How many rounds would you like to play? ";
	std::cin>>rounds;
	std::cout <<"Let the game begin! \n";
	
	int player=2; //id to determine whose turn it is
	//repeat game for however many rounds specified
	for(size_t i=0; i<rounds; i++){
		printboard(board);
		char winner=' ';
		
		//game
		for(;;){
			char current; //current marker for player 1(x) and player 2(o)
			if(player%2==0){
				current='x';
				std::cout<<"It is "<<p1.get_name()<<"'s turn. \n";
			}
			else{
				current='o';
				std::cout<<"It is "<<p2.get_name()<<"'s turn. \n";
			}
			
			std::cout<<"Where would you like to play? Enter your row position and column position: row col: ";
			changeboard(board, current);
			printboard(board);
			
			checkwin(board,winner);
			checktie(board);
			player++;
			if(checkwin(board,winner)==true || checktie(board)==true){
				break;
			}
		}
		
		if(winner=='x'){
			p1.add_win();
			std::cout<<p1.get_name()<<" won the round!\n";
		}
		
		else if(winner=='o'){
			p2.add_win();
			std::cout<<p2.get_name()<<" won the round!\n";
		}
		else{
			std::cout<<"That round was a tie. \n";
		}
		
		std::cout<<"Presently, "<<p1.get_name()<<" has "<<p1.get_wins()<<" points and "<<p2.get_name()<<" has "<<p2.get_wins()<<" points. \n";
		resetboard(board);
	}
	if(p1.get_wins()>p2.get_wins()){
		std::cout<<p1.get_name()<<" wins! \n";
	}
	if(p2.get_wins()>p1.get_wins()){
		std::cout<<p2.get_name()<<" wins! \n";
	}
	if(p1.get_wins()==p2.get_wins()){
		std::cout<<"It is a draw! \n";
	}
	
	return 0;
	
}

std::string Player::get_name() const{
	return name;
}

void Player::set_name(std::string input_name){
	name=input_name;
}

int Player::get_wins() const{
	return total_wins;
}

void Player::add_win(){
	total_wins++;
}

void printboard(std::vector<std::string> const input_board){ //prints each element of the vector in a new line
	std::cout<<input_board[0] <<'\n';
	std::cout<<input_board[1] <<'\n';
	std::cout<<input_board[2] <<'\n';
	std::cout<<input_board[3] <<'\n';
	std::cout<<input_board[4] <<'\n';
	std::cout<<input_board[5] <<'\n';
}

void changeboard(std::vector<std::string>& input_board, const char mark){
	int row;
	int col;
	std::cin>>row>>col;
	
	//row 1 on the board
	if((row==1)&&(col==1))
		input_board[1][1]=mark;
	if((row==1)&&(col==2))
		input_board[1][3]=mark;
	if((row==1)&&(col==3))
		input_board[1][5]=mark;
	//row 2 on board
	if((row==2)&&(col==1))
		input_board[3][1]=mark;
	if((row==2)&&(col==2))
		input_board[3][3]=mark;
	if((row==2)&&(col==3))
		input_board[3][5]=mark;
	//row 3 on board
	if((row==3)&&(col==1))
		input_board[5][1]=mark;
	if((row==3)&&(col==2))
		input_board[5][3]=mark;
	if((row==3)&&(col==3))
		input_board[5][5]=mark;
}

void resetboard(std::vector<std::string>& input_board){
	input_board = {" 1 2 3","1 | | "," -----","2 | | "," -----","3 | | "};
}

bool checkwin(std::vector<std::string> const input_board, char& winnerid){
	//if 3 x's in top row
	if((input_board[1][1]=='x')&&(input_board[1][3]=='x')&&(input_board[1][5]=='x')){
		winnerid='x';
		return true;
	}
	//if 3 x's in middle row
	else if((input_board[3][1]=='x')&&(input_board[3][3]=='x')&&(input_board[3][5]=='x')){
		winnerid='x';
		return true;
	}
	//if 3 x's in bottom row
	else if((input_board[5][1]=='x')&&(input_board[5][3]=='x')&&(input_board[5][5]=='x')){
		winnerid='x';
		return true;
	}
	//if 3 x's in left col
	if((input_board[1][1]=='x')&&(input_board[3][1]=='x')&&(input_board[5][1]=='x')){
		winnerid='x';
		return true;
	}
	//if 3 x's in middle col
	else if((input_board[1][3]=='x')&&(input_board[3][3]=='x')&&(input_board[5][3]=='x')){
		winnerid='x';
		return true;
	}
	//if 3 x's in right col
	else if((input_board[1][5]=='x')&&(input_board[3][5]=='x')&&(input_board[5][5]=='x')){
		winnerid='x';
		return true;
	}
	//if x's in descending diagonal
	else if((input_board[1][1]=='x')&&(input_board[3][3]=='x')&&(input_board[5][5]=='x')){
		winnerid='x';
		return true;
	}
	//if x's in ascending diagonal
	else if((input_board[5][1]=='x')&&(input_board[3][3]=='x')&&(input_board[1][5]=='x')){
		winnerid='x';
		return true;
	}
	
	//if 3 o's in top row
	else if((input_board[1][1]=='o')&&(input_board[1][3]=='o')&&(input_board[1][5]=='o')){
		winnerid='o';
		return true;
	}
	//if 3 o's in middle row
	else if((input_board[3][1]=='o')&&(input_board[3][3]=='o')&&(input_board[3][5]=='o')){
		winnerid='o';
		return true;
	}
	//if 3 o's in bottom row
	else if((input_board[5][1]=='o')&&(input_board[5][3]=='o')&&(input_board[5][5]=='o')){
		winnerid='o';
		return true;
	}
	//if 3 o's in left col
	if((input_board[1][1]=='o')&&(input_board[3][1]=='o')&&(input_board[5][1]=='o')){
		winnerid='o';
		return true;
	}
	//if 3 o's in middle col
	else if((input_board[1][3]=='o')&&(input_board[3][3]=='o')&&(input_board[5][3]=='o')){
		winnerid='o';
		return true;
	}
	//if 3 o's in right col
	else if((input_board[1][5]=='o')&&(input_board[3][5]=='o')&&(input_board[5][5]=='o')){
		winnerid='o';
		return true;
	}
	//if o's in descending diagonal
	else if((input_board[1][1]=='o')&&(input_board[3][3]=='o')&&(input_board[5][5]=='o')){
		winnerid='o';
		return true;
	}
	//if o's in ascending diagonal
	else if((input_board[5][1]=='o')&&(input_board[3][3]=='o')&&(input_board[1][5]=='o')){
		winnerid='o';
		return true;
	}
	
	else return false;
	
}

bool checktie(std::vector<std::string>const input_board){
	//if full board and no win(TIE)
	if ((input_board[1][1]!=' ')&&(input_board[1][3]!=' ')&&(input_board[1][5]!=' ')
		&&(input_board[3][1]!=' ')&&(input_board[3][3]!=' ')&&(input_board[5][3]!=' ')
		&&(input_board[5][1]!=' ')&&(input_board[5][3]!=' ')&&(input_board[5][5]!=' '))
		return true;
	else return false;
}
