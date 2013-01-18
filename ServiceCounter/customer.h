//Tacuma Solomon
//Programming Assignment 2
//Data Structures and C++

// customer.h

struct time{
	int hours;
	int minutes;
	int seconds;
};

struct Customer {
	int customerID;
	time arrivalTime;
	int queueLength;
	int waitingTime;
	Customer* next;		
};
