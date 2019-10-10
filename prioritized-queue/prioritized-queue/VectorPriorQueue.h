/*!
	\file
	\brief Header file containing class VectorPriorQueue
	\details This file contains an implementation of the priority queue based on the dynamically allocated array, std::vector
*/

#ifndef VECTORPRIORQUEUE_H
#define VECTORPRIORQUEUE_H

#include <vector>
#include "QueueBase.h"

/*!
	\brief Priority queue based on the dynamically allocated array, std::vector
	\details In order of this function to work properly, you should pass Pair<value, priority> as a value_type.
	The class itself is inheritted from the base of the priority queue and uses custom written dynamically allocated array, std::vector.
*/
template <class value_type>
class VectorPriorQueue : private QueueBase<std::vector<value_type>, value_type> {

};


#endif // !VECTORPRIORQUEUE_H
