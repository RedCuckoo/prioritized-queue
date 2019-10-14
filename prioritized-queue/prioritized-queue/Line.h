#ifndef LINE_H
#define LINE_H

#include "Circle.h"
#include "Pair.h"
#include <vector>

class Line {
private:
	//y = kx + b
	//k = slope, b = y_interception
	//ax+by+c = 0;
	//double slope, y_interception;
	double a, b, c;
public:

	friend class Circle;
	friend Pair<double,double> findSymmetricDot(const Line& baseLine, const Pair<double, double> dot);
	//Line(double k, double b) : slope(k), y_interception(b) {		}
	Line() = default;
	Line(double a_coef, double b_coef, double c_coef) : a(a_coef), b(b_coef), c(c_coef) {		}
	Line(Pair<double, double>, Pair<double, double>);

	Pair<double, double> intersection(const Circle& to_find);

	void reflectOverLine(const Line& baseLine);
	Circle inverse(const Circle& baseCircle);
};

#endif // !LINE_H
