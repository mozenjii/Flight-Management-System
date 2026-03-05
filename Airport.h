#pragma once
#include <iostream>
using namespace std;


class Airport {
	string airportName;
	string country;
	string usualWeatherCondition;
	int timeFromBeirut;
	int milesFromBeirut;
public:
	Airport(string airportName, string country, string usualWeatherCondition, int timeFromBeirut, int milesFromBeirut) : airportName(airportName), country(country), usualWeatherCondition(usualWeatherCondition), timeFromBeirut(timeFromBeirut), milesFromBeirut(milesFromBeirut) {}
	string getAirportName() {
		return airportName;
	}
	string getKey()const {
		return airportName;
	}
	string getCountry() {
		return country;
	}
	string getUsualWeatherCondition() {
		return usualWeatherCondition;
	}
	int getTimeFromBeirut() {
		return timeFromBeirut;
	}
	int getMilesFromBeirut() {
		return milesFromBeirut;
	}
	void setUsualWeatherCondition(string condition) {
		usualWeatherCondition = condition;
	}
	void setTimeFromBeirut(int time) {
		timeFromBeirut = time;
	}
	void setMilesFromBeirut(int miles) {
		milesFromBeirut = miles;
	}
	void display() {
		cout << "\nAirport Name: " << airportName << endl;
		cout << "Country: " << country << endl;
		cout << "Usual Weather Condition: " << usualWeatherCondition << endl;
		cout << "Time from Beirut: " << timeFromBeirut << " hours" << endl;
		cout << "Miles from Beirut: " << milesFromBeirut << " miles" << endl;
	}
};