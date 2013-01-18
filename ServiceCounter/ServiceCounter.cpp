//Tacuma Solomon
//Programming Assignment 2
//Data Structures and C++

// ServiceCounter.cpp


#include <iostream>
#include <fstream>
#include <string>
#include "QueType.h"
using namespace std;

int T ;
enum RelationType {LESS, GREATER, EQUAL};

time timeAddition (time, int);
int timeDifference(time,time);
void readfile(QueType&, ifstream&); //Function prototype 
void readqueries(QueType&, ifstream&, int, int, int, int); // Function prototype
RelationType compareTime(time,time);
void Footer();

int main(int argc, char *argv[])
{
	
	time currentTime = {9,0,0};
	time endTime = {5,0,0};
	time nineAM = { 9,0,0};
	QueType LL, finalLL;
	ifstream in, in2;
	Customer temp;
	int breakTime = 0;
	int totalBreakTime = 0;
	int maxBreakTime = 0;
	int numOfCustomersServed = 0;
	int maxQueuelength = 0;
	currentTime.hours = 9;
	in.open("customersfile.txt");
	in2.open("queriesfile.txt");
	if ( !in.is_open() || !in2.is_open()) {
			cout<<"Could not open file\n";
			Footer();
			system("pause");
			return 0;
	}
	readfile(LL,in);

	while ((compareTime(currentTime,endTime) == LESS) && !(LL.IsEmpty())){
		
		LL.Dequeue(temp);

		if (compareTime(temp.arrivalTime,nineAM) == LESS){
			temp.waitingTime = timeDifference(currentTime,temp.arrivalTime);
			if (compareTime(currentTime,nineAM) == EQUAL)
				temp.queueLength = 0;
			else {
				temp.queueLength = (timeDifference(currentTime,nineAM)/T) + 1;
				if (temp.queueLength > maxQueuelength)
					maxQueuelength = temp.queueLength;
			}
			currentTime = timeAddition(currentTime,T);
			numOfCustomersServed++;
			finalLL.Enqueue(temp);
		}
		else if (compareTime(currentTime,temp.arrivalTime) == GREATER){
			temp.waitingTime = timeDifference(currentTime,temp.arrivalTime);
			temp.queueLength = (temp.waitingTime/T)+1;
			if (temp.queueLength > maxQueuelength)
				maxQueuelength = temp.queueLength;
			currentTime = timeAddition(currentTime,T);
			numOfCustomersServed++;
			finalLL.Enqueue(temp);
		}
		else if (compareTime(currentTime,temp.arrivalTime) == LESS){
			breakTime = timeDifference(temp.arrivalTime,currentTime);
			if (breakTime > maxBreakTime)
				maxBreakTime = breakTime;
			currentTime = timeAddition(currentTime,breakTime);
			totalBreakTime += breakTime;

			temp.waitingTime = 0;
			temp.queueLength = 0;
			currentTime = timeAddition(currentTime,T);
			numOfCustomersServed++;
			finalLL.Enqueue(temp);
		}
		if ((compareTime(currentTime,endTime) == LESS) && LL.IsEmpty()) {
			breakTime = timeDifference(endTime,currentTime);
			if (breakTime > maxBreakTime)
				maxBreakTime = breakTime;
			totalBreakTime += breakTime;
		}
	}

	while (!LL.IsEmpty()) {
		LL.Dequeue(temp);
		if (compareTime(temp.arrivalTime,endTime) == LESS)
			temp.waitingTime = timeDifference(endTime,temp.arrivalTime);
		else if (compareTime(temp.arrivalTime, endTime) == GREATER)
			temp.waitingTime = 0;
		else
			temp.waitingTime = 0;
		finalLL.Enqueue(temp);
	}

	readqueries(finalLL,in2,totalBreakTime,maxBreakTime,numOfCustomersServed,maxQueuelength);
	Footer();
	system("pause");
	return 0;
}

