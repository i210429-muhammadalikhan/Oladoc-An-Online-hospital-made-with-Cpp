#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Person.h"
#include "Doctor.h"
#include "Patient.h"
#include "Feedback.h"

using namespace std;

class Admin : public Person
{
public:
	Admin() {
	}
public:
	virtual bool login(string username, string password) {
		fstream adminFile;
		adminFile.open("data/admin.txt", ios::in);
		if (adminFile.is_open()) {
			string line;
			getline(adminFile, line);
			stringstream ss(line);
			string user, pass;
			getline(ss, user, ',');
			getline(ss, pass, ',');

			adminFile.close();

			if (user == username && pass == password) {
				//Person p("admin", "", username, password);
				return true;
			}
			else {
				return false;
			}
		}
	}
public:
	Doctor* getDoctors() {
		Feedback feedback;
		int size;
		fstream doctorFile, doctorCount;

		doctorCount.open("data/doctor_count.txt", ios::in);
		doctorCount >> size;	// first line in the file contains size
		doctorCount.close();

		if (size != 0) {
			doctorFile.open("data/doctor.txt", ios::in);
			Doctor* doctors = new Doctor[size];

			Doctor d;
			string personId;
			string name;
			string username;
			string password;
			string cnic;
			string email;
			string category;
			string experience;
			string charges;
			string availability;
			string hospitalName;
			string city;
			string avgRating;
			string balance;
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
				getline(ss, category, ',');
				getline(ss, experience, ',');
				getline(ss, charges, ',');
				getline(ss, availability, ',');
				getline(ss, hospitalName, ',');
				getline(ss, city, ',');
				getline(ss, avgRating, ',');
				getline(ss, balance, ',');

				if ((!cnic.empty() || !email.empty()) && personId != "") {
					doctors[count].setPersonId(stoi(personId));
					doctors[count].setName(name);
					doctors[count].setUsername(username);
					doctors[count].setPassword(password);
					doctors[count].setCnic(cnic);
					doctors[count].setEmail(email);
					SpecializationCategory cat;
					cat.setName(category);
					doctors[count].setCategory(cat);
					doctors[count].setExperienceInYears(stoi(experience));
					doctors[count].setSize(size);
					doctors[count].setHourlyCharges(stoi(charges));
					doctors[count].setAvailabilituHours(availability);
					doctors[count].setHospitalName(hospitalName);
					doctors[count].setCity(city);
					doctors[count].setAvgRating(feedback.getAvgRatingOfDoctor(email != "" ? email : cnic));
					doctors[count].setBalance(stof(balance));

					count++;
				}
			}
			doctorFile.close();
			return doctors;
		}
		else {
			cout << "No Doctors Found!" << endl;
			return NULL;
		}
	}

	Patient* getPatients() {

		int size;
		fstream patientFile, patientCount;

		patientCount.open("data/patient_count.txt", ios::in);
		patientCount >> size;	// first line in the file contains size
		patientCount.close();

		if (size != 0) {
			patientFile.open("data/patient.txt", ios::in);
			Patient* patients = new Patient[size];

			Patient d;
			string personId;
			string name;
			string username;
			string password;
			string cnic;
			string email;
			string accountBalance;
			int count = 0;
			string line;

			while (getline(patientFile, line)) {
				stringstream ss(line);
				getline(ss, personId, ',');
				getline(ss, name, ',');
				getline(ss, username, ',');
				getline(ss, password, ',');
				getline(ss, cnic, ',');
				getline(ss, email, ',');
				getline(ss, accountBalance, ',');

				if ((!cnic.empty() || !email.empty()) && personId != "") {
					patients[count].setPersonId(stoi(personId));
					patients[count].setName(name);
					patients[count].setUsername(username);
					patients[count].setPassword(password);
					patients[count].setSize(size);
					patients[count].setCnic(cnic);
					patients[count].setEmail(email);
					patients[count].setAccountBalance(stof(accountBalance));

					count++;
				}
			}
			patientFile.close();
			return patients;
		}
		else {
			cout << "No Patients Found!" << endl;
			return NULL;
		}
	}

	void updatePatients(Patient* patient) {

		int size;
		fstream patientCount;

		patientCount.open("data/patient_count.txt", ios::in);
		patientCount >> size;	// first line in the file contains size
		patientCount.close();

		fstream patientFile;
		if (size != 0) {
			patientFile.open("data/patient.txt", ios::out);

			for (int i = 0; i < size; i++) {
				patientFile
					<< "\n"
					<< (size + 1) << ","
					<< patient[i].getName() << ","
					<< patient[i].getUsername() << ","
					<< patient[i].getPassword() << ","
					<< patient[i].getCnic() << ","
					<< patient[i].getEmail() << ","
					<< patient[i].getAccountBalance();
			}
			patientFile.close();
			return;
		}
	}

	void updateDoctors(Doctor* doctors) {

		int size;
		fstream doctorCount;

		doctorCount.open("data/doctor_count.txt", ios::in);
		doctorCount >> size;	// first line in the file contains size
		doctorCount.close();

		fstream doctorFile;
		if (size != 0) {
			doctorFile.open("data/doctor.txt", ios::out);

			for (int i = 0; i < size; i++) {
				doctorFile
					<< "\n"
					<< i + 1 << ","
					<< doctors[i].getName() << ","
					<< doctors[i].getUsername() << ","
					<< doctors[i].getPassword() << ","
					<< doctors[i].getCnic() << ","
					<< doctors[i].getEmail() << ","
					<< doctors[i].getCategory().getName() << ","
					<< doctors[i].getExperienceInYears() << ","
					<< doctors[i].getHourlyCharges() << ","
					<< doctors[i].getAvailabilituHours() << ","
					<< doctors[i].getHospitalName() << ","
					<< doctors[i].getCity() << ","
					<< doctors[i].getAvgRating() << ","
					<< doctors[i].getBalance() << ",";
			}
			doctorFile.close();
			return;
		}
	}

	void deleteDoctor(string cnicOrEmail) {
		Doctor* doctors = this->getDoctors();

		cout << doctors[0].getName() << endl;
		cout << doctors[1].getName() << endl;

		bool isEmail = false;
		if (cnicOrEmail.find("@") != std::string::npos)
			isEmail = true;

		int size;
		fstream doctorCount;

		doctorCount.open("data/doctor_count.txt", ios::in);
		doctorCount >> size;	// first line in the file contains size
		doctorCount.close();

		cout << size << endl;

		fstream doctorFile;
		if (size != 0) {
			doctorFile.open("data/doctor.txt", ios::out);

			for (int i = 0; i < size; i++) {
				if ((isEmail && doctors[i].getEmail() != cnicOrEmail) || (!isEmail && doctors[i].getCnic() != cnicOrEmail)) {
					cout << doctors[i].getCnic() << doctors[i].getEmail() << endl;
					doctorFile
						<< "\n"
						<< i + 1 << ","
						<< doctors[i].getName() << ","
						<< doctors[i].getUsername() << ","
						<< doctors[i].getPassword() << ","
						<< doctors[i].getCnic() << ","
						<< doctors[i].getEmail() << ","
						<< doctors[i].getCategory().getName() << ","
						<< doctors[i].getExperienceInYears() << ","
						<< doctors[i].getHourlyCharges() << ","
						<< doctors[i].getAvailabilituHours() << ","
						<< doctors[i].getHospitalName() << ","
						<< doctors[i].getCity() << ","
						<< doctors[i].getAvgRating() << ","
						<< doctors[i].getBalance();
				}
				else {
					cout << "****************************************************************************************************************************************" << endl;
					cout << doctors[i].getName() << " Deleted Successfully!" << endl;
					cout << "****************************************************************************************************************************************" << endl;
				}
			}
			doctorFile.close();
		}
		else {
			cout << "No Doctor Found!" << endl;
		}
		return;
	}

	
	Doctor getDoctorByCnicOrEmail(string cnicOrEmail) {
		Admin a;
		Doctor* doctors = a.getDoctors();

		int size;
		fstream doctorCount;

		doctorCount.open("data/doctor_count.txt", ios::in);
		doctorCount >> size;	// first line in the file contains size
		doctorCount.close();

		for (int i = 0; i < size; i++) {
			if (doctors[i].getCnic() == cnicOrEmail || doctors[i].getEmail() == cnicOrEmail) {
				return doctors[i];
			}
		}
	}

	Doctor getDoctorByUsername(string username) {
		Admin a;
		Doctor* doctors = a.getDoctors();

		int size;
		fstream doctorCount;

		doctorCount.open("data/doctor_count.txt", ios::in);
		doctorCount >> size;	// first line in the file contains size
		doctorCount.close();

		for (int i = 0; i < size; i++) {
			if (doctors[i].getUsername() == username) {
				return doctors[i];
			}
		}
	}

	Patient getPatientByUsername(string username) {
		Admin a;
		Patient* patients = a.getPatients();

		int size;
		fstream patientCount;

		patientCount.open("data/patient_count.txt", ios::in);
		patientCount >> size;	// first line in the file contains size
		patientCount.close();

		for (int i = 0; i < size; i++) {
			if (patients[i].getUsername() == username) {
				return patients[i];
			}

		}
	}

	Doctor* searchDoctorByCity(string city) {
		Admin a;
		Doctor* doctors = a.getDoctors();

		int size;
		fstream doctorCount;

		doctorCount.open("data/doctor_count.txt", ios::in);
		doctorCount >> size;	// first line in the file contains size
		doctorCount.close();

		for (int i = 0; i < size; i++) {
			if (doctors[i].getCity() == city) {

			}
		}
	}

	float getDoctorRating(string cnicOrEmail) {
		Feedback feedback;
		float rating = feedback.getAvgRatingOfDoctor(cnicOrEmail);
		return rating > 0 ? rating : 0 ;
	}
	
	

};


