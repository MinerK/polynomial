#pragma once
#include <iostream>
#include <string>

class polynomial
{
private:
	struct Node
	{
		double a;
		Node* next;
		Node(double z)
		{
			a = z;
			next = nullptr;
		}
	};
	Node* a0 = nullptr;

	void Tidy(Node*&);

public:
	polynomial();
	~polynomial();

	polynomial& operator=(polynomial&);
	polynomial operator+(polynomial&);
	polynomial operator-(polynomial&);
	polynomial operator*(double);
	polynomial operator*(polynomial&);
	double operator[](int);

	double operator()(double);

	int Degree();

	void Add(double);

	void Derive(int=1);
	polynomial& Derived(int = 1);

	void Integrate();
	polynomial& Integrated();

	std::string Print();


};

