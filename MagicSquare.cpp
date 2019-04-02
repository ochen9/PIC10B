//
//  MagicSquare.cpp
//  hw6n
//
//  Created by Olivia Chen on 2/27/19.
//  Copyright © 2019 Olivia Chen. All rights reserved.
//

#include "MagicSquare.h"

std::istream& operator>>(std::istream& in, std::vector<std::vector<int>>& init){
	int value; //input value
	const size_t size = init.size();
	
	for (size_t i = 0; i<size; ++i){
		for(size_t j = 0; j <size; ++j){
			in >>value;
			if(in.fail()){
				in.clear();
				in.ignore();
				continue; //if not valid value, clears
			}
			else{
				init[i][j]=value; //inputs value to square
			}
			
		}
	}
	return in;
}

std:: ostream&operator<<(std::ostream& out, std::vector<std::vector<int>>& init){
	const size_t size = init.size();
	
	for(size_t i =0; i<size; ++i){
		for(size_t j =0; j<size; ++j){
			out<<init[i][j]<<' '; //prints out value at index
		}
		out<<'\n';
	}
	return out;
}

const bool empty(const size_t& row, const size_t& col, const std::vector<std::vector<int>>& check){
	return (check[row][col]==0);
}


const bool taken(const int& i, const std::vector<std::vector<int>>& check){
	const size_t size = check.size();
	
	for(size_t j =0; j<size; ++j){
		for(size_t k =0; k<size; ++k){
			if(check[j][k] ==i){
				return true; //if the input number is already used, then return true
			}
		}
	}
	return false;
}

const bool checkValid(size_t size, const std::vector<std::vector<int>>& square){
	const size_t sum = size*((size*size)+1)/2;
	size_t diagonal =0;
	
	for(size_t i =0; i<size; ++i){
		diagonal +=square[i][i];
	}
	if(diagonal!=sum){ //checks lower diagonal if equal to sum
		return false;
	}
	
	size_t second_diagonal = 0;
	for(size_t i =0; i<size; ++i){
		second_diagonal+=square[i][size-1-i];
	}
	if(second_diagonal!=sum){ //checks upper diagonal if equal to sum
		return false;
	}
	
	for(size_t i =0; i<size; ++i){
		size_t row_sum=0;
		
		for(size_t j =0; j<size; ++j){
			row_sum+=square[i][j];
		}
		if(row_sum!=sum){
			return false; //checks if row total is equal to sum
		}
	}
	for(size_t i =0; i<size; ++i){
		size_t col_sum=0;
		
		for(size_t j =0; j<size; ++j){
			col_sum+=square[j][i];
		}
		if(col_sum!=sum){ //checks if col total is equal to sum
			return false;
		}
	}
	return true;
}

void solveSquare(size_t pos, std::vector<std::vector<int>>& vec, std::set<size_t>& unused, size_t& solutions){
	const size_t size = vec.size();
	
	if((pos==size*size) && checkValid(size,vec)){
		std::cout<<vec<<'\n';
		++solutions; //if valid solution, then prints valid square and ++ number of valid solutions
	}
	else if(pos<size*size){
		size_t row=pos/size;
		size_t col = pos%size;
		
		if(empty(row,col,vec)){
			std::set<size_t> check=unused;
			
			for(auto i: unused){
				vec[row][col] = i;
				check.erase(i);
				solveSquare(pos +1, vec, check, solutions);
				
				check.insert(i); //puts value in different spots and checks is result is correct
				vec[row][col] = 0;
			}
		}
		else{
			solveSquare(pos+1, vec, unused, solutions); //iterates to next possible numbers
		}
	}
}
