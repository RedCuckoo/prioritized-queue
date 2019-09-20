// prioritized-queue.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ListPriorQueue.h"
#include "Pair.h"
#include <list>
#include "List.h"

int main()
{
	//ListPriorQueue <int> a;
	//Pair<int, unsigned int> d = { 7,4 };
	//Pair<int, unsigned int> b = { 4,3 };
	//Pair<int, unsigned int> n = { 6,3 };
	//Pair<int, unsigned int> c = { 5,2 };
	//
	//a.add(n);
	//a.add(c);
	//a.add(d);
	//a.add(d);
	//a.add(b);
	//a.remove(d);
	//

	//a.out();

	List<int> a;
	a.push_back(4);
	a.push_back(6);
	a.insert((*a.begin())+1, 5);
	//a.push_back(3);
	a.out();
	std::list<int> k;
	auto f = k.begin();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
