#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <time.h>
#include <stdlib.h>

#include "Payment.h"
#include "Admin.h"
#include "JazzCash.h"
#include "EasyPaisa.h"
#include "PayPak.h"

using namespace std;

class Appointment
{
private:
	string apptId;
	string time;
	string status;
	string type;
	Doctor doc;
	Patient pat;
	int size;
	

public:
	Appointment() {}
public:
	void setTime(string time) { this->time = time; }
	string getTime() { return this->time; }
	void setStatus(string status) { this->status = status; }
	string getStatus() { return this->status; }
	void setType(string type) { this->type = type; }
	string getType() { return this->type; }
	void setApptId(string apptId) { this->apptId = apptId; }
	string getApptId() { return this->apptId; }
	void setSize(int size) { this->size = size; }
	int getSize() { return this->size; }
	void setDoc(Doctor doc) { this->doc = doc; }
	Doctor getDoc() { return this->doc; }
	void setPat(Patient pat) { this->pat = pat; }
	Patient getPat() { return this->pat; }


	
	void scheduleAppointment(Doctor doc, Patient pat, int apptType, int payMethod, string slot) {

		cout << doc.getName() << endl;
		cout << pat.getName() << endl;

		int size;
		fstream apptCount;
		apptCount.open("data/appointment_count.txt", ios::in);
		apptCount >> size;	
		apptCount.close();

		fstream apptFile;
		apptFile.open("data/appointment.txt", ios::app);

		if (apptFile.is_open()) {
			int apptId = getRandomNumber();
			apptFile
				<< "\n"
				<< apptId << ","
				<< (doc.getCnic().length() == 13 ? doc.getCnic() : doc.getEmail()) << ","
				<< doc.getName() << ","
				<< (pat.getCnic().length() == 13 ? pat.getCnic() : pat.getEmail()) << ","
				<< pat.getName() << ","
				<< (apptType == 1 ? "InPerson" : "Online") << ","
				<< "SCHEDULED" << ","
				<< slot;

			apptFile.close();

			// UPDATE SIZE IN FILE
			apptCount.open("data/appointment_count.txt", ios::out);
			apptCount << (size + 1);
			apptCount.close();
			
			Payment *pay;
			switch (payMethod) {
				case 1:
					pay = new JazzCash;
					pay->processPayment(doc, pat, apptId, apptType);
					break;
				case 2:
					pay = new EasyPaisa;
					pay->processPayment(doc, pat, apptId, apptType);
					break;
				case 3:
					pay = new PayPak;
					pay->processPayment(doc, pat, apptId, apptType);
					break;
				default:
					break;
			}
			cout << "****************************************************************************************************************************************" << endl;
			cout << "An Appointment With Dr. " << doc.getName() << " Is Scheduled Successfully!" << endl;
			cout << "****************************************************************************************************************************************" << endl;
		}
	}

	Appointment* getAppointments() {

		int size = getNumberOfAppts();
		fstream apptFile;

		if (size != 0) {
			apptFile.open("data/appointment.txt", ios::in);
			Appointment* appts = new Appointment[size];

			string apptId;
			string docCNICorEmail;
			string docName;
			string patCNICorEmail;
			string patName;
			string type;
			string status;
			string time;
			int count = 0;
			string line;

			while (getline(apptFile, line)) {
				stringstream ss(line);
				getline(ss, apptId, ',');
				getline(ss, docCNICorEmail, ',');
				getline(ss, docName, ',');
				getline(ss, patCNICorEmail, ',');
				getline(ss, patName, ',');
				getline(ss, type, ',');
				getline(ss, status, ',');
				getline(ss, time, ',');


				if (docCNICorEmail != "" && patCNICorEmail != "" && apptId != "") {
					appts[count].setApptId(apptId);

					// initialize doctor
					Doctor doc;
					if (docCNICorEmail.find("@") != std::string::npos) {
						doc.setEmail(docCNICorEmail);
					}
					else {
						doc.setCnic(docCNICorEmail);
					}
					doc.setName(docName);
					appts[count].setDoc(doc);

					Patient pat;

					if (patCNICorEmail.find("@") != std::string::npos) {
						pat.setEmail(patCNICorEmail);
					}
					else {
						pat.setCnic(patCNICorEmail);
					}
					pat.setName(patName);
					appts[count].setPat(pat);

					appts[count].setSize(size);
					appts[count].setType(type);
					appts[count].setStatus(status);
					appts[count].setTime(time);

					count++;
				}
			}
			apptFile.close();
			return appts;
		}
		else {
			cout << "No Appointments Found!" << endl;
			return NULL;
		}
	}

