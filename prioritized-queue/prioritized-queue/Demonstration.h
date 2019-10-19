#ifndef DEMONSTRATION_H
#define DEMONSTRATION_H

#include <iostream>
#include "Pair.h"
#include <vector>
#include <string>

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
	std::cout << "The first element in the queue is " << container.front();
	wait();
	std::cout << "\nThe last element in the queue is " << container.back();
	wait();
	std::cout << "\nLets pop an element from the queue and look at the first element again";
	container.pop();
	wait();
	std::cout << "\nThe first element in the queue is " << container.front();
	wait();
	std::cout << "\nThe amount of elements in the queue is " << container.size();
	wait();
	std::cout << "\nChecking if the queue is empty: " << ((container.empty()) ? "true" : "false");
	wait();
	std::cout << "\nLets delete all the elements and check if the queue is empty again.";
	container.out();
	while (!container.empty()) {
		container.pop();
	}
	wait();
	std::cout << "\n\nChecking if the queue is empty: " << ((container.empty()) ? "true\n" : "false\n");
	wait();
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
	std::cout << "The first element in the queue is " << container.front();
	wait();
	std::cout << "\nThe last element in the queue is " << container.back();
	wait();
	std::cout << "\nLets pop an element from the queue and look at the first element again";
	container.pop();
	wait();
	std::cout << "\nThe first element in the queue is " << container.front();
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
}


//
//template<class data_structure>
//void show_int_or_string(bool shInt = 1) {
//	data_structure container;
//	std::cout << "\nContainer of the given type created successfully\n\nPushing some random "<<((shInt) ? "integer numbers\n" : "string line\n");
//	unsigned int size = rand() % 15;
//	std::cout << size << " random "<<((shInt) ? "numbers" : "strings")<<" with random priority < 10 will be pushed to the queue with priority in the chosen configuration\n";
//
//	wait();
//	
//	std::cout << "\nThese are the elements with their priorities before adding them to the queue:\n";
//
//	(shInt) ? fillRandInt(container) : fillRandString(container);
//
//	wait();
//	std::cout << "\nThe elemets were pushed successfully, the queue looks like:\n";
//	container.out();
//	wait();
//	std::cout << "The first element in the queue is " << container.front();
//	wait();
//	std::cout << "\nThe last element in the queue is " << container.back();
//	wait();
//	std::cout << "\nLets pop an element from the queue and look at the first element again";
//	container.pop();
//	wait();
//	std::cout << "\nThe first element in the queue is " << container.front();
//	wait();
//	std::cout << "\nThe amount of elements in the queue is " << container.size();
//	wait();
//	std::cout << "\nChecking if the queue is empty: " << ((container.empty()) ? "true" : "false");
//	wait();
//	std::cout << "\nLets delete all the elements and check if the queue is empty again.";
//	while (!container.empty()) {
//		container.pop();
//	}
//	wait();
//	std::cout << "\n\nChecking if the queue is empty: " << ((container.empty()) ? "true\n" : "false\n");
//	wait();
//}
//
//
//
////template<class data_structure>
////void show(unsigned int ds) {
////	show_int_or_string<data_structure>(0);
////
////}
//
//
//void show_int(unsigned int ds);
#endif // !DEMONSTRATION_H
