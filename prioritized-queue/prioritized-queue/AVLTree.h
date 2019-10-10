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

	void BST_insert(std::stack < Node*>& way, const value_type& value) {
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
		//!!!!
		way.push(temp);
		//way.push(nullptr);
		//return temp;
	}

	void to_balance(std::stack<Node*>& way, bool deletion = false) {
		//way HAS to have top node of the height 1
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
			BST_insert(way, value);
			updateHeights();
			to_balance(way);
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

	bool empty() {
		return (!head) ? true : false;
	}

	AVLTree_iterator<value_type> begin() {
		return *AVLTree_iterator<value_type>(this).setFirst();
	}	
	
	AVLTree_iterator<value_type> end() {
		return *AVLTree_iterator<value_type>(this).setLast();
	}

	void updateHeights() {
		std::stack<Node*> st;
		//std::vector<Node*> to_upd;
		Node* temp_ptr = head;
		if (head) {
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
					//to_upd.push_back(temp_ptr);
					temp_ptr->height = 1 + maxHeight(temp_ptr->left, temp_ptr->right);
					temp_ptr = nullptr;
				}


			} while (!st.empty());
			

	
		}
		else {
			return;
		}
	}

	Node* minNode(std::stack<Node*>& way, Node* to_find) {
		while (to_find->left) {
			way.push(to_find);
			to_find = to_find->left;
		}
		return to_find;
	}

	AVLTree_iterator<value_type> erase(AVLTree_iterator<value_type>& it) {
		if (!head || !it.node) {
			//empty tree
			return AVLTree_iterator<value_type>();
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
						return nullptr;
				}
				else {
					if (temp->right)
						temp = temp->right;
					else
						return nullptr;
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

			if (!temp)
				return AVLTree_iterator<value_type>();
			
			updateHeights();
			to_balance(way,1);

			return AVLTree_iterator<value_type>(this, temp);
		}
	}
};

template <class value_type>
class AVLTree_iterator {
	template <class U>
	friend class AVLTree;

	AVLTree<value_type>* tree;
	typename AVLTree<value_type>::Node* node;
	unsigned int coord;
	std::vector<typename AVLTree<value_type>::Node*> listedTree;

	AVLTree_iterator* setLast() {
		node = listedTree[0];
		coord = 0;
		return this;
	}	
	
	AVLTree_iterator* setFirst() {
		coord = listedTree.size() - 1;
		node = listedTree[coord];
		return this;
	}

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

	void getCoord() {
		for (unsigned int i = 0; i < listedTree.size(); i++) {
			if (node == listedTree[i]) {
				coord = i;
				break;
			}
		}
	}
public:
	AVLTree_iterator() : tree(nullptr), node(nullptr), coord() {		}
	//AVLTree_iterator(AVLTree<value_type>* tree_ptr, typename AVLTree<value_type>::Node* node_ptr = nullptr) : tree(tree_ptr), node(node_ptr), treeToArray() {	}
	//AVLTree_iterator(AVLTree<value_type>* tree_ptr) {
	//	tree = tree_ptr;
	//	treeToArray();
	//}
	AVLTree_iterator(AVLTree<value_type>* tree_ptr, typename AVLTree<value_type>::Node* node_ptr = nullptr){ 
		tree = tree_ptr;
		node = node_ptr;
		treeToArray();
		getCoord();
	}
	AVLTree_iterator(const AVLTree_iterator& to_copy) {
		tree = to_copy.tree;
		node = to_copy.node;
		coord = to_copy.coord;
		listedTree = to_copy.listedTree;
	}
	AVLTree_iterator& operator++() {
		node = listedTree[--coord];
		return *this;
	}
	
	AVLTree_iterator& operator--() {
		node = listedTree[++coord];
		return *this;
	}

	bool operator== (const AVLTree_iterator<value_type>& to_compare) {
		return (coord == to_compare.coord) ? true : false;
	}

	bool operator!= (const AVLTree_iterator<value_type>& to_compare) {
		return (coord != to_compare.coord) ? true : false;
	}

	bool operator> (const AVLTree_iterator<value_type>& to_compare) {
		return (coord > to_compare.coord) ? true : false;
	}
	bool operator< (const AVLTree_iterator<value_type>& to_compare) {
		return (coord < to_compare.coord) ? true : false;
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
