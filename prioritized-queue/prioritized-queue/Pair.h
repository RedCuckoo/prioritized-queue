/*!
	\file
	\brief Header file containing class Pair

	This file contains template definition and implementation of such data structure as a Pair, which is customized
*/

#ifndef PAIR_H
#define PAIR_H

#include <iostream>

//TODO: overload operator<<
/*!
	\brief Customized Pair
	\details A custom implementation of Pair<S,T>, as it is used for queue with priority fields have the related names
	Currently it is possible to create a Pair only through the provided constructor
*/
template<class S, class T>
class Pair {
private:
	S value;
	T priority;
public:

	//Pair() = default;
	/*!
	A constructor to create a pair for the queue with priority
	\param[in] val The value which queue stores
	\param[in] prior The priority which provided value has
	*/
	Pair(S val, T prior){
		value = val;
		priority = prior;
	}

	/*!
	\brief Getter method for the value
	\details To get the value of the Pair
	*/
	S getVal() const {
		return value;
	}

	/*!
	\brief Getter method for the priority
	\details To get the priority of the Pair
	*/
	T getPrior() const {
		return priority;
	}

	/*!
	Overloaded "is bigger than" operator
	\param to_compare Const reference to the Pair that has to be compared with the Pair passed as an lvalue
	\return True value if current Pair is bigger than to_compare and false value otherwise
	*/
	bool operator>(const Pair& to_compare) const {
		return (priority > to_compare.getPrior()) ? true : false;
	}	
	
	/*!
	Overloaded "is bigger or equal than" operator
	\param to_compare Const reference to the Pair that has to be compared with the Pair passed as an lvalue
	\return True value if current Pair is bigger or equal than to_compare and false value otherwise
	*/
	bool operator>=(const Pair& to_compare) const {
		return (priority >= to_compare.getPrior()) ? true : false;
	}	
	
	/*!
	Overloaded "is less than" operator
	\param to_compare Const reference to the Pair that has to be compared with the Pair passed as an lvalue
	\return True value if current Pair is less than to_compare and false value otherwise
	*/
	bool operator<(const Pair& to_compare) const {
		return (priority < to_compare.getPrior()) ? true : false;
	}	
	
	/*!
	Overloaded "is less or equal than" operator
	\param to_compare Const reference to the Pair that has to be compared with the Pair passed as an lvalue
	\return True value if current Pair is less or equal than to_compare and false value otherwise
	*/
	bool operator<=(const Pair& to_compare) const {
		return (priority <= to_compare.getPrior()) ? true : false;
	}

	/*!
	Overloaded equality operator
	\param to_compare Const reference to the Pair that has to be compared with the Pair passed as an lvalue
	\return True value if they are equal and false value otherwise
	*/
	bool operator==(const Pair& to_compare) const {
		return (priority == to_compare.getPrior() && value == to_compare.getVal()) ? true : false;
	}	
	
	/*!
	Overloaded inequality operator
	\param to_compare Const reference to the Pair that has to be compared with the Pair passed as an lvalue
	\return True value if they are unequal and false value otherwise
	*/
	bool operator!=(const Pair& to_compare) const {
		return (priority != to_compare.getPrior() || value == to_compare.getVal()) ? true : false;
	}

	/*!
	Print stored fields of the Pair to the console, using <iostream> library
	*/
	void out() {
		std::cout << value << " " << priority << std::endl;
	}

};

#endif // !PAIR_H
