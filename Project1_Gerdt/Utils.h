#pragma once
#include <iostream>
using namespace std;
template <typename T>
T GetCorrectNumber(T min, T max)
{
	T a;
	while ((cin >> a).fail() || a < min || a > max || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Type number (" "from" << " " << min << " " << "to" << " " << max << "): ";
	}
	return a;
}