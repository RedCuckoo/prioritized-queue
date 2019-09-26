#ifndef LISTPRIORQUEUE_H
#define LISTPRIORQUEUE_H

//#include <list>
#include "List.h"
#include <iostream>
#include "Pair.h"

template <class T>
class ListPriorQueue {
private:
	List<Pair<int, unsigned int>>container;
public:
	void push(Pair<T, unsigned int> elem){
		if (container.empty()) {
			container.push_back(elem);
		}
		else {
			for (auto it = container.begin(); it != container.end(); ++it) {
				if ((*it)>elem){
					container.insert(it, elem);
					return;
				}
			}
			container.push_back(elem);
		}                                                                                                     
	}

	bool empty() {
		return (container.empty()) ? true : false;
	}

	void pop() {
		container.erase(--container.end());
	}

	Pair<T, unsigned int>& front() {
		return *--container.end();
	}

	Pair<T, unsigned int>& back() {
		return *container.begin();
	}

	unsigned int size() {
		return container.size();
	}

/*	void remove(Pair<T, unsigned int> elem) {
		for (auto it = container.begin(); it != container.end(); ++it) {
			if ((*it) == elem) {
				container.erase(it);
				return;
			}
		}
	}
*/

	void out() {
		for (auto f = container.begin(); f != container.end(); ++f) {
			(*f).out();
		}
	}
};

#endif // !LISTPRIORQUEUE_H
