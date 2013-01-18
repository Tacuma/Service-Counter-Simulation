//Tacuma Solomon
//Programming Assignment 2
//Data Structures and C++

//QueType.cpp

#include "customer.h"

class FullQueue
{};

class EmptyQueue
{};

class QueType
{
public:
	QueType();
	~QueType();
	void MakeEmpty();
	void Enqueue(int,time);
	void Enqueue(Customer);
	void Dequeue(Customer&);
	int getWaitTime(int);
	bool IsEmpty() const;
	bool IsFull() const;
private:
	Customer* front;
	Customer* rear;
};

