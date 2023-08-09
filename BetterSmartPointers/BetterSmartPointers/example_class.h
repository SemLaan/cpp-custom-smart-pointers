#pragma once
#include <iostream>

class Example
{
private:
	int m_var1;
	int* m_pVar2;
public:
	Example()
		: m_var1(0), m_pVar2(new int(5))
	{}

	Example(int a)
		: m_var1(a), m_pVar2(new int(5))
	{}

	~Example()
	{
		delete m_pVar2;
	}


	void PrintVars()
	{
		std::cout << "Var1: " << m_var1 << "\nDereferenced Var2: " << *m_pVar2 << "\n";
	}
};