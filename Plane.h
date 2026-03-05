#pragma once
#include <iostream>
using namespace std;


class Plane {
	int planeId;
	string description;
	int numberOfMilesTraveled;
	int numberOfSeatsPerClass[2]; //0 for business and 1 for economy
public:
	Plane(int planeId, string description, int numberOfMilesTraveled, int numberOfSeatsBusinessClass, int numberOfSeatsEconomyClass) : planeId(planeId), description(description), numberOfMilesTraveled(numberOfMilesTraveled) {
		numberOfSeatsPerClass[0] = numberOfSeatsBusinessClass;
		numberOfSeatsPerClass[1] = numberOfSeatsEconomyClass;
	}
	int getPlaneId() {
		return planeId;
	}
	int getKey()const {
		return planeId;
	}
	string getDescription() {
		return description;
	}
	int getNumberOfMilesTraveled() {
		return numberOfMilesTraveled;
	}
	int getNumberOfSeatsPerClass(int classType) {
		return numberOfSeatsPerClass[classType];
	}
	void setDescription(string desc) {
		description = desc;
	}
	void setNumberOfMilesTraveled(int miles) {
		numberOfMilesTraveled = miles;
	}
	void display() {
		cout << "\nPlane ID: " << planeId << endl;
		cout << "Description: " << description << endl;
		cout << "Number of Miles Traveled: " << numberOfMilesTraveled << " miles" << endl;
		cout << "Number of Seats in Business Class: " << numberOfSeatsPerClass[0] << endl;
		cout << "Number of Seats in Economy Class: " << numberOfSeatsPerClass[1] << endl;
	}
};