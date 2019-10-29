/*!
	\file
	\brief Header file containing class Line

	This file contains template definition and implementation of geometry figure, line
*/

#ifndef LINE_H
#define LINE_H

#include "Circle.h"
#include "..//priority_queue_data_structure/data_structures/Pair.h"
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
	\brief Friended operator<<
	\details Allows to output information with the stream
	*/
	friend std::ostream& operator<<(std::ostream& out, const Line& to_out);

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
	
	Line(Pair<double, double>, Pair<double, double>);
	Line(const Line& to_copy) : a(to_copy.a), b(to_copy.b), c(to_copy.c) {		}

	std::vector<Pair<double, double>> intersection(const Circle& to_find);
	std::vector<Pair<double, double>> intersection(const Line& to_find);
	void reflectOverLine(const Line& baseLine);
	Circle inverse(const Circle& baseCircle);

	bool operator==(const Line& to_compare) const;
	bool operator!=(const Line& to_compare) const;

	void out();
};

/*!
\brief Operator<<
\detail Allows to output information with the stream
\param out Stream which is defined automatically, has to be ostream or inherited streams
\param to_out This parameter is passed on the right of "<<", not changeble, the reference to the Line that has to be outputted
\return Reference to the ostream, to allow continous streaming
*/
inline std::ostream& operator<<(std::ostream& out_stream, const Line& to_out) {
	std::cout << to_out.a << " * x + " << to_out.b << " * y + " << to_out.c << " = 0";
	return out_stream;
}

#endif // !LINE_H
