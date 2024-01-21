#pragma once
#include <cstdarg>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#ifndef Matrix_header.h

using namespace std;

class Object
{
public:
    //загрузка из текстовой строки
    virtual void get_String(const string& str) = 0;
    // загрзука в текстовую строку
    virtual string* put_String() const = 0;
    //получение идентификатора класса   
    virtual int get_ClassIdentifier() const = 0;
    //получение указателя на строку с именем объекта
    virtual const char* get_ClassName() const = 0;
    // создание динам копии объекта
    virtual Object* clone() const = 0;
};
class Matrix: public Object
{
private:
    int n;
    int m;
    int** mass;
    int row, col;
    friend ostream& operator<<(ostream& os, const Matrix& matrix);
    friend istream& operator>>(istream& os, Matrix& matrix);

public:
    Matrix();
    Matrix(int n, int m, int defaulValue);
    int& getelement();
    Matrix(int n, int m, ...);
    Matrix(const Matrix& other);
    ~Matrix();
    void fill_mass();
    void print_mass(int** mass, int n, int m);
    void delete_mass(int** mass, int m);
    void create_mass_1x(int** mass, int n, int m);
    void add_matrix(const Matrix& matrix2);
    void subs_matrix(const Matrix& matrix2);
    void mult_matrix(const Matrix& matrix2);
    void change(int n, int m, int date);
    bool comp_matrix(const Matrix& matrix2);
    void extend(const Matrix& matrix);

    Matrix operator+(const Matrix& matrix2);
    Matrix operator-(const Matrix& matrix2);
    bool operator==(const Matrix& matrix2);
    bool operator>(const Matrix& matrix2);
    bool operator<(const Matrix& matrix2);
    Matrix operator*(const Matrix& matrix2);
    Matrix operator=(const Matrix& matrix2);
    Matrix operator+=(const Matrix& matrix2);
    Matrix operator-=(const Matrix& matrix2);
    Matrix operator*=(const Matrix& matrix2);
    const int* operator [](int index) const;
    void convert_matrix();

    //загрузка из текстовой строки
    void get_String(const string& str) override
    {
        istringstream ss(str);
        string element;
        int n2=0, m2=0;
        ss >> n2 >> m2;
        if (n != n2 || m != m2)
        {
            n = n2;
            m = m2;
            extend(*this);
        }
        char ch;
        for (int i = 0; i < n2; i++)
        {
            for (int j = 0; j < m; j++)
            {
                ss >> ch;
                mass[i][j] = ch-'0';
            }
        }

    }
    // загрзука в текстовую строку
    string* put_String() const override 
    {
        ostringstream ss;// входящий поток
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                ss << static_cast<char>(mass[i][j]);
        }
        string* result = new string(ss.str());
        return result;
    }
    //получение идентификатора класса   
    int get_ClassIdentifier() const override
    {
        return 1;
    }
    //получение указателя на строку с именем объекта
    const char* get_ClassName() const override
    {
        return typeid(*this).name();
    }
    // создание динам копии объекта
    Object* clone() const override
    {
        return new Matrix(*this);
    }
};

class SimpleInteger : public Object {
private:
    int value;

public:
    SimpleInteger(int val) : value(val) {}

    void get_String(const string& str) override {
        value = stoi(str);
    }

    string* put_String() const override 
    {
        string str;
        str = char(value);
        return &str;
    }

    int get_ClassIdentifier() const override {
        return 2; 
    }

    const char* get_ClassName() const override {
        return typeid(*this).name();
    }

    Object* clone() const override {
        return new SimpleInteger(value);
    }
};
struct Object_StructureDate
{
    Object* mass[3];
};
#endif Matrix_header.h
