#pragma once
#include <iostream>
#include <string>

using namespace std;

class Employee
{
protected:
	string FirstName;
	string LastName;
public:
	Employee(string fname, string lname) 
		: FirstName(fname), LastName(lname)
	{}

	virtual ~Employee() {}

	const string FNameGet() const 
	{
		return FirstName;
	}

	void FNameSet(string firstname)
	{
		FirstName = firstname;
	}

	const string LNameGet() const
	{
		return LastName;
	}

	void LNameSet(string lastname)
	{
		LastName = lastname;
	}

	virtual double calculateSalary() const = 0;

	virtual void ShowInfo() const = 0;

};

class Worker : public Employee
{
protected:
	int hoursNumber;
	int hourlyRate;
public:
	Worker(string fname, string lname, double hours, double rate)
		: Employee(fname, lname), hoursNumber(hours), hourlyRate(rate)
	{}

	double calculateSalary() const override 
	{
		double salary = 
			hoursNumber <= 40 ? hoursNumber * hourlyRate 
			: 40 * hourlyRate + (hoursNumber - 40) * 2 * hourlyRate;
		return salary;
	}

	void ShowInfo() const override
	{
		cout << "Worker : " << FirstName << " " << LastName 
			<< ", Salary: " << calculateSalary() << endl;
	}
};

class SalaryWorker : public Employee
{
protected:
	double salary;
	double bonus;
public:
	SalaryWorker(string fname, string lname, double s, double b)
		: Employee(fname, lname), salary(s), bonus(b)
	{}

	double calculateBonus() const 
	{
		return bonus;
	}

	double calculateSalary() const override 
	{
		return salary + calculateBonus();
	}

	void ShowInfo() const override 
	{
		cout 
			<< "SalaryWorker: " << FirstName << " " << LastName 
			<< ", Salary: " << calculateSalary() << endl;
	}
};

class Salesman : public SalaryWorker
{
private:
	double workPercent;
public:
	Salesman(string fname, string lname, double startsalary, double startbonus, double percentage)
		: SalaryWorker(fname, lname, startsalary, startbonus), workPercent(percentage)
	{}

	double calculateBonus() const
	{
		return bonus * workPercent / 100.0;
	}

	void display() const 
	{
		cout 
			<< "Salesman: " << FirstName << " " << LastName 
			<< ", Salary: " << calculateSalary() << std::endl;
	}
};

class Manager : public SalaryWorker
{
private:
	int count;
public:
	Manager(string fname, string lname, double startsalary, double startbonus, int client)
		: SalaryWorker(fname, lname, startsalary, startbonus), count(client)
	{}

	double calculateBonus() const  {
		double managerBonus = bonus;
		if (count > 100) {
			managerBonus *= 2;
		}
		if (count > 200) {
			managerBonus *= 3;
		}
		return managerBonus;
	}

	void display() const {
		cout 
			<< "Manager: " << FirstName << " " << LastName 
			<< ", Salary: " << calculateSalary() << std::endl;
	}

};