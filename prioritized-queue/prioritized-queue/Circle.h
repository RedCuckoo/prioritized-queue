/*!
	\file
	\brief Header file containing class Circle

	This file contains template definition and implementation of geometry figure, circle
*/

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Pair.h"
#include "Line.h"
#include <vector>

/*!
\brief A figure Circle
\details An implementation of the circle, given in a standart form: two points for center and radius
*/
class Circle {
private:
	//constuructor sets radius to positive value
	double radius;

	Pair<double, double> center;
	
	/*!
	\brief Center belonging check
	\details Check whether or not the center of the given Circle, lays on the current one
	\param [in] to_check A constant reference to the Circle which has to be checked
	\return True value if center of to_check lays on the current Circle and false value otherwise
	*/
	bool centerBelongToCircle(const Circle& to_check);

	/*!
	\brief Friended class Line
	\details Gives access to private fields of class Line
	*/
	friend class Line;

	/*!
	\brief Friended function of the inverse of the point
	\details Function inversePoint(Pair<double, double>&, const Circle&) gets access to the private field of the Circle
	*/
	friend void inversePoint(Pair<double, double>&, const Circle&);
public:
	/*!
	\brief Default constructor
	\details Creates an uninitialized object of class Circle, doesn't store any data, only for comparison
	*/
	Circle() = default;
	
	/*!
	\brief Constructor
	\detais Create an object from the given parametes
	\param [in] x The x coordinate of the center of the newly created Circle.
	\param [in] y The y coordinate of the center of the newly created Circle.
	\param [in] rad The radius of the newly created Cycle
	*/
	Circle(double x, double y, double rad) : radius((rad > 0) ? rad : -rad), center(Pair<double, double>(x, y)) {		}
	
	/*!
	\brief Searches points of intersection
	\details Looks for the points of intersection of the current circle and given line
	\param [in] to_find A constant reference to the Line, which intersection with the brother has to be found
	\return As the result of the search, returns a vector of none, one or two Pairs
	*/
	std::vector<Pair<double, double>> intersection(const Line& to_find);
	
	/*!
	\brief Reflect circle over the Line
	\details A symmetrical reflection of the Circle relatively to the provided Line
	\param [in] baseLine A constant refrence to the Line, relatively to which we have to do everything
	*/
	void reflectOverLine(const Line& baseLine);

	/*!
	\brief Find the inverse of the circle
	\details The inverse of the circle can be either a Circle or a Line, depending on the input value
	\param baseCircle A constant reference to the Circle, relatively to which we have to do the inverse.
	\return If the return value is Line(), then the answer is the Circle and current Circle is already changed.
	Otherwise, the current Circle will be equal to Circle() and the inverse of the given Circle will be a Line.
	*/
	Line inverse(const Circle& baseCircle);

	/*!
	\brief Overloaded equality operator
	\param [in] to_compare A constant reference to the Circle which has to be compared with current
	\return True value if they are equal and false value otherwise
	*/
	bool operator== (const Circle& to_compare);
};


#endif // !CIRCLE_H
