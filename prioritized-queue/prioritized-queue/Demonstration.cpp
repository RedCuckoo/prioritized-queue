#include "Demonstration.h"
#include "Circle.h"
#include "Line.h"
#include "Pair.h"
#include "ListPriorQueue.h"
#include "VectorPriorQueue.h"
#include "TreePriorQueue.h"
#include <iostream>
#include <string>

Pair<int> randIntPair(unsigned int topVal, unsigned int topPrior, bool negativeValue) {
	return Pair<int>(rand() % topVal - negativeValue * topVal / 2, rand() % topPrior + 1);
}

int randInt(unsigned int topVal, bool negativeValue) {
	return (rand() % topVal - negativeValue * topVal / 2);
}

Pair<std::string> randString(unsigned int topSize, unsigned int topPrior){
	std::string characters = "0123456789!@#$%^&*ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string ans;
	unsigned int size = rand() % topSize;

	for (unsigned int i = 0; i < size; i++) {
		ans.push_back(characters[randInt(characters.size())]);
	}
	
	return Pair<std::string>(ans, rand() % topPrior + 1);
}

void wait() {
	std::cin.clear();
	std::cin.get();
}
//
//template<data_structure>
//void show_int(unsigned int ds) {
//	data_structure container;
//	std::cout << "\nContainer of the given type created successfully\n\nPushing some random " << ((shInt) ? "integer numbers\n" : "string line\n");
//	unsigned int size = rand() % 15;
//	std::cout << size << " random " << ((shInt) ? "numbers" : "strings") << " with random priority < 10 will be pushed to the queue with priority in the chosen configuration\n";
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

void demo() {
	std::cout << "Welcome to the demonstration of the Lab #1\n\n";
	std::cout << "If demonstration stopped, press Enter to continue (unless something else specified)";
	while (true) {
		std::cout << "Choose which data type would you like to use:\n";
		std::cout << "1 - integer value\n";
		std::cout << "2 - string value\n";
		std::cout << "3 - Line\n";
		std::cout << "4 - Circle\n";
		std::cout << "Enter your choice, please: ";
		unsigned int ans1, ans2; std::cin >> ans1;
		std::cout << "\nChoose which implementation of the priority queue would you like to use:\n";
		std::cout << "1 - double linked list\n";
		std::cout << "2 - dynamic array\n";
		std::cout << "3 - self-balanced binary tree (AVL)\n";
		std::cout << "Enter your choice, please: ";
		std::cin >> ans2;

		if (ans1 == 1 && ans2 == 1)
			show_int<ListPriorQueue<Pair<int>>>();
		else if (ans1 == 2 && ans2 == 1)
			show_string<ListPriorQueue<Pair<std::string>>>();
		//else if (ans1 == 3 && ans2 == 1)
		//	show<ListPriorQueue<Pair<Line>>>(ans1);
		//else if (ans1 == 4 && ans2 == 1)
		//	show<ListPriorQueue<Pair<Circle>>>(ans1);
		else if (ans1 == 1 && ans2 == 2)
			show_int<VectorPriorQueue<Pair<int>>>();
		else if (ans1 == 2 && ans2 == 2)
			show_string<VectorPriorQueue<Pair<std::string>>>();
		//else if (ans1 == 3 && ans2 == 2)
		//	show<VectorPriorQueue<Pair<Line>>>(ans1);
		//else if (ans1 == 4 && ans2 == 2)
		//	show<VectorPriorQueue<Pair<Circle>>>(ans1);
		else if (ans1 == 1 && ans2 == 3)
			show_int<TreePriorQueue<Pair<int>>>();
		else if (ans1 == 2 && ans2 == 3)
			show_string<TreePriorQueue<Pair<std::string>>>();
		//else if (ans1 == 3 && ans2 == 3)
		//	show<TreePriorQueue<Pair<Line>>>(ans1);
		//else if (ans1 == 4 && ans2 == 3)
		//	show<TreePriorQueue<Pair<Circle>>>(ans1);
		else {

		}




		//Circle ac(2, 4, 10);
		//Circle bc(0, 0, 1);
		//Circle cc(-1, 3, -3);

		//Line al(2, 2, -1);
		//Line bl(-1, 9, -2);
		//Line cl(1, -3, 5);

		//Pair<Circle> acp = { ac, 3 };
		//Pair<Circle> bcp = { bc,2 };
		//Pair<Circle> ccp = { cc,2 };

		//Pair<Line> alp = { al,1 };
		//Pair<Line> blp = { bl,2 };
		//Pair<Line> clp = { cl,3 };

		//ListPriorQueue<Pair<Circle>> cp;
		//ListPriorQueue<Pair<Line>> lp;

		//cp.push(acp);
		//cp.push(bcp);
		//cp.push(ccp);

		//lp.push(alp);
		//lp.push(blp);
		//lp.push(clp);

		//cp.out();
		//lp.out();
	}
}