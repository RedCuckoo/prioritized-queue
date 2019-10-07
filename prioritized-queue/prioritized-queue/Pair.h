/*!
	\file
	\brief Header file containing class Pair

	This file contains template definition and implementation of such data structure as a Pair, which is customized
*/

#ifndef PAIR_H
#define PAIR_H

#include <iostream>

/*!
	\brief Customized Pair
	\details A custom implementation of Pair<value_type,priority_type>, as it is used for queue with priority fields have the related names
	Currently it is possible to create a Pair only through the provided constructor
*/
template<class value_type, class priority_type>
class Pair {
private:
	value_type value;
	priority_type priority;

	//friend int main();
	/*!
	\brief Friended operator<<
	\details Allows to output information with the stream
	*/
	template<class value_type, class priority_type>
	friend std::ostream& operator<<(std::ostream& out, const Pair<value_type, priority_type>& to_out);
public:
	/*!
	\brief Constructor
	\details Allowing a default constructor access
	*/
	Pair() = default;
	
	/*!
	\brief Constructor
	\details A constructor to create a pair for the queue with priority
	\param[in] val The value which queue stores
	\param[in] prior The priority which provided value has
	*/
	Pair(value_type val, priority_type prior){
		value = val;
		priority = prior;
	}

	/*!
	\brief Getter method for the value
	\details To get the value of the Pair
	*/
	value_type getVal() const {
		return value;
	}

	/*!
	\brief Getter method for the priority
	\details To get the priority of the Pair
	*/
	priority_type getPrior() const {
		return priority;
	}

	/*!
	\brief Overloaded "is bigger than" operator
	\param to_compare Const reference to the Pair that has to be compared with the Pair passed as an lvalue
	\return True value if current Pair is bigger than to_compare and false value otherwise
	*/
	bool operator>(const Pair& to_compare) const {
		return (priority > to_compare.getPrior()) ? true : false;
	}	
	
	/*!
	\brief Overloaded "is bigger or equal than" operator
	\param to_compare Const reference to the Pair that has to be compared with the Pair passed as an lvalue
	\return True value if current Pair is bigger or equal than to_compare and false value otherwise
	*/
	bool operator>=(const Pair& to_compare) const {
		return (priority >= to_compare.getPrior()) ? true : false;
	}	
	
	/*!
	\brief Overloaded "is less than" operator
	\param to_compare Const reference to the Pair that has to be compared with the Pair passed as an lvalue
	\return True value if current Pair is less than to_compare and false value otherwise
	*/
	bool operator<(const Pair& to_compare) const {
		return (priority < to_compare.getPrior()) ? true : false;
	}	
	
	/*!
	\brief Overloaded "is less or equal than" operator
	\param to_compare Const reference to the Pair that has to be compared with the Pair passed as an lvalue
	\return True value if current Pair is less or equal than to_compare and false value otherwise
	*/
	bool operator<=(const Pair& to_compare) const {
		return (priority <= to_compare.getPrior()) ? true : false;
	}

	/*!
	\brief Overloaded equality operator
	\param to_compare Const reference to the Pair that has to be compared with the Pair passed as an lvalue
	\return True value if they are equal and false value otherwise
	*/
	bool operator==(const Pair& to_compare) const {
		return (priority == to_compare.getPrior() && value == to_compare.getVal()) ? true : false;
	}	
	
	/*!
	\brief Overloaded inequality operator
	\param to_compare Const reference to the Pair that has to be compared with the Pair passed as an lvalue
	\return True value if they are unequal and false value otherwise
	*/
	bool operator!=(const Pair& to_compare) const {
		return (priority != to_compare.getPrior() || value == to_compare.getVal()) ? true : false;
	}

	/*!
	\brief Output stored information
	\details Print stored fields of the Pair to the console, using <iostream> library
	*/
	void out() {
		std::cout << value << " " << priority << std::endl;
	}
};

/*!
\brief Operator<<
\detail Allows to output information with the stream
\param out Stream which is defined automatically, has to be ostream or inherited streams
\param to_out This parameter is passed on the right of "<<", not changeble, the reference to the Pair that has to be outputted
\return Reference to the ostream, to allow continous streaming, like
	\code
	Pair<int,int> a = {3,4};
	Pair<int,int> b = {6,7};
	std::cout << a << b;
	//The output will be:
	//3 4
	//6 7
	\endcode
*/
template <class value_type, class priority_type>
std::ostream& operator<<(std::ostream& out_stream, const Pair<value_type, priority_type>& to_out) {
	
	std::cout << to_out.value << " " << to_out.priority;// << std::endl;
	return out_stream;
}

#endif // !PAIR_H
