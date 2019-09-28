#ifndef QUEUEBASE_H
#define QUEUEBASE_H

#include "Pair.h"

//TODO: remove Pair from QueueBase definition and think out about more parameters
template <class S, class T>
class QueueBase {
	/*
		key functions for the class S which is a container:
			void push_back();
			bool empty();
			iterator begin();
			iterator end();
			iterator insert();
			iterator erase();
			unsigned int size();
			
		and for iterators:
			iterator operator--();
			Pair<T, unsigned int> operator*();
		
		IF NOT: override functions with missed methods
	*/
private:
	S container;
public:
	void push(Pair<T, unsigned int> elem) {
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
		return *(container.begin());
	}

	unsigned int size() {
		return container.size();
	}

	void out() {
		for (auto i = container.begin(); i != container.end(); ++i) {
			(*i).out();
		}
	}
};

#endif // !QUEUEBASE_H