#ifndef FIGURE_H
#define FIGURE_H

#include <vector>
#include "priority_queue_data_structure/data_structures/Pair.h"
#include "figures/Circle.h"
#include "figures/Line.h

class Figure{
public:
	virtual std::vector<Pair<double, double>> intersection(const Circle& to_find) = 0;
	virtual std::vector<Pair<double, double>> intersection(const Line& to_find) = 0;
	virtual void reflectOverLine(const Line& baseLine) = 0;
	virtual void out() = 0;
};

#endif //FIGURE_H