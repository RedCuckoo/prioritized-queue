#ifndef VECTORPRIORQUEUE_H
#define VECTORPRIORQUEUE_H

#include <vector>
#include <iostream>
#include "Pair.h"
#include "QueueBase.h"

template <class T>
class VectorPriorQueue : public QueueBase<std::vector<Pair<T, unsigned int>>, T> {

};


#endif // !VECTORPRIORQUEUE_H
