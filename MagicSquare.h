//
//  MagicSquare.hpp
//  hw6n
//
//  Created by Olivia Chen on 2/27/19.
//  Copyright © 2019 Olivia Chen. All rights reserved.
// I, Olivia Chen, worked with Leif Mollo and David (forgot last name). All members contributed equally

#ifndef MagicSquare_h
#define MagicSquare_h

#include <vector>
#include<iostream>
#include <string>
#include <set>


/**
 input operator, fills in format of magic square
 @param in, input numbers
 @param init, vector of numbers
 returns the input vector
 */
std::istream& operator>>(std::istream& in, std::vector<std::vector<int>>& init);

/**
 output operator, prints out the magic square
 @param out, output of the vector
 @param init, the vector that is being read
 returns the output
 */
std::ostream& operator<<(std::ostream& out, std::vector<std::vector<int>>& init);


/**
figures out whether spot in square is empty
 @param row, row of square
 @param col, column of square
 @param check , the vector being checked
 
 returns true or false
 */
const bool empty(const size_t& row, const size_t&col, const std::vector<std::vector<int>>& check);


/**
 figures out whether number is used in square already
 @param i, the number being checked
 @param check , the vector being checked
 
 returns true or false
 */
const bool taken(const int& i, const std::vector<std::vector<int>>& check);


/**
checks whether solution is valid or not
 @param size, size of row or column
 @param square, the vector being checked
 
 returns true or false
 */
const bool checkValid(size_t size, const std::vector<std::vector<int>>& square);

/**
solves the square
 @param pos, the position in square
 @param vec, square being solved
 @param unused, set of numbers that aren't used in square yet
 @param slutions the number of solutions
 */
void solveSquare(size_t pos, std::vector<std::vector<int>>& vec, std::set<size_t>& unused, size_t& solutions);

#endif /* MagicSquare_h */
