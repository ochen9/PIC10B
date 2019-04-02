//
//  BinarySearchTree.cpp
//  hw8
//
//  Created by Olivia Chen on 3/9/19.
//  Copyright © 2019 Olivia Chen. All rights reserved.
//

#include "BinarySearchTree.h"


void pic10b::Tree::deleteTree(node* n) //  function recursively deletes the tree using node
{
	if (n != nullptr) // check that we are acutally pointing to a node
	{
		if (n->left != nullptr) // if the current node's left child is not null
		{
			deleteTree(n->left); // use recursion to call function on the next left node, keep going until we move as far left as possible
		}
		
		if (n->right != nullptr) // if the current node's right child is not null
		{
			deleteTree(n->right); // use recursion to call function on the next right node, keep going down as far right as possible
		}
		
		delete n; // delete current node we are pointing to
		n = nullptr; // set current delete node to null
		tree_size--; // decrease size
	}
}

void pic10b::Tree::traverseInsert(node* n) //  function helps with copying
{
	insert(n->val); // insert value using already constructed insert function
	
	if (n->left != nullptr) // if the current node's left child is not null
	{
		traverseInsert(n->left); // use recursion to call function on the next left node, keep going until we move as far left as possible
	}
	
	if (n->right != nullptr) // if the current node's right child is not null
	{
		traverseInsert(n->right); // use recursion to call function on the next right node, keep going down as far right as possible
	}
}

pic10b::Tree::Tree() : root(nullptr), tree_size(0) {} // a default tree constructor storing nothing with root set to null and size set to 0

pic10b::Tree::~Tree() //  a destructor function for Tree class
{
	deleteTree(root); // use recursive deleteTree function to destroy Tree object
}

pic10b::Tree::Tree(const Tree& other) : root(nullptr), tree_size(0) // Copy constructor
{
	if (other.root) // if there is a tree to copy over, ie that the root is not pointing to null
	{
		traverseInsert(other.root); // calls a recursive function on nodes to copy over
	}
}

pic10b::Tree::Tree(Tree&& other) : Tree() // Move constructor
{
	swap(*this, other); // use member swap to swap object we just created in default constructor with the Tree inserted into function (ie: "other")
}

pic10b::Tree& pic10b::Tree::operator=(Tree other) // asignment operator for both copy and move constructor
{
	swap(*this, other); // use member swap to swap objects
	return *this; // return the implicit object
}

pic10b::Tree::iterator pic10b::Tree::begin() const // returning iterators to the beginning of Tree
{
	if (root == nullptr) // if root node is null then tree is empty
	{
		return iterator(nullptr, this); // return an iterator that is null
	}
	
	node *n = root; // begin at the root
	
	while (n->left != nullptr) // while we can still move left (ie: move to lower value)
	{
		n = n->left; // go left on tree by making n equal to the one on its left, very first node of tree is the node furthest left
	}
	
	return iterator(n, this); // return iterator created by most left node that contains the smallest value
}

pic10b::Tree::iterator pic10b::Tree::end() const // returning const iterators pointing past the end
{
	return iterator(nullptr, this); // end iterator means "past the end" therefor, create iterator storing null
}

void pic10b::Tree::insert(double num) // insert value before the point where the iterator points
{
	if (!root) // if the root is empty, ie: if tree is empty
	{
		root = new node(std::move(num)); // make new node and set it to be root
		++tree_size; // increase size of Tree
	}
	else // otherwise root contains values already
	{
		node *n = new node(std::move(num)); // create a new node with input value and set it to "n"
		
		if (root->insertNode(n)) // try to insert node and if successful incerstion of node
		{
			++tree_size; // increase size of tree if successful incerstion
		}
	}
}

