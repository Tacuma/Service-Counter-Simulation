//Tacuma Solomon
//Programming Assignment 2
//Data Structures and C++

// QueType.cpp


#include <cstddef>
#include <new>
#include "QueType.h"


typedef Customer ItemType;

QueType::QueType()
{
	front = NULL;
	rear = NULL;
}

void QueType::MakeEmpty()
{
	Customer* tempPtr;

	while (front != NULL)
	{
		tempPtr = front;
		front = front->next;
		delete tempPtr;
	}
	rear = NULL;
}

QueType::~QueType()
{
	MakeEmpty();
}

bool QueType::IsFull() const
{
	Customer* location;
	try
	{
		location = new Customer;
		delete location;
		return false;
	}
	catch(std::bad_alloc exception)
	{
		return true;
	}
}

bool QueType::IsEmpty() const
{
	return (front == NULL);
}

void QueType::Enqueue(int ID,time atime)
{
	if (IsFull())
		throw FullQueue();
	else
	{
		Customer* newNode;

		newNode = new Customer;
		newNode->customerID = ID;
		newNode->arrivalTime = atime;
		newNode->next = NULL;
		if (rear == NULL)
			front = newNode;
		else
			rear->next = newNode;
		rear = newNode;
	}
}

void QueType::Enqueue(Customer temp)
{
	if (IsFull())
		throw FullQueue();
	else
	{
		Customer* newNode;

		newNode = new Customer;
		*newNode = temp;
		newNode->next = NULL;
		if (rear == NULL)
			front = newNode;
		else
			rear->next = newNode;
		rear = newNode;
	}
}

void QueType::Dequeue(Customer& Node)
{
	if (IsEmpty())
		throw EmptyQueue();
	else
	{
		Customer* tempPtr;
		tempPtr = front;
		Node = *front;
		Node.next = NULL;
		front = front->next;
		if (front == NULL)
			rear = NULL;
		delete tempPtr;
	}
}

int QueType::getWaitTime (int CustID){
	Customer* tempPtr;
	tempPtr = front;
	while (tempPtr != NULL)
	{
		if(tempPtr->customerID == CustID)
			return tempPtr->waitingTime;
		tempPtr = tempPtr->next;
	}
}




