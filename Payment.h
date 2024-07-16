#pragma once
#include <iostream>
#include "Doctor.h"
#include "Patient.h"

using std::string;

class Payment
{
private:
	string date;
	string type;

public:
	Payment() {
	}

public:
	void setDate(string date) { this->date = date; }
	string getDate() { return this->date; }
	void setType(string type) { this->type = type; }
	string getType() { return this->type; }

public:
	virtual void processPayment(Doctor doc, Patient pat, int apptId, int apptType){}
public:
	virtual void revertPayment(Doctor doc, Patient pat, int apptId, int apptType) {}

	string getTodayDate() {
		time_t time;
		std::time(&time);
		tm* tm;
		tm = localtime(&time);
		char date[50];
		strftime(date, 50, "%d-%m-%y", tm);
		return date;
	}
};

