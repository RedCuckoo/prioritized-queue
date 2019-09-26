#ifndef PAIR_H
#define PAIR_H

#include <iostream>

template<class S, class T>
class Pair {
private:
	S value;
	T priority;
public:
	Pair() = default;

	Pair(S val, T prior){
		value = val;
		priority = prior;
	}

	S getVal() const {
		return value;
	}

	T getPrior() const {
		return priority;
	}

	bool operator>(const Pair& to_compare) const {
		return (priority > to_compare.getPrior()) ? true : false;
	}	
	
	bool operator>=(const Pair& to_compare) const {
		return (priority >= to_compare.getPrior()) ? true : false;
	}	
	
	bool operator<(const Pair& to_compare) const {
		return (priority < to_compare.getPrior()) ? true : false;
	}	
	
	bool operator<=(const Pair& to_compare) const {
		return (priority <= to_compare.getPrior()) ? true : false;
	}

	bool operator==(const Pair& to_compare) const {
		return (priority == to_compare.getPrior() && value == to_compare.getVal()) ? true : false;
	}	
	
	bool operator!=(const Pair& to_compare) const {
		return (priority != to_compare.getPrior() || value == to_compare.getVal()) ? true : false;
	}

	void out() {
		std::cout << value << " " << priority << std::endl;
	}

};

#endif // !PAIR_H
