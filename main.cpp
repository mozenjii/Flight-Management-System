#include <iostream>
#include <fstream>
#include <algorithm>
#include "Airport.h"
#include "Flight.h"
#include "Customer.h"
#include "Ticket.h"
#include "Offers.h"
#include <vector>
#include "HashTableAVL.h"
#include "Plane.h"
#include "DoublyLInkedList.h"
using namespace std;

SinglyLinkedList<Airport,string> airportList;
SinglyLinkedList<Plane, int> planeList;
AVL<Customer> customerList;
DLinkedList<Flights, int> flightList;
Offers offerList[10];
HashTableAVL<AVL<Ticket>, Ticket> ticketList(14);

void displayOffers() {
	cout << "\nAvailable Offers:\n";
	for (int i = 0; i < 10; i++) {
		if (offerList[i].getOfferId() != -1)
			offerList[i].display();
	}
}

void setupAirportList() {
	fstream file;
	file.open("airports.txt", ios::in);
	if (!file) {
		cerr << "Error opening airports.txt file!" << endl;
		return;
	}
	string airportName;
	string country;
	string usualWeatherCondition;
	string timeFromBeirut;
	string milesFromBeirut;

	while (true) {
		if (!getline(file, airportName, ',')) break;
		if (!getline(file, country, ',')) break;
		if (!getline(file, usualWeatherCondition, ',')) break;
		if (!getline(file, timeFromBeirut, ',')) break;
		if (!getline(file, milesFromBeirut)) break;
		airportList.insert(Airport(airportName, country, usualWeatherCondition, strToNum(timeFromBeirut), strToNum(milesFromBeirut)));
	}
	file.close();
}

void setupPlaneList() {
	fstream file;
	file.open("planes.txt", ios::in);
	if (!file){
		cerr << "Error opening planes.txt file!" << endl;
		return;
	}

	string planeId;
	string description;
	string numberOfMilesTraveled;
	string numberOfSeatsPerClass[2];

	while (true) {
		if (!getline(file, planeId, ',')) break;
		if (!getline(file, description, ',')) break;
		if (!getline(file, numberOfMilesTraveled, ',')) break;
		if (!getline(file, numberOfSeatsPerClass[0], ',')) break;
		if (!getline(file, numberOfSeatsPerClass[1])) break;
		planeList.insert(Plane(strToNum(planeId), description, strToNum(numberOfMilesTraveled), strToNum(numberOfSeatsPerClass[0]), strToNum(numberOfSeatsPerClass[1])));

	}	
	file.close();
}

void setupCustomerList() {
	fstream file;
	file.open("customers.txt", ios::in);
	if (!file) {
		cerr << "Error opening customers.txt file!" << endl;
		return;
	}
	string customerId;
	string name;
	string phone;
	string dob;
	string numOfFlights;
	string milesTraveled;
	while (true) {
		if (!getline(file, customerId, ',')) break;
		if (!getline(file, name, ',')) break;
		if (!getline(file, phone, ',')) break;
		if (!getline(file, dob, ',')) break;
		if (!getline(file, numOfFlights, ',')) break;
		if (!getline(file, milesTraveled)) break;
		customerList.insert(Customer(strToNum(customerId), name, strToNum(phone), dob, strToNum(numOfFlights), strToNum(milesTraveled)));
	}
	file.close();
}

void setupFlightList() {
	fstream file;
	file.open("flights.txt", ios::in);
	if (!file) {
		cerr << "Error opening flights.txt file!" << endl;
		return;
	}
	string flightNumber;
	string planeId;
	string day;
	string month;
	string year;
	string departureTime;
	string destination;
	string ticketInfo1;
	string ticketInfo2;
	int businessCount = 0;
	int economyCount = 0;
	while (true) {
		if (!getline(file, flightNumber, ',')) break;
		if (!getline(file, planeId, ',')) break;
		if (!getline(file, day, ',')) break;
		if (!getline(file, month, ',')) break;
		if (!getline(file, year, ',')) break;
		if (!getline(file, departureTime, ',')) break;
		if (!getline(file, destination, ',')) break;
		if (!getline(file, ticketInfo1, ',')) break;
		if (!getline(file, ticketInfo2)) break;
		planeList.assignValuesCount(businessCount, economyCount, strToNum(planeId));
		if (businessCount == 0 && economyCount == 0) {
			continue;
		}
		Flights obj(strToNum(flightNumber), strToNum(planeId), strToNum(day), strToNum(month), strToNum(year), departureTime, destination, ticketInfo1, ticketInfo2, businessCount, economyCount);
		flightList.insert(obj);
	}
	file.close();
}

