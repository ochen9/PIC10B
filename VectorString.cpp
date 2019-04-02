#include "VectorString.h"

#include <string>
#include <memory>
#include <iostream>

//default constructor
pic10b::VectorString::VectorString():vec_size(0),vec_capacity(1)
{
	addr = std::unique_ptr<std::string[]> (new std::string[vec_capacity]);
}

//constructor, allocats dynamic array of 2x input size
pic10b::VectorString::VectorString(size_t x){
	vec_size = x;
	vec_capacity = 2 * x;
	addr = std::unique_ptr<std::string[]> (new std::string[vec_capacity]);
	for (int i = 0; i < vec_capacity; i++){
		addr[i] = " ";
	}
}

//constructor that takes in an input string
pic10b::VectorString::VectorString(size_t x, std::string s)
{
	vec_size = x;
	vec_capacity = 2 * vec_size;
	addr = std::unique_ptr<std::string[]> (new std::string[vec_capacity]);
	for (int i = 0; i < vec_size; i++){
		addr[i] = s;
	}
}

//copy constructor
pic10b::VectorString::VectorString(const VectorString& addr) {}

//move constructor
pic10b::VectorString::VectorString(VectorString&& ) {
	pic10b::VectorString moved_vector((VectorString()));
}

size_t pic10b::VectorString::size(){
	return vec_size;
}

size_t pic10b::VectorString::capacity(){
	return vec_capacity;
}

//pushback function that adds element to the end of the vector
void pic10b::VectorString::push_back(std::string s){
	
	if (vec_size < vec_capacity){
		addr[vec_size] = s;
		vec_size ++;
	}
	//if the vector size is over the capacity, double the capcity
	else
	{
		std::unique_ptr<std::string[]> new_addr;
		new_addr = std::unique_ptr<std::string[]> (new std::string[2*vec_capacity]);
		for (size_t i = 0; i < vec_capacity; i++)
		{
			new_addr[i] = addr[i];
		}
		addr = move(new_addr);
		addr[vec_size] = s;
		vec_size ++;
	}
	
}

//removes last element of vector
void pic10b::VectorString::pop_back(){
	vec_size--;
}

//deletes element at given index
void pic10b::VectorString::deleteAt(size_t index) {
	if (index < vec_size){
		
		for (size_t i = index; i < vec_size; i++){
			addr[i] = addr[i+1];
		}
		vec_size--;
	}
}


//accepts an index and a string and inserts the string into the vector at that index
void pic10b::VectorString::insertAt(size_t index, std::string s) {
	if (vec_size < vec_capacity){
		
		for (size_t i = (vec_size-1); i >= index && i <=vec_capacity; i--){
			addr[i+1] = addr[i];
		}
		addr[index] = s;
	}
	else {
		std::unique_ptr<std::string[]> new_addr = std::unique_ptr<std::string[]> (new std::string[2 * vec_capacity]);
		
		for (size_t i = 0; i < (vec_capacity); i++) {
			new_addr[i] = addr[i];
		}
		addr = move(new_addr);
		
		for (size_t i = (vec_size-1); i >= index && i <=vec_capacity*2; i--) {
			addr[i+1] = addr[i];
		}
		
		addr[index] = s;
		vec_capacity = 2 * vec_capacity;
	}
	vec_size++;
}

//returns element at given index
std::string& pic10b::VectorString::at(size_t index){
	return addr[index];
}



//main routine
pic10b::VectorString foo() {
	return pic10b::VectorString(2);
}

int main(){
	pic10b::VectorString vs;
	std::cout << "vs stats: " << vs.size() << " " << vs.capacity() << '\n';
	vs.push_back("hello");
	std::cout << "vs stores: " << vs.at(0) << '\n';
	
	pic10b::VectorString vs2(foo());
	std::cout << "vs2 stats: " << vs2.size() << " " << vs2.capacity() << '\n';
	
	std::cout << "vs2 stores: ";
	for (std::size_t i = 0, total_size = vs2.size(); i < total_size; ++i) {
		std::cout << vs2.at(i) << ",";
	}
	std::cout << '\n';
	
	pic10b::VectorString vs3(4, "beta");
	vs3.pop_back();
	vs3.push_back("delta");
	vs3.push_back("epsilon");
	vs3.at(1) = "gamma";
	vs3.insertAt(0, "alpha");
	vs3.push_back("zeta");
	vs3.push_back("theta");
	vs3.insertAt(vs3.size() - 1, "eta");
	vs3.deleteAt(3);
	
	std::cout << "v3 stats: " << vs3.size() << " " << vs3.capacity() << '\n';
	std::cout << "v3 stores: ";
	for (std::size_t i = 0, total_size = vs3.size(); i < total_size; ++i) {
		std::cout << vs3.at(i) << ",";
	}
	
	std::cin.get();
	return 0;
}
