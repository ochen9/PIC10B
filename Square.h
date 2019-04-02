
#ifndef Square_h
#define Square_h

class Square:public Shape{
public:
	Square(int x, int y, int size);
	/**
	 overrides set_stars in base class
	 */
	void set_stars() override; 
};


#endif /* Square_h */