void setupOffersList() {
	fstream file;
	file.open("offers.txt", ios::in);
	if (!file) {
		cerr << "Error opening offers.txt file!" << endl;
		return;
	}
	string offerId;
	string flightNumber;
	string offerType;
	string discountAmount;
	int index = 0;
	while (true) {
		if (!getline(file, offerId, ',')) break;
		if (!getline(file, flightNumber, ',')) break;
		if (!getline(file, offerType, ',')) break;
		if (!getline(file, discountAmount)) break;
		offerList[index].setOfferDetails(strToNum(offerId), strToNum(flightNumber), offerType, strToNum(discountAmount));
		index++;
	}
	file.close();
}

void setupTicketList() {
	fstream file;
	file.open("tickets.txt", ios::in);
	if (!file) {
		cerr << "Error opening tickets.txt file!" << endl;
		return;
	}
	string customerId;
	string name;
	string flightNum;
	string ticketNumber;
	string ticketType;
	string costOfFlight;
	string discount;
	string reasonForDiscount;
	string dateTime;
	string seatNumber;
	while (true) {
		if (!getline(file, customerId, ',')) break;
		if (!getline(file, name, ',')) break;
		if (!getline(file, flightNum, ',')) break;
		if (!getline(file, ticketNumber, ',')) break;
		if (!getline(file, ticketType, ',')) break;
		if (!getline(file, costOfFlight, ',')) break;
		if (!getline(file, discount, ',')) break;
		if (!getline(file, reasonForDiscount, ',')) break;
		if (!getline(file, dateTime, ',')) break;
		if (!getline(file, seatNumber)) break;
		ticketList.insert(Ticket(customerId, name, strToNum(flightNum), strToNum(ticketNumber), ticketType, strToNum(costOfFlight), strToNum(discount), reasonForDiscount, dateTime, strToNum(seatNumber)));
	}
	file.close();
}

void setupSystemData() {
	cout << "\nSetting up system data...\n";
	setupAirportList();
	cout << "Airport data loaded successfully!\n";
	setupPlaneList();
	cout << "Plane data loaded successfully!\n";
	setupCustomerList();
	cout << "Customer data loaded successfully!\n";
	setupOffersList();
	cout << "Offers data loaded successfully!\n";
	setupTicketList();
	cout << "Ticket data loaded successfully!\n";
	setupFlightList();
	cout << "Flight data loaded successfully!\n";
}

void saveAirportList() {
	fstream file;
	file.open("airports.txt", ios::out);
	if (!file) {
		cerr << "Error  while opening airports.txt file!" << endl;
		return;
	}
	Node<Airport>* temp = airportList.getHead();
	while (temp){
		file << temp->data.getAirportName() << "," << temp->data.getCountry() << "," << temp->data.getUsualWeatherCondition() << "," << numToStr(temp->data.getTimeFromBeirut()) << "," << numToStr(temp->data.getMilesFromBeirut()) << endl;
		temp = temp->next;
	}
	file.close();
}

void savePlaneList() {
	fstream file;
	file.open("planes.txt", ios::out);
	if (!file) {
		cerr << "Error while opening planes.txt file!" << endl;
		return;
	}
	Node<Plane>* temp = planeList.getHead();
	while (temp) {
		file << numToStr(temp->data.getPlaneId()) << "," << temp->data.getDescription() << "," << numToStr(temp->data.getNumberOfMilesTraveled()) << "," << numToStr(temp->data.getNumberOfSeatsPerClass(0)) << "," << numToStr(temp->data.getNumberOfSeatsPerClass(1)) << endl;
		temp = temp->next;
	}
	file.close();
}

void saveCustomerList() {
	fstream file;
	file.open("customers.txt", ios::out);
	if (!file) {
		cerr << "Error while opening customers.txt file!" << endl;
		return;
	}
	customerList.saveData(file);
	file.close();
}

