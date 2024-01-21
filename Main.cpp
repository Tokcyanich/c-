#include <iostream>
#include <locale.h>
#include <typeinfo>
#include "Matrix_header.h"
#include "List_header.h"
#include <string>

using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	Matrix matr1(2, 2, 4, 3, 2, 1);
	Matrix matr2(2, 2, 1, 2, 3, 4);
	SimpleInteger number1 = 5;
	
	Object_StructureDate obj;
	obj.mass[0] = &matr1;
	obj.mass[1] = &matr2;
	obj.mass[2] = &number1;
	for (int i = 0; i < 3; i++)
	{
		cout<<obj.mass[i]->get_ClassIdentifier();
		cout << endl;
	}

}