//
//  List.cpp
//  hw7
//
//  Created by Olivia Chen on 3/5/19.
//  Copyright © 2019 Olivia Chen. All rights reserved.
//

#include "List.h"


/*constructor for a LinkedList object; takes in an initializer list and loops through to push_back every value into the LinkedList */
pic10b::LinkedList::LinkedList (std::initializer_list<int> store): LinkedList() {
	for(int i: store){ //loops through every element of the initializer list
		push_back(i);
	}
}

// swap directly swaps the pointers
void pic10b::swap(LinkedList& one, LinkedList& another) {
	using std::swap;
	swap(one.first, another.first); //swaps the first and last nodes
	swap(one.last, another.last);
}

//assignment operator that sets the lhs value equal to the rhs by swapping
pic10b::LinkedList& pic10b::LinkedList::operator=(LinkedList list){
	pic10b::swap(*this, list);
	return *this;
}

pic10b::const_iterator pic10b::LinkedList::begin() const{
	return const_iterator (first, this);
}

pic10b::const_iterator pic10b::LinkedList::end() const{
	return const_iterator (nullptr, this);
}

pic10b::iterator pic10b::LinkedList::begin(){
	return iterator (first, this);
}

pic10b::iterator pic10b::LinkedList::end(){
	return iterator(nullptr, this);
}

//adds a passed in value to the end of the LinkedList
void pic10b::LinkedList::push_back(int val){
	pic10b::node *n = new node(val);
	if (last) { // if the last node doesn't return null
		last->next = n; // make last point to n
		n->prev = last; // make n have last as its previous node
		last = n; // update the last position
	}
	else { // in this case the last node is null so list is empty
		first = last = n; // both equal to n
	}
	++sz;
}

//adds a passed in value to the front of the LinkedList
void pic10b::LinkedList::push_front(int val){
	node *n=new node(val);
	if(first){
		first->prev = n;
		n->next = first;
		first = n;
	}
	
	else{
		first = last = n;
	}
	++sz;
}

//deletes the last element within the LinkedList
void pic10b::LinkedList::pop_back(){
	if (!last) { //if the list is at null, then your list is completely empty and you can't continue to call the pop_back() function on it
		throw std::logic_error("pop back on empty list");
	}
	else if (first == last){ // if first and last are the same then...
		delete first; // free up the heap memory
		first = last = nullptr; // make both pointers to null because the entire LinkedList is empty
	}
	else {
		node *newlast = last->prev; // store the new last node
		newlast->next = nullptr; // set its next pointer to null
		delete last; // free the heap memory
		last = newlast; // update the last value
	}
	--sz;
}

//inserts a value at the location that iterator it is pointing to
void pic10b::LinkedList::insert(iterator it, int val) {
	if (it.curr == nullptr) { // then inserting before past-the-end
		push_back(val);
	}
	
	else if (it.curr == first) { // then at beginning
		push_front(val);
	}
	
	else{ // then in middle
		node *n = new node(val); // create new node
		n->next = it.curr; // set n’s next
		n->prev = it.curr->prev; // set n’s previous
		it.curr->prev->next = n; // make current previous’ next node into n
		it.curr->prev = n; // make current previous node into n
	}
	++sz;
}

//erases the element at the location that iterator it is pointing to
void pic10b::LinkedList::erase(iterator it) {
	if (it.curr == first) { //if the iterator is currently pointing to first then...
		pop_front(); // remove first
	}
	else if (it.curr == last) { //if the iterator is currently pointing to last then...
		pop_back(); // remove last
	}
	else { // if it's pointing to somewhere in the middle
		it.curr->prev->next = it.curr->next; //reroute the current iterator's previous node's next to be equal to it's next node
		it.curr->next->prev = it.curr->prev; // reroute previous of next to be the node prior to it
		delete it.curr; // free the heap memory of item being removed
	}
	--sz;
}

//deletes the first element within the LinkedList
void pic10b::LinkedList::pop_front(){
	if (!last) {
		throw std::logic_error("pop front on empty list");
	}
	else if(first == last){
		delete first;
		first = last = nullptr;
	}
	else{
		node *newfront = first->next;
		newfront->prev = nullptr;
		delete first;
		first = newfront;
	}
	--sz;
}

// copy constructor: copy elements over one by one via a range based for loop
pic10b::LinkedList::LinkedList(const LinkedList& rhs) : first(nullptr), last(nullptr) { //constructs a new LinkedList object with first and last equal to a nullptr
	for (int i:rhs){ //take each int value from rhs and push it back into this copy
		push_back(i);
		++sz;
	}
}
/* move constructor: take pointers to first and last then set rhs pointers to
 null so it is in valid destructible state */
pic10b::LinkedList::LinkedList(LinkedList&& rhs) : LinkedList() { // default construct a new LinkedList object
	swap(*this, rhs); // use member swap
}

//destructor for the LinkedList
pic10b::LinkedList::~LinkedList() {
	node *n = first; // start at first node
	while (n != nullptr) { // while not past the end denoted by nullptr
		node *temp = n->next; // temporarily store the next position
		delete n; // delete the node on heap
		n = temp; // move n right
	}
}

//pre-decrement operator for the iterator class
pic10b::iterator& pic10b::iterator::operator--(){
	if(curr == container->first) { //if the current ptr to a node is equal to the first
		throw std::logic_error("Invalid address");
	}
	else if(curr == nullptr) { //if the current node is equal to a nullptr, then go to the last element
		curr = container->last; // now make iterator refer to last element
	}
	else { //if the current node is in the middle somewhere
		curr = curr->prev; // reference previous node
	}
	return *this;
}

