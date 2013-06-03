// testbed.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <functional>
#include <iostream>
#include <vector>
#include <initializer_list>
using std::cout;
using std::cin;

void minMax(int (&arr)[5], int dim, int &min, int &max);



void traverse(int row, int col, std::function<void ()> func);
void adder();

class animal
{
public:
	animal();
private:
	int color;
};
int factorial_normal(int n)
{
	return (n==1) ? 1 :n*factorial_normal(n-1);
}
using std::endl;
int _tmain(int argc, _TCHAR* argv[])
{

//	std :: vector <std :: string> foo = std::initializer_list<std::string>("a", "b");
	const int dim = 5;
	int arr[dim] = {9, 13, 1, -4, 99};
	int min = 0, max = 0;

	//minMax(arr, dim, min, max);
	//cout << min << endl << max << endl;


	int row(1), col(7);
	traverse(row, col, [&] () { cout<< "test" << row; } );

		int end = 0;



	std::function<int (int)> factorial = [&factorial](int n) {
	return (n==1) ? 1 : n*factorial(n-1);
	};

	cout << factorial(4) << endl;

	cout <<factorial_normal(4) << endl;
		cin >> end;
	return 0;
}



void minMax(int (&arr)[5], int dim, int &min, int &max)
{

	int runningmin = arr[0], runningmax = arr[0];

	//for (int &i : arr)
	//{
	//	if (i < runningmin)
	//		runningmin = i;
	//	if (i > runningmax)
	//		runningmax = i;
	//}
	min = runningmin;
	max = runningmax;
}

void adder(int row, int col)
{
	row++; 
	col++;
}


void traverse(int row, int col, std::function<void ()> func)
{
	//if(row > 5)
	//	func(row, col);
	row = 99;
	if(col > 5)
		func();
	//if(row == 3)
	//	func();
}