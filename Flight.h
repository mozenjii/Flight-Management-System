#pragma once
#include <iostream>
#include "AVL.h"
#include <vector>
#include "SinglyLinkedList.h"
#include "Queue.h"
#include <fstream>
#include "Plane.h"
#include "Customer.h"
#include "utility.h"
#include "Customer.h"
using namespace std;
#include <string>

class Flights {
	int flightNumber;
	int planeId;
	int day;
	int month;
	int year;
	string departureTime;
	string destination;
	string ticketInfo[2];
	int passengersCount[2]; //0 for business and 1 for economy
	AVL<Customer> passengers;
	vector<int> seatNumber;
	Queue<Customer>* businessWaiting;
	Queue<Customer>* economyWaiting;
public:
	Flights(int flightNumber, int planeId, int day,int month, int year, string departureTime, string destination, string ticketInfo1, string ticketInfo2, int businessCount, int economyCount):flightNumber(flightNumber), planeId(planeId),day(day), month(month), year(year), departureTime(departureTime), destination(destination){
		ticketInfo[0] = ticketInfo1;
		ticketInfo[1] = ticketInfo2;
		businessWaiting = new Queue<Customer>(businessCount);
		economyWaiting = new Queue<Customer>(economyCount);
		passengersCount[0] = 0;
		passengersCount[1] = 0;
	}

	Flights(const Flights& other) : flightNumber(other.flightNumber), planeId(other.planeId), 
		day(other.day), month(other.month), year(other.year), 
		departureTime(other.departureTime), destination(other.destination), 
		passengers(other.passengers), seatNumber(other.seatNumber){
		ticketInfo[0] = other.ticketInfo[0];
		ticketInfo[1] = other.ticketInfo[1];
		passengersCount[0] = other.passengersCount[0];
		passengersCount[1] = other.passengersCount[1];
		if (other.businessWaiting && other.economyWaiting) {
			businessWaiting = new Queue<Customer>(other.businessWaiting->getSize());
			economyWaiting = new Queue<Customer>(other.economyWaiting->getSize());
		}else{
			businessWaiting = nullptr;
			economyWaiting = nullptr;
		}
	}

	Flights& operator=(const Flights& other) {
		if (this != &other) {  
			flightNumber = other.flightNumber;
			planeId = other.planeId;
			day = other.day;
			month = other.month;
			year = other.year;
			departureTime = other.departureTime;
			destination = other.destination;
			ticketInfo[0] = other.ticketInfo[0];
			ticketInfo[1] = other.ticketInfo[1];
			passengers = other.passengers;
			seatNumber = other.seatNumber;
			passengersCount[0] = other.passengersCount[0];
			passengersCount[1] = other.passengersCount[1];
			delete businessWaiting;
			delete economyWaiting;

			if (other.businessWaiting && other.economyWaiting) {
				businessWaiting = new Queue<Customer>(other.businessWaiting->getSize());
				economyWaiting = new Queue<Customer>(other.economyWaiting->getSize());
			}else{
				businessWaiting = NULL;
				economyWaiting = NULL;
			}
		}
		return *this;
	}

	void insertWaitingList(Customer customer, int type) {
		if (type == 0) {
			businessWaiting->enqueue(customer);
			businessWaiting->incrementCurrentSize();
		}
		else {
			economyWaiting->enqueue(customer);
			economyWaiting->incrementCurrentSize();
		}
	}

	void insertPassenger(Customer customer, int type, int seatNumber) {
		if (type == 0) 
			passengersCount[0]++;
		else 
			passengersCount[1]++;
		passengers.insert(customer);
		this->seatNumber.push_back(seatNumber);
	}

	void removePassenger(const int& customerId, const int& classTypeIndex, const int& seatNumber) {
		passengers.Delete(customerId);
		passengersCount[classTypeIndex]--;
		for (int i = 0; i < this->seatNumber.size(); i++) {
			if (seatNumber == this->seatNumber[i]) {
				this->seatNumber.erase(this->seatNumber.begin() + i);
				break;
			}
		}
	}

	vector<int> getSeats()const {
		return seatNumber;
	}

