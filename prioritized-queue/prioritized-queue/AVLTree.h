/*!
	\file
	\brief Header file containing class List and class List_iterator

	This file contains template definition and implementation of such data structure as a binary search AVL tree
*/

#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <stack>
#include <vector>

/*!
	\brief Binary search AVL Tree
	\details A custom implementation of STL library std::map with custom random access iterator
*/
template <class value_type>
class AVLTree {
	/*!
	\brief A node of binary search AVL tree
	\details This class stores pointers to the left and right node, if there is none, then nullptr is stored instead
	The value stored depends on the type given to the class AVLTree.
	*/
	struct Node {
		value_type value;
		unsigned int height;
		Node* left = nullptr, * right = nullptr;
		/*!
		\brief Constructor
		\details Constructor which creates a node from the provided parameters.
		\param[in] val The value that node will store
		\param[in] h The height of the node in the tree
		\param[in] l Pointer to the left child (for the beginning of the list, nullptr is passed)
		\param[in] r Pointer to the riht child (for the end of the list, pointer to an empty node is passed)
		*/
		Node(const value_type& val, unsigned int h = 1, Node* l = nullptr, Node* r = nullptr) : value(val), height(h), left(l), right(r) {	}

		/*!
		\brief Output stored information
		\details Print stored value of the node to the console, using <iostream> library
		This function outputs it in the formatted way
		\code
		//For example
		2 4(2) 4 6 7 8
		//value (height) left_child_value right_child_value
		//The value of the node is the pair (2,4), its' height is 2, left child is (4,6), right child is (7,8)
		\endcode
		*/
		void out() {
			std::cout << value << "(" << height << ") : ";
			if (left)
				std::cout << left->value;
			else
				std::cout << "--";
			if (right)
				std::cout << " " << right->value;
			else
				std::cout << "--";
			std::cout << std::endl;
		}

		/*!
		\brief Output stored information
		\details Print stored value of the node to the console, using <iostream> library, with overloaded stream operator<< of the value_type
		*/
		//void out() {
		//	std::cout << value;
		//}
	};
	Node* head;
	unsigned int tree_size = 0;

	/*!
	\brief Maximum height out of two nodes
	\details Returns the bigger height, dependes on the two nodes passed
	\param [in] firstNode Pointer to the first element to get height
	\param [in] secondNode Pointer to the second element to get height
	\return The maximum height
	*/
	unsigned int maxHeight(Node* firstNode, Node* secondNode) {
		unsigned int h1 = 0, h2 = 0;
		if (firstNode)
			h1 = firstNode->height;	
		if (secondNode)
			h2 = secondNode->height;
		return (h1 > h2) ? h1 : h2;
	}

	/*!
	\brief Checks if element is balanced
	\details The element is balanced if the difference of its' left and right child is not bigger then 1 (by definition of the AVL tree)
	\param to_check A pointer to the Node to be checked
	\return True if the Node is balanced and false value otherwise
	*/
	bool balanced(Node* to_check) {
		int h1 = 0, h2 = 0;
		if (to_check->left)
			h1 = to_check->left->height;
		if (to_check->right)
			h2 = to_check->right->height;

		h1 -= h2;
		return (h1 < -1 || h1 > 1) ? false : true;
	}

	/*!
	\brief Left rotation of the Node
	\details In order to balance tree, operation of left rotation and right rotation have to be implemented.
	\param [in] to_rotate A pointer to the Node to be rotated (parent, which has the following properties)
	This function receives a Node, which definetily has a right child and a right-left grandchild. Then it performs rotations as following.
	\code
	//		to_rotate										  child
	//		/		\										/		\
	//	   T1		child	      leftRotation			to_rotate	T2
	//				/	\			======>				/		\
	//		grandchild	T2							   T1	grandchild
	//		/		\										/		\
	//		T3		T4										T3		T4
	\endcode
	\return In order for this function to work, you have to assign returned value to the node you have passed as a parameter
	*/
	Node* leftRotation(Node* to_rotate) {
		Node* child = to_rotate->right;
		Node* grandchild = child->left;

		bool headCheck = false;
		if (to_rotate == head)
			headCheck = true;

		child->left = to_rotate;
		to_rotate->right = grandchild;
		to_rotate->height = 1 + maxHeight(to_rotate->left, to_rotate->right);
		child->height = 1 + maxHeight(child->left, child->right);

		if (headCheck)
			head = child;

		return child;
	}	
	
