#ifndef LISTPRIORQUEUE_H
#define LISTPRIORQUEUE_H

#include "List.h"
#include <iostream>
#include "Pair.h"
#include "QueueBase.h"

template <class value_type>
class ListPriorQueue : public QueueBase<List<value_type>, value_type> {

};

#endif // !LISTPRIORQUEUE_H
