#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Person.h"
#include "SpecializationCategory.h"

using namespace std;

class Doctor : public Person
{
private:
	int experienceInYears;
	int hourlyCharges;
	string availabilituHours;
	SpecializationCategory category;
	string hospitalName;
	string city;
	float avgRating;
	int size;
	float balance;

public:
	Doctor() {}
public:
	Doctor(string availabilituHours) {
		availabilituHours = availabilituHours;
	}
public:
	Doctor(int experienceInYears,
		int hourlyCharges,
		string availabilituHours,
		string hospitalName,
		string city) {
		experienceInYears = experienceInYears;
		hourlyCharges = hourlyCharges;
		availabilituHours = availabilituHours;
		hospitalName = hospitalName;
		city = city;
	}

public:
	virtual bool login(string username, string password) {

		cout << username << " " << password << endl;

		int size;
		fstream docCount;
		docCount.open("data/doctor_count.txt", ios::in);
		docCount >> size;
		docCount.close();

		bool isValidLogin = false;
		fstream docFile;
		docFile.open("data/doctor.txt", ios::in);
		if (docFile.is_open()) {
			for (int i = 0; i < size; i++) {

				string line;
				getline(docFile, line);
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
		docFile.close();
		return isValidLogin;
	}

public:
	void setExperienceInYears(int experienceInYears) { this->experienceInYears = experienceInYears; }
	int getExperienceInYears() { return this->experienceInYears; }
	void setHourlyCharges(int hourlyCharges) { this->hourlyCharges = hourlyCharges; }
	int getHourlyCharges() { return this->hourlyCharges; }
	void setSize(int size) { this->size = size; }
	int getSize() { return this->size; }

	void setAvailabilituHours(string availabilituHours) { this->availabilituHours = availabilituHours; }
	string getAvailabilituHours() { return this->availabilituHours; }
	void setHospitalName(string hospitalName) { this->hospitalName = hospitalName; }
	string getHospitalName() { return this->hospitalName; }
	void setCity(string city) { this->city = city; }
	string getCity() { return this->city; }
	void setAvgRating(float  avgRating) { this->avgRating = avgRating; }
	float  getAvgRating() { return this->avgRating; }
	void setBalance(float balance) { this->balance = balance; }
	float getBalance() { return this->balance; }

	void setCategory(SpecializationCategory category) { this->category = category; }
	SpecializationCategory getCategory() { return this->category; }

	Doctor validateCnicOrEmail(Doctor doc) {
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
				if(cnicOrEmail.length() == 13) {
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
		int size;
		fstream doctorCount;
		doctorCount.open("data/doctor_count.txt", ios::in);
		doctorCount >> size;
		doctorCount.close();
		if (size != 0) {
			Doctor* doctors = new Doctor[size];

			fstream doctorFile;
			doctorFile.open("data/doctor.txt", ios::in);
			if (doctorFile.is_open()) {

				Doctor d;
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
	}

	bool validateCnicExistence(string inputEmail) {
		int size;
		fstream doctorCount;
		doctorCount.open("data/doctor_count.txt", ios::in);
		doctorCount >> size;
		doctorCount.close();
		if (size != 0) {
			Doctor* doctors = new Doctor[size];

			fstream doctorFile;
			doctorFile.open("data/doctor.txt", ios::in);
			if (doctorFile.is_open()) {
				Doctor d;
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
	}

	void registerDoctor(Doctor doc) {
		int size;
		fstream doctorCount;
		doctorCount.open("data/doctor_count.txt", ios::in);
		doctorCount >> size;	// first line in the file contains size
		doctorCount.close();


		fstream doctorFile;
		doctorFile.open("data/doctor.txt", ios::app);

		if (doctorFile.is_open()) {
			//doctorFile << "\n";
			doctorFile
				<< "\n"
				<< (size + 1) << ","
				<< doc.getName() << ","
				<< doc.getUsername() << ","
				<< doc.getPassword() << ","
				<< doc.getCnic() << ","
				<< doc.getEmail() << ","
				<< doc.getCategory().getName() << ","
				<< doc.getExperienceInYears() << ","
				<< doc.getHourlyCharges() << ","
				<< doc.getAvailabilituHours() << ","
				<< doc.getHospitalName() << ","
				<< doc.getCity() << ","
				<< 0.0;

			doctorFile.close();

			// UPDATE SIZE IN FILE
			doctorCount.open("data/doctor_count.txt", ios::out);
			doctorCount << (size + 1);
			doctorCount.close();

			cout << "****************************************************************************************************************************************" << endl;
			cout << "Congratualtions, Dr. " << doc.getName() << " Registered Successfully!" << endl;
			cout << "****************************************************************************************************************************************" << endl;
		}
	}

	
	


};

