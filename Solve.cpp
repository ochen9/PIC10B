//
//  main.cpp
//  hw6n
//
//  Created by Olivia Chen on 2/27/19.
//  Copyright © 2019 Olivia Chen. All rights reserved.
//


#include "MagicSquare.h"

int main(){
	std::cout<<"Enter a square size: ";
	size_t n = 0;
	std::cin>>n;
	std::cout<<"Enter a square format: "<<'\n';
	std::vector<int>row(n,0);
	std::vector<std::vector<int>> square(n,row);
	std::cin >> square;
	std::set<size_t>unused;
	
	for(size_t i =0; i<n*n; ++i){
		unused.insert(i+1);
	}
	
	for(size_t i=0; i<n; ++i){
		for(size_t j=0; j<n; ++j){
			if(square[i][j] !=0){
				unused.erase(square[i][j]);
			}
		}
	}
	
	size_t count = 0;
	solveSquare(0,square,unused,count);
	std::cout<<"finished solving! number of solutions: "<<count<< '\n';
	
	return 0;
}