void saveOffersList() {
	fstream file;
	file.open("offers.txt", ios::out);
	if (!file) {
		cerr << "Error while opening offers.txt file!" << endl;
		return;
	}
	for (int i = 0; i < 10; i++) {
		if (offerList[i].getOfferId() != -1)
			file << numToStr(offerList[i].getOfferId()) << "," << numToStr(offerList[i].getFlightNumber()) << "," << offerList[i].getOfferType() << "," << numToStr(offerList[i].getDiscountAmount()) << endl;
	}
	file.close();
}

void saveTicketList() {
	fstream file;
	file.open("tickets.txt", ios::out);
	if (!file) {
		cerr << "Error while opening tickets.txt file!" << endl;
		return;
	}
	ticketList.saveData(file);
	file.close();
}

void saveFlightList() {
	fstream file;
	file.open("flights.txt", ios::out);
	if (!file) {
		cerr << "Error while opening flights.txt file!" << endl;
		return;
	}
	flightList.saveData(file);
	file.close();
}

void saveAllData() {
	cout << "\nSaving all data to files...\n";
	saveAirportList();
	cout << "Airport data saved successfully!\n";
	savePlaneList();
	cout << "Plane data saved successfully!\n";
	saveCustomerList();
	cout << "Customer data saved successfully!\n";
	saveOffersList();
	cout << "Offers data saved successfully!\n";
	saveTicketList();
	cout << "Ticket data saved successfully!\n";
	saveFlightList();
	cout << "Flight data saved successfully!\n";
}


int generateCustomerId(string name) {
	int id = 0;
	for(int i=0;i<name.length(); i++) {
		id += name[i];
	}
	id = id % 10000;
	while (customerList.search(id)) {
		id = (id + 1) % 10000;
	}
	return id;
}

int gnerateFlightNumber(string destination, int planeId) {
	int temp = 0;
	for (int i = 0; i < destination.length(); i++) {
		temp += destination[i];
	}
	temp += planeId;
	temp = temp % 10000;
	while (flightList.search(temp)) {
		temp = (temp + 1) % 10000;
	}
	return temp;
}

void addNewCustomer(){
	int customerId;
	string name;
	int phone;
	int month, day, year;
	cout << "Enter Name: ";
	getline(cin, name);
	customerId = generateCustomerId(name);
	cout << "Enter Phone Number: ";
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
	customerList.insert(Customer(customerId, name, phone, dob, 0, 0));
	cout << "\nCustomer added successfully!\n";
}

void updateCustomerInfo() {
	int customerId;
	cout << "Enter Customer ID to update: ";
	inputPosInt(customerId);
	if (customerList.search(customerId) && customerList.updateData(customerId))
		cout << "\nCustomer information updated successfully!\n";
	else
		cout << "\nCustomer ID not found!\n";
}

void deleteCustomer() {
	int customerId;
	cout << "Enter Customer ID to delete: ";
	inputPosInt(customerId);
	if (customerList.search(customerId) && customerList.Delete(customerId))
		cout << "\nCustomer deleted successfully!\n";
	else
		cout << "\nCustomer ID not found!\n";
}

void viewCustomerProfile() {
	int customerId;
	cout << "Enter Customer ID to view: ";
	inputPosInt(customerId);
	if (!customerList.display(customerId))
		cout << "\nNo such customer exists!\n";
}

void addFlight(){
	int flightNumber, planeId, day, month, year, businessCount, economyCount;
	string departureTime;
	string destination;
	string ticketInfo[2];
	do {
		cout << "Enter Plane ID: ";
		inputPosInt(planeId);
	} while (!planeList.search(planeId));

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
	getline(cin, ticketInfo[0]);
	cout << "Enter the ticket information for Economy: ";
	getline(cin, ticketInfo[1]);
	planeList.assignValuesCount(businessCount, economyCount, planeId);
	flightNumber = flightList.getTail() ? flightList.getTail()->data.getFlightNumber() + 1 : gnerateFlightNumber(destination,planeId);
	Flights obj(flightNumber, planeId, day, month, year, departureTime, destination, ticketInfo[0], ticketInfo[1], businessCount, economyCount);
	flightList.insert(obj);
	cout << "\nFlight added successfully!\n";
}

