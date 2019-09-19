#ifndef LISTPRIORQUEUE_H
#define LISTPRIORQUEUE_H

#include <list>
#include <iostream>
#include "Pair.h"

template <class T>
class ListPriorQueue {
private:
	std::list<Pair<T, unsigned int>>container;
	
public:
	void add(Pair<T, unsigned int> elem){
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

	void remove(Pair<T, unsigned int> elem) {
		for (auto it = container.begin(); it != container.end(); ++it) {
			if ((*it) == elem) {
				container.erase(it);
				return;
			}
		}
	}



	void out() {
		for (auto it = container.begin(); it != container.end(); ++it) {
			std::cout << it->getVal() << std::endl;
		}
	}
};

#endif // !LISTPRIORQUEUE_H
