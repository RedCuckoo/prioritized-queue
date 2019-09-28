/*!
	\file
	\brief Header file containing class List and class List_iterator

	This file contains template definition and implementation of such data structure as a double linked list
*/

#ifndef LIST_H
#define LIST_H

#include <iostream>
//TODO: refactor
//TODO: documentation

/*!
	\brief Double linked list
	\details A custom implementation of STL library std::list with custom random access iterator
*/
template <class T>
class List {
private:
	/*!
		\brief A node of double linked list
		\details This class stores pointers to the previous and next node.
		The value stored depends on the type given to the class List.
		As well it is possible to create an empty node, which will serve as the end of the list.
		Such possibility is provided by the "type" field.
	*/
	struct Node {
	public:
		//TODO: while refactoring make sure that it's better to store node values in a public rather than private field
		T value;
		Node* next, * prev;
		bool type = 1;
		
		/*!
		Constructor which creates an empty node, which is used as the end of the list (iterator on the end of the list)
		*/
		Node() {
			type = 0;
			next = nullptr;
			prev = nullptr;
		}

		/*!
		Constructor which creates a node from the provided parameters.
		\param[in] val The value that node will store
		\param[in] pr Pointer to the previous node (for the beginning of the list, nullptr is passed)
		\param[in] ne Pointer to the next node (for the end of the list, pointer to an empty node is passed)
		*/
		Node(T val, Node* pr, Node* ne) {
			value = val;
			prev = pr;
			next = ne;
		}

		//TODO: add value.out() support somehow
		/*!
		Print stored value of the node to the console, using <iostream> library
		*/
		void out() {
			std::cout << value << std::endl;
		}

		/*!
		Overloaded equality operator.
		\param to_compare Const reference to the node that has to be compared with the node passed as an lvalue
		\return True value if they are equal and false value otherwise
		*/
		bool operator==(const Node& to_compare) const{
			return (type == to_compare.type && value == to_compare.value && next == to_compare.next && prev == to_compare.prev) ? true : false;
		}
		
		/*!
		Overloaded inequality operator.
		\param to_compare Const reference to the node that has to be compared with the node passed as an lvalue
		\return True value if they are unequal and false value otherwise
		*/
		bool operator!=(const Node& to_compare) const{
			return (type != to_compare.type || value != to_compare.value || next != to_compare.next || prev != to_compare.prev) ? true : false;
		}

	};
	Node* head, * tail;
public:
	//TODO: check how to write documentation for the friend declaration
	template <class U>
	friend class List_iterator;

	//--------iterator-----------
	/*!
	Method that returns the iterator to the beginning of the list
	\return Iterator to the beginning of the list
	*/
	List_iterator<T> begin() {
		return List_iterator<T>(this, head);
	}

	/*!
	Method that returns the iterator to the end of the list
	\return Iterator to the end of the list
	*/
	List_iterator<T> end() {
		return List_iterator<T>(this, tail);
	}

	//-----------List-----------
	/*!
	Default construct which creates a List object with no elements in it
	*/
	List() {
		head = new Node();
		tail = head;
	}

	/*!
	This method checks whether or not current list is empty
	\return True value if the list is empty and false value otherwise
	*/
	bool empty() {
		return (head == tail) ? true : false;
	}

	/*!
	To get the amount of elements of the list
	\return Size of the list
	*/
	unsigned int size() {
		Node* temp = head;
		unsigned int size = 0;
		while (temp != tail) {
			size++;
			temp = temp->next;
		}
	return size;
	}

	/*!
	Add elements to the end of the list
	\param[in] val Value which has to be added to the list
	*/
	void push_back(T val) {
		if (head == tail) {
			head = new Node(val, nullptr, tail);
			tail->prev = head;
		}
		else {
			tail->prev =tail->prev->next = new Node(val, tail->prev, tail);
		}
	}

	/*!
	Insert elements in the iterated position in the list
	\param[in] it Iterator to the position where the element has to be inserted 
	\param[in] to_insert Reference to the element which has to be inserted
	The value is interted on the left of the iterator.
	\code
	//If we are given the following sequence with the iterator to the second element
	//
	//1 2 3 4 5 6
	//  ^
	//
	//If we call the function insert(second_position_iterator, 0) our sequence will have the following look:
	//
	//1 0 2 3 4 5 6
	//    ^
	//
	\endcode
	The passed iterator will NOT be valid, though it will be returned as the return value.
	\return A valid iterator to the same value that passed parameter was pointing to
	*/
	List_iterator<T> insert(const List_iterator<T>& it, const T& to_insert) {
		if (it == begin()) {
			it->prev = new Node(to_insert, nullptr, head);
			head = head->prev;
		}
		else {
			Node* temp = it->prev;
			it->prev = new Node(to_insert, it->prev, it.node);
			temp->next = it->prev;
		}
		return it;
	}
	
	//TODO: implement exceptions?
	/*!
	Erases element on the iterated position in the list
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

	/*!
	Overloaded equality operator.
	\param to_compare Const reference to the list that has to be compared with the list passed as an lvalue
	\return True value if they are equal and false value otherwise
	*/
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

	/*!
	Overloaded inequality operator.
	\param to_compare Const reference to the list that has to be compared with the list passed as an lvalue
	\return True value if they are unequal and false value otherwise
	*/
	bool operator!=(List& to_compare) {
		return (*this == to_compare) ? false : true;
	}

};

/*!
A custom written class which emplements iterators for the class List.
It has the same properties as STL library std::random_access_iterator
*/
template <class T>
class List_iterator {
	template<class U>
	friend class List;

	List<T>* list;
	typename List<T>::Node* node;

public:
	/*!
	A default constuctor which creates an empty iterator with fields that are pointing to the null value
	*/
	List_iterator() : list(nullptr), node(nullptr) {	}

	/*!
	A constructor that creates iterator from the provided parameters
	\param[in] list_ptr Pointer to the list, where current iterator belongs to
	\param[in] node_ptr Pointer to the node, where current iterator has to point
	*/
	List_iterator(List<T>* list_ptr, typename List<T>::Node* node_ptr) : list(list_ptr), node(node_ptr) {	}

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
	/*!
	\param[in] to_add is a parameter without reference because we need to create a local variable either or
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

