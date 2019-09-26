#ifndef QUEUEBASE_H
#define QUEUEBASE_H

#include "Pair.h"

template <class S, class T>
class QueueBase {
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