#ifndef DEMONSTRATION_H
#define DEMONSTRATION_H

#include <iostream>
#include "Pair.h"
#include <vector>
#include <string>
#include "Line.h"
#include "Circle.h"

Pair<int> randIntPair(unsigned int topVal = 100, unsigned int topPrior = 10, bool negativeValue = 1);
int randInt(unsigned int topVal, bool negativeValue = 0);
Pair<std::string> randString(unsigned int topSize = 30, unsigned int topPrior = 10);


template<class data_structure>
void fillRandInt(data_structure& cont, unsigned int size) {
	Pair<int> work_pair_int;
	
		for (unsigned int i = 0; i < size; i++) {
		work_pair_int = randIntPair();
		cont.push(work_pair_int);
		if (i != size - 1)
			std::cout << work_pair_int << ", ";
		else
			std::cout << work_pair_int;
	}
}

template<class data_structure>
void fillRandString(data_structure& cont, unsigned int size) {
	Pair<std::string> work_pair_string;

	for (unsigned int i = 0; i < size; i++) {
		work_pair_string = randString();
		cont.push(work_pair_string);
		if (i != size - 1)
			std::cout << work_pair_string << ", ";
		else
			std::cout << work_pair_string;
	}
}

void wait();
//
void demo();

template <class data_structure>
void show_int() {
	data_structure container;
	std::cout << "\nContainer of the given type created successfully\n\nPushing some random " <<"integer numbers\n";
	unsigned int size = rand() % 15;
	std::cout << size << " random numbers with random priority < 10 will be pushed to the queue with priority in the chosen configuration\n";
	wait();

	std::cout << "\nThese are the elements with their priorities before adding them to the queue:\n";

	fillRandInt<data_structure>(container, size);
	wait();
	std::cout << "\nThe elemets were pushed successfully, the queue looks like:\n";
	container.out();
	wait();
	std::cout << "The first element in the queue is ";
	if (!container.empty())
		std::cout << container.front();
	wait();
	std::cout << "\nThe last element in the queue is ";
	if (!container.empty())
		container.back();
	wait();
	std::cout << "\nLets pop an element from the queue and look at the first element again";
	if (!container.empty())
		container.pop();
	wait();
	std::cout << "\nThe first element in the queue is ";
	if (!container.empty()) 
		std::cout << container.front();
	wait();
	std::cout << "\nThe amount of elements in the queue is " << container.size();
	wait();
	std::cout << "\nChecking if the queue is empty: " << ((container.empty()) ? "true" : "false");
	wait();
	std::cout << "\nLets delete all the elements and check if the queue is empty again.";
	//container.out();
	while (!container.empty()) {
		container.pop();
	}
	wait();
	std::cout << "\n\nChecking if the queue is empty: " << ((container.empty()) ? "true\n" : "false\n");
	wait();
	std::cout << "Current demonstration was successful!\n";
}

template <class data_structure>
void show_string() {
	data_structure container;
	std::cout << "\nContainer of the given type created successfully\n\nPushing some random " <<"line of characters\n";
	unsigned int size = rand() % 15;
	std::cout << size << " random strings with random priority < 10 will be pushed to the queue with priority in the chosen configuration\n";
	wait();

	std::cout << "\nThese are the elements with their priorities before adding them to the queue:\n";

	fillRandString<data_structure>(container, size);
	wait();
	std::cout << "\nThe elements were pushed successfully, the queue looks like:\n";
	container.out();
	wait();
	std::cout << "The first element in the queue is ";
	if (!container.empty())
		std::cout << container.front();
	wait();
	std::cout << "\nThe last element in the queue is ";
	if (!container.empty()) 
		std::cout<<container.back();
	wait();
	std::cout << "\nLets pop an element from the queue and look at the first element again";
	if (!container.empty())
		container.pop();
	wait();
	std::cout << "\nThe first element in the queue is ";
	if (!container.empty())
		std::cout << container.front();
	wait();
	std::cout << "\nThe amount of elements in the queue is " << container.size();
	wait();
	std::cout << "\nChecking if the queue is empty: " << ((container.empty()) ? "true" : "false");
	wait();
	std::cout << "\nLets delete all the elements and check if the queue is empty again.";
	while (!container.empty()) {
		container.pop();
	}
	wait();
	std::cout << "\n\nChecking if the queue is empty: " << ((container.empty()) ? "true\n" : "false\n");
	wait();
	std::cout << "Current demonstration was successful!\n";
}

