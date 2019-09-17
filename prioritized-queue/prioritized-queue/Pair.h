#ifndef PAIR_H
#define PAIR_H

template<class S, class T>
class Pair {
private:
	S value;
	T priority;
public:
	Pair(S val, T prior) {
		value = val;
		priority = prior;
	}

	S getVal() {
		return value;
	}

	T getPrior() {
		return priority;
	}

};


#endif // !PAIR_H