//post-decrement operator for the iterator class
pic10b::iterator pic10b::iterator::operator--(int val) {
	iterator copy(*this); //create a copy to be returned
	this-> operator--(); //decrement the copy by calling the pre-decrement operator previously defined
	return copy; //return the copy
}

//pre-increment operator for the iterator class
pic10b::iterator& pic10b::iterator::operator++(){
	if(curr == container->first){ //if the currently managed node is equal to the first in the LinkedList
		curr = curr->next;
	}
	else if(curr==nullptr){ //if the currently managed node is equal to one past the last
		throw std::logic_error("Cannot go beyond end");
	}
	else{ //if the currently managed node is somewhere in the middle
		curr = curr->next;
	}
	return *this;
}

//post-increment operator for the iterator class
pic10b::iterator pic10b::iterator::operator++(int val){
	iterator copy(*this);
	this-> operator++();
	return copy;
}

// dereferencing operator for iterator
int& pic10b::iterator::operator*() const {
	return curr->val; // return reference to the int stored
}

//pre-increment operator for the const_iterator class
pic10b::const_iterator& pic10b::const_iterator::operator++(){
	if(curr == container->first){ //checls if the currently managed node is equal to the first in the LinkedList
		curr = curr -> next; //then move it to the node after it
	}
	else if(curr == nullptr){ //checks if the currently managed node is equal to one past the end
		throw std::logic_error("Cannot go beyond end"); //then throw a logic_error
	}
	else{ //if the currently managed node is somewhere between the first and one past the end
		curr = curr->next; //then move the current node to be the next node after it
	}
	return *this;
}

//post-increment operator for the const_iterator class
pic10b::const_iterator pic10b::const_iterator::operator++(int val){
	const_iterator copy(*this); //create a copy of the current const_iterator
	this -> operator++();
	return copy;
}

pic10b::const_iterator& pic10b::const_iterator::operator--(){
	if(curr == container->first) { //if the current ptr to a node is equal to the first
		throw std::logic_error("Invalid address");
	}
	else if(curr == nullptr) { //if the current node is equal to a nullptr, then go to the last element
		curr = container->last; // now make iterator refer to last element
	}
	else { //if the current node is in the middle somewhere
		curr = curr->prev; // reference previous node
	}
	return *this;
}

pic10b::const_iterator pic10b::const_iterator::operator--(int val){
	const_iterator copy(*this); //create a copy to be returned
	this-> operator--(); //decrement the copy by calling the pre-decrement operator previously defined
	return copy; //return the copy
}

// dereferencing operator for const_iterator
const int& pic10b::const_iterator::operator*() const {
	return curr->val; // return copy of the int stored
}
// comparison overloaded operator for iterator class
bool pic10b::operator==(const iterator& left, const iterator& right) {
	return ((left.curr == right.curr) && (left.container == right.container));
}

//comparison overloaded operator for const_iterator class
bool pic10b::operator==(const const_iterator& left, const const_iterator& right) {
	return ((left.curr == right.curr) && (left.container == right.container));
}

void pic10b::LinkedList::sort(){
	auto beg =  begin(); //store an iterator holding the beginning node
	iterator past_end(nullptr, this); //store an iterator holding the node that is one past the end in the LinkedList
	if(beg == past_end){ //if the beginning iterator is equal to one past the end
		std::cout << "empty list";
		return;
	}
	
	while (beg != past_end){ //while the beginning iterator does not equal to one past the end
		auto minpos = beg; //minpos is the smallest value to compare against
		auto curr = beg;
		++curr; //increment so that curr now points to one past beg
		while(curr != past_end){ //while curr does not equal to one past the end
			if(*curr<*minpos){ //if the underlying value of curr is smaller than that of minpos
				minpos = curr; //then have minpos point to the curr node
			}
			++curr; //then increment curr to keep going through the whole list (it'll keep going through the list until it is at the last node)
		}
		std::swap (*minpos, *beg); //once we've found the smallest underlying value, swap the 2 underlying values
		++beg;
	}
}

//returns the underlying size of the LinkedList
size_t pic10b::LinkedList::size() const{
	return sz;
}

std::ostream& pic10b::operator<< (std::ostream& out, const pic10b::LinkedList& obj){
	for(auto it = obj.begin(); it != obj.end(); ++it){ //for loop creating an iterator it that goes through the entire Linked List and prints out the underlying values
		out << *it << " ";
	}
	return out;
}

//looks through a given range of const_iterators and traverses the linked list to look for the pass in value
bool pic10b::seqSearch (const_iterator one, const_iterator two, const int val){
	/*if (*one==val){ //if the first const_iterator passed in is equal to the
	 return true;
	 }*/
	
	for (auto it = one; it != two; ++it){ //iterates through the range of iterators passed in
		if(*it == val){ //swap pointers if the left is larger than the right
			return true;
		}
	}
	
	
	return false;
}

//conversion operator, moves from an iterator to a const_iterator
pic10b::iterator::operator const_iterator(){
	return const_iterator (curr, container);
} //just call the const_iterator constructor

//overloaded operator!= for iterators; is overloaded by negating the overloaded operator==
bool pic10b::operator !=(const iterator& one, const iterator& two){
	return !(one==two);
}

//overloaded operator!= for const_iterators; is overloaded by negating the overloaded operator==
bool pic10b::operator !=(const const_iterator& one, const const_iterator& two){
	return !(one==two);
}

