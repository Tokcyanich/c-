#pragma once
#include <iostream>
#include <fstream>
#include "Matrix_header.h"

#ifndef List_header.h
using namespace std;

template<typename T>
class List
{
public:
	List();
	~List();
	// ����� ������
	friend ostream& operator<<(ostream& os, const List<T>& list) 
	{
		Node<T>* current = list.head;
		while (current != nullptr)
		{
			os << *(current->data) << " ";  
			current = current->pNext;
		}
		return os;
	}

	// ���������� ������ �������
	friend istream& operator>>(istream& is, List<T>& list) 
	{
		T* temp=new T()	;// ����� ������������ ������ 
		is >> *temp;// �������� ������� ������
		list.push_back(temp);
		return is;
	}

	//�������� ������� �������� � ������
	void pop_front();

	//���������� �������� � ����� ������
	void push_back(T* data);

	// �������� ������
	void clear();

	// �������� ���������� ��������� � ������
	int GetSize() { return Size; }

	// ���������� ����� ������� 
	Matrix* operator[](const int index);

	//���������� �������� � ������ ������
	void push_front(T* data);

	//���������� �������� � ������ �� ���������� �������
	void insert(T* data, int index);

	//�������� �������� � ������ �� ���������� �������
	void removeAt(int index);

	//�������� ���������� �������� � ������
	void pop_back();

	// ����� �������������
	void serch_max();

	// ������ ������������
	void serch_min();

	// ���������� �� ������
	void selection_sort_list();

private:
	template<typename T>
	class Node
	{
	public:
		Node* pNext;
		T* data;

		Node(T* data = T(), Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};
	int Size;
	Node<T>* head;
};
//  Lister_header.impl   *.inl
template<typename T>
List<T>::List()
{
	Size = 0;
	head = nullptr;
}


template<typename T>
List<T>::~List()
{
	clear();
}


template<typename T>
void List<T>::pop_front()
{
	Node<T>* temp = head;

	head = head->pNext;

	delete temp;

	Size--;

}

template<typename T>
void List<T>::push_back(T* data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T>* current = this->head;

		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node<T>(data);

	}

	Size++;
}

template<typename T>
void List<T>::clear()
{
	while (Size)
	{
		pop_front();
	}
}

template<typename T>
Matrix* List<T>::operator[](const int index)
{
	int counter = 0;

	Node<T>* current = this->head;

	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
	return nullptr;
}

template<typename T>
void List<T>::push_front(T* data)
{
	head = new Node<T>(data, head);
	Size++;
}

template<typename T>
void List<T>::insert(T* data, int index)
{

	if (index == 0)
	{
		push_front(data);
	}
	else
	{
		Node<T>* previous = this->head;

		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* newNode = new Node<T>(data, previous->pNext);

		previous->pNext = newNode;

		Size++;
	}
}

template<typename T>
void List<T>::removeAt(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}


		Node<T>* toDelete = previous->pNext;

		previous->pNext = toDelete->pNext;

		delete toDelete;

		Size--;
	}

}

template<typename T>
void List<T>::pop_back()
{
	removeAt(Size - 1);
}

template<typename T>
void List<T>::serch_max()
{
	if (head == nullptr)
	{
		cout << "������ ����\n";
	}
	else
	{
		Node<T>* current = head;
		T maxMatrix = *(current->data); 
		while (current != nullptr)
		{
			if (*(current->data)[0][0] > maxMatrix[0][0])
			{
				maxMatrix = *(current->data);
			}
			current = current->pNext;
		}
		cout << "������������ ������� [0][0]: " << maxMatrix[0][0] << endl;
	}
}

template<typename T>
void List<T>::serch_min()
{
	if (head == nullptr)
	{
		cout << "������ ����\n";
	}
	else
	{
		Node<T>* current = head;
		T maxMatrix = *(current->data);
		while (current != nullptr)
		{
			if (*(current->data)[0][0] < maxMatrix[0][0])
			{
				maxMatrix = *(current->data);
			}
			current = current->pNext;
		}
		cout << "����������� ������� [0][0]: " << maxMatrix[0][0] << endl;
	}
}

template<typename T>
void List<T>::selection_sort_list() 
{
	Node<T>* current = this->head;

	while (current != nullptr) 
	{
		Node<T>* minNode = current;
		Node<T>* nextNode = current->pNext;
		while (nextNode != nullptr) 
		{
			if (*(nextNode->data[0][0]) < *(minNode->data[0][0]))
			{
				minNode = nextNode;
			}
			nextNode = nextNode->pNext;
		}

		// ����� ���������� 
		T* temp = current->data;
		current->data = minNode->data;
		minNode->data = temp;

		current = current->pNext;
	}
}

#endif List_header.h