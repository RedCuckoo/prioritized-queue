#include "Circle.h"
#include "Line.h"	
#include "Pair.h"
#include "Math.h"
#include <vector>


/*!
\param [in] fPoint One of the points, which form a Line
\param [in] sPoint Another of the points, which form a Line
*/
Line::Line(Pair<double, double> fPoint, Pair<double, double> sPoint) {
	double x1 = fPoint.getVal(), x2 = sPoint.getVal(), y1 = fPoint.getPrior(), y2 = sPoint.getPrior();
	a = y2 - y1;
	b = x1 - x2;
	c = x2 * y1 - x1 * y2;
}

/*!
This function uses already defined and implemented function, from the class of Circle.
*/
std::vector<Pair<double, double>> Line::intersection(const Circle& to_find) {
	Circle copy = to_find;
	return copy.intersection(*this);
}

/*!
The function checks, if the lines aren't in the form of x = const.
If they are not, the function will find the intersection points, choose a point which is not on the intersection and return a Line out of two points.
Also some trivial cases are included to prevent division on 0.
*/
void Line::reflectOverLine(const Line& baseLine) {
	double a2 = baseLine.a, b2 = baseLine.b, c2 = baseLine.c;
	if (b2 && b) {
		double x0, y0, xs, ys;
		
		if (!a && !a2) {
			x0 = 0;
		}
		else {
			x0 = (c * b2 - c2 * b) / (a2 * b - a * b2);
		}

		y0 = (-a / b) * x0 - c / b;
		Pair<double, double> symetricNew = findSymmetricDot(baseLine, Pair<double, double>(x0 + 1, (-a / b) * x0 - c / b));
		
		xs = symetricNew.getVal();
		ys = symetricNew.getPrior();
		
		if (!a && !a2) {
			symetricNew = findSymmetricDot(baseLine, Pair<double, double>(x0, y0));
			x0 = symetricNew.getVal();
			y0 = symetricNew.getPrior();
		}

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
		//!b && !b2
		if (a && a2) {
			Pair<double, double> symmetricNew = findSymmetricDot(baseLine, Pair<double, double>(-c / a, 0));
			a = 1;
			c = -symmetricNew.getVal();
		}
	}
}

/*!
If the center of the base Circle doesn't lay on the Line, the inversion of the Line will be a Circle.
The center of the base Circle will lay on the newly formed Circle. 

If the center of the base Circle lays on the Line, the inversion of the Line will be Line itself. 

The function calculates the closes point of the newly formed Circle to the Line, following the calculation on the center and radius relatively.
*/
Circle Line::inverse(const Circle& baseCircle) {
	Pair<double, double> diamPoint;
	double x0 = baseCircle.center.getVal(), y0 = baseCircle.center.getPrior();
	diamPoint.setVal((b * b * x0 - a * c - a * b * y0) / (b * b + a * a));
	diamPoint.setPrior((-a / b) * diamPoint.getVal() - c / b);
	inversePoint(diamPoint, baseCircle);
	return Circle((x0 + diamPoint.getVal()) / 2, (y0 + diamPoint.getPrior()) / 2, sqrt((diamPoint.getVal() - x0) * (diamPoint.getVal() - x0) + (diamPoint.getPrior() - y0) * (diamPoint.getPrior() - y0)) / 2);
}