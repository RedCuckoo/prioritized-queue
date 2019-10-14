#include "Circle.h"
#include "Pair.h"
#include <vector>

//TODO:add separate file for technical functions
std::vector<Pair<double, double>> squareEquationSolver(double a, double b, double c) {
	double d = b * b - 4 * a * c;
	std::vector<Pair<double, double>> ans;
	if (d > 0) {
		Pair<double, double> p1, p2;
		p1.setVal((-b + sqrt(d)) / (2 * a));
		p2.setVal((-b - sqrt(d)) / (2 * a));
		ans.push_back(p1);
		ans.push_back(p2);
	}
	else if (d == 0) {
		Pair<double, double> p;
		p.setVal(-b / (2 * a));
		ans.push_back(p);
	}
	else {

	}
	return ans;
}

Pair<double, double> findSymmetricDot(const Line& baseLine, const Pair<double, double> dot) {
	double a = baseLine.a, b = baseLine.b, c = baseLine.c, x = dot.getVal(), y = dot.getPrior();
	Pair<double, double> ans;
	if (b) {
		double slope = -a / b, y_intersection = -c / b;
		ans.setVal(2 * ((slope * (y_intersection - y) - x) / (-slope * slope - 1)) - x);
		ans.setPrior(2 * slope * (((y_intersection - y) * slope - x) / (-slope * slope - 1)) + 2 * y_intersection - y);
	}
	else {
		//x = const
		if (a) {
			ans.setVal(2 * (-c / a) - x);
			ans.setPrior(y);
		}
	}
	return ans;
}

void inversePoint(Pair<double, double>& to_inverse, const Circle& baseCircle) {
	double x = to_inverse.getVal(), y = to_inverse.getPrior(), x0 = baseCircle.center.getVal(), y0 = baseCircle.center.getPrior(), r = baseCircle.radius;
	if (x != x0 || y != y0) {
		to_inverse.setVal(x0 + ((r * r * (x - x0)) / ((x - x0) * (x - x0) + (y - y0) * (y - y0))));
		to_inverse.setPrior(y0 + ((r * r * (y - y0)) / ((x - x0) * (x - x0) + (y - y0) * (y - y0))));
	}
}

std::vector<Pair<double, double>> Circle::intersection(const Line& to_find) {
	/*
	{(x-x0)^2 + (y-y0)^2 = r^2
	{y = k*x + b
	*/

	double a = to_find.a, b = to_find.b, c = to_find.c;

	std::vector<Pair<double, double>> intersectionPoints;
	if (b) {
		double slope = -a / b;
		double y_intersection = -c / b;
		intersectionPoints = squareEquationSolver(slope * slope + 1, 2. * (slope * (y_intersection - center.getPrior()) - center.getVal()), center.getVal() * center.getVal() + y_intersection * (y_intersection - 2. * center.getPrior()) + center.getPrior() * center.getPrior() - radius * radius);
	}
	else {
		//x = -c/a
			//the dot is on the left from x = -c/a
		if (a) {
			double d = radius * radius - (-c / a - center.getVal()) * (-c / a - center.getVal());
			Pair<double, double> temp;
			temp.setVal(-c / a);
			if (d > 0) {
				temp.setPrior(center.getPrior() + sqrt(d));
				intersectionPoints.push_back(temp);
				temp.setPrior(center.getPrior() - sqrt(d));
				intersectionPoints.push_back(temp);
			}
			else if (d == 0) {
				temp.setPrior(center.getPrior());
				intersectionPoints.push_back(temp);
			}
			else {

			}
		}
	}

	if (b) {
		for (unsigned int i = 0; i < intersectionPoints.size(); i++) {
			intersectionPoints[i].setPrior((-a / b) * intersectionPoints[i].getVal() + (-c / b));
		}
	}

	//TODO: change return value
	return intersectionPoints;
}

void Circle::reflectOverLine(const Line& baseLine) {
	center = findSymmetricDot(baseLine, center);
}

Line Circle::inverse(const Circle& baseCircle) {
	//not the same
	double x = center.getVal(), y = center.getPrior(), x0 = baseCircle.center.getVal(), y0 = baseCircle.center.getPrior();
	//diameter dots on the circle	

	if (*this == baseCircle)
		return Line();

	std::vector<Pair<double, double>> diamPoints;

	if (this->centerBelongToCircle(baseCircle)) {
		//the answer will be line
		Pair<double, double> linePoint1 = { 2 * x - x0, 2 * y - y0 };
		Pair<double, double> linePoint2 = { x + radius, y };

		if (linePoint2 == baseCircle.center || linePoint2 == linePoint1) {
			linePoint2.setVal(x);
			linePoint2.setPrior(y + radius);
		}

		inversePoint(linePoint1, baseCircle);
		inversePoint(linePoint2, baseCircle);
		*this = Circle();
		return Line(linePoint1, linePoint2);
	}

	if (this->center == baseCircle.center) {
		//same center but different radius
		diamPoints = this->intersection(Line(y - y0, x0 - x - radius, (x + radius) * y0 - x0 * y));
	}
	else {
		diamPoints = this->intersection(Line(y - y0, x0 - x, x * y0 - x0 * y));
	}

	for (unsigned int i = 0; i < diamPoints.size(); ++i) {
		inversePoint(diamPoints[i], baseCircle);
	}

	x0 = diamPoints[0].getVal();
	y0 = diamPoints[0].getPrior();
	x = diamPoints[1].getVal();
	y = diamPoints[1].getPrior();
	radius = sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0)) / 2;
	center.setVal((x + x0) / 2);
	center.setPrior((y + y0) / 2);
	return Line();
}

bool Circle::operator==(const Circle& to_compare) {
	return (center == to_compare.center && radius == to_compare.radius) ? true : false;
}

bool Circle::centerBelongToCircle(const Circle& to_check) {
	double x0 = to_check.center.getVal(), y0 = to_check.center.getPrior(), x = center.getVal(), y = center.getPrior();
	return ((x0 - x) * (x0 - x) + (y0 - y) * (y0 - y) == radius * radius) ? true : false;
}