	/*!
	\brief Right rotation of the Node
	\details In order to balance tree, operation of left rotation and right rotation have to be implemented.
	\param [in] to_rotate A pointer to the Node to be rotated (parent, which has the following properties)
	This function receives a Node, which definetily has a left child and a left-right grandchild. Then it performs rotations as following.
	\code
	//		to_rotate										  child
	//		/		\										/		\
	//	 child		 T1	      rightRotation				  T2      to_rotate
	//	 /		\				======>							  /		 \
	//	T2	grandchild										grandchild    T1
	//		/		\										/		\
	//		T3		T4										T3		T4
	\endcode
	\return In order for this function to work, you have to assign returned value to the node you have passed as a parameter
	*/
	Node* rightRotation(Node* to_rotate) {
		Node* child = to_rotate->left;
		Node* grandchild = child->right;

		bool headCheck = false;
		if (to_rotate == head)
			headCheck = true;

		child->right = to_rotate;
		to_rotate->left = grandchild;
		to_rotate->height = 1 + maxHeight(to_rotate->left, to_rotate->right);
		child->height = 1 + maxHeight(child->left, child->right);

		if (headCheck)
			head = child;

		return child;
	}

	/*!
	\brief Perform a standart binary search tree insertion
	\details Using stack, in order to achieve improvement in memory usage, the function perform a BST insertion, without changing height of the nodes, as there is a speacial method for that.
	\param [out] way The working stack, which will be changed in the function. When finished, it will store the way to the inserted Node. Later it can be used to balancing.
	\param [in] value Non changeable reference to the value, which will be inserted in the tree.
	*/
	void BST_insert(std::stack < Node*>& way, const value_type& value) {
		Node* temp = head;
		while (true) {
			way.push(temp);
			if (value <= temp->value) {
				if (!temp->left) {
					temp->left = new Node(value);
					temp = temp->left;
					break;
				}
				temp = temp->left;
			}
			else {
				if (!temp->right) {
					temp->right = new Node(value);
					temp = temp->right;
					break;
				}
				temp = temp->right;
			}
		}
		way.push(temp);
	}

