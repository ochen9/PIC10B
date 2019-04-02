
#ifndef Collection_h
#define Collection_h
#include <vector>
#include <utility> 

class Collection{
private:
	std::vector<std::shared_ptr<Shape>> shapes;
	int lx;
	int hx;
	int ly;
	int hy;
	std::vector<std::vector<char>> screen; //what is output to the console
	
public:
	Collection(int lx, int ly, int hx, int hy);
	
	/**
	 returns total stars on the board
	 */
	int totalStars();
	
	/**
	 @input_shape takes in input shape and adds it to collection
	 */
	void addShape(std::shared_ptr<Shape>input_shape);
	
	/**
	 displays screen
	 */
	void display();
	
	/**
	 moves shape
	 @int dx, amount you want to move in x direction
	 @int dy, amount you want to move in y direction
	 */
	void moveBy(int dx, int dy);
	
	
	/**
	 changes vector to new size
	 @int new_size input for changing size
	 */
	void setSize(int new_size);
	
	
	/**
	 clears collection
	 */
	void clear_all();
	
};
#endif /* Collection_h */
