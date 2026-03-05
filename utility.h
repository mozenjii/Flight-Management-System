#pragma once
#include <limits>
#include <iostream>
using namespace std;

void inputInt(int& choice) {
	bool valid = false;
	do {
		if (cin >> choice)
			valid = true;
		else {
			cout << "Invalid input. Please enter a number: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (!valid);
}

void inputFloat(float& choice) {
	bool valid = false;
	do {
		if (cin >> choice)
			valid = true;
		else {
			cout << "Invalid input. Please enter a number: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (!valid);
}

void inputDouble(double& choice) {
	bool valid = false;
	do {
		if (cin >> choice)
			valid = true;
		else {
			cout << "Invalid input. Please enter a number: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (!valid);
}

void inputPosInt(int& choice) {
	bool valid = false;
	do {
		if (cin >> choice) {
			if (choice >= 0)
				valid = true;
			else {
				cout << "Invalid input. Please enter a positive number: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		else {
			cout << "Invalid input. Please enter a positive number: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (!valid);
}

void inputPosFloat(float& choice) {
	bool valid = false;
	do {
		if (cin >> choice) {
			if (choice >= 0)
				valid = true;
			else {
				cout << "Invalid input. Please enter a positive number: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		else {
			cout << "Invalid input. Please enter a positive number: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (!valid);
}


int strToNum(string str) {
	int scope = 1, num = 0;

	for (int i = 1; i < str.length(); i++)
		scope *= 10;

	for (int i = 0; i < str.length(); i++) {
		int numtemp = 0;
		if (isdigit(str[i])) {
			numtemp = (str[i] - '0') * scope;
			scope /= 10;
		}
		num += numtemp;
	}

	return num;
}

int charToNum(char chr) {
	for (int j = 48; j <= 57; j++) {
		if ((chr) == j)
			return j - 48;
	}
	return -909;
}


string numToStr(int num) {
	if (num == 0) return "0";

	string str = "";
	bool isNegative = false;

	if (num < 0) {
		isNegative = true;
		num = -num;
	}

	while (num > 0) {
		int digit = num % 10;
		str = static_cast<char>('0' + digit) + str;
		num /= 10;
	}

	if (isNegative) str = "-" + str;
	return str;
}

bool isDigit(char c) {
	return c >= '0' && c <= '9';
}

