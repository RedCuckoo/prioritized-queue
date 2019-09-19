#ifndef LIST_H
#define LIST_H

#include <iostream>

template <class T>
class List {

public:


/** Class Node expresses the node of the list with its characteristics and has various method
*/
	class Node {
	private:
		T value;
		Node* next, * prev;
	public:
		Node(T val, Node* pr = NULL, Node* ne = NULL) {
			value = val;
			next = ne;
			prev = pr;
		}

		void add_next(T val) {
			next = new Node(val, this);
		}

		Node* getNext(){
			return next;
		}

		T getVal() {
			return value;
		}

	};


// Class List is the actual implementation of the list library
private:
	Node* head, * tail;

public:
	List() {
		head = NULL;
		tail = NULL;
	}

	void push_back(T val) {
		if (head == NULL) {
			head = new Node(val);
			tail = head;
		}
		else {
			tail->add_next(val);
			tail = tail->getNext();
		}
	}

	Node* begin() {
		return head;
	}

	Node* end() {
		return tail;
	}

	void out() {
		Node* temp = head;
		while (head != tail) {
			std::cout << temp->getVal() << " ";
			temp = temp->getNext();
		}
	}

	//void erase ()

};


#endif // !LIST_H

