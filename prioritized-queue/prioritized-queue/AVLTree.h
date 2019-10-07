#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <stack>
#include <vector>
//TODO: overload stream operator<< for all the types
template <class value_type>
class AVLTree {
	struct Node {
		value_type value;
		unsigned int height;
		Node* left = nullptr, * right = nullptr;
		Node() = default;
		Node(const value_type& val, unsigned int h = 1, Node* l = nullptr, Node* r = nullptr) : value(val), height(h), left(l), right(r) {	}

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
		
		//void out() {
		//	std::cout << value;
		//}
	};
	Node* head;
	unsigned int tree_size = 0;

	unsigned int maxHeight(Node* firstNode, Node* secondNode) {
		unsigned int h1 = 0, h2 = 0;
		if (firstNode)
			h1 = firstNode->height;	
		if (secondNode)
			h2 = secondNode->height;
		return (h1 > h2) ? h1 : h2;
	}


	bool balanced(Node* to_check) {
		int h1 = 0, h2 = 0;
		if (to_check->left)
			h1 = to_check->left->height;
		if (to_check->right)
			h2 = to_check->right->height;

		//UPDATING HEGIHT HERE
		to_check->height = 1 + maxHeight(to_check->left, to_check->right);

		//ans is stored in h1
		h1 -= h2;
		return (h1 < -1 || h1 > 1) ? false : true;

	}

	//changes to_rotate via return value only
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

	Node* BST_insert(std::stack < Node*>& way, const value_type& value) {
		Node* temp = head;
		while (true) {
			//standart BinarySearchTree insertion
			way.push(temp);
			if (value <= temp->value) {
				if (!temp->left) {
					temp->left = new Node(value);
					temp->height = 1 + maxHeight(temp->left, temp->right);
					temp = temp->left;
					break;
				}

				//if (maxHeight(temp->left, temp->right) == temp->left->height)
				//	++(temp->height);

				temp = temp->left;
			}
			//else if (value == temp->value) {
			//	//TODO: throw exception because of the same value
			//	break;
			//}
			else {
				if (!temp->right) {
					temp->right = new Node(value);
					temp->height = 1 + maxHeight(temp->left, temp->right);
					temp = temp->right;
					break;
				}

				//if (maxHeight(temp->left, temp->right) == temp->right->height)
				//	++(temp->height);

				temp = temp->right;
			}
		}
		return temp;
	}

	void to_balance(std::stack<Node*>& way, const value_type& value) {
		Node* grandchild = BST_insert(way, value);
		Node* child = way.top();
		Node* parChiGra[3];
		parChiGra[0] = child;
		parChiGra[1] = grandchild;
		//parChiGra[0] = nullptr;
		//Node* parent = nullptr;
		way.pop();
		while (!way.empty()) {
			if (!balanced(way.top())) {
				//grandchild = child;
				//child = parent;

				Node* parent = way.top();
				parChiGra[2] = parChiGra[1];
				parChiGra[1] = parChiGra[0];
				parChiGra[0] = parent;
				child = parChiGra[1];
				grandchild = parChiGra[2];
				way.pop();




				//cases
				//way.top() is a previous element before parent
				//so no need to pop way
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

	template<class U>
	friend class AVLTree_iterator;

public:
	AVLTree() : head(nullptr) {		}

	void push(const value_type& value) {
		++tree_size;
		if (!head) {
			head = new Node(value);
		}
		else {
			//way to the inserted node
			std::stack <Node*> way;
			to_balance(way, value);
		}
	}

	unsigned int size() {
		return tree_size;
	}

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

	//void out(Node* start = nullptr) {
	//	if (!start)
	//		start = head;
	//	start->out();

	//	if (start->left)
	//		out(start->left);
	//	if (start->right)
	//		out(start->right);
	//}


	bool empty() {
		return (!head) ? true : false;
	}

	AVLTree_iterator<value_type> begin() {
		return *AVLTree_iterator<value_type>(this).setFirst();
	}	
	
	AVLTree_iterator<value_type> end() {
		return *AVLTree_iterator<value_type>(this).setLast();
	}
};

template <class value_type>
class AVLTree_iterator {
	template <class U>
	friend class AVLTree;

	AVLTree<value_type>* tree;
	typename AVLTree<value_type>::Node* node;
	std::vector<typename AVLTree<value_type>::Node*> listedTree;

	AVLTree_iterator* setFirst() {
		node = listedTree[0];
		return this;
	}	
	
	AVLTree_iterator* setLast() {
		node = listedTree[listedTree.size()-1];
		return this;
	}

	void treeToArray() {
		std::stack<typename AVLTree<value_type>::Node*> temp_stack;
		typename AVLTree<value_type>::Node* temp_ptr = tree->head;

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
public:
	AVLTree_iterator() : tree(nullptr), node(nullptr) {		}
	//AVLTree_iterator(AVLTree<value_type>* tree_ptr, typename AVLTree<value_type>::Node* node_ptr = nullptr) : tree(tree_ptr), node(node_ptr), treeToArray() {	}
	//AVLTree_iterator(AVLTree<value_type>* tree_ptr) {
	//	tree = tree_ptr;
	//	treeToArray();
	//}
	AVLTree_iterator(AVLTree<value_type>* tree_ptr, typename AVLTree<value_type>::Node* node_ptr = nullptr){ 
		tree = tree_ptr;
		node = node_ptr;
		treeToArray();
	}
	AVLTree_iterator(const AVLTree_iterator& to_copy) {
		tree = to_copy.tree;
		node = to_copy.node;
	}
	AVLTree_iterator& operator++() {
		node = node->next;
	}

	value_type& operator*()const {
		return node->value;
	}

	void out() {
		for (size_t i = 0; i < listedTree.size(); i++)
		{
			listedTree[i]->out();
		}
	}
};

#endif // !AVLTREE_H