void pic10b::Tree::erase(iterator pos) // erase node managed by iterator from tree
{
	if ((pos.curr->left) && (pos.curr->right)) // if node has 2 children
	{
		iterator temp = pos; // create a temp iterator that points to position you want to delete
		temp++; // use already defined ++ operator to increase the iterator and move to the next largest value (or node) by finding its right child's far left value
		
		std::swap(pos.curr->val, temp.curr->val); // overwrite the given node's vlaue with the right-far-left value : set the position you want to delete equal to the new temp node that will take its place
		
		erase(temp); // use recursion to erase the position of the node that you used to overwrite the input position, this will ensure that if this node has 0, 1, or 2 children the structure of the tree will be preserved when deleting this node that you moved
		
	}
	else if ((pos.curr->left) && (!pos.curr->right)) // if node has left child : left child is present, but NO right child
	{
		node *temp = pos.curr; // create temp node pointer to hold original position
		pos.curr = pos.curr->left; // move position to the correct left child of the given node
		pos.curr->parent = temp->parent; // // set given node's child's (ie: new pos) parent to give node's (ie: temp) parent
		
		if (temp->parent->left == temp) // if the temp (which is pointing to value we want to earse) is its parent's left child
		{
			temp->parent->left = pos.curr; // than set given node's parent's corresponding left child to given node's child (ie: new pos)
		}
		else // else the temp (which is pointing to value we want to earse) is its parent's right child
		{
			temp->parent->right = pos.curr; // than set given node's parent's corresponding right child to given node's child (ie: new pos)
		}
		
		delete temp; // delete the original node
		pos.curr = nullptr; // set current delete node to null
		--tree_size; // decrease size of tree
	}
	else if ((pos.curr->right) && (!pos.curr->left)) // if node has right child : right child present, but NO left child
	{
		node *temp = pos.curr; // create temp node pointer to hold original position
		pos.curr = pos.curr->right; // move position to the correct right child of the given node
		pos.curr->parent = temp->parent; // set given node's child's (ie: new pos) parent to give node's (ie: temp) parent
		
		if (temp->parent->left == temp) // if the temp (which is pointing to value we want to earse) is its parent's left child
		{
			temp->parent->left = pos.curr; // than set given node's parent's corresponding left child to given node's child (ie: new pos)
		}
		else // else the temp (which is pointing to value we want to earse) is its parent's right child
		{
			temp->parent->right = pos.curr; // than set given node's parent's corresponding right child to given node's child (ie: new pos)
		}
		
		delete temp; // delete the original node
		pos.curr = nullptr; // set current delete node to null
		--tree_size; // decrease size of tree
	}
	else // if nod has node children
	{
		if (pos.curr == pos.curr->parent->left) // if curr position is its parents left child
		{
			pos.curr->parent->left = nullptr; // make the curr's parent pointer point to null if it is the left child
		}
		else // else the curr position is its parents right child
		{
			pos.curr->parent->right = nullptr; // make the curr's parent pointer point to null if it is the right child
		}
		
		delete pos.curr; // delete the node
		pos.curr = nullptr; // set current delete node to null
		--tree_size; // decrease size of tree
	}
}

size_t pic10b::Tree::size() const // returns number of elements in Tree
{
	return tree_size; // return Tree size variable
}

pic10b::Tree::iterator pic10b::Tree::find(const double input) const // returns iterator to the node with a given value if found and otherwise returning the past-the-end iterator
{
	iterator itr = begin(); // create an iterator that starts at the beginning
	
	while ((*itr != input) && (itr != end())) // while the current iterator you are at does not equal the input value AND while the itr is not equal to the end pointer
	{
		++itr; // increase iterator to next node
	}
	
	return itr; // return iterator if the while loop gets to the end without finding the input value then it will return the past-the-end iterator
}

void pic10b::swap (Tree& one, Tree& two) // redeclared swap function at namespace level
{
	std::swap(one.root, two.root); // swap each Tree's root
	std::swap(one.tree_size, two.tree_size); // swap each Tree's size
}

/************************************ NODE CLASS ********************************/

pic10b::Tree::node::node(double new_val) : left(nullptr), right(nullptr), parent(nullptr), val(new_val) {} // constructor function to create new node, sets value but points to null for its left and right children and parent node

bool pic10b::Tree::node::insertNode(node* new_node) // inserts node into Tree
{
	if (val < new_node->val) // if value is less than new node value, new node should go to the right
	{
		if (right) // if this node has a right child (ie: is not nullptr)
		{
			right->insertNode(new_node); // use recursion on right child
		}
		else // if right child is null, the node does not have a right child
		{
			right = new_node; // make new node the right child
			new_node->parent = this; // make new_node's parent point to current implicit "this" node
		}
		return true; // return true if successfully inserted right child
	}
	else if (val > new_node->val) // if value is larger than new node value, new node should go to the left
	{
		if(left) // if this node has a left child (ie: is not nullptr)
		{
			left->insertNode(new_node); // use recursion on left child
		}
		else // if the left child is null, the node does not have a left child
		{
			left = new_node; // make new node the left child
			new_node->parent = this; // make new_node's parent point to current implicit "this" node
		}
		return true; // return true if successfully inserted left child
	}
	
	// we don't add anything if new_node value is neither < nor > than current value
	delete new_node; // free allocated node memory
	return false; // return false if no insertion occured
}

/**************************** ITERATOR CLASS ******************************/

pic10b::Tree::iterator::iterator(node* n, const Tree* tree) : curr(n), container(tree) {} // iterator constructor, sets current node and container to inputs

