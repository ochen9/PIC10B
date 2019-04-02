

#ifndef Shape_h
#define Shape_h
#include <vector>
#include <utility>

class Shape{
private:
	int xpos;
	int ypos;
	int size;
	std::vector<std::pair<int, int> > points;

protected:
	/**
	 sets stars for a shape
	 */
	virtual void set_stars()=0;
	/**
	 adds a single point to the vector
	 */
	void add_point(int x, int y);

public:
	/**
	 returns x value
	 */
	int get_x() const;
	
	/**
	 returns y value
	 */
	int get_y() const;
	
	/**
	 returns size
	 */
	int get_size() const;
	
	/**
	 returns points
	 */
	std::vector<std::pair<int, int> > get_points() const;
	
	/**
	 clears all points from vector
	 */
	void clear_all();
	
	
	//constructor
	Shape(int xpos, int ypos, int size);
	
	/**
	 @int dx, amount you want to move x value
	 @int dy, amount you want to move y value
	 */
	void moveBy(int dx, int dy);
	
	/**
	 changes vector to new size
	 @int new_size input for changing size
	 */
	void setSize(int new_size);
	

};

#endif /* Shape_h */
