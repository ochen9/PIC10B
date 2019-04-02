//
//  List.h
//  hw7
//
//  Created by Olivia Chen on 3/5/19.
//  Copyright © 2019 Olivia Chen. All rights reserved.
//

#ifndef List_hpp
#define List_hpp

#include <stdio.h>
#include <stdexcept>
#include <iostream>

namespace pic10b{
	class node;
	class iterator;
	class const_iterator;
	
	class LinkedList{
	public:
		friend iterator; //has a pointer to a node and a container that they're going through
		friend const_iterator;
		friend void swap(LinkedList& one, LinkedList& another);
		
		LinkedList(): sz(1), first(0), last (nullptr) {} //default constructor
		LinkedList (std::initializer_list<int> store); //constructor
		LinkedList(const LinkedList& rhs); //copy constructor
		LinkedList(LinkedList&& rhs); //move constructor
		~LinkedList(); //destructor
		
		/**
		 assignment operators
		 @param list takes in the linked list
		 */
		LinkedList& operator=(LinkedList list);
		
		/**
		 accesses the const begin iterator
		 */
		const_iterator begin() const;
		
		/**
		 accesses the const iterator pointing past end
		 */
		const_iterator end() const;
		
		/**
		 regular begin iterator
		 */
		iterator begin();
		
		/**
		 regular end iterator, points to null node via nullptr
		 */
		iterator end();
		
		/**
		 insert value at the iterator's position
		 @param it, position that value is inserted at
		 @param val, value to be inserted
		 */
		void insert(iterator it, int val);
		
		/**
		 erase value at the iterator's position
		 @param it, position that value is erased at
		 */
		void erase(iterator it);
		
		/**
		 appends int at end
		 @param val, value to be added
		 */
		void push_back(int val);
		
		/**
		 pops off end element, throws exception if list is empty
		 */
		void pop_back();
		
		/**
		 prepends int at beginning
		 @param val, value to be added
		 */
		void push_front(int val);
		
		/**
		 erases int at beginning
		 */
		void pop_front();
		
		/**
		 sorts elements in ascending order from beginning to end
		 */
		void sort();
		
		/**
		 returns number of elements in list
		 */
		size_t size() const;
		
	private:
		node *first, *last; //pointers to the first and last nodes
		size_t sz;
	};
	
	
	class node{
	public:
		friend LinkedList;
		friend class iterator; //needs to give this friendship to access the underlying values
		friend class const_iterator; //needs to give this friendship to access the underlying values
		
	private:
		int val;
		node *prev, *next;
		node(int i): val(i), prev(nullptr), next(nullptr) {} //constructor to create a new node is private
	};
	
	
	class iterator{
		friend LinkedList;
		friend const_iterator;
	public:
		iterator& operator++(); //prefix ++ operator
		iterator operator++(int val); //postfix ++ operator
		
		iterator& operator--(); //prefix --
		iterator operator--(int val); //postfix --
		
		operator const_iterator(); //conversion operator
		
		int& operator*() const; //dereferencing operator (unary)
		friend bool operator==(const iterator& left, const iterator& right); //comparison
	private:
		node *curr; //currently managed node
		const LinkedList *container; //the iterator shouldn't change the list
		
		iterator(node* n, const LinkedList* l): curr(n), container(l) {}
	};
	
	
	class const_iterator{
	public:
		friend iterator;
		friend LinkedList;
		const_iterator& operator++(); //prefix ++
		const_iterator operator++(int val); //postfix ++
		
		const_iterator& operator--(); //prefix --
		const_iterator operator--(int val); //postfix --
		
		const int& operator*() const; //a const member function that can't change the underlying value within the node; also returns a const integer
		friend bool operator==(const const_iterator& left, const const_iterator& right); //comparison
	private:
		node *curr; //currently managed node
		const LinkedList *container; //the iterator shouldn't change the list
		
		const_iterator(node* n, const LinkedList* l): curr(n), container(l) {}
	};
	
	
	//operator overloading and outside nonmember functions
	std::ostream& operator<< (std::ostream& out, const LinkedList& obj);
	bool operator !=(const iterator& one, const iterator& two);
	bool operator !=(const const_iterator& one, const const_iterator& two);
	bool seqSearch (const_iterator one, const_iterator two, const int val);
	
}

#endif /* List_h */
