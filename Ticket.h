#pragma once
#include <iostream>
using namespace std;

class Ticket {
	string customerId;
	string name;
	int flightNum;
	int ticketNumber;
	string ticketType;
	int costOfFlight;
	bool discount;
	string reasonForDiscount;
	string dateTime;
	int seatNumber;
public:
	Ticket(string customerId, string name, int flightNum, int ticketNumber, string ticketType, int costOfFlight, bool discount = false, string reasonForDiscount = "", string dateTime = "", int seatNumber = 0) : customerId(customerId), name(name), flightNum(flightNum), ticketNumber(ticketNumber), ticketType(ticketType), costOfFlight(costOfFlight), discount(discount), reasonForDiscount(reasonForDiscount), dateTime(dateTime), seatNumber(seatNumber) {}
	string getCustomerId() {
		return customerId;
	}
	int getKey()const {
		return ticketNumber;
	}

	string getName() {
		return name;
	}
	int getFlightNum() {
		return flightNum;
	}
	int getTicketNumber() {
		return ticketNumber;
	}
	string getTicketType() {
		return ticketType;
	}
	int getCostOfFlight() {
		return costOfFlight;
	}
	bool hasDiscount() {
		return discount;
	}
	string getReasonForDiscount() {
		return reasonForDiscount;
	}
	string getDateTime() {
		return dateTime;
	}
	int getSeatNumber() {
		return seatNumber;
	}

	void saveData(fstream& file) {
		file << customerId << "," << name << "," << numToStr(flightNum) << "," << numToStr(ticketNumber) << "," << ticketType << "," << numToStr(costOfFlight) << "," << numToStr(discount) << "," << reasonForDiscount << "," << dateTime << "," << numToStr(seatNumber) << endl;
	}

	void display() {
		cout << "\nCustomer ID: " << customerId << endl;
		cout << "Name: " << name << endl;
		cout << "Flight Number: " << flightNum << endl;
		cout << "Ticket Number: " << ticketNumber << endl;
		cout << "Ticket Type: " << ticketType << endl;
		cout << "Cost of Flight: $" << costOfFlight << endl;
		if (discount) {
			cout << "Discount Applied: Yes" << endl;
			cout << "Reason for Discount: " << reasonForDiscount << endl;
		}
		else {
			cout << "Discount Applied: No" << endl;
		}
		cout << "Date and Time of Flight: " << dateTime << endl;
		cout << "Seat Number: " << seatNumber << endl;
	}
};