	/*!
	\brief Method which balance the tree
	\details This method can used both in balancing tree after insertion and deletion. The way it will function depends on the parameter.
	\param [out] way Reference to the working stack. On the input it has to store the way to inserted function. 
	Such inconvinience is used in order to save up on the memory and traversal tree iteratively rather than recursively
	Also, the top element of the way has to have the height equal to 1 (if insertion) or be equal nullptr itself for the deletion.
	The stack has to have more than two elements. It is logical, as there is nothing to balance if two elements with heights 2 and 1 relatively are given.
	\code
	//For insertion, the following stack is valid:
	//
	{3 (3), 4 (2), 1 (1)}
	//Where the numbers in brackets are the heights of the node
	//
	//For deletion, the following stack is valid:
	//
	{4 (2), 5 (1), nullptr}
	//
	//As an example, the following stacks are not valid
	//
	{5 (2), 4 (3), 9 (2)}
	{5 (2), 4 (3)}
	{5 (2), nullptr}
	//
	//And so on
	\endcode
	\param [in] deletion A bool value which indicates whether the deletion occurs or not. 
	The difference between these balancing is that for insertion, it doesn't matter which height does the node has.
	For deletion you have to take the child with the highest height in the parent, and grandchild with the highest height also.
	*/
	void to_balance(std::stack<Node*>& way, bool deletion = false) {
		if (((deletion && way.top() == nullptr) || (!deletion && way.top()->height ==  1)) && way.size() > 2) {
			Node* grandchild, *child, * parChiGra[3];
			grandchild = way.top();
			way.pop();
			child = way.top();
			parChiGra[0] = child;
			parChiGra[1] = grandchild;
			way.pop();

			bool firstTimeDeletion = true;

			while (!way.empty()) {
				if (!balanced(way.top())) {
					Node* parent = way.top();
					if (deletion && firstTimeDeletion) {
						child = (parent->right->height > parent->left->height) ? parent->right : parent->left;
						grandchild = (child->right->height > child->left->height) ? child->right : child->left;
						parChiGra[0] = child;
						parChiGra[1] = grandchild;
						firstTimeDeletion = false;
					}

					parChiGra[2] = parChiGra[1];
					parChiGra[1] = parChiGra[0];
					parChiGra[0] = parent;
					child = parChiGra[1];
					grandchild = parChiGra[2];
					way.pop();

					//cases
					bool leftWayChild = true;
					if (!way.empty()) {
						leftWayChild = (way.top()->left == parent) ? true : false;
					}

					if (parent->left == child) {
						if (child->left == grandchild) {
							//left-left case
							parent = rightRotation(parent);
						}
						else {
							//left-right case
							child = leftRotation(child);
							parent->left = child;
							parent = rightRotation(parent);
						}
					}
					else {
						if (child->left == grandchild) {
							//right-left case
							child = rightRotation(child);
							parent->right = child;
							parent = leftRotation(parent);
						}
						else {
							//right-right case
							parent = leftRotation(parent);
						}
					}

					if (!way.empty()) {
						if (leftWayChild) {
							way.top()->left = parent;
						}
						else {
							way.top()->right = parent;
						}
					}
				}
				else {
					parChiGra[2] = parChiGra[1];
					parChiGra[1] = parChiGra[0];
					parChiGra[0] = way.top();
					child = parChiGra[1];
					grandchild = parChiGra[2];
					way.pop();
				}
			}
		}
	}

	/*!
	\brief Friended class AVLTree_iterator
	\details Gives access to private fields of class AVLTree_iterator
	*/
	template<class U>
	friend class AVLTree_iterator;

public:
	/*!
	\brief Constructor
	\details Constructor which creates an empty tree, so you can declare a tree, but not define
	*/
	AVLTree() : head(nullptr) {		}

	/*!
	\brief Add elements
	\details Add elements to the tree and balance the tree
	\param[in] value Value which has to be added to the tree
	*/
	void push(value_type value) {
		++tree_size;
		if (!head) {
			head = new Node(value);
		}
		else {
			//way to the inserted node
			std::stack <Node*> way;
			BST_insert(way, value);
			updateHeights();
			to_balance(way);
		}
	}

	/*!
	\brief Get the size of the tree
	\details To get the amount of elements of the tree
	\return Size of the tree
	*/
	unsigned int size() {
		return tree_size;
	}

	//TODO: check if we need this function
	/*!
	\brief Output stored information
	\details Print stored value of the tree to the console, using <iostream> library, with Node::out() formatted value
	*/
	void out (Node* start = nullptr)  {
		std::stack<Node*> temp_stack;
		Node* temp_ptr = head;

		while (!temp_stack.empty() || temp_ptr) {
			if (temp_ptr) {
				if (temp_ptr->height == 1) {
					temp_ptr->out();
					temp_ptr = nullptr;
				}
				else {
					temp_stack.push(temp_ptr);
					temp_ptr = temp_ptr->left;
				}
			}
			else {
				temp_ptr = temp_stack.top();
				temp_stack.pop();
				temp_ptr->out();
				temp_ptr = temp_ptr->right;
			}

		}
		
	}

	/*!
	\brief Checks emptiness of the tree
	\details This method checks whether or not current tree is empty
	\return True value if the tree is empty and false value otherwise
	*/
	bool empty() {
		return (!head) ? true : false;
	}

	//TODO: put in order function in all containers
	/*!
	\brief Get iterator on the beginning
	\details Method that returns the iterator to the beginning of the list
	\return Iterator to the beginning of the list
	*/
	AVLTree_iterator<value_type> begin() {
		return *AVLTree_iterator<value_type>(this).setFirst();
	}	
	
