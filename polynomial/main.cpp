#include "polynomial.h"
#include <iostream>

using namespace std;

void main()
{
	double x;
	cout << "P1: " << endl;
	polynomial P1;
	cin >> x;
	do
	{
		P1.Add(x);
		cin >> x;
	} 
	while (x!=100);

	cout << P1.Degree() << endl;
	cout << P1.Print() << endl;

	polynomial dP1 = P1.Derived();
	cout << "Derived: " << dP1.Print() << endl;

	polynomial iP1 = P1.Integrated();
	cout << "Integrated: " << iP1.Print() << endl;

	cout << "P2: " << endl;
	polynomial P2;
	cin >> x;
	do
	{
		P2.Add(x);
		cin >> x;
	} while (x != 100);

	cout << P2.Degree() << endl;
	cout << P2.Print() << endl;

	polynomial sum = P1 + P2;
	cout << "Sum: " << sum.Print() << endl;
	
	polynomial prod = P1*P2;
	cout << "Product: " << prod.Print() << endl;
	

	system("pause");
}