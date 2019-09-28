/*!
	\file
	\brief Header file containing class QueueBas
	\details This file contains template definition and implementation of the base class for the queue with priority. 
*/

#ifndef QUEUEBASE_H
#define QUEUEBASE_H

#include "Pair.h"

//TODO: remove Pair from QueueBase definition and think out about more parameters
/*!
\brief Base class of the private methods for the queue
\details In order to use it, you have to pass a type of container to container_type, which has to have implemented the following functions:
\code
	void push_back();
	bool empty();
	iterator begin();
	iterator end();
	iterator insert(iterator, container_node);
	iterator erase();
	unsigned int size();
\endcode
By iterator meant container_type_iterator, the iterator for container_type.
As well, for the iterators next functions have to be implemented:
\code
	iterator operator--();
	container_node operator*();
\endcode
If something is missing in your passed type, override functions changing missed methods
*/
template <class container_type, class container_node>
class QueueBase {
private:
	container_type container;
public:
	/*!
	\brief Add elements 
	\details Add elements following the rules of the queue with priority
	\param[in] elem Element which has to be added
	*/
	void push(container_node elem) {
		if (container.empty()) {
			container.push_back(elem);
		}
		else {
			for (auto it = container.begin(); it != container.end(); ++it) {
				if (*it > elem) {
					container.insert(it, elem);
					return;
				}
			}
			container.push_back(elem);
		}
	}

	/*!
	\brief Checks emptiness of the container
	\details This method checks whether or not passed container is empty
	\return True value if the container is empty and false value otherwise
	*/
	bool empty() {
		return (container.empty()) ? true : false;
	}
	
	/*!
	\brief Remove front element
	\details This method removes the front value in the queue
	*/
	void pop() {
		container.erase(--container.end());
	}

	/*!
	\brief Getter for the top element in the queue
	\return Reference to the top element in the queue
	*/
	container_node& front() {
		return *--container.end();
	}

	/*!
	\brief Getter for the last element in the queue
	\return Reference to the last element in the queue
	*/
	container_node& back() {
		return *(container.begin());
	}

	/*!
	\brief Get the size of the queue
	\details To get the amount of elements in the queue
	\return Size of the queue 
	*/
	unsigned int size() {
		return container.size();
	}

	/*!
	\brief Output stored information
	\details Print stored fields of the queue to the console, using <iostream> library
	*/
	void out() {
		for (auto i = container.begin(); i != container.end(); ++i) {
			(*i).out();
		}
	}
};

#endif // !QUEUEBASE_H