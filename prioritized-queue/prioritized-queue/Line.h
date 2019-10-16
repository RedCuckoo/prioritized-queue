/*!
	\file
	\brief Header file containing class Line

	This file contains template definition and implementation of geometry figure, line
*/

#ifndef LINE_H
#define LINE_H

#include "Circle.h"
#include "Pair.h"
#include <vector>

/*!
\brief A figure Line
\details An implementation of the Line, provided with an equation in a standart form: a * x + b * y + c = 0
*/
class Line {
private:
	double a, b, c;
	
	/*!
	\brief Friended class Circle
	\details Gives access to private fields of class Circle
	*/
	friend class Circle;

	/*!
	\brief Friended function of the finding symmetric point
	\details Function findSymmetricDot(const Line&, const Pair<double, double>) gets access to the private field of the Line, because it need to use it in the function, when accepting it as a parameter.
	*/
	friend Pair<double, double> findSymmetricDot(const Line& baseLine, const Pair<double, double> dot);
public:
	/*!
	\brief Default constructor
	\details Creates an uninitialized object of class Circle, doesn't store any data, only for comparison
	*/
	Line() = default;

	/*!
	\brief Constructor
	\detais Create an object from the given parametes, following the equation a * x + b * y + c = 0
	\param [in] a_coef Coeficient near x
	\param [in] b_coef Coeficient near y
	\param [in] c_coef Coeficient without variable
	*/
	Line(double a_coef, double b_coef, double c_coef) : a(a_coef), b(b_coef), c(c_coef) {		}
	
	/*!
	\brief Constructor
	\details Create a Line from two points.
	*/
	Line(Pair<double, double>, Pair<double, double>);
	
	/*!
	\brief Intersect current Line with a provided Circle
	\details The function calculates points of intersection between an object of this class and a Circle.
	\param [in] to_find A Circle that this object intersects with
	\return 
	*/
	std::vector<Pair<double, double>> intersection(const Circle& to_find);

	/*!
	\brief Symmetrical reflection of the object over given Line
	\details Function finds a Line which is a symmetrical to the object over the given Line
	\param baseLine The Line over which the symmetrical object is being calculated
	*/
	void reflectOverLine(const Line& baseLine);

	/*!
	\brief Inverse of a Line
	\param [in] baseCircle A Circle of inversion
	\return A newly formed Circle. Circle() is returned, if the center of base Circle is laying on the Line.
	*/
	Circle inverse(const Circle& baseCircle);
};

#endif // !LINE_H

