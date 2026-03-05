#pragma once
#include <iostream>
#include <string>
using namespace std;

class Offers {
	int offerId;
	int flightNumber;
	string offerType;
	int discountAmount;
public:
	Offers(int offerId = -1, int flightNumber = -1, string offerType = "", int discountAmount = 0) : offerId(offerId), offerType(offerType), discountAmount(discountAmount), flightNumber(flightNumber){}
	int getOfferId()const {
		return offerId;
	}
	string getOfferType()const {
		return offerType;
	}
	int getDiscountAmount()const {
		return discountAmount;
	}
	int getFlightNumber()const {
		return flightNumber;
	}
	void setOfferType(string type) {
		offerType = type;
	}
	void setDiscountAmount(int amount) {
		discountAmount = amount;
	}

	void setFlightNumber(int flightNum) {
		flightNumber = flightNum;
	}
	void setOfferId(int id) {
		offerId = id;
	}
	void display() {
		cout << "\nOffer ID: " << offerId << endl;
		cout << "Flight Number: " << flightNumber << endl;
		cout << "Offer Type: " << offerType << endl;
		cout << "Discount Amount: " << discountAmount << "%" << endl;
	}
	void setOfferDetails(int offerId, int flightNumber, string offerType,int discountAmount) {
		this->offerId = offerId;
		this->flightNumber = flightNumber;
		this->offerType = offerType;
		this->discountAmount = discountAmount;
	}
};