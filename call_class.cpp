#include <iostream>
#include <string>
#include <fstream>

#include "call_class.h"


using namespace std;


/************************************************************************************************************************************/
//Name: default constructor
//Precondition:		takes no parameters
//Postcondition:	initializes the class "call_class" and reads the data from the file “callstats_data.txt” into the dynamic array call_DB 
//Decription: Reads the data file of call information (cell number, relays and call length) into the dynamic array of call record, 
//call_DB. If the count because equal to the size the function double_size is called and the memory allocated to call_DB is doubled.
/************************************************************************************************************************************/
call_class::call_class()
{
	size = 5;
	count = 0;

	call_DB = new call_record[size];

	ifstream in;
	in.open("callstats_data.txt");

	double_size();

	while (!in.eof())
	{
		if (is_full() == true)
		{
			double_size();
		}

		in >> call_DB[count].firstname >> call_DB[count].lastname
			>> call_DB[count].cell_number >> call_DB[count].relays
			>> call_DB[count].call_length;
		count++;

	}
	in.close();

}

/************************************************************************************************************************************/
//Name: copy constructor
//Precondition:		takes the class to be copied as the only parameter
//Postcondition:	makes a deep copy of the class
//Decription: performs a deep copy.
/************************************************************************************************************************************/
call_class::call_class(const call_class & cop)
{
	
	count = cop.count;
	size = cop.size;

	call_DB = new call_record[size];

	for (int i = 0; i < count; i++)
	{
		call_DB[i] = cop.call_DB[i];
	}

}


/***********************************************************************************************************************************/
//Name: empty
//Precondition:		takes no parameters
//Postcondition:	If count == 0 then true is returned; otherwise false is returned
//Decription: returns true if call_DB is empty
/**********************************************************************************************************************************/
bool call_class::empty()
{
	if (count == 0)
	{
		cout << "record is empty" << endl;
		return true;
	}

	return false;

}

/**********************************************************************************************************************************/
//Name: is_full 
//Precondition:		takes no parameters
//Postcondition:	If count == size then true is return; otherwise false. The size is the capacity which is the total number of cells allocated to call_DB
//Decription: returns true if call_DB is full
/*********************************************************************************************************************************/
bool call_class::is_full()
{
	if (count == size)
	{
		return true;
	}

	return false;

}

/**********************************************************************************************************************************/
//Name: search
//Precondition:		takes no parameters
//Postcondition:	returns the location of key in call_DB if it is there; otherwise -1 is returned
//Decription: locates key in call_DB if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int call_class::search(const string key)
{

	for (int i = 0; i < count; i++)
	{
		if (call_DB[i].cell_number == key)
		{
			return i;
		}

	}

	return -1;
}

/*********************************************************************************************************************************/
//Name: add
//Precondition:		takes a string variable called "key" in which stores the phone number provided by the user
//Postcondition:	prompts the user for the firstname, lastname, relays and call length to add a new record in call_DB
//Decription: add key to call_DB; if call_DB is full, double_size is called to increase the size of call_DB.
/********************************************************************************************************************************/
void call_class::add(const string key)
{
	if (is_full() == true)
	{
		double_size();
	}

	call_DB[count].cell_number = key;

	cout << "Please enter the First Name: ";
	cin >> call_DB[count].firstname;
	cout << endl;
	cout << "Please enter the Last Name: ";
	cin >> call_DB[count].lastname;
	cout << endl;
	cout << "Please enter the Relay: ";
	cin >> call_DB[count].relays;
	cout << endl;
	cout << "Please enter the Call Length: ";
	cin >> call_DB[count].call_length;
	cout << endl;

	count++;
}


/******************************************************************************************************************************/
//Name: double_size
//Precondition:		takes no parameters
//Postcondition:	doubles the size of the array of records (call_DB)
//Decription: doubles the size (capacity) of call_DB
/******************************************************************************************************************************/
void call_class::double_size()
{
	size *= 2;
	call_record *temp = new call_record[size];

	for (int i = 0; i<count; i++)
	{
		temp[i] = call_DB[i];
	}

	delete[] call_DB;
	call_DB = temp;
}