	int getWaitingPassenger(int type)const {
		if (type == 0) {
			if (businessWaiting->getCurrentSize() == 0)
				return -1;
			return businessWaiting->dequeue();
		}
		else {
			if (economyWaiting->getCurrentSize() == 0)
				return -1;
			return economyWaiting->dequeue();
		}
	}

	int getTicketPrice(int type)const {
		string str = "";
		if(type == 0){
			for(int i=9;i<ticketInfo[0].length();i++){
				str += ticketInfo[0][i];
			}
		}
		else{
			for(int i=8;i<ticketInfo[1].length();i++){
				str += ticketInfo[1][i];
			}
		}
		return strToNum(str);
	}

	int getPassengersCount(int type)const {
		return passengersCount[type];
	}

	int getTotalCount(int type)const {
		return type==0?businessWaiting->getSize():economyWaiting->getSize();
	}
	
	int getWaitingCount(int type)const {
		return type == 0 ? businessWaiting->getCurrentSize() : economyWaiting->getCurrentSize();
	}

	int getKey()const {
		return flightNumber;
	}
	int getFlightNumber()const {
		return flightNumber;
	}
	int getPlaneId()const {
		return planeId;
	}
	int getDay()const {
		return day;
	}
	int getMonth()const {
		return month;
	}
	int getYear()const {
		return year;
	}
	string getDepartureTime()const {
		return departureTime;
	}
	string getDestination()const {
		return destination;
	}
	
	void saveData(fstream& file){
		file << numToStr(flightNumber) << "," << numToStr(planeId) << "," << numToStr(day) << "," << numToStr(month) << "," << numToStr(year) << "," << departureTime << "," << destination << "," << ticketInfo[0] << "," << ticketInfo[1] << endl;
	}

	void display() {
		cout << "\nFlight Number: " << flightNumber << endl;
		cout << "Plane ID: " << planeId << endl;
		cout << "Date: " << day << "/" << month << "/" << year << endl;
		cout << "Departure Time: " << departureTime << endl;
		cout << "Destination: " << destination << endl;
		cout << "Ticket Price for: " << ticketInfo[0] << endl;
		cout << "Ticket Price for: " << ticketInfo[1] << endl;
	}
	
	~Flights() {
		if (businessWaiting) {
			delete businessWaiting;
			businessWaiting = nullptr;
		}
		if (economyWaiting) {
			delete economyWaiting;
			economyWaiting = nullptr;
		}
	}

	void updateData(SinglyLinkedList<Plane, int>& planeList) {
		int day, month, year, businessCount, economyCount;
		string departureTime;
		string destination;
		string ticketInfo1, ticketInfo2;
		do {
			cout << "Enter the departure time: ";
			cin >> departureTime;
		} while (departureTime.length() != 5 || departureTime[2] != ':' || !isDigit(departureTime[0]) || !isDigit(departureTime[1]) || !isDigit(departureTime[3]) || !isDigit(departureTime[4]) || 0 > (charToNum(departureTime[0]) * 10 + charToNum(departureTime[1])) || (charToNum(departureTime[0]) * 10 + charToNum(departureTime[1])) > 23 || 0 > (charToNum(departureTime[3]) * 10 + charToNum(departureTime[4])) || (charToNum(departureTime[3]) * 10 + charToNum(departureTime[4])) > 60);
		bool flag;
		do {
			flag = true;
			cout << "Enter the day of the flight: ";
			inputPosInt(day);
			if (day < 1 || day>30)
				flag = false;
			cout << "Enter the month (1-12) of the flight: ";
			inputPosInt(month);
			if (month < 1 || month > 12)
				flag = false;
			cout << "Enter the year of the flight: ";
			inputPosInt(year);
			if (year < 1900 || year > 2900)
				flag = false;

		} while (flag == false);
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter the destination: ";
		getline(cin, destination);
		cout << "Enter the ticket information for Business: ";
		getline(cin, ticketInfo1);
		cout << "Enter the ticket information for Economy: ";
		getline(cin, ticketInfo2);
		planeList.assignValuesCount(businessCount, economyCount, planeId);
		this->day = day;
		this->month = month;
		this->year = year;
		this->departureTime = departureTime;
		this->destination = destination;
		this->ticketInfo[0] = ticketInfo1;
		this->ticketInfo[1] = ticketInfo2;
	}
};