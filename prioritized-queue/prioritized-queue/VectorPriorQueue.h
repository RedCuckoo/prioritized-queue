#ifndef VECTORPRIORQUEUE_H
#define VECTORPRIORQUEUE_H

#include <vector>
#include <iostream>
#include "Pair.h"
#include "QueueBase.h"

template <class T>
class VectorPriorQueue : private QueueBase<std::vector<Pair<T, unsigned int>>, Pair<T, unsigned int>> {

};


#endif // !VECTORPRIORQUEUE_H
