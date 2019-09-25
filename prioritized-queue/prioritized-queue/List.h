#ifndef LIST_H
#define LIST_H

#include <iostream>

template <class T>
class List {
	struct Node {
		T value;
		Node* next, * prev;
		bool type = 1;
		
		Node() {
			type = 0;
			next = nullptr;
			prev = nullptr;
		}

		Node(T val, Node* pr, Node* ne) {
			value = val;
			prev = pr;
			next = ne;
		}

		void out() {
			std::cout << value << std::endl;
		}

		bool operator==(const Node& to_compare) const{
			return (type == to_compare.type && value == to_compare.value && next == to_compare.next && prev == to_compare.prev) ? true : false;
		}
		
		bool operator!=(const Node& to_compare) const{
			return (type != to_compare.type || value != to_compare.value || next != to_compare.next || prev != to_compare.prev) ? true : false;
		}

	};
	Node* head, * tail;
public:
	List() {
		head = new Node();
		tail = head;
	}

	bool empty() {
		return (head == tail) ? false : true;
	}

	//void out() {
	//	Node* temp = head;
	//	while (temp != tail) {
	//		temp->out();
	//		temp = temp->next;
	//	}
	//	tail->out();
	//}

	void push_back(T val) {
		if (head == tail) {
			head = new Node(val, nullptr, tail);
			tail->prev = head;
		}
		else {
			tail->prev =tail->prev->next = new Node(val, tail->prev, tail);
		}
	}
/*
	void insert(Node* it, T to_insert) {
		if (it) {
			if (it->prev) {
				it->prev->next = new Node(to_insert, it->prev, it);
				it->prev = it->prev->next;
			}
			else {
				Node* new_head = new Node(to_insert, nullptr, it);
				it->prev = new_head;
				head = new_head;
			}
		}
	}*/

	void erase(Node* it) {

	}

	bool operator==(List& to_compare) {
		Node* temp1 = head;
		Node* temp2 = to_compare;
		
		while (temp1 != tail || temp2!= to_compare->tail) {
			if (temp1 == temp2) {
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
			else {
				return false;
			}
		}

		return (temp1 == temp2) ? true : false;
	}

	bool operator!=(List& to_compare) {
		return (*this == to_compare) ? false : true;
	}

	template <class U>
	friend class List_iterator;

	typedef List_iterator<T> iterator;
	typedef List_iterator<const T> const_iterator;

	iterator begin() {
		return iterator(this, head);
	}

	iterator end() {
		return iterator(this, tail);
	}
};

template <class T>
class List_iterator {
	template<class U>
	friend class List;


	List<T>* list;
	typename List<T>::Node* node;

public:
	List_iterator() : list(nullptr), node(nullptr) {	}
	List_iterator(List<T>* l, typename List<T>::Node* n) : list(l), node(n) {	}

	List_iterator(const List_iterator& to_copy) : list(to_copy.list), node(to_copy.node) {	}

	List_iterator& operator++() {
		node = node->next;
		return *this;
	}

	List_iterator operator++(int) {
		List_iterator result = *this;
		node = node->next;
		return result;
	}

	List_iterator& operator--() {
		node = node->prev;
		return *this;
	}

	List_iterator operator--(int) {
		List_iterator result = *this;
		node = node->prev;
		return result;
	}

	List_iterator& operator+(int val) {
		if (val >= 0) {
			for (unsigned int i = 0; i < val; ++i) {
				node = node->next;
			}
		}
		else {
			for (unsigned int i = 0; i < -val; ++i) {
				node = node->prev;
			}
		}
		return *this;
	}
	
	List_iterator& operator-(int val) {
		if (val >= 0) {
			for (unsigned int i = 0; i < val; ++i) {
				node = node->prev;
			}
		}
		else {
			for (unsigned int i = 0; i < -val; ++i) {
				node = node->next;
			}
		}
		return *this;
	}

	

	bool operator== (const List_iterator& to_compare) const {
		return (list == to_compare.list && node == to_compare.node);
	}	
	
	bool operator!= (const List_iterator& to_compare) const {
		return (list != to_compare.list || node != to_compare.node);
	}

	T& operator*() const{
		return node->value;
	}

	T* operator->() const{
		return &(node->value);
	}
	


	template <class U>
	friend List_iterator<U> operator+ (int val, List_iterator<U> to_add);
};

template <class T>
List_iterator<T> operator+ (int val, List_iterator<T> to_add) {
	if (val >= 0) {
		for (int i = 0; i < val; ++i) {
			to_add.node = to_add.node->next;
		}
	}
	else {
		for (int i = 0; i < -val; ++i) {
			to_add.node = to_add.node->prev;
		}
	}
	return to_add;
}

#endif // !LIST_H