void updateFlight() {
	int flightNumber;
	cout << "Enter Flight Number to update: ";
	inputPosInt(flightNumber);
	if (flightList.search(flightNumber) && flightList.updateData(flightNumber, planeList))
		cout << "\nFlight information updated successfully!\n";
	else
		cout << "\nFlight Number not found!\n";
}

void deleteFlight() {
	int flightId;
	cout << "Enter Flight ID to delete: ";
	inputPosInt(flightId);
	flightList.display();
	if (flightList.Delete(flightId))
		cout << "\nFlight deleted successfully!\n";
	else
		cout << "\nFlight ID not found!\n";
}

void viewFlight() {
	int flightId;
	cout << "Enter Flight ID to view: ";
	inputPosInt(flightId);
	if (!flightList.display(flightId))
		cout << "\nNo such flight exists!\n";
}

int generateSeatNumber(int customerId, int flightNumber, string customerName, vector<int> seats) {
	int temp = 0;
	temp = customerId*flightNumber*customerName.length();
	for(int i=0;i<customerName.length();i++) {
		temp += customerName[i];
	}
	
	temp = temp % 10000;
	while (find(seats.begin(), seats.end(), temp) != seats.end()) 
		temp = (temp + 2) % 10000;
	return temp;
}

int generateTicketNumber(int customerId, int flightNumber, string customerName) {
	int temp = 0;
	temp = customerId*flightNumber*customerName.length();
	for(int i=0;i<customerName.length();i++) {
		temp += customerName[i];
	}
	temp = temp % 10000;
	while(ticketList.search(temp))
		temp = (temp + 2) % 10000;
	return temp;
}

int checkDiscount(int customerId, int flightNumber) {
	for(int i=0;i<10;i++) {
		if(offerList[i].getFlightNumber() == flightNumber) {
			return i;
		}
	}
	return -1;
}

void updateCustomerMiles(int customerId, int miles, bool type) {
	customerList.getNode(customerId)->data.updateMilesTraveled(miles, type);
	customerList.getNode(customerId)->data.updateNumOfFlights(type);
}

void reserveFlight() {
	bool existingCustomer;
	cout << "Are you an existing customer? (1:Yes/0:No): ";
	cin >> existingCustomer;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	int customerId;
	if (!existingCustomer) {
		string name;
		int phone;
		int month, day, year;
		cout << "Enter Name: ";
		getline(cin, name);
		customerId = generateCustomerId(name);
		cout << "Your Customer ID is: " << customerId << endl;
		cout << "Enter Phone Number: ";
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
		customerList.insert(Customer(customerId, name, phone, dob, 0, 0));
		cout << "\nCustomer added successfully!\n";
	}
	else {
		cout << "Enter your Customer ID: ";
		inputPosInt(customerId);
		if(!customerList.search(customerId)) {
			cout << "\nCustomer ID not found! returning to the previous menu...\n";
			return;
		}
	}
	int flightNumber;
	cout << "Enter the flight number you want to reserve: ";
	inputPosInt(flightNumber);
	while(!flightList.search(flightNumber)) {
		cout << "\nFlight number not found! Please enter a valid flight number: ";
		inputPosInt(flightNumber);
	}
	DNode<Flights>* flight = flightList.getNode(flightNumber);
	string classType;
	do {
		cout << "Enter the type of seat you want to reserve (Business/Economy): ";
		cin >> classType;
		if(classType.length() > 0) {
			classType[0] = toupper(classType[0]);
			for(int i = 1; i < classType.length(); i++) {
				classType[i] = tolower(classType[i]);
			}
		}
	} while (classType != "Business" && classType != "Economy");
	int classTypeIndex = classType == "Business" ? 0 : 1;
	if (flight->data.getPassengersCount(classTypeIndex) >= flight->data.getTotalCount(classTypeIndex)) {
		cout << "\n All the seats are already occupied in this flight for this seat type!\n";
		cout << "Do you want to be added to the waiting list? (Y/N): ";
		char choice;
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (choice == 'Y' || choice == 'y') {
			if(flight->data.getWaitingCount(classTypeIndex) < flight->data.getTotalCount(classTypeIndex)) {
				flight->data.insertWaitingList(customerList.getNode(customerId)->data, classTypeIndex);
				cout << "\nFlight reserved successfully!\n";
			}
			else 
				cout << "\nThere is no space in the waiting list for your seat type...\n";
		}
		else {
			cout << "\nReturning to the previous menu...\n";
		}
	}
	else {
		vector<int> seats = flight->data.getSeats();
		int seatNumber = generateSeatNumber(customerId, flightNumber, customerList.getNode(customerId)->data.getName(), seats);
		flight->data.insertPassenger(customerList.getNode(customerId)->data, classTypeIndex, seatNumber);
		int ticketNumber = generateTicketNumber(customerId, flightNumber, customerList.getNode(customerId)->data.getName());
		int offerIndex = checkDiscount(customerId, flightNumber);
		bool discount = offerIndex != -1;
		string reasonForDiscount = "";
		if(discount) {
			reasonForDiscount = offerList[offerIndex].getOfferType();
		}
		double costOfFlight = flight->data.getTicketPrice(classTypeIndex);
		if(discount) {
			costOfFlight -= offerList[offerIndex].getDiscountAmount()/100.0*costOfFlight;
		}
		string dateTime = flight->data.getDepartureTime() + "  " + numToStr(flight->data.getDay()) + "/" + numToStr(flight->data.getMonth()) + "/" + numToStr(flight->data.getYear());
		Ticket ticket(numToStr(customerId), customerList.getNode(customerId)->data.getName(), flightNumber, ticketNumber, classType, static_cast<int>(costOfFlight), discount, reasonForDiscount, dateTime, seatNumber);
		ticketList.insert(ticket);
		updateCustomerMiles(customerId, airportList.getMiles(flight->data.getDestination()), 1);
		cout << "\nFlight reserved successfully!\n";
	}	
}

