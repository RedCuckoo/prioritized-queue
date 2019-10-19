/*!
	\file
	\brief Header file containing class TreePriorQueue
	\details This file contains an implementation of the priority queue based on the binary search tree	
*/

#ifndef TREEPRIORQUEUE_H
#define TREEPRIORQUEUE_H

#include "QueueBase.h"
#include "AVLTree.h"

/*!
	\brief Priority queue based on the binary search tree
	\details In order of this function to work properly, you should pass Pair<value, priority> as a value_type.
	The class itself is inheritted from the base of the priority queue and uses custom written self balanced AVL tree.
*/
template <class value_type>
class TreePriorQueue : public QueueBase<AVLTree<value_type>, value_type> {
public:
	/*!
	\brief Method to add element to the queue
	\details Overridden method of the QueueBase class, because the given there function adds elements to the list.
	That way we didn't have to implement function insert, as rules of parent class states.
	\param [in] elem Element to be added
	*/
	void push(value_type elem);

	void out();

	value_type& front();
	value_type& back();
	void pop();
};


template <class value_type>
void TreePriorQueue<value_type>::pop() {
	QueueBase<AVLTree<value_type>, value_type>::container.erase(QueueBase<AVLTree<value_type>, value_type>::container.begin());
}

template<class value_type>
value_type& TreePriorQueue<value_type>::front(){
	return *QueueBase<AVLTree<value_type>, value_type>::container.begin();
}

template<class value_type>
value_type& TreePriorQueue<value_type>::back(){
	return *--QueueBase<AVLTree<value_type>, value_type>::container.end();
}

template <class value_type>
void TreePriorQueue<value_type>::push(value_type elem) {
	QueueBase<AVLTree<value_type>, value_type>::container.push(elem);
}

template<class value_type>
void TreePriorQueue<value_type>::out() {
	for (auto i = QueueBase<AVLTree<value_type>, value_type>::container.begin(); i != QueueBase<AVLTree<value_type>, value_type>::container.end(); ++i) {
		(*i).out();
	}
}

#endif // !TREEPRIORQUEUE_H
