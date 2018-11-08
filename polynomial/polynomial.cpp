#include "polynomial.h"

void polynomial::Tidy(Node*& p)
{
	if (p)
	{
		if (p->next)
		{
			Tidy(p->next);
			if (p->next == nullptr && p->a == 0)
			{
				delete p;
				p = nullptr;
			}
		}
		else
		{
			if (p->a == 0)
			{
				delete p;
				p = nullptr;
			}
		}
	}
}

polynomial::polynomial()
{
	a0 = nullptr;
}


polynomial::~polynomial()
{
	while (a0!=nullptr)
	{
		Node* t = a0->next;
		delete a0;
		a0 = t;
	}
}

polynomial& polynomial::operator=(polynomial& p1)
{
	if (Degree() <= p1.Degree())
	{
		for (int i = 0; i < p1.Degree() - Degree(); i++)
		{
			Add(0);
		}
	}
	else
	{
		for (int i = 0; i < Degree() - p1.Degree(); i++)
		{
			Node* t = a0->next;
			delete a0;
			a0 = t;
		}
	}
	Node* c1, *c2;
	for (c1 = a0, c2 = p1.a0; c1 != nullptr; c1 = c1->next, c2 = c2->next)
	{
		c1->a = c2->a;
	}
	return *this;
}

polynomial polynomial::operator+(polynomial& p1)
{
	polynomial* p2;
	polynomial* sum = new polynomial;

	if (Degree() >= p1.Degree())
	{
		*sum = *this;
		p2 = &p1;
	}
	else
	{
		*sum = p1;
		p2 = this;
	}
	for (Node *c1 = sum->a0, *c2 = p2->a0; c2 != nullptr; c1 = c1->next, c2 = c2->next)
	{
		c1->a += c2->a;
	}

	sum->Tidy(sum->a0);
	return *sum;
}

polynomial polynomial::operator-(polynomial &p1)
{
	polynomial* p2;
	polynomial* sum = new polynomial;

	if (Degree() >= p1.Degree())
	{
		*sum = *this;
		p2 = &p1;
	}
	else
	{
		*sum = p1;
		p2 = this;
	}
	for (Node *c1 = sum->a0, *c2 = p2->a0; c2 != nullptr; c1 = c1->next, c2 = c2->next)
	{
		c1->a -= c2->a;
	}

	sum->Tidy(sum->a0);
	return *sum;
}

polynomial polynomial::operator*(double c)
{
	polynomial* sum = new polynomial;
	*sum = *this;
	Node* cursor = sum->a0;
	for (; cursor != nullptr; cursor = cursor->next)
		cursor->a *= c;
	return *sum;
}

polynomial polynomial::operator*(polynomial& p)
{
	polynomial *prod = new polynomial();
	int n = Degree() + p.Degree();
	for (int i = 0; i <= n; i++)
	{
		double r = 0;
		Node *c1 = a0;
		for (int j = 0; j <= i; j++)
		{
			try
			{
				r += (*this)[j]->a *p[i - j]->a;
			}
			catch (const char*)
			{}
		}
		prod->Add(r);
	}
	prod->Tidy(prod->a0);
	return *prod;
}

polynomial::Node* polynomial::operator[](int n)
{
	Node* c = a0;
	for (int i = 0; i < n && c != nullptr; i++, c = c->next);
	if (c)
		return c;
	else
		throw "null";

}

double polynomial::operator()(double x)
{
	if (a0)
	{
		double sum = a0->a;
		Node* cursor = a0->next;
		for (double x1 = x; cursor != nullptr; cursor = cursor->next, x1*=x)
		{
			if (cursor->a != 0)
			{
				sum += x1*cursor->a;
			}
		}
		return sum;
	}
	else
	{
		return 0.0;
	}
}

int polynomial::Degree()
{
	int k = -1, r = 0;
	Node* cursor = a0;
	bool in0 = true;
	for (; cursor != nullptr; cursor = cursor->next)
	{
		if (cursor->a == 0)
			r++;
		else
			if (in0)
			{
				k += r+1;
				r = 0;
			}
			else
				k++;
		in0 = cursor->a == 0;
	}
	return k;
}

void polynomial::Add(double v)
{
	Node* newnode = new Node(v);
	if (a0 == nullptr)
	{
		a0 = newnode;
	}
	else
	{
		Node* last;
		for (last = a0; last->next != nullptr; last = last->next);
		last->next = newnode;
	}
}

void polynomial::Derive(int k)
{

	if (k < Degree())
	{
		for (int p = 0; p < k; p++)
		{
			Node* tmp = a0->next;
			delete a0;
			a0 = tmp;
			for (int i = 1; tmp != nullptr; tmp = tmp->next, i++)
				tmp->a *= i;
		}
	}
	else
	{
		if (k>Degree())
		{
			this->~polynomial();
			a0 = new Node(0);
		}
		else
		{
			Node* last;
			for (last = a0; last->next != nullptr; last = last->next);
			double tmp = last->a;
			this->~polynomial();
			a0 = new Node(tmp);
		}
	}
}

polynomial& polynomial::Derived(int k)
{
	polynomial* diff = new polynomial;
	*diff = *this;
	diff->Derive(k);
	return *diff;
}

void polynomial::Integrate()
{
	(*this)[Degree()]->next = new Node(0);
	for (int i = Degree(); i >= 0; i--)
		(*this)[i]->next->a = ((*this)[i]->a) / (i + 1);
	a0->a = 111;
}

polynomial& polynomial::Integrated()
{
	polynomial* integ = new polynomial;
	*integ = *this;
	integ->Integrate();
	return *integ;
}

std::string polynomial::Print()
{
	using namespace std;
	if (a0 != nullptr)
	{
		string p = a0->a != 0 ? to_string(a0->a) :(a0->next==nullptr? "0":"");
		if (a0->next)
		{
			Node* cursor = a0->next;
			for (int k = 1; cursor != nullptr; cursor = cursor->next, k++)
			{
				if (cursor->a!=0)
				{
					p = p + (cursor->a > 0 ? "+" : "") + to_string(cursor->a) + (k > 1 ? "x^" + to_string(k) : "x");
				}
			}
		}
		return p;
	}
	else
	{
		return "NULL";
	}
}
