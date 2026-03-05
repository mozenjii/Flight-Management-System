#pragma once
#include <iostream>
#include "utility.h"
#include <fstream>
using namespace std;
#include <string>

class Customer {
	int customerId;
	string name;
	int phone;
	string dob;
	int numOfFlights;
	int milesTraveled;
public:
	Customer(int customerId, string name, int phone = 0, string dob = "", int numOfFlights = 0, int milesTraveled = 0) :customerId(customerId), name(name), phone(phone), dob(dob), numOfFlights(numOfFlights), milesTraveled(milesTraveled) {}
	int getCustomerId()const {
		return customerId;
	}
	int getKey()const {
		return customerId;
	}
	string getName()const {
		return name;
	}
	int getPhone()const {
		return phone;
	}
	string getDob()const {
		return dob;
	}
	int getNumOfFlights()const {
		return numOfFlights;
	}
	int getMilesTraverled()const {
		return milesTraveled;
	}
	void setCustomerId(int customerId) {
		this->customerId = customerId;
	}
	void setName(string name) {
		this->name = name;
	}
	void setPhone(int phone) {
		this->phone = phone;
	}
	void setDob(string dob) {
		this->dob = dob;
	}
	void setNumOfFlights(int numOfFLights) {
		this->numOfFlights = numOfFlights;
	}
	void setMilesTraverled(int milesTraveled) {
		this->milesTraveled = milesTraveled;
	}

	void updateMilesTraveled(int miles, bool type) {
		if(type) {
			this->milesTraveled += miles;
		}
		else {
			this->milesTraveled -= miles;
		}
	}
	void updateNumOfFlights(bool type) {
		if(type) {
			this->numOfFlights++;
		}
		else {
			this->numOfFlights--;
	
		}
	}

	void saveData(fstream& file) {
		file << numToStr(customerId) << "," << name << "," << numToStr(phone) << "," << dob << "," << numToStr(numOfFlights) << "," << numToStr(milesTraveled) << endl;
	}

	void updateData() {
		string name;
		int phone;
		int month, day, year;
		cout << "Enter New Name: ";
		getline(cin, name);
		cout << "Enter New Phone Number: ";
		inputPosInt(phone);
		bool flag;
		do {
			flag = true;
			cout << "Enter the day of your birth: ";
			inputPosInt(day);
			if (day < 1 || day>30)
				flag = false;
			cout << "Enter the month (1-12) of your birth: ";
			inputPosInt(month);
			if (month < 1 || month > 12)
				flag = false;
		cout << "Enter the year of your birth: ";
		inputPosInt(year);
		if (year < 1000 || year > 5000)
			flag = false;
		} while (flag = false);
		string dob = numToStr(day) + "/" + numToStr(month) + "/" + numToStr(year);
		this->name = name;
		this->phone = phone;
		this->dob = dob;
	}

	void display() {
		cout << "\nCustomer ID: " << customerId << endl;
		cout << "Name: " << name << endl;
		cout << "Phone: " << phone << endl;
		cout << "Date of Birth: " << dob << endl;
		cout << "Number of Flights: " << numOfFlights << endl;
		cout << "Miles Traveled: " << milesTraveled << " miles" << endl;
	}
};