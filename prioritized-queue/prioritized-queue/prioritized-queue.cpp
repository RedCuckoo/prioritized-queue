// prioritized-queue.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ListPriorQueue.h"
#include "Pair.h"
#include <list>
#include "List.h"
#include "VectorPriorQueue.h"
#include "AVLTree.h"

int main()
{
	//VectorPriorQueue <int> a;
	//ListPriorQueue <int> a;
	//PriorQueue <int> a;
	//AVLTree<Pair<int, unsigned int>> a;
	AVLTree<int> a;
	Pair<int, unsigned int> d = { 7,4 };
	Pair<int, unsigned int> b = { 4,3 };
	Pair<int, unsigned int> n = { 6,3 };
	Pair<int, unsigned int> c = { 5,2 };
	//a.push(3);
	//a.push(7);
	//a.push(8);
	//a.push(9);
	//a.push(10);

	//for (size_t i = 0; i < 5; ++i) {
	//	a.push(i);
	//	a.out();
	//	std::cout << std::endl;
	//}
	//a.out();
	a.push(1);
	a.push(2);
	a.push(3);
	a.push(4);
	a.push(5);
	a.push(6);
	//a.out(); std::cout << std::endl;
	//a.push(5);
	//a.push(d);
	//a.push(n);
	//a.push(c);
	//a.push(b);
	//a.push(c);
	a.out();

	//a.push(n);
	//a.push(c);
	//a.push(d);
	//a.push(d);
	//a.push(b);
	//a.pop();


	//a.out();
	//std::cout << "\n";
	//a.front().out();
	//a.back().out();

	} 

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to push/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > push New Item to create new code files, or Project > push Existing Item to push existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
