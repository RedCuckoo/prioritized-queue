#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
//TODO: overload stream operator<< for all the types
template <class T>
class AVLTree {
	struct Node {
		T value;
		unsigned int height;
		Node* left = nullptr, * right = nullptr;
		Node() = default;
		Node(const T& val, unsigned int h = 0, Node* l = nullptr, Node* r = nullptr) : value(val), height(h), left(l), right(r) {	}
		Node& operator= (const Node& to_assign) {
			value = to_assign.value;
			height = to_assign.height;
			left = to_assign.left;
			right = to_assign.right;
		}
		void out() {
			std::cout << value << " : ";
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
	};
	Node* head;
public:
	AVLTree() : head(nullptr) {		}

	void push_back(const T& value) {
		if (!head) {
			head = new Node(value);
		}
		else {
			unsigned int height_counter = 0;
			Node* temp = head;
			while (true) {
				if (value < temp->value) {
					if (!temp->left) {
						temp->left = new Node(value, height_counter);
						return;
					}
					temp = temp->left;
				}
				else if (value == temp->value) {
					return;
				}
				else {
					if (!temp->right) {
						temp->right = new Node(value, height_counter);
						return;
					}
					temp = temp->right;
				}
				++height_counter;
			}
		}
	}

	void out(Node* start = nullptr)  {
		if (!start)
			start = head;
		start->out();
		
		if (start->left)
			out(start->left);
		if (start->right)
			out(start->right);
	}


};


#endif // !AVLTREE_H
