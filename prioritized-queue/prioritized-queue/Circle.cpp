#include "Circle.h"
#include "Pair.h"
#include <vector>
#include "Math.h"

/*!
In case of coeficient near y not equal to 0, the function will rewrite the equation to the slope form ( y = k*x + l).
Then, we can substitute y in the equation of the circle ( (x-x0)^2 + (y-y0)^2 = r^2 ).
As the result, we'll need to solve the following kvadratic equation: ( k^2 + 1 ) * x^2 + 2 * ( k * (l - y0) - x0 ) * x + x0^2 + l * ( l - 2 * y0) + y0^2 - r^2.
Searched points will be intersection points, which the function will return.

Otherwise if the coeficient near y is equal to 0, the function will subtitute x in the equation of the circle to x = - c / a.
The formula for y will be: y = y0 + sqrt ( r^2 - ( - c/ a - x0)^2 ).
*/
std::vector<Pair<double, double>> Circle::intersection(const Line& to_find) {
	double a = to_find.a, b = to_find.b, c = to_find.c;

	std::vector<Pair<double, double>> intersectionPoints;
	if (b) {
		double slope = -a / b;
		double y_intersection = -c / b;
		intersectionPoints = squareEquationSolver(slope * slope + 1, 2. * (slope * (y_intersection - center.getPrior()) - center.getVal()), center.getVal() * center.getVal() + y_intersection * (y_intersection - 2. * center.getPrior()) + center.getPrior() * center.getPrior() - radius * radius);
	}
	else {
		//x = -c/a
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

	return intersectionPoints;
}

std::vector<Pair<double, double>> Circle::intersection(const Circle& to_find) {
	double x1 = center.getVal(), y1 = center.getPrior(), x2 = to_find.center.getVal(), y2 = to_find.center.getPrior();
	return intersection(Line(-2 * x2, -2 * y2, x2 * x2 + y2 * y2 + radius * radius - to_find.radius * to_find.radius));

}

/*!
Symmetry of the circle relatively to the Line, will be a Circle with the same radius but with the center in the symmetrical to the old center point.
*/
void Circle::reflectOverLine(const Line& baseLine) {
	center = findSymmetricDot(baseLine, center);
}

/*!
The inversion occurs over the Circle, in the way,
that each point inverses in such point, that if P is the old point, P` - inversed, r - radius, then:
OP * OP` = r^2.
This function is inversing a Circle.

If given Circle is the same as the base Circle, then the Circle will inverse into itself.

If center of the base Circle lays on the Circle which is being inversed, then the answer will be a Line, which doesn't belong to the center.
In order to do this, the function calculates the opposite to the center of the base Circle point (which lays on the provided Circle).
Then this point is being inversed, it will be a point on the perpendicular line to searched Line.
A next step is to take a random point, not equal to the mentioned above, inverse it and return a Line from the equation of two points.

If center of the base Circle doesn't belong to the provided Circle, we check if the centers aren't the same.
If they are, we find an intersection between a Circle and a Line calculated from the center point and some side point.
Otherwise, the Line is calculated between two centers.

The next step is to inversed the points which we found (two points that lie on the opposite sides of diameter).
And finaly we can calculate a center of inversed Circle as the midpoint between them.
The radius is a half distance between them.
*/
Line Circle::inverse(const Circle& baseCircle) {
	double x = center.getVal(), y = center.getPrior(), x0 = baseCircle.center.getVal(), y0 = baseCircle.center.getPrior();
	
	if (*this == baseCircle)
		return Line();

	std::vector<Pair<double, double>> diamPoints;

	if (this->centerBelongToCircle(baseCircle)) {
		//the answer will be line
		Pair<double, double> linePoint1 = { 2 * x - x0, 2 * y - y0 };
		Pair<double, double> linePoint2 = { x + radius, y };

		//change point
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

bool Circle::operator==(const Circle& to_compare) const {
	return (center == to_compare.center && radius == to_compare.radius) ? true : false;
}

bool Circle::operator!=(const Circle& to_compare) const {
	return (center != to_compare.center || radius != to_compare.radius) ? true : false;
}

bool Circle::centerBelongToCircle(const Circle& to_check) {
	double x0 = to_check.center.getVal(), y0 = to_check.center.getPrior(), x = center.getVal(), y = center.getPrior();
	return ((x0 - x) * (x0 - x) + (y0 - y) * (y0 - y) == radius * radius) ? true : false;
}

void Circle::out() {
	std::cout << "(x - " << center.getVal() << ")^2 + (y - " << center.getPrior() << ")^2 = " << radius << "^2";
}