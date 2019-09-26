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
	template <class U>
	friend class List_iterator;

	//--------iterator-----------

	List_iterator<T> begin() {
		return List_iterator<T>(this, head);
	}

	List_iterator<T> end() {
		return List_iterator<T>(this, tail);
	}

	//-----------List-----------

	List() {
		head = new Node();
		tail = head;
	}

	bool empty() {
		return (head == tail) ? true : false;
	}

	unsigned int size() {
		Node* temp = head;
		unsigned int size = 0;
		while (temp != tail) {
			size++;
			temp = temp->next;
		}
		return size;
	}

	void push_back(T val) {
		if (head == tail) {
			head = new Node(val, nullptr, tail);
			tail->prev = head;
		}
		else {
			tail->prev =tail->prev->next = new Node(val, tail->prev, tail);
		}
	}

	void insert(const List_iterator<T>& it, const T& to_insert) {
		if (it == begin()) {
			it->prev = new Node(to_insert, nullptr, head);
			head = head->prev;
		}
		else {
			Node* temp = it->prev;
			it->prev = new Node(to_insert, it->prev, it.node);
			temp->next = it->prev;
		}

	}
	
//EXCEPTIONS

	List_iterator<T> erase(List_iterator<T> it) {
		//throw exception if end()
		Node* temp = it.node;
		if (it == begin()) {
			head = head->next;
			it = begin();
		}
		else {
			it = List_iterator<T>(this, temp->next);
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
		}
		delete temp;
		return it;
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

/*
	bool operator<= (const List_iterator& to_compare) const {
		typename List<T>::Node temp = list->head;
		while (temp != this->node || temp != to_compar.node) {
			temp = temp->next;
		}

		return (temp == this->node) ? true : false;
	}

	bool operator< (const List_iterator& to_compare) const {
		return (*this <= to_compare && *this != to_compare) ? true : false;
	}	

	bool operator>= (const List_iterator& to_compare) const {
		typename List<T>::Node temp = list->head;
		while (temp != this->node || temp != to_compare.node) {
			temp = temp->next;
		}

		return (temp == to_compare.node) ? true : false;
	}

	bool operator> (const List_iterator& to_compare) const {
		return (*this >= to_compare && *this != to_compare) ? true : false;
	}
*/

	template <class U>
	friend List_iterator<U> operator+ (int val, List_iterator<U> to_add);

private:
	typename List<T>::Node* operator->() const{
		return node;
	}
	

};

template <class T>
List_iterator<T> operator+ (int val, List_iterator<T> to_add) {
	/**to_add is a parameter without reference because we need to create a local variable either or
	so in this case we use already copied parameter*/
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

