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

	a.push_back(3);
	a.push_back(5);
	a.push_back(7);
	a.push_back(2);
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