	/*!
	\brief Get iterator on the end
	\details Method that returns the iterator to the end of the list
	\return Iterator to the end of the list
	*/
	AVLTree_iterator<value_type> end() {
		return *AVLTree_iterator<value_type>(this).setLast();
	}

	/*!
	\brief The method to update height in the whole tree
	\details It uses postorder traversal of the tree implemented iteratively, to allow wiser memory usage.
	*/
	void updateHeights() {
		if (head) {
			std::stack<Node*> st;
			Node* temp_ptr = head;
			do {
				while (temp_ptr) {
					if (temp_ptr->right) {
						st.push(temp_ptr->right);
					}
					st.push(temp_ptr);
					temp_ptr = temp_ptr->left;
				}
				temp_ptr = st.top();
				st.pop();
				if (temp_ptr->right && !st.empty() && temp_ptr->right == st.top()) {
					st.pop();
					st.push(temp_ptr);
					temp_ptr = temp_ptr->right;
				}
				else {
					temp_ptr->height = 1 + maxHeight(temp_ptr->left, temp_ptr->right);
					temp_ptr = nullptr;
				}
			} while (!st.empty());
		}
	}

	/*!
	\brief Get the minimal value in the tree
	\details The method allows to get the minimal value in the tree, starting from the given Node
	\param [out] way Reference to the parameter which doesn't have any limitations on the input, but will be pushed with the way to the Node with minimal value
	\param [in] to_find A pointer to the Node where we start looking for a minimal value
	\return A pointer to the Node with the minimal value
	*/
	Node* minNode(std::stack<Node*>& way, Node* to_find) {
		while (to_find->left) {
			way.push(to_find);
			to_find = to_find->left;
		}
		return to_find;
	}

	/*!
	\brief Erase element
	\details Erases element on the iterated position in the tree
	\param[in] it Iterator to the position where the element has to be erased
	The value is erased, making the iterator invalid.
	\code
	//If we are given the following sequence with the iterator to the second element
	//
	//1 2 3 4 5 6
	//  ^
	//
	//If we call the function erase(second_position_iterator) our sequence will have the following look:
	//
	//1 3 4 5 6
	//  ^
	//
	//Where "^" is the iterator returned as a return value
	//
	\endcode
	\return A valid iterator to the same position that passed parameter was pointing to
	*/
	AVLTree_iterator<value_type> erase(AVLTree_iterator<value_type> it) {
		if (!head || !it.node) {
			//empty tree
			return AVLTree_iterator<value_type>(this);
		}
		else {
			Node* temp = head;
			std::stack<Node*> way;
			std::stack<Node*> temp_way;
			while (true) {
				way.push(temp);
				AVLTree_iterator<value_type> temp_it (this, temp);
				if (temp_it == it) {
					break;
				}
				else if (temp_it > it) {
					if (temp->left)
						temp = temp->left;
					else
						return AVLTree_iterator<value_type>(this);
				}
				else {
					if (temp->right)
						temp = temp->right;
					else
						return AVLTree_iterator<value_type>(this);
				}
			}
			bool twoChilder = true;

			if (!temp->left || !temp->right) {
				twoChilder = false;
				//one or no child
				//t_ptr is the node of the left or right child
				Node* t_ptr = (temp->left) ? temp->left : temp->right;

				//TODO: check if comparison has to be checked via Node
				if (!t_ptr) {
					way.pop();
					if (way.top()->left == temp) {
						way.top()->left = nullptr;
						
					}
					else {
						way.top()->right = nullptr;
					}
					t_ptr = temp;
					
				}
				else {
					//one child
					temp->value = t_ptr->value;
					if (temp->left == t_ptr)
						temp->left = nullptr;
					else {
						temp->right = nullptr;
					}
					delete t_ptr;
				}
				way.push(nullptr);
			}
			else {
				//two children
				//t_ptr is the node to be inserted in the old node
				Node* t_ptr = minNode(way, temp->right);
				temp->value = t_ptr->value;
				if (way.top()->left == t_ptr) {
					way.top()->left = nullptr;
				}
				else {
					way.top()->right = nullptr;
				}
				way.push(nullptr);
				delete t_ptr;

			}

			updateHeights();
			to_balance(way,1);
			--tree_size;
			if (temp)
				delete temp;
			return AVLTree_iterator<value_type>(this, (++it).node);
		}
	}
};