	Appointment* getAppointmentsByDoctor(string cnicOrEmail) {

		int size = getNumberOfAppts();
		fstream apptFile;

		if (size != 0) {
			apptFile.open("data/appointment.txt", ios::in);
			Appointment* appts = new Appointment[size];

			string apptId;
			string docCNICorEmail;
			string docName;
			string patCNICorEmail;
			string patName;
			string type;
			string status;
			string time;
			int count = 0;
			string line;

			while (getline(apptFile, line)) {
				stringstream ss(line);
				getline(ss, apptId, ',');
				getline(ss, docCNICorEmail, ',');
				getline(ss, docName, ',');
				getline(ss, patCNICorEmail, ',');
				getline(ss, patName, ',');
				getline(ss, type, ',');
				getline(ss, status, ',');
				getline(ss, time, ',');

				if (cnicOrEmail == docCNICorEmail) {
					if (docCNICorEmail != "" && patCNICorEmail != "" && apptId != "") {
						appts[count].setApptId(apptId);

						// initialize doctor
						Doctor doc;
						if (docCNICorEmail.find("@") != std::string::npos) {
							doc.setEmail(docCNICorEmail);
						}
						else {
							doc.setCnic(docCNICorEmail);
						}
						doc.setName(docName);
						appts[count].setDoc(doc);

						Patient pat;

						if (patCNICorEmail.find("@") != std::string::npos) {
							pat.setEmail(patCNICorEmail);
						}
						else {
							pat.setCnic(patCNICorEmail);
						}
						pat.setName(patName);
						appts[count].setPat(pat);

						appts[count].setSize(size);
						appts[count].setType(type);
						appts[count].setStatus(status);
						appts[count].setTime(time);

						count++;
					}
				}
			}
			apptFile.close();
			return appts;
		}
		else {
			cout << "No Appointments Found!" << endl;
			return NULL;
		}
	}

	Appointment* getAppointmentsByPatient(string cnicOrEmail) {

		int size = getNumberOfAppts();
		fstream apptFile;

		if (size != 0) {
			apptFile.open("data/appointment.txt", ios::in);
			Appointment* appts = new Appointment[size];

			string apptId;
			string docCNICorEmail;
			string docName;
			string patCNICorEmail;
			string patName;
			string type;
			string status;
			string time;
			int count = 0;
			string line;

			while (getline(apptFile, line)) {
				stringstream ss(line);
				getline(ss, apptId, ',');
				getline(ss, docCNICorEmail, ',');
				getline(ss, docName, ',');
				getline(ss, patCNICorEmail, ',');
				getline(ss, patName, ',');
				getline(ss, type, ',');
				getline(ss, status, ',');
				getline(ss, time, ',');

				if (cnicOrEmail == patCNICorEmail) {
					if (docCNICorEmail != "" && patCNICorEmail != "" && apptId != "") {
						appts[count].setApptId(apptId);

						// initialize doctor
						Doctor doc;
						if (docCNICorEmail.find("@") != std::string::npos) {
							doc.setEmail(docCNICorEmail);
						}
						else {
							doc.setCnic(docCNICorEmail);
						}
						doc.setName(docName);
						appts[count].setDoc(doc);

						Patient pat;

						if (patCNICorEmail.find("@") != std::string::npos) {
							pat.setEmail(patCNICorEmail);
						}
						else {
							pat.setCnic(patCNICorEmail);
						}
						pat.setName(patName);
						appts[count].setPat(pat);

						appts[count].setSize(size);
						appts[count].setType(type);
						appts[count].setStatus(status);
						appts[count].setTime(time);

						count++;
					}
				}
			}
			apptFile.close();
			return appts;
		}
		else {
			cout << "No Appointments Found!" << endl;
			return NULL;
		}
	}

	void cancelAppointment(string apptId) {
		Appointment* appts = this->getAppointments();
		int size = getNumberOfAppts();

		fstream apptFile;
		apptFile.open("data/appointment.txt", ios::out);
		if (apptFile.is_open()) {
			for (int i = 0; i < size; i++)
			{
				if (apptId == appts[i].getApptId()) {
					apptFile
						<< "\n"
						<< appts[i].getApptId() << ","
						<< (appts[i].getDoc().getEmail() != "" ? appts[i].getDoc().getEmail() : appts[i].getDoc().getCnic()) << ","
						<< appts[i].getDoc().getName() << ","
						<< (appts[i].getPat().getEmail() != "" ? appts[i].getPat().getEmail() : appts[i].getPat().getCnic()) << ","
						<< appts[i].getPat().getName() << ","
						<< appts[i].getType() << ","
						<< "CANCELED" << ","
						<< appts[i].getTime();

					Payment *pay = new JazzCash;
					pay->revertPayment(appts[i].getDoc(), appts[i].getPat(), stoi(appts[i].getApptId()), 
						appts[i].getType() == "InPerson" ? 1 : 2);
				}
				else {
					apptFile
						<< "\n"
						<< appts[i].getApptId() << ","
						<< (appts[i].getDoc().getEmail() != "" ? appts[i].getDoc().getEmail() : appts[i].getDoc().getCnic()) << ","
						<< appts[i].getDoc().getName() << ","
						<< (appts[i].getPat().getEmail() != "" ? appts[i].getPat().getEmail() : appts[i].getPat().getCnic()) << ","
						<< appts[i].getPat().getName() << ","
						<< appts[i].getType() << ","
						<< (apptId == appts[i].getApptId() ? "CANCELED" : appts[i].getStatus()) << ","
						<< appts[i].getTime();
				}
				
			}
		}
		apptFile.close();

		cout << "****************************************************************************************************************************************" << endl;
		cout << "Appointment Cancelled Successfully!" << endl;
		cout << "****************************************************************************************************************************************" << endl;
	}

	int getNumberOfAppts() {
		int num = 0;
		fstream apptCount, apptFile;
		apptCount.open("data/appointment_count.txt", ios::in);
		apptCount >> num;
		apptCount.close();
		return num;
	}

	string getDate() {
		time_t curr_time;
		tm* curr_tm;
		char date_string[100];

		std::time(&curr_time);
		curr_tm = localtime(&curr_time);

		strftime(date_string, 50, "%d-%m-%y", curr_tm);
		cout << date_string << endl;
	}

	int getRandomNumber() {
		srand(std::time(NULL));   
		return rand();
	}

	

	

};