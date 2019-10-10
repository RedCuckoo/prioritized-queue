#ifndef VECTORPRIORQUEUE_H
#define VECTORPRIORQUEUE_H

#include <vector>
#include <iostream>
#include "Pair.h"
#include "QueueBase.h"

template <class value_type>
class VectorPriorQueue : private QueueBase<std::vector<value_type>, value_type> {

};


#endif // !VECTORPRIORQUEUE_H