template<class data_structure>
void show_line() {
	std::cout << "\nLet's create and initialize the following lines:\n";
	wait();
	Line al(randInt(20,1), randInt(20, 1), randInt(20, 1));
	Line bl(randInt(20, 1), randInt(20, 1), randInt(20, 1));
	Line cl(randInt(20, 1), randInt(20, 1), randInt(20, 1));
	al.out(); std::cout << "\n";
	bl.out(); std::cout << "\n";
	cl.out(); std::cout << "\n";

	std::cout << "\nIn order to check inversion, lets create a simple Circle:";
	wait();
	Circle c(randInt(20, 1), randInt(20, 1), randInt(20, 1));
	c.out();


	std::cout << "\n\nChecking intersection of second and third lines, the point of intersection is: ";
	wait();
	Pair<double, double> temp_pair = bl.intersection(cl);
	temp_pair.out();

	std::cout << "\nThe point(s) of intersection between first line and a following circle: ";
	wait();
	std::vector<Pair<double, double>> temp_vect = al.intersection(c);
	for (unsigned int i = 0; i < temp_vect.size(); i++) {
		std::cout << temp_vect[i];
	}

	std::cout << "\n\nTo complete a check on a symmetrical reflection over line and inversing over circle, we will do these steps twice, as these operations are reversible\n";
	std::cout << "The result of reflecting second line over the first will be:";
	wait();
	bl.reflectOverLine(al);
	bl.out();
	std::cout << "\n\nLets reflect the same line again over the previous line, we should get the previous line:";
	wait();
	bl.reflectOverLine(al);
	bl.out();
	std::cout << "\n\nSame thing for the inversion, permorming it for the first time on the first line:";
	wait();
	Circle cans = al.inverse(c);
	cans.out();
	std::cout << "\n\nInversing the circle and getting back the line:";
	wait();
	al = cans.inverse(c);
	al.out();

	std::cout << "\n\nNow lets check the queue, assigning the first and third line priority 1, and second line priority 2\n";
	std::cout << "Initializing queue with priority and pushing element will create the following:";
	wait();
	data_structure container;
	Pair<Line> alp = { al,1 };
	Pair<Line> blp = { bl,2 };
	Pair<Line> clp = { cl,1 };
	container.push(alp);
	container.push(blp);
	container.push(clp);
	container.out();
	std::cout << "\nLet's remove an element:";
	wait();
	if (!container.empty())
		container.pop();
	container.out();
	std::cout << "\nLooking at the top element: ";
	if (!container.empty())
		std::cout << container.front();
	wait();

	std::cout << "\nLooking at the last element: ";
	if (!container.empty())
		std::cout << container.back();
	wait();

	std::cout << "\nQueue has " << container.size() << " elements";
	wait();
	std::cout << "\nIs it empty? - " << container.empty();
	wait();

	std::cout << "\nAnd after removing all elemements - ";
	while (!container.empty())
		container.pop();
	std::cout << container.empty();
	wait();

	std::cout << "\nCurrent demonstration was successful!\n";
	wait();
	//c.out();
	std::cout << "\n";
}

template<class data_structure>
void show_circle() {
	std::cout << "\nLet's create and initialize the following circles:\n";
	wait();
	Circle ac(randInt(20,1), randInt(20, 1), randInt(20, 1));
	Circle bc(randInt(20, 1), randInt(20, 1), randInt(20, 1));
	Circle cc(randInt(20, 1), randInt(20, 1), randInt(20, 1));
	ac.out(); std::cout << "\n";
	bc.out(); std::cout << "\n";
	cc.out(); std::cout << "\n";

	std::cout << "\nIn order to check intersection, lets create a line:";
	wait();
	Line l(randInt(20, 1), randInt(20, 1), randInt(20, 1));
	l.out();


	std::cout << "\n\nChecking intersection of second and third circle, the points of intersection are: ";
	wait();
	std::vector<Pair<double, double>> temp_pair = bc.intersection(cc);
	for (unsigned int i = 0; i < temp_pair.size(); ++i) {
		temp_pair[i].out();
	}

	std::cout << "\nThe point(s) of intersection between first circle and a created line: ";
	wait();
	std::vector<Pair<double, double>> temp_vect = ac.intersection(l);
	for (unsigned int i = 0; i < temp_vect.size(); i++) {
		std::cout << temp_vect[i];
	}

	std::cout << "\n\nTo complete a check on a symmetrical reflection over line and inversing over circle, we will do these steps twice, as these operations are reversible\n";
	std::cout << "The result of reflecting second circle over the line will be:";
	wait();
	bc.reflectOverLine(l);
	bc.out();
	std::cout << "\n\nLets reflect the same line again over the previous line, we should get the previous line:";
	wait();
	bc.reflectOverLine(l);
	bc.out();
	std::cout << "\n\nSame thing for the inversion, permorming it for the first time on the first circle, relatively to the third:";
	wait();
	Line lans = ac.inverse(cc);
	if (lans != Line())
		lans.out();
	else
		ac.out();
	std::cout << "\n\nInversing the circle and getting back the circle:";
	wait();
	if (lans == Line()) {
		ac.inverse(cc);
	}
	else {
		ac = lans.inverse(cc);
	}

	ac.out();

	std::cout << "\n\nNow lets check the queue, assigning the first and third line priority 1, and second line priority 2\n";
	std::cout << "Initializing queue with priority and pushing element will create the following:";
	wait();
	data_structure container;
	Pair<Circle> acp = { ac,1 };
	Pair<Circle> bcp = { bc,2 };
	Pair<Circle> ccp = { cc,1 };
	container.push(acp);
	container.push(bcp);
	container.push(ccp);
	container.out();
	std::cout << "\nLet's remove an element:";
	wait();
	if (!container.empty())
		container.pop();
	container.out();
	std::cout << "\nLooking at the top element: ";
	if (!container.empty())
		std::cout << container.front();
	wait();

	std::cout << "\nLooking at the last element: ";
	if (!container.empty())
		std::cout << container.back();
	wait();

	std::cout << "\nQueue has " << container.size() << " elements";
	wait();
	std::cout << "\nIs it empty? - " << container.empty();
	wait();

	std::cout << "\nAnd after removing all elemements - ";
	while (!container.empty())
		container.pop();
	std::cout << container.empty();
	wait();

	std::cout << "\nCurrent demonstration was successful!\n";
	wait();
	//c.out();
	std::cout << "\n";
}

#endif // !DEMONSTRATION_H