/*!
\brief iterator
\details A custom written class which implements iterators for the class AVLTree.
It has the same properties as STL library std::random_access_iterator.
*/
template <class value_type>
class AVLTree_iterator {
	/*!
	\brief Friended class AVLTree
	\details Gives access to private fields of class AVLTree
	*/
	template <class U>
	friend class AVLTree;

	AVLTree<value_type>* tree;
	typename AVLTree<value_type>::Node* node;

	//allows to access element with complexity of O(1)
	unsigned int coord;
	
	std::vector<typename AVLTree<value_type>::Node*> listedTree;

	/*!
	\brief Convert iterator to the end()
	\details This method converts current iterator to the iterator on the end of the list, in this case on the nullptr.
	\return Returns a pointer to current object but with changed fields
	*/
	AVLTree_iterator* setLast() {
		node = listedTree[0];
		coord = 0;
		return this;
	}	
	
	/*!
	\brief Convert iterator to the begin()
	\details This method converts current iterator to the iterator on the beginning of the list.
	\return Returns a pointer to current object but with changed fields
	*/
	AVLTree_iterator* setFirst() {
		coord = listedTree.size() - 1;
		node = listedTree[coord];
		return this;
	}

	/*!
	\brief Fill listedTree field
	\details Part of constructor which converts tree to the list, so you can navigate easily, helps to implement overloading of the operators.
	*/
	void treeToArray() {
		std::stack<typename AVLTree<value_type>::Node*> temp_stack;
		typename AVLTree<value_type>::Node* temp_ptr = tree->head;
		listedTree.push_back(nullptr);
		while (!temp_stack.empty() || temp_ptr) {
			if (temp_ptr) {
				if (temp_ptr->height == 1) {
					listedTree.push_back(temp_ptr);
					temp_ptr = nullptr;
				}
				else {
					temp_stack.push(temp_ptr);
					temp_ptr = temp_ptr->left;
				}
			}
			else {
				temp_ptr = temp_stack.top();
				temp_stack.pop();
				listedTree.push_back(temp_ptr);
				temp_ptr = temp_ptr->right;
			}
		}
	}

	/*!
	\brief Fill coord field
	\details Part of constructor which gets the coordinate of the node in the tree converted to the list, helps to implement overloading of the operators
	*/
	void getCoord() {
		for (unsigned int i = 0; i < listedTree.size(); i++) {
			if (node == listedTree[i]) {
				coord = i;
				break;
			}
		}
	}
	
	/*!
	\brief Update information that iterator stores
	\details The method call two functions, one to refresh tree written as the list, another to get the coordinate of the stored node in the updated list.
	*/
	void updateIterator() {
		treeToArray();
		getCoord();
	}
public:
	/*!
	\brief Constructor
	\details A constructor that creates iterator from the provided parameters
	\param[in] tree_ptr Pointer to the list, where current iterator belongs to
	\param[in] node_ptr Pointer to the node, where current iterator has to point. Assigned as nullptr automatically
	*/
	AVLTree_iterator(AVLTree<value_type>* tree_ptr, typename AVLTree<value_type>::Node* node_ptr = nullptr){ 
		tree = tree_ptr;
		node = node_ptr;
		updateIterator();
	}

	/*!
	\brief Copy constructor
	\details Overloaded copy constructor to make sure that it works as supposed to
	*/
	AVLTree_iterator(const AVLTree_iterator& to_copy) {
		tree = to_copy.tree;
		node = to_copy.node;
		coord = to_copy.coord;
		listedTree = to_copy.listedTree;
	}
	