void handleWaitingList(DNode<Flights>* flight, const int classTypeIndex) {
	int customerId = flight->data.getWaitingPassenger(classTypeIndex);
	if (customerId == -1) {
		return; // No one in waiting list
	}
	vector<int> seats = flight->data.getSeats();
	int seatNumber = generateSeatNumber(customerId, flight->data.getFlightNumber(), customerList.getNode(customerId)->data.getName(), seats);
	flight->data.insertPassenger(customerList.getNode(customerId)->data, classTypeIndex, seatNumber);
	int ticketNumber = generateTicketNumber(customerId, flight->data.getFlightNumber(), customerList.getNode(customerId)->data.getName());
	int offerIndex = checkDiscount(customerId, flight->data.getFlightNumber());
	bool discount = offerIndex != -1;
	string reasonForDiscount = "";
	if (discount) {
		reasonForDiscount = offerList[offerIndex].getOfferType();
	}
	double costOfFlight = flight->data.getTicketPrice(classTypeIndex);
	if (discount)
		costOfFlight -= offerList[offerIndex].getDiscountAmount() / 100.0 * costOfFlight;
	string dateTime = flight->data.getDepartureTime() + "  " + numToStr(flight->data.getDay()) + "/" + numToStr(flight->data.getMonth()) + "/" + numToStr(flight->data.getYear());
	Ticket ticket(numToStr(customerId), customerList.getNode(customerId)->data.getName(), flight->data.getFlightNumber(), ticketNumber, classTypeIndex == 0 ? "Business" : "Economy", static_cast<int>(costOfFlight), discount, reasonForDiscount, dateTime, seatNumber);
	ticketList.insert(ticket);
	updateCustomerMiles(customerId, airportList.getMiles(flight->data.getDestination()), 1);
}

