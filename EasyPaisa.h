#pragma once

#include <iostream>
#include "Admin.h"
#include "Payment.h"

using namespace std;

class EasyPaisa : public Payment
{
	int taxPercentage = 2;

public:
	EasyPaisa() {}

public:
	void setTaxPercentage(int taxPercentage) { this->taxPercentage = taxPercentage; }
	int getTaxPercentage() { return this->taxPercentage; }

public:
	virtual void processPayment(Doctor doc, Patient pat, int apptId, int apptType) {

		cout << doc.getBalance() << " " << pat.getAccountBalance();

		fstream apptFile;
		apptFile.open("data/payment.txt", ios::app);
		if (apptFile.is_open()) {
			apptFile
				<< "\n"
				<< apptId << ","
				<< "JazzCash" << ","
				<< doc.getHourlyCharges() << ","
				<< "Completed" << ","
				<< getTodayDate();

			apptFile.close();
		}

		// UPDATE PATIENT AND DOCTOR BALANCE
		float amountToAdd = 0;
		if (apptType != 1)	// if not InPerson, then 70% charges apply
			amountToAdd = 0.7 * doc.getHourlyCharges();
		else
			amountToAdd = doc.getHourlyCharges();

		doc.setBalance(doc.getBalance() + amountToAdd);
		pat.setAccountBalance(pat.getAccountBalance() - amountToAdd);

		addAmountToDoctorAccount(doc);
		deductAmountFromPatientAccount(pat);

		cout << "payment by jazz cash done" << endl;
	}

public:
	virtual void revertPayment(Doctor doc, Patient pat, int apptId, int apptType) {

		float chargesToAdd = deductAmountFromDoctorAccount(doc, apptType);
		addAmountToPatientAccount(pat, chargesToAdd);
	}

	void addAmountToDoctorAccount(Doctor doc) {
		Admin a;
		Doctor* doctors = a.getDoctors();

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
					<< (doctors[i].getCnic() == doc.getCnic() && doctors[i].getEmail() == doc.getEmail() ? doc.getBalance() : doctors[i].getBalance());
			}
			doctorFile.close();
			return;
		}
	}

	void deductAmountFromPatientAccount(Patient pat) {
		Admin a;
		Patient* patients = a.getPatients();

		int size;
		fstream patientCount;
		patientCount.open("data/patient_count.txt", ios::in);
		patientCount >> size;	// first line in the file contains size
		patientCount.close();


		if (size != 0) {
			fstream patientFile;
			patientFile.open("data/patient.txt", ios::out);
			if (patientFile.is_open()) {

				for (int i = 0; i < size; i++) {
					patientFile
						<< "\n"
						<< patients[i].getPersonId() << ","
						<< patients[i].getName() << ","
						<< patients[i].getUsername() << ","
						<< patients[i].getPassword() << ","
						<< patients[i].getCnic() << ","
						<< patients[i].getEmail() << ","
						<< (patients[i].getCnic() == pat.getCnic() && patients[i].getEmail() == pat.getEmail() ? pat.getAccountBalance() : patients[i].getAccountBalance());
				}
				patientFile.close();
			}
		}
	}

	float deductAmountFromDoctorAccount(Doctor doc, int apptType) {

		Admin a;
		Doctor* doctors = a.getDoctors();

		float amountToDeduct = 0;
		int size = 0;
		fstream doctorCount;

		doctorCount.open("data/doctor_count.txt", ios::in);
		doctorCount >> size;	// first line in the file contains size
		doctorCount.close();

		fstream doctorFile;
		if (size != 0) {
			doctorFile.open("data/doctor.txt", ios::out);

			for (int i = 0; i < size; i++) {
				if (doctors[i].getCnic() == doc.getCnic() && doctors[i].getEmail() == doc.getEmail()) {


					if (apptType != 1)	// if not InPerson, then 70% charges apply
						amountToDeduct = 0.7 * doctors[i].getHourlyCharges();
					else
						amountToDeduct = doctors[i].getHourlyCharges();

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
						<< doctors[i].getBalance() - amountToDeduct;
				}
				else {
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

			}
			doctorFile.close();
			return amountToDeduct;
		}
	}

	void addAmountToPatientAccount(Patient pat, float chargesToAdd) {
		Admin a;
		Patient* patients = a.getPatients();

		int size;
		fstream patientCount;
		patientCount.open("data/patient_count.txt", ios::in);
		patientCount >> size;	// first line in the file contains size
		patientCount.close();


		if (size != 0) {
			fstream patientFile;
			patientFile.open("data/patient.txt", ios::out);
			if (patientFile.is_open()) {

				for (int i = 0; i < size; i++) {
					patientFile
						<< "\n"
						<< patients[i].getPersonId() << ","
						<< patients[i].getName() << ","
						<< patients[i].getUsername() << ","
						<< patients[i].getPassword() << ","
						<< patients[i].getCnic() << ","
						<< patients[i].getEmail() << ","
						<< (patients[i].getCnic() == pat.getCnic() && patients[i].getEmail() == pat.getEmail() ? patients[i].getAccountBalance() + chargesToAdd : patients[i].getAccountBalance());
				}
				patientFile.close();
			}
		}
	}

};