// Reads file and fills the Queue of Customers
void readfile(QueType& customers, ifstream& in)
{
	int custID;
	time aTime;
	in >> T;

	while (!(in.eof())) {
		in.ignore(20,':');
		in >> custID;
		in.ignore(20,':');
		in >> aTime.hours ;
		in.ignore(1);
		in >> aTime.minutes; 
		in.ignore(1);
		in >> aTime.seconds;
		customers.Enqueue(custID,aTime);
	}
}

//Compares 2 times and returns an ENUM value LESS, GREATER, or EQUAL
RelationType compareTime(time time1, time time2)
{
	int time1inSeconds;
	int time2inSeconds;

	if(time1.hours <= 6)
		time1.hours+=12;

	if(time2.hours <= 6)
		time2.hours+=12;

	time1inSeconds = (time1.hours*3600)+(time1.minutes*60)+(time1.seconds);
	time2inSeconds = (time2.hours*3600)+(time2.minutes*60)+(time2.seconds);

	if (time1inSeconds>time2inSeconds)
		return GREATER;
	if (time1inSeconds<time2inSeconds)
		return LESS;
	if (time1inSeconds=time2inSeconds)
		return EQUAL;
}

//Returns the difference Between two times in seconds
int timeDifference(time time1, time time2)
{
	int time1inSeconds;
	int time2inSeconds;

	if(time1.hours <= 6)
		time1.hours+=12;

	if(time2.hours <= 6)
		time2.hours+=12;

	time1inSeconds = (time1.hours*3600)+(time1.minutes*60)+(time1.seconds);
	time2inSeconds = (time2.hours*3600)+(time2.minutes*60)+(time2.seconds);
	
	return (time1inSeconds-time2inSeconds);
}

//Adds two times and returns the result in seconds
time timeAddition (time time1, int seconds)
{
	int time1inSeconds;

	if(time1.hours <= 6)
		time1.hours+=12;

	time1inSeconds = (time1.hours*3600)+(time1.minutes*60)+(time1.seconds);
	int newSeconds = time1inSeconds + seconds;

	time newTime;
	newTime.hours = (newSeconds/3600);
	newTime.minutes = (newSeconds%3600)/60;
	newTime.seconds = (newSeconds%3600)%60;

	return newTime;
}

// Reads and executes commmands from queriesfile.txt
void readqueries(QueType& FinalLL, ifstream& in, int totalBreakTime,int maxBreakTime, 
				 int numOfCustomersServed, int maxQueuelength){
	string command;
	int custID;
	int waitTime;

	while (!(in.eof())) {
		in >> command;
		if (command == "WAITING-TIME-OF"){
				in >> custID;
				waitTime = FinalLL.getWaitTime(custID);
				cout << "WAITING-TIME-OF " << custID << ":" << waitTime << endl;
		}
		else if (command == "NUMBER-OF-CUSTOMERS-SERVED")
			cout << "NUMBER-OF-CUSTOMERS-SERVED:" << numOfCustomersServed << endl;
		else if (command == "LONGEST-BREAK-LENGTH")
			cout << "LONGEST-BREAK-LENGTH:" << maxBreakTime << endl;
		else if (command == "TOTAL-IDLE-TIME")
			cout << "TOTAL-IDLE-TIME:" << totalBreakTime << endl;
		else if (command == "MAXIMUM-NUMBER-OF-PEOPLE-IN-QUEUE-AT-ANY-TIME"){
			cout << "MAXIMUM-NUMBER-OF-PEOPLE-IN-QUEUE-AT-ANY-TIME:" << maxQueuelength << endl;
		}
	}

}

void Footer()
{
	cout << endl << endl;
	cout << "() Code by Tacuma Solomon " << endl;
	cout << "() Not for Redistribution or Reuse." << endl << endl;
}

/*
NUMBER-OF-CUSTOMERS-SERVED:10
LONGEST-BREAK-LENGTH:9905
TOTAL-IDLE-TIME:25899
MAXIMUM-NUMBER-OF-PEOPLE-IN-QUEUE-AT-ANY-TIME:3
WAITING-TIME-OF 1:1783
WAITING-TIME-OF 2:568
WAITING-TIME-OF 3:0
WAITING-TIME-OF 7:685


() Code by Tacuma Solomon
() Not for Redistribution or Reuse.

Press any key to continue . . .
*/