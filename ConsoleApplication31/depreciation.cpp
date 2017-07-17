/*
	Program name: Depreciation 
	Programmer: O.Butakov
*/


#include <iostream>
#include <conio.h>
#include <string>
#include <cctype>
#include <iomanip>
#include <algorithm>

using namespace std;

void printArgError() {
	cout
		<< "Invalid number of Argumets!\n"
		<< "USAGE is commandline [Depreciation Type] [Cost] [Scrap] [Number of Years]\n"
		<< "\n\tDepreciation types:"
		<< "\n\t\t - SL - for Straight Line Depreciation"
		<< "\n\t\t - SYD - for Sum-of-the-Years'-Digits Depreciation"
		<< "\n\t\t - UP - for Units of Production Depreciation Depreciation"
		<< "\n\t\t - DDB - for Double Declining Balance Depreciation"
		<< "\nExiting ...";

}
void printSL(char* cost, char* scrap, char* years)
{
	double
		total = 0,
		cost1 = atof(cost),
		scrap1 = atof(scrap);

	double pureMoney = cost1 - scrap1;

	int years1 = atoi(years);



	cout << endl << setw(15) << left << "YEARS" << setw(28) << left << "DEPRECIATION" << setw(20) << left << "ACCUM. DEPRECIAION" << endl << endl;

	for (int i = 0; i < years1; i++)
	{
		total += pureMoney / years1;
		cout << setw(15) << left << i+1 << setw(30) << left << setprecision(2) << fixed << pureMoney/years1 << setw(12) << setprecision(2) << fixed << right << total << endl;
	
	}
}

void printSYD(char* cost, char* scrap, char* years)
{

	int
		years1 = atoi(years);
	double
		cost1 = atof(cost),
		scrap1 = atof(scrap),
		pureMoney = cost1-scrap1,
		sumOfYears = (years1*(years1 + 1)) / 2,
		total = 0;

	cout << endl << setw(15) << left << "YEARS" << setw(28) << left << "DEPRECIATION" << setw(20) << left << "ACCUM. DEPRECIAION" << endl << endl;

	for (int i = 0; i < years1; i++)
	{
		total += ((years1-i) / sumOfYears)*pureMoney;
		cout << setw(18) << left << i + 1 << setw(28) << left << setprecision(2) << fixed << ((years1-i) / sumOfYears)*pureMoney << setw(12) << setprecision(2) << fixed << right << total << endl;
	}
}

void printDDB(char* cost, char* scrap, char* years)
{

	double
		years1 = atof(years),
		total = 0,
		remainingTotal,
		valuePerYear;
	int
		cost1 = atoi(cost),
		scrap1 = atoi(scrap),
		pureMoney = cost1 - scrap1;

	remainingTotal = cost1;

	cout << endl << setw(15) << left << "YEARS" << setw(28) << left << "DEPRECIATION" << setw(20) << left << "ACCUM. DEPRECIAION" << endl << endl;

	for (int i = 0; i < years1; i++)
	{
		if (i + 1 == years1) 
		{
			valuePerYear = pureMoney - total;
			total = pureMoney;
		}
		else
		{
			total += (2 / years1)*remainingTotal;
			valuePerYear = (2 / years1)*remainingTotal;
		}
		cout << setw(18) << left << i + 1 << setw(28) << left << setprecision(2) << fixed << valuePerYear << setw(12) << setprecision(2) << fixed << right << total << endl;
		remainingTotal -= valuePerYear;
		
	}
}

string suffix(int i) //-------- return suffix for the argument from 1-99
{
	string prefix;
	if ((i == 1) || (i >= 21 && i % 10 == 1))
		prefix = "st";
	else if (i == 2 || (i >= 22 && i % 10 == 2))
		prefix = "nd";
	else if (i == 3 || (i >= 23 && i % 10 == 3))
		prefix = "rd";
	else
		prefix = "th";

	return prefix;
}

int getPosInteger() // ---------- validates for non-numeric and non-negative integer
{
	int x;

	cin >> x;

	while (cin.fail())
	{
		cout << "\nInvalid Input! Please input a numerical value: ";
		cin.clear();
		while (cin.get() != '\n');
		cin >> x;
		if ((int)x != x || x<=0)
			cout << "\nPositive Integer only! Please try again: ";
	}
	return x;
}

void printUP(char* cost, char* scrap, char* years)
{

	int
		years1 = atoi(years);
	int *milesPerYear = new int [years1];
	double
		cost1 = atof(cost),
		scrap1 = atof(scrap),
		pureMoney = cost1 - scrap1,
		total = 0;

	cout << "How many units of production you want to get: ";
	int units = getPosInteger();
	double ratio = pureMoney / units;

	for (int j = 0; j < years1; j++)
	{
		if (total >= units)
		{
			cout << "Total amount of miles should not exceed OR be equal " << pureMoney;
			cout << "\nExiting ... ";
			exit(1);
		}
		cout << "How many miles for the " << j + 1 << suffix(j + 1) << " year: ";
		*(milesPerYear + j) = getPosInteger();
		total += *(milesPerYear + j);
	}

	if (total != units) 
	{
		cout << "Total amount of miles should not exceed OR be less than " << units;
		cout << "\nExiting ... ";
		exit(1);
	}

	total = 0;
	cout << endl;

	cout << setw(5) << "YEAR" << setw(10) << "AMOUNT" << endl << endl;

	for (int k = 0; k < years1; k++)
		cout << setw(5) << k + 1 << setw(10) << setprecision(2) << fixed << *(milesPerYear + k) << endl;

	double perYear ;
	cout << endl << setw(15) << left << "YEARS" << setw(28) << left << "DEPRECIATION" << setw(20) << left << "ACCUM. DEPRECIAION" << endl << endl;

	for (int i = 0; i < years1; i++)
	{
		perYear = (*(milesPerYear + i))*ratio;
		total += perYear;
		cout << setw(18) << left << i + 1 << setw(28) << left << setprecision(2) << fixed << perYear << setw(12) << setprecision(2) << fixed << right << total << endl;
	}
}

int validate(char *str) // validates if c string contains numberic values
{
	for (int i = 0; i < strlen(str); i++) {
		if (!isdigit(str[i]))
			return 1;
	}
	return 0;
}



int main(int argc, char* argv[])
{
	if (argc != 5) // ---------- vaidates for invalid number of argumets 
	{
		printArgError();
		return 1;
	}

	if (validate(*(argv + 2)) == 1 || validate(*(argv + 2)) || validate(*(argv + 3)))  // ----------- validates for non-numeric arguments
	{
		printArgError();

		return 1;
	}

	string deprType = *(argv+1);
	transform(deprType.begin(), deprType.end(), deprType.begin(), ::toupper); // ---- converting [Depreciation Type] c string to all uppercase letters


	if (deprType == "SL")
	{
		printSL(*(argv + 2), *(argv + 3), *(argv + 4));
	}
	else if (deprType == "UP")
	{
		printUP(*(argv + 2), *(argv + 3), *(argv + 4));
	}
	else if (deprType == "SYD")
	{
		printSYD(*(argv + 2), *(argv + 3), *(argv + 4));
	}
	else if (deprType == "DDB")
	{
		printDDB(*(argv + 2), *(argv + 3), *(argv + 4));
	}
	else 
		printArgError();

	_getch();

	return 0;
}