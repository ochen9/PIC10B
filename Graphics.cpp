/*
 

Olivia Chen 604882033
 
 2/6/2019
 
 I, Olivia Chen, declare that I collaborated on this homework and got help in the PIC Lab and Office Hours.
 
 I collaborated with Melissa Carey and I confirm that we both contributed equally in the code.
 
 */

#include "Shape.h"
#include "Collection.h"
#include "Square.h"
#include "Diamond.h"
#include <iostream>
#include <memory>

//Shape constructor
Shape::Shape(int xpos, int ypos, int size) : xpos(xpos), ypos(ypos), size(size){}

void Shape::clear_all(){
	points.clear(); //clears all the elements in points
}

void Shape::add_point(int x, int y){
	points.push_back(std::make_pair(x,y)); //adds a point in the shape
}

void Shape::moveBy(int dx, int dy){
	xpos+=dx; //move x position by dx and y position by dy
	ypos+=dy;
	set_stars(); //calls set_stars
}

std::vector< std::pair<int, int> > Shape::get_points() const{
	return points; //returns points in shape
}

int Shape::get_x() const{
	return xpos;
}

int Shape::get_y() const{
	return ypos;
}

int Shape::get_size() const{
	return size;
}

void Shape::setSize(int new_size){
	std::vector<std::pair<int, int>> points2(0); //creates new vector and changes size and swaps what was in the old one tot he new one
	points.swap(points2);
	size = new_size;
	set_stars();
}


//constructor for Square
Square::Square(int xpos, int ypos, int size): Shape(xpos, ypos, size){
	set_stars();
}


void Square::set_stars(){
	int xTopLeft = get_x();
	int yTopLeft = get_y();
	int squareSize = get_size();
	
	int xTopRight = xTopLeft + squareSize-1;
	int yBottomLeft = yTopLeft + squareSize-1;
	
	clear_all();  //clears the points on the board so that previous times the function was called does not mess up results
	
	for(int j = yTopLeft; j<= yBottomLeft; ++j)	{
		for(int i = xTopLeft; i<= xTopRight; ++i) {
			add_point(i,j);  //adds stars in shape of square based on input
		}
	}
}


//Collection constructor
Collection::Collection(int lx, int hx, int ly, int hy) : lx(lx), hx(hx), ly(ly), hy(hy){
	std::vector<char> columns; //creates vector for columns
	for (int i = lx; i <= hx; ++i){
		columns.push_back('-'); //puts dashes on the board
	}
	
	for (int j = ly; j <= hy; ++j) // constructing the screen
	{
		screen.push_back(columns);
	}
}


void Collection::clear_all(){
	screen.clear(); //clears the screen
	std::vector<char> columns;
	for (int i = lx; i <= hx; ++i){
		columns.push_back('-'); //resets the screen with dashes again
	}

	for (int j = ly; j <= hy; ++j) // constructing the screen
	{
		screen.push_back(columns);
	}
}


void Collection::display(){
	clear_all();
	for (auto& s:shapes)
	{
		for (std::pair<int, int> a:s->get_points()) {
			if ((a.first >= lx && a.first <= hx) && (a.second >= ly && a.second <= hy)){
				screen[a.first-lx][a.second-ly] = '*'; //displays stars based on the shapes and their points that are in the Collection
			}
		}
	}
	
	for (int i = lx; i <= hx; i++)
	{
		for (int j = ly; j <= hy; j++)
		{
			std::cout << screen[j-ly][i-lx];
		}
		std::cout<<'\n';
	}
	
	
	
	// uses dynamic pointer cast to determine actual shape
	
	for (auto& s:shapes)
	{
		auto ptr = std::dynamic_pointer_cast<Square>(s);
		if (ptr)
		{
			std::cout << "square, ";
		}
		
		else
		{
			std::cout << "diamond, ";
		}
		std:: cout << "\b";
	}
	
}



void Collection::moveBy(int dx,  int dy)
{
	for (auto& s:shapes)
	{
		s->moveBy(dx, dy);//same as moveBy in shape but uses pointer instead
	}
}


//adds a new shape to the collection vector
void Collection::addShape(std::shared_ptr<Shape> s)
{
	shapes.push_back(s);
}



int Collection::totalStars()
{
	int numStars = 0;
	for (int i = lx; i <= hx; i++)
	{
		for (int j = ly; j <= hy; j++)
		{
			if (screen[i-lx][j-ly] == '*')
			{
				numStars++; //if there is a star on the board, adds to total number of stars
			}
		}
	}
	return numStars;
	
};




//changes the size of collection
void Collection::setSize(int new_size)
{
	for (auto& s:shapes)
	{
		s->setSize(new_size);
	}
}


//Diamond constructor
Diamond::Diamond(int xpos, int ypos, int size) : Shape(xpos, ypos, size)
{
	set_stars();
}



void Diamond::set_stars()
{
	
	int xpos = get_x();
	int ypos = get_y();
	int size = get_size();
	clear_all();
	add_point(xpos, ypos);
	
	//adds points from center outwards based on size provided
	for (int i = 0; i < size; i++) {
		int distance = static_cast<int>(i);
		add_point(xpos + distance, ypos);
		add_point(xpos - distance, ypos);
		add_point(xpos, ypos + distance);
		add_point(xpos , ypos - distance);
	}
	
	for (int i = 1; i < get_size(); i++){
		for (int j = 1; j <= size-1-i; j++) {
			int xdistance = i;
			int ydistance = j;
			
			add_point(xpos - xdistance, ypos + ydistance);
			add_point(xpos + xdistance, ypos + ydistance);
			add_point(xpos - xdistance, ypos - ydistance);
			add_point(xpos + xdistance, ypos - ydistance);
			
		}
		
	}
	
}