pic10b::Tree::iterator& pic10b::Tree::iterator::operator++() // prefix operator to increment
{
	if (curr == nullptr) // if current position is just past the end (top of tree), you cannont increment beyond this node since it has no where else to go
	{
		throw std::logic_error("Invalid address"); // throw logic error because of invlaid address
	}
	else if (curr->right != nullptr) // if position does have a right child node
	{
		node *temp; // create a temp pointer to hold current node's right child
		temp = curr->right; // set temp pointer to current node's right child
		
		while (temp->left != nullptr) // while the current node's right child still has a left child to move to
		{
			temp = temp->left; // set temp pointer to current node's left child, keep moving pointer as far left as possible
		}
		
		curr = temp; // reset curr to equal new temp position
	}
	else // else position does NOT have a right child (ie: right child is nullptr)
	{
		node *par = curr->parent; // create new node to hold position of current node's parent
		while ((par != nullptr) && (par->right == curr)) // while the current node's parent is not equal to null and has a right node that equals the current node
		{
			curr = par; // make iterator refer to parent node as next element, move through parent nodes until one of those upward moves takes us farther right
			par = par->parent; // resent par variable to hold the new parent node of the new current node
		}
		
		curr = curr->parent; // if current node's parent does not equal that parent node's right node then just set the curr pointer equal to its parent
	}
	
	return *this; // return implicit object
}

pic10b::Tree::iterator pic10b::Tree::iterator::operator++(int unused) // postfix operator to increment
{
	iterator copy (*this); // create copy of iterator
	this->operator++(); // increment implicit object
	return copy; // return the copy
}

pic10b::Tree::iterator& pic10b::Tree::iterator::operator--() // prefix operator to decrement
{
	if (curr == nullptr) // if current position is nullptr : if current position is first in Tree, you cannont decrement before first element
	{
		curr = container->root; // we are decrementing from end() so we get the root of the tree and set it equal to curr
		
		if (curr == nullptr) // if you are trying to decrement from an empty tree
		{
			throw std::logic_error("Invalid address"); // throw logic error because of invlaid address
		}
		
		while (curr->right != nullptr) // while the current node you are at has a right child not equal to nullptr : try to move as far right as possible in tree
		{
			curr = curr->right; // keep moving right to the largest value in the tree, which will be the last node in order
		}
	}
	else if (curr->left != nullptr) // if position has a left child
	{
		node *temp; // create a temp pointer to hold current node's left child
		temp = curr->left; // set temp pointer to current node's left child
		
		while (temp->right != nullptr) // while the current node still has a right child to move to
		{
			temp = temp->right; // set temp pointer to the node's right child, keep moving pointer as far right as possible
		}
		
		curr = temp; // resent curr node to temp
	}
	else // else position does NOT have a left child (Ie: left child is nullptr)
	{
		node *par = curr->parent; // create new node to hold position of current node's parent
		while ((par != nullptr)&& (par->left == curr)) // while the current node's parent is not equal to null and has a left node that equals the current node
		{
			curr = par; // make iterator refer to parent node as next element, move through parent nodes until one of those upward moves takes us farther left
			par = par->parent; // resent par variable to hold the new parent node of the new current node
		}
		
		curr = curr->parent; // set curr pointer to its parent node, which is less than itself, if current node's parent does not equal that parent node's left node then just set the curr pointer equal to its parent
	}
	return *this; // return implicit object
}

pic10b::Tree::iterator pic10b::Tree::iterator::operator--(int unused) // postfix operator to decrement
{
	iterator copy (*this); // create copy of iterator
	this->operator--(); // decrement implicit object
	return copy; // return the copy
}

const double& pic10b::Tree::iterator::operator*() const // dereferencing operator
{
	return curr->val; // return the current node's value (ie: double it holds) also return a reference to const so that user cannont change the actual value of original int object
}

const double* pic10b::Tree::iterator::operator->() const // arrow operator, allows access to member functions
{
	return &(curr->val); // need to return a pointer to the object in the Tree class, so just return the address to the current node's value
}

bool pic10b::operator== (const Tree::iterator& left, const Tree::iterator& right) // comparison operator for "==" for iterators
{
	return ((left.curr == right.curr) && (left.container == right.container)); // return true if both left and right curr node pointer and container are equal to each other, false otherwise
}

bool pic10b::operator!= (const Tree::iterator& left, const Tree::iterator& right) // comparison operator for "!=" for iterators
{
	return !(left == right); // return if left iterator is not equal to right iterator, use already defined operator functions (ie: operator==)
}
