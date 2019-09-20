#ifndef LISTPRIORQUEUE_H
#define LISTPRIORQUEUE_H

//#include <list>
#include "List.h"
#include <iostream>
#include "Pair.h"

template <class T>
class ListPriorQueue {
private:
	//std::list<Pair<T, unsigned int>>container;
	List<Pair<int, unsigned int>>container;
public:
	void add(Pair<T, unsigned int> elem){
		//if (container.empty()) {
		//	container.push_back(elem);
		//}
		//else {
		//	//for (auto it = container.begin(); it != container.end(); it = it->getNext()) {
		//	//	if ((*it)>elem){
		//	//		container.insert(it, elem);
		//	//	return;
		//	//	}
		//	//}
		//	container.push_back(elem);
		//}
	}

	void remove(Pair<T, unsigned int> elem) {
		//for (auto it = container.begin(); it != container.end(); ++it) {
		//	if ((*it) == elem) {
		//		container.erase(it);
		//		return;
		//	}
		//}
	}



	void out() {

	}
};

#endif // !LISTPRIORQUEUE_H
