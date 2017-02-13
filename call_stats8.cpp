/*
Name:  Godson Fortil                     Z#:  23320667
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
Due Date:  04/29/2016                    Due Time: 11:59
Total Points: 100
Assignment 8: call_stats8.cpp*/


/*
DESCRIPTION:

In this assignment  a program called management system is implemented.  The program used a class and multiple functions.
A function gets input from the "call_data.txt" file, the data is processed to perform
the necessary calculations, and the results are printed out.

*/


#include <iostream>
#include <string>
#include <fstream>
#include "call_class.h"

using namespace std;







//driver to test the functionality of your class.
int main()
{
	
	call_class MyClass;
	
	MyClass.process(); //processes previously available data

	call_class MyClass_2 = MyClass; //makes a deep copy of previously processed data

	int choice = 0;
	string key;	//cell number
	int index = 0;


	cout << "Please enter the cell number of the record: ";
	cin >> key;
	cout << endl;

	index = MyClass.search(key); //passes the return value of search


	cout << "Here is what you can perform:" << endl << endl << "1.	Add a new record"
		<< endl << "Any other number to process the records on file"
		<< endl << endl << "Please enter the number associated with your choice: ";
	cin >> choice;
	cout << endl;

	if (choice == 1) //to add a record
	{
		MyClass.add(key);
	}
	

	MyClass.process(); //processes new data

	cout << "***************************************************************************************************" << endl
		 << "                                       ~ OLD RECORDS ~" <<endl	
		 << "***************************************************************************************************" << endl << endl;
	
	cout << MyClass_2 << endl << endl;

	if (choice == 1) //prints a new list of all the records if user added a new record
	{
		cout << "***************************************************************************************************" << endl
			 << "                                   ~ NEW RECORDS ~" <<endl		
			 << "***************************************************************************************************" << endl << endl;

		cout << MyClass << endl;
	}

	return 0;
}