	/*!
	\brief Overloaded left increment operator
	\return A reference to the iterator, pointing to the next element
	*/
	AVLTree_iterator& operator++() {
		updateIterator();
		node = listedTree[--coord];
		return *this;
	}

	/*!
	\brief Overloaded right increment operator
	\return An iterator, pointing to the next element
	*/
	AVLTree_iterator operator++(int) {
		updateIterator();
		AVLTree_iterator result = *this;
		node = listedTree[--coord];
		return result;
	}

	/*!
	\brief Overloaded left decrement operator
	\return A reference to the iterator, pointing to the previous element
	*/
	AVLTree_iterator& operator--() {
		updateIterator();
		node = listedTree[++coord];
		return *this;
	}

	/*!
	\brief Overloaded right decrement operator
	\return A reference to the iterator, pointing to the previous
	*/
	AVLTree_iterator operator--(int) {
		updateIterator();
		AVLTree_iterator result = *this;
		node = listedTree[++coord];
		return result;
	}

	/*!
	\brief Overloaded summing operator, shifts iterator to the left or right relatively of the parameter
	\param val If this parameter is >0 then it iterator shifts to the right, else - to the left
	\return A reference to the iterator, pointing to the next or previous element
	*/
	AVLTree_iterator& operator+(int val) {
		updateIterator();
		if (val > 0) {
			coord -= val;
			node = listedTree[coord];
		}
		else if (val == 0) {

		}
		else {
			coord += val;
			node = listedTree[coord];
		}
		return *this;
	}

	/*!
	\brief Overloaded suntracting operator, shifts iterator to the left or right relatively of the parameter
	\param val If this parameter is >0 then it iterator shifts to the left, else - to the right
	\return A reference to the iterator, pointing to the next or previous element
	*/
	AVLTree_iterator& operator-(int val) {
		updateIterator();
		if (val > 0) {
			coord += val;
			node = listedTree[coord];
		}
		else if (val == 0) {

		}
		else {
			coord -= val;
			node = listedTree[coord];
		}
		return *this;
	}

	/*!
	\brief Overloaded equality operator
	\param to_compare Const reference to the AVLTree_iterator that has to be compared with the AVLTree_Iterator passed as an lvalue
	\return True value if they are equal and false value otherwise
	*/
	bool operator== (const AVLTree_iterator<value_type>& to_compare) {
		return (coord == to_compare.coord) ? true : false;
	}

	/*!
	\brief Overloaded inequality operator
	\param to_compare Const reference to the AVLTree_iterator that has to be compared with the AVLTree_Iterator passed as an lvalue
	\return True value if they are unequal and false value otherwise
	*/
	bool operator!= (const AVLTree_iterator<value_type>& to_compare) {
		return (coord != to_compare.coord) ? true : false;
	}

	/*!
	\brief Overloaded bigger than operator
	\param to_compare Const reference to the AVLTree_iterator that has to be compared with the AVLTree_Iterator passed as an lvalue
	\return True value if current iterator's value is bigger than passed and false value otherwise
	*/
	bool operator> (const AVLTree_iterator<value_type>& to_compare) {
		return (coord > to_compare.coord) ? true : false;
	}

	/*!
	\brief Overloaded smaller than operator
	\param to_compare Const reference to the AVLTree_iterator that has to be compared with the AVLTree_Iterator passed as an lvalue
	\return True value if current iterator's value is smaller than passed and false value otherwise
	*/
	bool operator< (const AVLTree_iterator<value_type>& to_compare) {
		return (coord < to_compare.coord) ? true : false;
	}

	/*!
	\brief Overloaded dereference operator
	\return A value (of the value_type) that is stored in the node of the list that current iterator is pointing to
	*/
	value_type& operator*()const {
		return node->value;
	}

	//void out() {
	//	treeToArray();
	//	for (size_t i = 0; i < listedTree.size(); i++)
	//	{
	//		listedTree[i]->out();
	//	}
	//}
};

#endif // !AVLTREE_H