/******************************************************************************************************************************/
//Name: process
//Precondition:		takes no parameters
//Postcondition:	calculate the net cost of a call (net_cost), the tax on a call (call_tax) and the total cost of the call (total_cost)
//					using the number of relay stations (relays) and the length in minutes of the call (call_length) 
//					for all call records stored in call_DB
//Decription: calculate the net cost, tax rate, call tax and total cost for every call record in call_DB.
/*****************************************************************************************************************************/
void call_class::process()
{
	for (int i = 0; i < count; i++)
	{

		call_DB[i].net_cost = call_DB[i].relays / 50.0 * 0.40 * call_DB[i].call_length;

		if (call_DB[i].relays <= 5)
		{
			call_DB[i].tax_rate = 0.01;
		}
		else if (call_DB[i].relays >= 6 && call_DB[i].relays <= 11)
		{
			call_DB[i].tax_rate = 0.03;
		}
		else if (call_DB[i].relays >= 12 && call_DB[i].relays <= 20)
		{
			call_DB[i].tax_rate = 0.05;
		}
		else if (call_DB[i].relays >= 21 && call_DB[i].relays <= 50)
		{
			call_DB[i].tax_rate = 0.08;
		}
		else if (call_DB[i].relays > 50)
		{
			call_DB[i].tax_rate = 0.12;
		}



		call_DB[i].call_tax = call_DB[i].net_cost * call_DB[i].tax_rate;

		call_DB[i].total_cost = call_DB[i].net_cost + call_DB[i].call_tax;

	}

	return;
}


/****************************************************************************************************************************/
//Name: operator<<
//Precondition: takes ostream variable and an object of the class call_class
//Postcondition: overloads the output operator "<<" and prints the output into a file and the screen
//Decription: Overloading operator<< as a friend function. Prints every field of every call_record in call_DB 
//                   formatted to the screen and a file called "stats7_output.txt".
/***************************************************************************************************************************/
ostream & operator<<(ostream & out, call_class & Org)
{
	for (int i = 0; i<Org.count; i++)
	{
		out << Org.call_DB[i].firstname << "     "
			<< Org.call_DB[i].lastname << "		"
			<< Org.call_DB[i].cell_number << "	"
			<< Org.call_DB[i].relays << "	"
			<< Org.call_DB[i].call_length << "	"
			<< Org.call_DB[i].net_cost << "	"
			<< Org.call_DB[i].tax_rate << "	"
			<< Org.call_DB[i].call_tax << "	"
			<< Org.call_DB[i].total_cost << endl;
	}

	ofstream output;
	output.open("stats7_output.txt");
	if (output.fail())
	{
		cout << "Unable to open the output file" << endl;
	}
	else
	{
		for (int i = 0; i<Org.count; i++)
		{
			output << Org.call_DB[i].firstname << "     "
				<< Org.call_DB[i].lastname << "		"
				<< Org.call_DB[i].cell_number << "	"
				<< Org.call_DB[i].relays << "	"
				<< Org.call_DB[i].call_length << "	"
				<< Org.call_DB[i].net_cost << "	"
				<< Org.call_DB[i].tax_rate << "	"
				<< Org.call_DB[i].call_tax << "	"
				<< Org.call_DB[i].total_cost << endl;
		}
	}


	output.close();

	return out;
}

/****************************************************************************************************************************/
//Name: destructor
//Precondition:		takes no parameters
//Postcondition:	automatically called by the compiler to de-allocate new memory that was allocated to call_DB
//Decription: de-allocates all memory allocated to call_DB.  This should be the last function to be called before the program
//            is exited.
/***************************************************************************************************************************/
call_class::~call_class()
{
	delete[]call_DB;
}

