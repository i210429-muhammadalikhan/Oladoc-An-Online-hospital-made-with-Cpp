#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Person.h"

using namespace std;


class Patient : public Person
{
private:
	float accountBalance;
	int size;

public:
	Patient() {
		accountBalance = 3500;
	}

public:
	virtual bool login(string username, string password) {

		cout << username << " " << password << endl;

		int size;
		fstream patientCount;
		patientCount.open("data/patient_count.txt", ios::in);
		patientCount >> size;
		patientCount.close();

		bool isValidLogin = false;
		fstream adminFile;
		adminFile.open("data/patient.txt", ios::in);
		if (adminFile.is_open()) {
			for (int i = 0; i < size; i++) {

				string line;
				getline(adminFile, line);
				stringstream ss(line);

				string id, name, user, pass;
				getline(ss, id, ',');
				getline(ss, name, ',');
				getline(ss, user, ',');
				getline(ss, pass, ',');

				if (user == username && pass == password) {
					isValidLogin = true;
					break;
				}
			}
		}
		adminFile.close();
		return isValidLogin;
	}

public:
	
	void setAccountBalance(float  accountBalance) { this->accountBalance = accountBalance; }
	float  getAccountBalance() { return this->accountBalance; }
	void setSize(int size) { this->size = size; }
	int getSize() { return this->size; }

	Patient validateCnicOrEmail(Patient doc) {
		string cnicOrEmail;
		for (int i = 0; i < 10; i++) {
			cout << "CNIC or Email: ";
			cin >> cnicOrEmail;
			if (cnicOrEmail.find("@") != std::string::npos) {// it is email
				if (validateEmailExistence(cnicOrEmail)) {
					cout << "****************************************************************************************************************************************" << endl;
					cout << "Account already registered with this email. Please use another email." << endl;
					cout << "****************************************************************************************************************************************" << endl;
				}
				else {
					doc.setEmail(cnicOrEmail);
					break;
				}
			}
			else {
				if (cnicOrEmail.length() == 13) {
					if (validateCnicExistence(cnicOrEmail)) {
						cout << "****************************************************************************************************************************************" << endl;
						cout << "Account already registered with this CNIC. Please use another CNIC." << endl;
						cout << "****************************************************************************************************************************************" << endl;
					}
					else {
						doc.setCnic(cnicOrEmail);
						break;
					}
				}
				else {
					cout << "****************************************************************************************************************************************" << endl;
					cout << "Invalid CNIC. Please enter a 13 digit CNIC number." << endl;
					cout << "****************************************************************************************************************************************" << endl;
				}
			}
		}
		return doc;
	}

	bool validateEmailExistence(string inputEmail) {
		cout << "validateEmailExistence";
		int size;
		fstream patientCount;
		patientCount.open("data/patient_count.txt", ios::in);
		patientCount >> size;
		patientCount.close();
		if (size != 0) {
			Patient* doctors = new Patient[size];

			fstream doctorFile;
			doctorFile.open("data/patient.txt", ios::in);
			if (doctorFile.is_open()) {

				Patient d;
				string personId;
				string name;
				string username;
				string password;
				string cnic;
				string email;
				int count = 0;
				string line;

				while (getline(doctorFile, line)) {
					stringstream ss(line);
					getline(ss, personId, ',');
					getline(ss, name, ',');
					getline(ss, username, ',');
					getline(ss, password, ',');
					getline(ss, cnic, ',');
					getline(ss, email, ',');
					
					if (!email.empty() && email == inputEmail) {
						return true;
					}
				}
			}
			return false;
		}
		else {
			return false;
		}
	}

	bool validateCnicExistence(string inputEmail) {
		int size;
		fstream patientCount;
		patientCount.open("data/patient_count.txt", ios::in);
		patientCount >> size;
		patientCount.close();
		if (size != 0) {
			Patient* doctors = new Patient[size];

			fstream doctorFile;
			doctorFile.open("data/patient.txt", ios::in);
			if (doctorFile.is_open()) {

				Patient d;
				string personId;
				string name;
				string username;
				string password;
				string cnic;
				int count = 0;
				string line;

				while (getline(doctorFile, line)) {
					stringstream ss(line);
					getline(ss, personId, ',');
					getline(ss, name, ',');
					getline(ss, username, ',');
					getline(ss, password, ',');
					getline(ss, cnic, ',');

					if (!cnic.empty() && cnic == inputEmail) {
						return true;
					}
				}
			}
			return false;
		}
		else {
			return false;
		}
	}

	void registerPatient(Patient doc) {
		int size;
		fstream patientCount;
		patientCount.open("data/patient_count.txt", ios::in);
		patientCount >> size;	// first line in the file contains size
		patientCount.close();

		fstream patientFile;
		patientFile.open("data/patient.txt", ios::app);
		if (patientFile.is_open()) {
			
			patientFile
				<< "\n"
				<< (size + 1) << ","
				<< doc.getName() << ","
				<< doc.getUsername() << ","
				<< doc.getPassword() << ","
				<< doc.getCnic() << ","
				<< doc.getEmail() << ","
				<< 3500;
			
			patientFile.close();

			// UPDATE SIZE IN FILE
			patientCount.open("data/patient_count.txt", ios::out);
			patientCount << (size + 1);
			patientCount.close();

			cout << "****************************************************************************************************************************************" << endl;
			cout << doc.getName() << " Registered Successfully!" << endl;
			cout << "****************************************************************************************************************************************" << endl;
		}
	}

	


};

