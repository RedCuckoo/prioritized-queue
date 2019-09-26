#ifndef LISTPRIORQUEUE_H
#define LISTPRIORQUEUE_H

#include "List.h"
#include <iostream>
#include "Pair.h"
#include "QueueBase.h"

template <class T>
class ListPriorQueue : public QueueBase<List<Pair<T, unsigned int>>, T> {

};

#endif // !LISTPRIORQUEUE_H
