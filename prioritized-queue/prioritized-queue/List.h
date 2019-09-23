#ifndef LIST_H
#define LIST_H

#include <iostream>

template <class T>
class List {
	struct Node {
		T value;
		Node* next, * prev;
		
		Node(T val, Node* pr = NULL, Node* ne = NULL) {
			value = val;
			prev = pr;
			next = ne;
		}

		void out() {
			std::cout << value << std::endl;
		}

		//FIX FOR INT???
		Node* operator+ (unsigned int inc) {
			//increments pointer in a correct way
			Node* ans = this;
			for (unsigned int i = 0; i < inc; i++) {
				ans = ans->next;
			}
			return ans;
		}
	};
	Node* head, * tail;
public:

	template <class U>
	friend class List_iterator;

	typedef List_iterator<T> iterator;
	typedef List_iterator<const T> const_iterator;

	iterator begin() {

	}

	List() {
		head = NULL;
		tail = NULL;
	}
	
	//Node* begin() {
	//	return head;
	//}

	//Node* end() {
	//	return tail;
	//}

	bool empty() {
		return (head) ? false : true;
	}

	void out() {
		Node* temp = head;
		while (temp != tail) {
			temp->out();
			temp = temp->next;
		}
		tail->out();
	}

	void push_back(T val) {
		if (!head) {
			head = new Node(val);
			tail = head;
		}
		else {
			tail->next = new Node(val, tail);
			tail = tail->next;
		}
	}

	void insert(Node* it, T to_insert) {
		if (it) {
			if (it->prev) {
				it->prev->next = new Node(to_insert, it->prev, it);
				it->prev = it->prev->next;
			}
			else {
				Node* new_head = new Node(to_insert, NULL, it);
				it->prev = new_head;
				head = new_head;
			}
		}
	}

	void erase(Node* it) {

	}

	//void operator<<

};

template <class T>
class List_iterator : std::iterator <std::random_access_iterator_tag, T, unsigned int, T*, T&> {
	template<class U>
	friend class List;
	
	T* pointer;
	
	List_iterator(T* ptr) {
		pointer(ptr);
	}

public:
	List_iterator(const List_iterator& it) {
		pointer(it.pointer);
	}

};

#endif // !LIST_H

