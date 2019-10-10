#ifndef TREEPRIORQUEUE_H
#define TREEPRIORQUEUE_H

#include "QueueBase.h"
#include "AVLTree.h"
#include "Pair.h"

template <class value_type>
class TreePriorQueue : 
	public QueueBase<AVLTree<value_type>, value_type> {
public:
	void push(value_type elem) {
		QueueBase<AVLTree<Pair<value_type, unsigned int>>, Pair<value_type, unsigned int>>::container.push(elem);
	}
};

#endif // !TREEPRIORQUEUE_H
