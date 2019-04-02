

#ifndef Diamond_h
#define Diamond_h

class Diamond:public Shape{
public:
	//constructor
	Diamond(int x, int y, int size);
	
	/**
	 overrides set_stars in base base
	 */
	void set_stars() override; 
};

#endif /* Diamond_h */
