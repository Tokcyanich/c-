#include <iostream>
#include "Matrix_header.h"
#include <cstdarg>
#include <cstdlib>
#include <vector>
using namespace std;

void Matrix::fill_mass() 
{
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				mass[i][j] = rand() % 30;
			}
		}
	}
}

void Matrix::print_mass(int** mass, int n, int m)
{
	cout << "Matrix:" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << mass[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Matrix::delete_mass(int** mass, int m)
{
	for (int i = 0; i < m; i++)
	{
		delete[]mass[i];
	}
	delete[] mass;
}

void Matrix::create_mass_1x(int** mass, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		mass[i] = new int[m];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			mass[i][j] = 0;
		}
	}
}

Matrix::Matrix()
{
	this->n = 0;
	this->m = 0;
	this->col = 0;
	this->row = 0;
	this->mass = nullptr;
}
Matrix::Matrix(int n, int m, ...)
{
	this->n = n;
	this->m = m;
	mass = new int* [n];
	create_mass_1x(mass, n, m);
	va_list args; // создаем список
	va_start(args, m); // обрабатываем список до последнего аргумента
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			mass[i][j] = va_arg(args, int);// преобразуем каждый элемент из спика
		}
	}
	va_end(args); // ощищвем ресурсы
}
Matrix::Matrix(int n, int m, int defaultValue)
{
	this->n = n;
	this->m = m;
	mass = new int* [n];
	create_mass_1x(mass, n, m);
}
Matrix::Matrix(const Matrix& other)// kopiya
{
	n = other.n;
	m = other.m;
	mass = new int* [n];
	for (int i = 0; i < n; i++)
	{
		mass[i] = new int[m];
		for (int j = 0; j < m; j++)
		{
			mass[i][j] = other.mass[i][j];
		}
	}

}
Matrix::~Matrix()// destruktor
{
	delete_mass(mass, m);
}

int& Matrix::getelement()
{
	row = 0;
	col = 0;
	cout << "Vvedite nomer yacheyki: ";
	cin >> row >> col;
	if ((row >= 0 && col >= 0) && (row < n && col < m))
	{
		return mass[row][col];
	}
	else
	{
		cout << "durak" << endl;
		exit(2);
	}
}
void Matrix::extend(const Matrix& matrix2)
{
	int** mass_extend = new int* [n];
	create_mass_1x(mass_extend, n, matrix2.m);
	for (int i = 0; i < n; i++)
	{
		delete[]mass[i];
	}
	mass = mass_extend;
	m = matrix2.m;
}
void Matrix::add_matrix(const Matrix& matrix2)
{
	if (matrix2.m == m && matrix2.n == n)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				mass[i][j] += matrix2.mass[i][j];
			}
		}
	}
	else
	{
		cout << " Raznie matrici" << endl;
		exit(1);
	}
}
void Matrix::subs_matrix(const Matrix& matrix2)
{
	if (matrix2.m == m && matrix2.n == n)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				mass[i][j] -= matrix2.mass[i][j];
			}
		}
	}
	else
	{
		cout << " Raznie matrici" << endl;
		return;
	}
	print_mass(mass, n, m);
}
void Matrix::mult_matrix(const Matrix& matrix2)
{
	Matrix matrix_kopy = *this; // Matrix matrix_kopy(*this),  matrix2{};
	int sum = 0;
	if (m != matrix2.n)
	{
		cout << "Vvedite novuy matrixe m!=n" << endl;
		return;
	}
	else if (matrix2.m == m && matrix2.n == n)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				for (int k = 0; k < m; k++)
				{
					sum += matrix_kopy.mass[j][k] * matrix2.mass[k][j];
				}
				mass[i][j] = sum;
				sum = 0;
			}
		}
	}
	else
	{

		extend(matrix2);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				for (int k = 0; k < matrix2.n; k++)
				{
					mass[i][j] += matrix_kopy.mass[i][k] * matrix2.mass[k][j];
				}
			}
		}
	}
}
void Matrix::change(int a, int b, int date)
{
	if (a < this->n && a >= 0 && b < this->m && b >= 0)
	{
		mass[a][b] = date;
	}
	else
	{
		cout << "Pole ne cushestvuet" << endl;
	}
}
bool Matrix::comp_matrix(const Matrix& matrix2)
{

	if (matrix2.n == n && matrix2.m == m)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (mass[i][j] != matrix2.mass[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

ostream& operator<<(ostream& os, const Matrix& matrix)
{
	os <<"Matrix: " << endl;
	for (int i = 0; i < matrix.n; i++)
	{
		for (int j = 0; j < matrix.m; j++)
		{
			os << matrix.mass[i][j] << " ";
		}
		cout << endl;
	}
	return os;
}
istream& operator>>(istream& os, Matrix& matrix)
{
	cout << "¬ведите размеры матрицы (n m): ";
	os >> matrix.n >> matrix.m;
	matrix.mass = new int* [matrix.n];
	for (int i = 0; i < matrix.n; i++)
	{
		matrix.mass[i] = new int[matrix.m];
		for (int j = 0; j < matrix.m; j++)
		{
			cout << "¬ведите элемент [" << i << "][" << j << "]: ";
			os >> matrix.mass[i][j];
		}
	}
	return os;
}
Matrix Matrix:: operator+(const Matrix& matrix2)
{
	Matrix result(*this);
	result.add_matrix(matrix2);
	return result;
}
Matrix Matrix::operator-(const Matrix& matrix2)
{
	Matrix result(*this);
	result.subs_matrix(matrix2);
	return result;
}
bool Matrix::operator==(const Matrix& matrix2)
{
	Matrix result(*this);
	bool res = result.comp_matrix(matrix2);
	if (res == true)
	{
		return true;
	}
	else
	{
		return false;
	}

}
bool Matrix::operator>(const Matrix& matrix2)
{
	return mass[0][0] > matrix2.mass[0][0];
}
bool Matrix::operator<(const Matrix& matrix2)
{
	return mass[0][0] < matrix2.mass[0][0];
}
Matrix Matrix::operator*(const Matrix& matrix2)
{
	Matrix result(*this);
	result.mult_matrix(matrix2);
	return result;
}
Matrix Matrix::operator=(const Matrix& matrix2)
{
	if (n == matrix2.n && m == matrix2.m)
	{
		if (this != &matrix2)
		{
			n = matrix2.n;
			m = matrix2.m;
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					this->mass[i][j] = matrix2.mass[i][j];
				}
			}
		}
	}
	return *this;
}
Matrix Matrix::operator+=(const	 Matrix& matrix2)
{
	add_matrix(matrix2);
	return *this;
}
Matrix Matrix::operator-=(const Matrix& matrix2)
{
	this->subs_matrix(matrix2);
	return *this;
}
Matrix Matrix::operator*=(const Matrix& matrix2)
{
	this->mult_matrix(matrix2);
	return *this;
}


const int* Matrix::operator[](int index) const
{
	return mass[index]; // двойное индексирование
}
void Matrix::convert_matrix()
{
	double** convert_mass=new double*[n];
	for (int i = 0; i < this->n; i++) 
	{
		convert_mass[i] = new double[m];
		for (int j = 0; j < this->m; j++) 
		{
			convert_mass[i][j] = static_cast<double>(this->mass[i][j]); // приведение типа на этапе компил€ции,безопасность)
		}
	}
}