void cancelReservation() {
	int customerId;
	cout << "Enter Customer ID to cancel reservation: ";
	inputPosInt(customerId);
	if(!customerList.search(customerId)) {
		cout << "\nCustomer ID not found! returning to the previous menu...\n";
		return;
	}
	int flightNumber;
	cout << "Enter the flight number for which you want to cancel reservation: ";
	inputPosInt(flightNumber);
	while(!flightList.search(flightNumber)) {
		cout << "\nFlight number not found! Please enter a valid flight number: ";
		inputPosInt(flightNumber);
	}
	DNode<Flights>* flight = flightList.getNode(flightNumber);
	int ticketNumber = ticketList.getTicketNumber(numToStr(customerId),flightNumber);
	if(ticketNumber == -1) {
		cout << "\nNo reservation found for this customer on the specified flight!\n";
		return;
	}
	else {
		Ticket* ticket = ticketList.getNode(ticketNumber);
		if (!ticket) {
			cout << "\nError: Ticket not found!\n";
			return;
		}
		int classTypeIndex = ticket->getTicketType() == "Business" ? 0 : 1;
		int seatNumber = ticket->getSeatNumber();
		flight->data.removePassenger(customerId, classTypeIndex, seatNumber);
		ticketList.Delete(ticketNumber);
		updateCustomerMiles(customerId, airportList.getMiles(flight->data.getDestination()), 0);
		handleWaitingList(flight,classTypeIndex);
		cout << "\nReservation cancelled successfully!\n";
	}
}

void changeReservation() {
	cancelReservation();
	cout << "\nNow, please provide details for the new reservation:\n";
	reserveFlight();
	cout << "\nReservation changed successfully!\n";
}

int main(){

	char choice;
	cout << "WELCOME TO 'EIGESS' AVIONICS\n";
	do {
		cout << "\nWhat do you wwant to inquire about: \n"
			"a. Flight Reservation\n"
			"b. Customers\n"
			"c. Flights\n"
			"d. Setup System Data\n"
			"e. Save Data to Text Files\n"
			"f. Exit\n";
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		choice = tolower(choice);
		if (choice == 'a') {
			do {
				cout << "\nChoose one of the following:\n"
					"a. Search for Destination\n"
					"b. Reserve Flight\n"
					"c. Cancel Reservation\n"
					"d. Change Reservation\n"
					"e. Back to the Main Menu\n";
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		choice = tolower(choice);
				
				if (choice == 'a') {
					string destination;
					cout << "\n Which country do you wanna tarvel to?\n>";
					getline(cin, destination);
					flightList.display(destination);
				}
				else if (choice == 'b') {
					reserveFlight();
				}
				else if (choice == 'c') {
					cancelReservation();
				}
				else if (choice == 'd') {
					changeReservation();
				}
				else if(choice!='e'){
					cout << "\nInvalid selection; please choose a valid option...\n";
				}
			} while (choice != 'e');
		}
		else if (choice == 'b') {
			do {
				cout << "\nChoose one of the following:\n"
					"a. Add Customer\n"
					"b. Update Customer Info\n"
					"c. Delete Customer\n"
					"d. View Customer Profile\n"
					"e. Back to the Main Menu\n";
				cin >> choice;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				choice = tolower(choice);
				if (choice == 'a') {
					addNewCustomer();
				}
				else if (choice == 'b') {
					updateCustomerInfo();
				}
				else if (choice == 'c') {
					deleteCustomer();
				}
				else if (choice == 'd') {
					viewCustomerProfile();
				}
				else if(choice != 'e'){
					cout << "\nInvalid selection; please choose a valid option...\n";
				}
			} while (choice != 'e');
		}
		else if (choice == 'c') {
			do {
				cout << "\nChoose one of the following:\n"
					"a. Add Flight\n"
					"b. Update Flight\n"
					"c. Delete Flight\n"
					"d. View Flights\n"
					"e. Back to the Main Menu\n";
				cin >> choice;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				choice = tolower(choice);
				if (choice == 'a') {
					addFlight();
				}
				else if (choice == 'b') {
					updateFlight();
				}
				else if (choice=='c') {
					deleteFlight();
				}
				else if (choice=='d') {
					viewFlight();
				}
				else if (choice!='e'){
					cout << "\nInvalid selection; please choose a valid option...\n";
				}
			} while (choice != 'e');
		}
		else if (choice == 'd') {
			setupSystemData();
		}
		else if (choice == 'e') {
			saveAllData();
		}
		else if (choice == 'f') {
			cout << "\nExiting 'Eigess'. It was an honour serving master!\n";
		}
		else {
			cout << "\nInvalid selection; please choose a valid option...\n";
		}
	} while (choice != 'f');
}