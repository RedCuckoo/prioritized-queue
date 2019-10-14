// prioritized-queue.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ListPriorQueue.h"
#include "Pair.h"
#include <list>
#include "List.h"
#include "VectorPriorQueue.h"
#include "TreePriorQueue.h"
#include "Circle.h"
#include "AVLTree.h"

int main()
{
	//VectorPriorQueue <int> a;
	//ListPriorQueue <int> a;
	//ListPriorQueue <Pair<int, unsigned int>> a;
	//PriorQueue <int> a;
	//AVLTree<Pair<int>> a;
	////TreePriorQueue<int> a;
	////AVLTree<int> a;
	//Pair<int, unsigned int> d = { 7,4 };
	//Pair<int, unsigned int> b = { 4,3 };
	//Pair<int, unsigned int> e = { 5,3 };
	//Pair<int, unsigned int> f = { 2,3 };
	//Pair<int, unsigned int> g = { 2,2 };
	//Pair<int, unsigned int> h = { 9,6 };
	//Pair<int, unsigned int> r = { 8,5 };
	//Pair<int, unsigned int> n = { 6,3 };
	//Pair<int, unsigned int> c = { 5,2 };
	//
	//a.push(c);
	//a.push(n);
	//a.push(r);
	//a.push(h);
	//a.push(g);
	//a.push(f);
	//a.push(e);
	//a.push(b);
	//a.push(d);
	//a.out(); std::cout << std::endl;

	Circle q(0, 0, 6);
	Pair<double, double> point = { 9,9 };
	Circle g(0, 0, 2);
	Line k(1,0,-9);
	Line p(1, 2, -2);
	Circle l = p.inverse(q);
	auto e = l.inverse(q);
	inversePoint(point, q);
	inversePoint(point, q);
	//g.reflectOverLine(q);
	//q.inverse(q);
	//auto e = p.inverse(q);
	//a.out();
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
