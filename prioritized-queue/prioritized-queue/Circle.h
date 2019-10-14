#ifndef CIRCLE_H
#define CIRCLE_H

#include "Pair.h"
#include "Line.h"
#include <vector>

std::vector<Pair<double, double>> squareEquationSolver(double, double, double);
Pair<double, double> findSymmetricDot(const Line& baseLine, const Pair<double, double> dot);
void inversePoint(Pair<double, double>&, const Circle&);

class Circle {
private:
	//constructor will make it positive value
	double radius;
	//coordinates of the center
	Pair<double, double> center;

	friend class Line;
	friend void inversePoint(Pair<double, double>&, const Circle&);
public:
	Circle() = default;
	Circle(double x, double y, double rad) : radius((rad > 0) ? rad : -rad), center(Pair<double, double>(x, y)) {		}
	std::vector<Pair<double, double>> intersection(const Line& to_find);
	void reflectOverLine(const Line& baseLine);
	Line inverse(const Circle& baseCircle);
	bool operator== (const Circle& to_compare);
	bool centerBelongToCircle(const Circle& to_check);
};


#endif // !CIRCLE_H
