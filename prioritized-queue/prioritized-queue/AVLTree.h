#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <stack>
//TODO: overload stream operator<< for all the types
template <class T>
class AVLTree {
	struct Node {
		T value;
		unsigned int height;
		Node* left = nullptr, * right = nullptr;
		Node() = default;
		Node(const T& val, unsigned int h = 1, Node* l = nullptr, Node* r = nullptr) : value(val), height(h), left(l), right(r) {	}
		Node& operator= (const Node& to_assign) {
			value = to_assign.value;
			height = to_assign.height;
			left = to_assign.left;
			right = to_assign.right;
			return *this;
		}
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
/*
		void swap(Node& to_swap) {
			Node temp = to_swap;
			to_swap = value;
			value = temp.value;
			to_swap.left = left;
			left = to_swap.left;
			to_swap.right = right;
			right = to_swap.right;
		}

		void leftRotation() {
			Node temp_this = this;
			value = right->value;
			right = right->right;
			*left = *temp_this;
			*temp_this->right = *right;
		}

		void rightRotation() {
			Node* temp_this;
			*temp_this = *this;
			value = left->value;
			left = left->left;
			right = temp_this;
			temp_this->left = left;
		}*/
	};
	Node* head;

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
		//ans is stored in h1
		h1 -= h2;
		return (h1 < -1 || h1 > 1) ? false : true;

	}

	//only change with return value
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
public:
	AVLTree() : head(nullptr) {		}

	void push(const T& value) {
		if (!head) {
			head = new Node(value);
		}
		else {
			//unsigned int height_counter = 2;
			Node* temp = head;
			//way to the 
			std::stack <Node*> way;
			while (true) {
				//standart BinarySearchTree insertion
				//TODO: refactor
				way.push(temp);
				if (value < temp->value) {
					if (!temp->left) {
						temp->left = new Node(value);
						temp->height = 1 + maxHeight(temp->left, temp->right);
							//new

						temp = temp->left;
						break;
					}
					//next comment
					if (maxHeight(temp->left, temp->right) == temp->left->height)
						++(temp->height);
					//temp->height = 2 + maxHeight(temp->left, temp->right);
					temp = temp->left;
				}
				else if (value == temp->value) {
					//TODO: throw exception because of the same value
					break;
				}
				else {
					if (!temp->right) {
						temp->right = new Node(value);
						temp->height = 1 + maxHeight(temp->left, temp->right);
						temp = temp->right;
						break;
					}
					//temp->height = 2 + maxHeight(temp->left, temp->right);
					if (maxHeight(temp->left, temp->right) == temp->right->height)
						++(temp->height);
					temp = temp->right;
				}
				//++height_counter;
			}
			//recalculate heights
			//std::stack<Node*> way_temp;
			//while (!way_temp.empty()) {
			//	way_temp.top()->height = 1 + maxHeight(way_temp.top()->left, way_temp.top()->right);
			//	way_temp.pop();
			//}



			Node* newNode = temp;
			Node* child = way.top();
			Node* grandchild = newNode;
			way.pop();
			//check whether there are unbalanced nodes
			while (!way.empty()) {
				if (!balanced(way.top())) {
					if (child->left == grandchild) {
						//left-left case
						if (way.top()->left == child) {
							//rightrotation(way.top())
							way.top() = rightRotation(way.top());
						}
						//right-left
						else {
							//rightrotationg (child)
							child = rightRotation(child);
							//leftrotation (way.top())
							way.top() = leftRotation(way.top());
						}
					}
					else {
						//left-right case
						if (way.top()->left == child) {
							//leftrotation(child)
							child = leftRotation(child);
							//rightrotation(way.top())
							way.top() = rightRotation(way.top());
						}
						//right-right case
						else {
							//leftrotation (way.top())
							way.top() = leftRotation(way.top());
						//	out();
						}
					}
				}
				way.pop();
			}


			//while (!way.empty()) {
			//	way.top()->out();
			//	std::cout << " " << balanced(way.top());
			//	std::cout <<  std::endl;
			//	way.pop();
			//}
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
