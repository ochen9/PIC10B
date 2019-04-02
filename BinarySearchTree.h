//
//  BinarySearchTree.h
//  hw8
//
//  Created by Olivia Chen on 3/9/19.
//  Copyright © 2019 Olivia Chen. All rights reserved.
//

#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include <iostream>

/**
 Creates new namespace that holds a class object of type BinarySearchTree
 */
namespace pic10b
{
	//TREE CLASS
	/**
	 This class creates a Tree class that stores double values, node class, and iterator class
	 */
	class Tree
	{
	private:
		/**
		 Class declares a nested node class object to be used within the Tree class, class is private because user should not have access to it
		 */
		class node;
		
		node *root; // create node object for root of tree
		size_t tree_size; // create variable to store size (ie: number of elements) within tree
		
		/**
		 function recursively deletes the tree using node
		 @param n : node position to delete
		 */
		void deleteTree(node* n);
		
		/**
		 function helps with copying
		 @param n : node position to traverse insert
		 */
		void traverseInsert(node* n);
		
	public:
		/**
		 Class declares a nested interator class object to be used within Tree class, iterator class can be used by users because they are the only way to work through the tree
		 */
		class iterator;
		
		/**
		 a default constructor, creating an empty Tree object
		 */
		Tree();
		
		/**
		 a destructor function for Tree class
		 */
		~Tree();
		
		/**
		 Copy constructor makes new independent copy of other Tree
		 @param other Tree to copy from
		 */
		Tree(const Tree& other);
		
		/**
		 Move constructor takes data from an rvalue of type Tree
		 @param other Tree reach end of its lifetime
		 */
		Tree(Tree&& other);
		
		/**
		 asignment operator for both copy and move constructor, using copy and move swap idiom
		 @param other Tree object
		 */
		Tree& operator=(Tree other);
		
		/**
		 friend function swaps two Tree objects
		 @param one : first Tree to swap
		 @param two : second Tree to swap
		 */
		friend void swap(Tree& one, Tree& two);
		
		/**
		 member function overloaded on const, returning iterators to the beginning of Tree
		 @return const iterator pointing to beginning
		 */
		iterator begin() const;
		
		/**
		 member function overloaded on const returning iterators pointing past the end
		 @return const interator pointing to one past the end
		 */
		iterator end() const;
		
		/**
		 insert value before the point where the iterator points
		 @param num : value to insert
		 */
		void insert(double num);
		
		/**
		 erase or remove the node managed by the iterator from the tree
		 @param pos : iterator pointing to the position where to erase given value
		 */
		void erase(iterator pos);
		
		/**
		 returns the number of elements in the Tree
		 @return size_t value of the number of elements contained in Tree
		 */
		size_t size() const;
		
		/**
		 returns iterator to the node with a given value if found and otherwise returning the past-the-end iterator
		 @param input : double value input
		 @return iterator to node with given value if found and otherwise retun the past-the-end iterator
		 */
		iterator find(const double input) const;
	};
	
	/**
	 declare function at namespace level too which swaps two Tree objects
	 @param one : first Tree to swap
	 @param two : second Tree to swap
	 */
	void swap (Tree& one, Tree& two);
	
	/************************************ NODE CLASS ********************************/
	
	/**
	 Class declares a node nested class object to be used within the Tree class
	 */
	class Tree::node
	{
		friend Tree; // make Tree a friend because its member functions can search through nodes
		friend iterator; // make iterator friend becuase it needs to be able to advance by checking the node
		
	private:
		/**
		 private node constructor function to create new node, make private because nodes purpose is to manage the linked lists therefore the user should not be able to construct nodes, take by value and move it
		 @param new_val : new double value to construct with node
		 */
		node(double new_val);
		
		node *left, *right; // private vairable storing pointers to left and right nodes (ie: its children)
		node *parent; // private variable storing pointer to parent node
		double val; // the data value it stores
		
		/**
		 member function for inserting node
		 @param new_node : new node to insert into Tree
		 @return true if insertion happens successfuly otherwise return false
		 */
		bool insertNode(node* new_node);
	};
	
	/**************************** ITERATOR CLASS ******************************/
	
	class Tree::iterator
	{
		friend Tree; // make Tree a friend because it needs to allow iterator modifications through Tree operations
		
	private:
		/**
		 private iterator constructor that creates new iterator object, only Tree can construct these iterators therefore make constructor private
		 @param n : a node object
		 @param tree : a Tree object to create an iterator on
		 */
		iterator(node* n, const Tree* tree);
		
		node *curr; // create pointer to currently managed node
		const Tree *container; // create a pointer to a const Tree because this iterator should not change anything; its the holding container
		
	public:
		/**
		 prefix operator member function that increments iterator forward
		 @return by reference a new, changed left-hand side iterator that is increased
		 */
		iterator& operator++();
		
		/**
		 postfix operator member function that increments iterator forward
		 @return a copy of the left-hand side iterator that is increased
		 */
		iterator operator++(int unused);
		
		/**
		 prefix operator member function that decrements iterator backward
		 @return by reference a new, changed left-hand side iterator that is decreased
		 */
		iterator& operator--();
		
		/**
		 postfix operator member function that decrements iterator backward
		 @return a copy of the left-hand side iterator that is decreased
		 */
		iterator operator--(int unused);
		
		/**
		 dereferencing operator function that allows the iterator to access value it is pointing at, return by reference to const so that we cannot change the value
		 @return the double object the iterator is pointing to
		 */
		const double& operator*() const;
		
		/**
		 arrow operator function that allows the iterator to access member functions of a class on the object it is pointing at
		 @return the double object the iterator is pointing to
		 */
		const double* operator->() const;
		
		/**
		 comparison operator for "==" that compares two iterators, make friend so it can access
		 @param left : iterator object on the left-hand side
		 @param right : iterator object on the right-hand side
		 @return the "==" comparison of the two iterator objects
		 */
		friend bool operator== (const iterator& left, const iterator& right);
	};
	
	/**
	 comparison operator for "!=" that compares two iterators
	 @param left : iterators object on the left-hand side
	 @param right : iterators object on the right-hand side
	 @return the "!=" comparison of the two iterator objects
	 */
	bool operator!= (const Tree::iterator& left, const Tree::iterator& right);
	
}

#endif /* BinarySearchTree_h */
