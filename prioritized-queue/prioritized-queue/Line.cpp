#include "Circle.h"
#include "Line.h"	
#include "Pair.h"

Line::Line(Pair<double, double> fPoint, Pair<double, double> sPoint) {
	double x1 = fPoint.getVal(), x2 = sPoint.getVal(), y1 = fPoint.getPrior(), y2 = sPoint.getPrior();
	a = y2 - y1;
	b = x1 - x2;
	c = x2 * y1 - x1 * y2;
}

Pair<double, double> Line::intersection(const Circle& to_find) {
	/*
	{(x-x0)^2 + (y-y0)^2 = r^2
	{y = k*x + b
	*/
	std::vector<Pair<double, double>> intersectionPoints;
	double x = to_find.center.getVal(), y = to_find.center.getPrior(), radius = to_find.radius;


	if (b) {
		double slope = -a / b;
		double y_intersection = -c / b;
		//sets x value
		intersectionPoints = squareEquationSolver(slope * slope + 1, 2. * (slope * (y_intersection - y) - x), x * x + y_intersection * (y_intersection - 2. * y) + y * y - radius * radius);
		//std::vector<Pair<double, double>> intersectionPoints = squareEquationSolver(x, 8, 0);
	}
	else {
		//sets whole pair
		if (a) {
				//the dot is on the left from x = -c/a
				double d = radius * radius - (-c / a - x) * (-c / a - x);
				Pair<double, double> temp;
				temp.setVal(-c / a);
				if (d > 0) {
					temp.setPrior(y + sqrt(d));
					intersectionPoints.push_back(temp);
					temp.setPrior(y - sqrt(d));
					intersectionPoints.push_back(temp);
				}
				else if (d == 0) {
					temp.setPrior(y);
					intersectionPoints.push_back(temp);
				}
				else {

				}
		}
	}


	if (b){
		for (unsigned int i = 0; i < intersectionPoints.size(); i++) {
			intersectionPoints[i].setPrior((-a / b) * intersectionPoints[i].getVal() + -c / b);
		}
	}
	//TODO: change return value
	return to_find.center;
}

void Line::reflectOverLine(const Line& baseLine) {
	double a2 = baseLine.a, b2 = baseLine.b, c2 = baseLine.c;
	if (b2 && b) {
		double x0 = (c * b2 - c2 * b) / (a2 * b - a * b2);
		double y0 = (-a / b) * x0 - c / b;
		Pair<double, double> symetricNew = findSymmetricDot(baseLine, Pair<double, double>(x0 + 1, (-a / b) * x0 - c / b));
		double xs = symetricNew.getVal();
		double ys = symetricNew.getPrior();
		a = y0 - ys;
		b = xs - x0;
		c = x0 * ys - xs * y0;
	}
	else if (b && !b2) {
		b = -b;
	}
	else if (b2 && !b) {
		b = a;
		a = 0;
	}
	else {
		if (a && a2) {
			Pair<double, double> symmetricNew = findSymmetricDot(baseLine, Pair<double, double>(-c / a, 0));
			a = 1;
			c = -symmetricNew.getVal();
		}
	}
}

Circle Line::inverse(const Circle& baseCircle) {
	Pair<double, double> diamPoint;
	double x0 = baseCircle.center.getVal(), y0 = baseCircle.center.getPrior();
	diamPoint.setVal((b * b * x0 - a * c - a * b * y0) / (b * b + a * a));
	diamPoint.setPrior((-a / b) * diamPoint.getVal() - c / b);
	inversePoint(diamPoint, baseCircle);
	return Circle((x0 + diamPoint.getVal()) / 2, (y0 + diamPoint.getPrior()) / 2, sqrt((diamPoint.getVal() - x0) * (diamPoint.getVal() - x0) + (diamPoint.getPrior() - y0) * (diamPoint.getPrior() - y0)) / 2);
}