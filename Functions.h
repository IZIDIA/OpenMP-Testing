#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
int Adder(int begin, int end)
{
	int sum = NULL;
	for (int i = begin; i <= end; i++)
	{
		sum += i;
	}
	return sum;
}
#endif 