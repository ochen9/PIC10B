
#ifndef Header_h
#define Header_h

#include <string>
#include <memory>

namespace pic10b{
	class VectorString{
	public:
		VectorString(); //default constructor
		VectorString(size_t x); //constructor
		VectorString(size_t x, std::string s);//input constructor
		VectorString(const VectorString& addr);//copy constructor
		VectorString(VectorString&& ); //move constructor
		
		/**
		 returns size of vector
		 **/
		size_t size();
		
		/**
		 returns capacity of vector
		 **/
		size_t capacity();
		
		/**
		 @param index
		 returns element of vector at given index
		 **/
		std::string& at(size_t index);
		
		/**
		 takes in input string and inserts it at the end of the vector
		 @param s, input string
		 **/
		void push_back(std::string s);
		
		/**
		 removes last element of the vector
		 **/
		void pop_back();
		
		/**
		deletes element at input index
		 @param index, input index
		 **/
		void deleteAt(size_t index);
		
		/**
		 takes in input index and string and inserts string at the index
		 @param index, input index
		 @param s, input string
		 **/
		void insertAt(size_t index, std::string s);
		
	private:
		std::unique_ptr<std::string[]> addr;
		size_t vec_size;
		size_t vec_capacity;
	};
}

#endif /* Header_h */
