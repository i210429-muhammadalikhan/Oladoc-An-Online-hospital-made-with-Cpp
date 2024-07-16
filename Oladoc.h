#pragma once
#include <iostream>
#include <iomanip>
# include <string>
# include <cctype>
#include <ctime>

#include "DateTime.h"
#include "Admin.h"
#include "Appointment.h"
#include "Feedback.h"

using namespace std;

class Oladoc
{
public: 
	string systemName;
	int menuOption;
	const char separator = ' ';
	const int stringColumnWidth = 15;
	const int intColumnWidth = 8;
	string loggedInPatientUsername = "";
	string loggedInDoctorUsername = "";
    
public:
	Oladoc() {
		systemName = "Oladoc - Digital Healthcare";
	}
	void run() {
		int loginAs = 0;
		int registerAs = 0;
		cout << systemName + " " + "Version 1.0";
		do {
			system("cls");
			showRoleMenu();
			menuOption = getMenuOption();
			switch (menuOption) {
			case 1:
				cout << "Login As: \n";
				cout << "1 > Admin: \n";
				cout << "2 > Doctor: \n";
				cout << "3 > Patient: \n";
				cout << "Selection: ";
				cin >> loginAs;
				switch (loginAs) {
					case 1:
						if (loginAdmin())
							showAdmin();
						system("PAUSE");
						break;
					case 2:
						if (loginDoctor())
							showDoctor();
						system("PAUSE");
						break; 
					case 3:
						if (loginPatient())
							showPatient();
						system("PAUSE");
						break;
				}
				system("PAUSE");
				break;
			/*
			case 2:
				if (loginAdmin())
					showAdmin();
				system("PAUSE");
				break;
			case 3:
				if (loginDoctor())
					showDoctor();
				system("PAUSE");
				break;
			case 4:
				if (loginPatient())
					showPatient();
				system("PAUSE");
				break;
			*/
			case 2:
				cout << "Register As: \n";
				cout << "1 > Doctor: \n";
				cout << "2 > Patient: \n";
				cout << "Selection: ";
				cin >> registerAs;
				switch (registerAs) {
				case 1:
					registerDoctor();
					system("PAUSE");
					break;
				case 2:
					registerPatient();
					system("PAUSE");
					break;
				}
				break;
			/*
			case 5:
				registerDoctor();
				system("PAUSE");
				break;
			case 6:
				registerPatient();
				system("PAUSE");
				break; 
			case 7:
				cout << isValidPassword("1/Lw6789"); // VALID
				system("PAUSE");
				break;
			*/
			default:
				break;
			}
		} while (menuOption != 3);
	}

	void showAdmin() {

		do {
			system("cls");
			showAdminMenu();
			menuOption = getMenuOption();
			switch (menuOption) {
			case 1:
				getDoctors();
				crudDoctor();	// create/read/update/delete doctor
				system("PAUSE");
				break;
			case 2:
				getPatients();
				system("PAUSE");
				break;
			case 3:
				getDoctors();
				resetDoctorPassword();
				system("PAUSE");
				break;
			default:
				break;
			}
		} while (menuOption != 4);
	}

	void showDoctor() {
		int result = 0;
		do {
			system("cls");
			showDoctorMenu();
			menuOption = getMenuOption();
			switch (menuOption) {
			case 1:
				result = getDoctorAppointments();
				if (result > 0) {
					cancelAppointment();
					result = 0;
				}
				system("PAUSE");
				break;
			case 2:
				doctorProfile();
				system("PAUSE");
				break;
			default:
				break;
			}
		} while (menuOption != 3);
	}

	void showPatient() {
		int result = 0;
		do {
			system("cls");
			showPatientMenu();
			menuOption = getMenuOption();
			switch (menuOption) {
			case 1:
				 result = getPatientAppointments();
				 if (result > 0) {
					 cancelAppointment();
					 result = 0;
				 }
				system("PAUSE");
				break;
			case 2:
				viewPatientProfile();
				system("PAUSE");
				break;
			case 3:
				result = searchDoctorByCategory();
				if (result > 0) {
					showSlotsAndBookAppointment();
					result = 0;
				}
				system("PAUSE");
				break;
			case 4:
				result = searchDoctorByCity();
				if (result > 0) {
					showSlotsAndBookAppointment();
					result = 0;
				}
				system("PAUSE");
				break;
			case 5:
				result = searchDoctorByHospital();
				if (result > 0) {
					showSlotsAndBookAppointment();
					result = 0;
				}
				system("PAUSE");
				break;
			case 6:
				getFeedback();
				system("PAUSE");
				break;
			case 7:
				resetPatientPassword();
				system("PAUSE");
				break;
			default:
				break;
			}
		} while (menuOption != 8);
	}


	void crudDoctor() {

		do {
			//system("cls");
			showEditDoctorMenu();
			menuOption = getMenuOption();
			switch (menuOption) {
			case 1:
				registerDoctor();
				system("PAUSE");
				break;
			case 2:
				editDoctor();
				system("PAUSE");
				break;
			case 3:
				deleteDoctor();
				system("PAUSE");
				break;
			default:
				break;
			}
		} while (menuOption != 4);
	}

	void showRoleMenu()
	{
		cout << "Choose Menu\n";
		cout << "Please make your selection\n";
		cout << "1 - Login\n";
		cout << "2 - Register\n";
		cout << "3 - Quit\n";
		cout << "Selection: ";
		/*
		cout << "Choose Menu\n";
		cout << "Please make your selection\n";
		cout << "1 - Doctors\n";
		cout << "2 - Login As Admin\n";
		cout << "3 - Login As Doctor\n";
		cout << "4 - Login As Patient\n";
		cout << "5 - Register As Doctor\n";
		cout << "6 - Register As Patient\n";
		//cout << "7 - Password Validity\n";
		cout << "6 - Quit\n";
		cout << "Selection: ";
		*/
	}

	void showAdminMenu()
	{
		cout << "Choose Menu\n";
		cout << "Please make your selection\n";
		cout << "1 - Doctors\n";
		cout << "2 - Patients\n";
		cout << "3 - Reset Doctor Password\n";
		cout << "Selection: ";
	}

	void showDoctorMenu() {
		cout << "Choose Menu\n";
		cout << "Please make your selection\n";
		cout << "1 - My Appointments\n";
		cout << "2 - My Profile\n";
		cout << "3 - Quit\n";
		cout << "Selection: ";
	}

	void showPatientMenu() {
		cout << "Choose Menu\n";
		cout << "Please make your selection\n";
		cout << "1 - My Appointments\n";
		cout << "2 - View Profile\n";
		cout << "3 - Search Doctor By - Category/Speciality\n";
		cout << "4 - Search Doctor By - City\n";
		cout << "5 - Search Doctor By - Hospital\n";
		cout << "6 - Feedback\n";
		cout << "7 - Reset Password\n";
		cout << "8 - Quit\n";
		cout << "Selection: ";
	}

	void showEditDoctorMenu()
	{
		cout << "Choose Menu\n";
		cout << "Please make your selection\n";
		cout << "1 - Add Doctor\n";
		cout << "2 - Edit Doctor\n";
		cout << "3 - Delete Doctor\n";
		cout << "4 - Quit\n";
		cout << "Selection: ";
	}

	int getMenuOption() {
		cin >> menuOption;
		return menuOption;
	}

	bool loginAdmin() {
		Person p = getUsernameAndPassword();
		Admin a;
		bool isLoggedIn = a.login(p.getUsername(), p.getPassword());
		
		if (isLoggedIn) {
			return true;
		} else {
			cout << "Invalid Username/Password\n";
			return false;
		}
	}

	bool loginDoctor() {
		Person p = getUsernameAndPassword();
		Doctor doc;
		bool isLoggedIn = doc.login(p.getUsername(), p.getPassword());

		if (isLoggedIn) {
			loggedInDoctorUsername = p.getUsername();
			return true;
		}
		else {
			cout << "Invalid Username/Password\n";
			return false;
		}
	}

	bool loginPatient() {
		Person p = getUsernameAndPassword();
		Patient pat;
		bool isLoggedIn = pat.login(p.getUsername(), p.getPassword());

		if (isLoggedIn) {
			loggedInPatientUsername = p.getUsername();
			return true;
		}
		else {
			cout << "Invalid Username/Password\n";
			return false;
		}
	}

	Person getUsernameAndPassword() {
		Person p;
		string username, password;
		cout << "Username: ";
		cin >> username;
		p.setUsername(username);
		cout << "Password: ";
		cin >> password;
		p.setPassword(password);
		return p;
	}

	void registerDoctor() {
		Doctor doc;
		string name, username, password, cnicOrEmail, availabilityHours, hospitalName, city, specialty;
		int experienceInYears, hourlyCharges;

		cout << "Username: ";
		cin >> username;
		doc.setUsername(username);
		doc.setPassword(getPassword());
		doc = doc.validateCnicOrEmail(doc);

		cout << "Full Name: ";
		cin >> name;
		doc.setName(name);

		cout << "Category (Specialty): ";
		cin >> specialty;
		SpecializationCategory cat;
		cat.setName(specialty);
		doc.setCategory(cat);

		cout << "Availability Hours: ";
		cin >> availabilityHours;
		doc.setAvailabilituHours(availabilityHours);

		cout << "Hospital Name: ";
		cin >> hospitalName;
		doc.setHospitalName(hospitalName);

		cout << "City: ";
		cin >> city;
		doc.setCity(city);

		cout << "Experience (Years): ";
		cin >> experienceInYears;
		doc.setExperienceInYears(experienceInYears);

		cout << "Charges: ";
		cin >> hourlyCharges;
		doc.setHourlyCharges(hourlyCharges);

		doc.registerDoctor(doc);

	}

	void editDoctor() {
		string cnicOrEmail;
		cout << "Enter Doctor CNIC or Email: ";
		cin >> cnicOrEmail;

		Admin a;
		Doctor* doctors = a.getDoctors();
		int arrSize = doctors[0].getSize();
		for (int i = 0; i < arrSize; i++) {
			if (doctors[i].getCnic() == cnicOrEmail || doctors[i].getEmail() == cnicOrEmail) {
				cout << "*****************************************************************************************************************************************************" << endl;
				cout << "Showing " << doctors[i].getName() << " Information . . ." << endl;
				cout << "*****************************************************************************************************************************************************" << endl;
				printPrettyTable("NAME", stringColumnWidth);
				printPrettyTable("CNIC", stringColumnWidth);
				printPrettyTable("EMAIL", stringColumnWidth * 2);
				printPrettyTable("EXPERIENCE", stringColumnWidth);
				printPrettyTable("CHARGES", stringColumnWidth);
				printPrettyTable("HOURS", stringColumnWidth);
				printPrettyTable("HOSPITAL", stringColumnWidth);
				printPrettyTable("CITY", stringColumnWidth);
				printPrettyTable("RATING", stringColumnWidth);
				cout << endl;
				cout << "*****************************************************************************************************************************************************" << endl;
				printPrettyTable(doctors[i].getName(), stringColumnWidth);
				printPrettyTable(doctors[i].getCnic(), stringColumnWidth);
				printPrettyTable(doctors[i].getEmail(), stringColumnWidth * 2);
				printPrettyTable(doctors[i].getExperienceInYears(), stringColumnWidth);
				printPrettyTable(doctors[i].getHourlyCharges(), stringColumnWidth);
				printPrettyTable(doctors[i].getAvailabilituHours(), stringColumnWidth);
				printPrettyTable(doctors[i].getHospitalName(), stringColumnWidth);
				printPrettyTable(doctors[i].getCity(), stringColumnWidth);
				printPrettyTable(doctors[i].getAvgRating(), stringColumnWidth);
				cout << endl;
				cout << "*****************************************************************************************************************************************************" << endl;

				string name, username, password, cnicOrEmail, availabilityHours, hospitalName, city;
				int experienceInYears, hourlyCharges;
				cout << "Full Name: ";
				cin >> name;
				doctors[i].setName(name);

				cout << "Availability Hours: ";
				cin >> availabilityHours;
				doctors[i].setAvailabilituHours(availabilityHours);

				cout << "Hospital Name: ";
				cin >> hospitalName;
				doctors[i].setHospitalName(hospitalName);

				cout << "City: ";
				cin >> city;
				doctors[i].setCity(city);

				cout << "Experience (Years): ";
				cin >> experienceInYears;
				doctors[i].setExperienceInYears(experienceInYears);

				cout << "Charges: ";
				cin >> hourlyCharges;
				doctors[i].setHourlyCharges(hourlyCharges);
				
				break;
			}
		}
		a.updateDoctors(doctors);
		return;
	}

	void deleteDoctor() {
		string cnicOrEmail;
		cout << "Enter Doctor CNIC or Email: ";
		cin >> cnicOrEmail;

		Admin a;
		a.deleteDoctor(cnicOrEmail);
		return;
	}

	void registerPatient() {
		Patient pat;
		string name, username, password, cnicOrEmail;

		cout << "Username: ";
		cin >> username;
		pat.setUsername(username);
		pat.setPassword(getPassword());
		pat = pat.validateCnicOrEmail(pat);

		cout << "Full Name: ";
		cin >> name;
		pat.setName(name);

		cout << pat.getEmail();
		pat.registerPatient(pat);
	}

	string getPassword() {
		string password = "";
		string rePassword = "";
		cout << "****************************************************************************************************************************************" << endl;
		cout << "Password must 8 characters long and the use of a minimum of one special character, uppercase, lowercase, and the numeric digit is a must" << endl;
		cout << "Password & confirm password should be same" << endl;
		cout << "****************************************************************************************************************************************" << endl;
		do {
			cout << "Password: ";
			cin >> password;
		} while (!isValidPassword(password));

		do {
			cout << "Confirm Password: ";
			cin >> rePassword;
		} while (password != rePassword);
		return password;
	}

	void getDoctors() {
		Admin a;
		Doctor* doctors = a.getDoctors();
		printDoctors(doctors);
		return;
	}

	void printDoctors(Doctor* doctors) {
		//int arrSize = sizeof(*doctors) / sizeof(doctors[0]);
		int arrSize = doctors[0].getSize();

		/* TABLE HEADING */

		cout << "******************************************************************************************************************************************************************" << endl;
		printDoctorTableHeading();
		cout << endl;
		cout << "******************************************************************************************************************************************************************" << endl;
		
		for (int i = 0; i < arrSize; i++) {
			printDoctorData(doctors[i]);
			cout << endl;
		}
		cout << "******************************************************************************************************************************************************************" << endl;
		return;
	}

	void getPatients() {
		Admin a;
		Patient* patients = a.getPatients();
		printPatients(patients);
		return;
	}

	void printPatients(Patient* patients) {
		//int arrSize = sizeof(*doctors) / sizeof(doctors[0]);
		int arrSize = patients[0].getSize();

		/* TABLE HEADING */

		cout << "*****************************************************************************************************************************************************" << endl;
		printPrettyTable("NAME", stringColumnWidth);
		printPrettyTable("CNIC", stringColumnWidth);
		printPrettyTable("EMAIL", stringColumnWidth * 2);
		printPrettyTable("BALANCE", stringColumnWidth);
		cout << endl;
		cout << "*****************************************************************************************************************************************************" << endl;

		for (int i = 0; i < arrSize; i++) {
			printPrettyTable(patients[i].getName(), stringColumnWidth);
			printPrettyTable(patients[i].getCnic(), stringColumnWidth);
			printPrettyTable(patients[i].getEmail(), stringColumnWidth * 2);
			printPrettyTable(patients[i].getAccountBalance(), stringColumnWidth);
			cout << endl;
		}
		cout << "*****************************************************************************************************************************************************" << endl;
		return;
	}

	template<typename T> void printPrettyTable(T t, const int& width) {
		cout << left << setw(width) << setfill(separator) << t;
	}

	bool isValidPassword(string password) {
		bool containsDigit = false;
		bool containsUpper = false;
		bool containsLower = false;
		bool containsSpecial = false;

		if (!isPasswordLengthValid(password)) return false;

		for (char c : password) {
			isupper(c) ? containsLower = true
			: islower(c) ? containsUpper= true
			: isdigit(c) ? containsDigit = true
			: isSpecialChar(c) ? containsSpecial = true : containsSpecial = false; // invalid character
		}
		if (containsDigit && containsSpecial && containsUpper && containsLower ) {
			return true;
		}
		else {
			cout << "****************************************************************************************************************************************" << endl;
			cout << "Password must 8 characters long and the use of a minimum of one special character, uppercase, lowercase, and the numeric digit is a must" << endl;
			cout << "Password Mismatch" << endl;
			cout << "****************************************************************************************************************************************" << endl;
			return false;
		}
			
	}

	bool isPasswordLengthValid(string password) {
		int MIN_MAX_CHARACTERS = 8;
		if (password.size() < MIN_MAX_CHARACTERS)
			return false;
		if (password.size() > MIN_MAX_CHARACTERS)
			return false;
		return true;
	}
	
	bool isSpecialChar(char c) {
		string specialChars = "!@#$%^&*()_+{}><?/~`";
		return specialChars.find(c) != string::npos;
	}

	int getDoctorAppointments() {
		Appointment appt; Admin a;
		Doctor doc = a.getDoctorByUsername(loggedInDoctorUsername);

		string cnicOrEmail = doc.getEmail() != "" ? doc.getEmail() : doc.getCnic();
		Appointment* appts = appt.getAppointmentsByDoctor(cnicOrEmail);
		cout << "name: " << appts[0].getDoc().getName() << endl;
		int arrSize = appts[0].getSize();

		/* TABLE HEADING */
		cout << "***********************************************************************************************************************************************************" << endl;
		printAppointmentTableHeading();
		cout << endl;
		cout << "***********************************************************************************************************************************************************" << endl;
		int searchResults = 0;
		for (int i = 0; i < arrSize; i++) {
			printAppointmentData(appts[i]);
			cout << endl;
			searchResults++;
		}
		cout << "***********************************************************************************************************************************************************" << endl;

		return searchResults;
	}
	
	int getPatientAppointments() {
		Appointment appt; Admin a;
		Patient pat = a.getPatientByUsername(loggedInPatientUsername);

		string cnicOrEmail = pat.getCnic().length() == 13 ? pat.getCnic() : pat.getEmail();
		Appointment* appts = appt.getAppointmentsByPatient(cnicOrEmail);
		cout << "name: " << appts[0].getDoc().getName() << endl;
		int arrSize = appts[0].getSize();

		/* TABLE HEADING */
		cout << "***********************************************************************************************************************************************************" << endl;
		printAppointmentTableHeading();
		cout << endl;
		cout << "***********************************************************************************************************************************************************" << endl;
		int searchResults = 0;
		for (int i = 0; i < arrSize; i++) {
				printAppointmentData(appts[i]);
				cout << endl;
				searchResults++;
		}
		cout << "***********************************************************************************************************************************************************" << endl;
		
		return searchResults;
	}

	void cancelAppointment() {
		string apptId;
		cout << "*****************************************************************************************************************************************************" << endl;
		cout << "For Appointment Cancellation, Enter Appointment ID: ";
		cin >> apptId;
		if (apptId == "0") {
			return;
		}
		Appointment appt;
		appt.cancelAppointment(apptId);
	}

	void viewPatientProfile() {
		Admin a;
		Patient pat = a.getPatientByUsername(loggedInPatientUsername);

		cout << "*****************************************************************************************************************************************************" << endl;
		printPrettyTable("Name", stringColumnWidth * 2); cout << pat.getName() << endl;
		printPrettyTable("Username", stringColumnWidth * 2); cout << pat.getUsername() << endl;
		printPrettyTable("CNIC/Email", stringColumnWidth * 2); cout << (pat.getEmail() != "" ? pat.getEmail() : pat.getCnic()) << endl;
		printPrettyTable("Account Balance", stringColumnWidth * 2); cout << pat.getAccountBalance() << endl;
		cout << "*****************************************************************************************************************************************************" << endl;
	}


	void resetDoctorPassword() {
		string cnicOrEmail;
		cout << "*****************************************************************************************************************************************************" << endl;
		cout << "Enter Doctor CNIC/Email to Reset Password: ";
		cin >> cnicOrEmail;

		Admin a;
		Doctor doc = a.getDoctorByCnicOrEmail(cnicOrEmail);
		Doctor* doctors = a.getDoctors();
		int arrSize = doctors[0].getSize();
		for (int i = 0; i < arrSize; i++) {
			if (doctors[i].getEmail() == doc.getEmail() && doctors[i].getCnic() == doc.getCnic()) {
				doctors[i].setPassword("12345@Ab");
			}
		}
		a.updateDoctors(doctors);
		cout << "*****************************************************************************************************************************************************" << endl;
		cout << "Password Reset Successfully, New Password: 12345@Ab" << endl;
		cout << "*****************************************************************************************************************************************************" << endl;
	}

	void resetPatientPassword() {
		Admin a;
		Patient pat = a.getPatientByUsername(loggedInPatientUsername);

		Patient* patients = a.getPatients();
		int arrSize = patients[0].getSize();
		for (int i = 0; i < arrSize; i++) {
			if (patients[i].getEmail() == pat.getEmail() && patients[i].getCnic() == pat.getCnic()) {
				patients[i].setPassword("12345@Ab");
			}
		}
		a.updatePatients(patients);
		cout << "*****************************************************************************************************************************************************" << endl;
		cout << "Password Reset Successfully, New Password: 12345@Ab" << endl;
		cout << "*****************************************************************************************************************************************************" << endl;
	}

	void doctorProfile() {
		Admin a;
		Doctor doc = a.getDoctorByUsername(loggedInDoctorUsername);
		int personId;
		string name;
		string cnic;
		string email;
		string username;
		string password;
		int experienceInYears;
		int hourlyCharges;
		string availabilituHours;
		SpecializationCategory category;
		string hospitalName;
		string city;
		float avgRating;
		int size;
		float balance;

		cout << "*****************************************************************************************************************************************************" << endl;
		printPrettyTable("Name", stringColumnWidth * 2); cout << doc.getName() << endl;
		printPrettyTable("Username", stringColumnWidth * 2); cout << doc.getUsername() << endl;
		printPrettyTable("CNIC/Email", stringColumnWidth * 2); cout << (doc.getEmail() != "" ? doc.getEmail() : doc.getCnic()) << endl;
		printPrettyTable("Specialization", stringColumnWidth * 2); cout << doc.getCategory().getName() << endl;
		printPrettyTable("Experience", stringColumnWidth * 2); cout << doc.getExperienceInYears() << " Yrs" << endl;
		printPrettyTable("Hourly Charges", stringColumnWidth * 2); cout << doc.getHourlyCharges() << endl;
		printPrettyTable("Availability Hours", stringColumnWidth * 2); cout << doc.getAvailabilituHours() << endl;
		printPrettyTable("Rating", stringColumnWidth * 2); cout << a.getDoctorRating((doc.getEmail() != "" ? doc.getEmail() : doc.getCnic())) << endl;
		cout << "*****************************************************************************************************************************************************" << endl;

		int selection = 0;
		cout << "Choose Menu\n";
		cout << "Please make your selection\n";
		cout << "1 - Edit Availability Hours\n";
		cout << "2 - Edit Hourly Charges\n";
		cout << "Selection: ";
		cin >> selection;
		switch (selection) {
			case 1:
				updateDoctorAvailability(doc);
				break;
			case 2:
				updateDoctorCharges(doc);
				break;
			default: 
				break;
		}
	}

	void updateDoctorAvailability(Doctor doc) {
		string availHours = "";
		cout << "Enter Availability Hours: ";
		cin >> availHours;

		Admin a;
		Doctor* doctors = a.getDoctors();
		int arrSize = doctors[0].getSize();
		for (int i = 0; i < arrSize; i++) {
			if (doctors[i].getEmail() == doc.getEmail() && doctors[i].getCnic() == doc.getCnic()) {
				doctors[i].setAvailabilituHours(availHours);
			}
		}
		a.updateDoctors(doctors);
		cout << "*****************************************************************************************************************************************************" << endl;
		cout << "Availability Hourly Updated Successfully!" << endl;
		cout << "*****************************************************************************************************************************************************" << endl;
	}

	void updateDoctorCharges(Doctor doc) {
		int hourlyCharges = 0;
		cout << "Enter Hourly Charges: ";
		cin >> hourlyCharges;

		Admin a;
		Doctor* doctors = a.getDoctors();
		int arrSize = doctors[0].getSize();
		for (int i = 0; i < arrSize; i++) {
			if (doctors[i].getEmail() == doc.getEmail() && doctors[i].getCnic() == doc.getCnic()) {
				doctors[i].setHourlyCharges(hourlyCharges);
			}
		}
		a.updateDoctors(doctors);
		cout << "*****************************************************************************************************************************************************" << endl;
		cout << "Hourly Charges Updated Successfully!" << endl;
		cout << "*****************************************************************************************************************************************************" << endl;
	}


	int searchDoctorByCategory() {
		string category;
		cout << "Enter Category/Specialty: ";
		cin >> category;
		Admin a;
		Doctor* doctors = a.getDoctors();
		int arrSize = doctors[0].getSize();

		/* TABLE HEADING */
		cout << "*****************************************************************************************************************************************************" << endl;
		printDoctorTableHeading();
		cout << endl;
		cout << "*****************************************************************************************************************************************************" << endl;
		int searchResults = 0;
		for (int i = 0; i < arrSize; i++) {
			if (doctors[i].getCategory().getName() == category) {
				printDoctorData(doctors[i]);
				cout << endl;
				searchResults++;
			}
		}
		cout << "*****************************************************************************************************************************************************" << endl;
		return searchResults;
	}

	int searchDoctorByCity() {
		string city;
		cout << "Enter City: ";
		cin >> city;
		Admin a;
		Doctor* doctors = a.getDoctors();
		int arrSize = doctors[0].getSize();

		/* TABLE HEADING */

		cout << "*****************************************************************************************************************************************************" << endl;
		printDoctorTableHeading();
		cout << endl;
		cout << "*****************************************************************************************************************************************************" << endl;
		int searchResults = 0;
		for (int i = 0; i < arrSize; i++) {
			if (doctors[i].getCity() == city) {
				printDoctorData(doctors[i]);
				cout << endl;
				searchResults++;
			}
		}
		cout << "*****************************************************************************************************************************************************" << endl;
		return searchResults;
	}

	int searchDoctorByHospital() {
		string hospital;
		cout << "Enter Hospital Name: ";
		cin >> hospital;
		Admin a;
		Doctor* doctors = a.getDoctors();
		int arrSize = doctors[0].getSize();

		/* TABLE HEADING */

		cout << "*****************************************************************************************************************************************************" << endl;
		printDoctorTableHeading();
		cout << endl;
		cout << "*****************************************************************************************************************************************************" << endl;
		int searchResults = 0;
		for (int i = 0; i < arrSize; i++) {
			if (doctors[i].getHospitalName() == hospital) {
				printDoctorData(doctors[i]);
				cout << endl;
				searchResults++;
			}
		}
		cout << "*****************************************************************************************************************************************************" << endl;
		return searchResults;
	}

	void showSlotsAndBookAppointment() {
		int slotNumber = 1;
		string cnicOrEmail, appointmentType, slot;
		int payMethod;
		cout << "*****************************************************************************************************************************************************" << endl;
		cout << "Enter Doctor CNIC/Email to Book Appointment: ";
		cin >> cnicOrEmail;
		if (cnicOrEmail == "0")
			return;
		cout << "Enter 1 for In-Person & 2 for Online Appointment: ";
		cin >> appointmentType;
		cout << "Available Payment Methods: \n";
		cout << "Enter 1 for - Jazz Cash  \n";
		cout << "Enter 2 for - Easy Paisa \n";
		cout << "Enter 3 for - PayPak \n";
		cout << "Enter Payment Method: ";
		cin >> payMethod;


		time_t base;
		tm* curr_tm;
		char date_string[100];

		time(&base);
		//time_t base = 1142085600;
		cout << "************************************************" << endl;
		cout << "Available Day/Time Slots: " << endl;
		cout << "************************************************" << endl;
		for (int i = 0; i < 4; ++i) {
			struct tm* tm = localtime(&base);
			tm->tm_mday += i;
			time_t next = mktime(tm);
			std::cout << i + 1 << " | " << ctime(&next);
		}
		cout << "************************************************" << endl;

		cout << "Enter Slot Number to Book Appointment: ";
		cin >> slotNumber;

		for (int i = 0; i < 4; ++i) {
			struct tm* tm = localtime(&base);
			tm->tm_mday += i;
			time_t next = mktime(tm);
			if ((slotNumber - 1) == i)
				slot = ctime(&next);
		}
		cout << slot << endl;
		bookAppointment(cnicOrEmail, stoi(appointmentType), payMethod, slot);
	}

	void bookAppointment(string doctorCnicOrEmail, int appointmentType, int payMethod, string slot) {
		Doctor doc;
		Patient pat;
		Admin a;
		pat = a.getPatientByUsername(loggedInPatientUsername);
		doc = a.getDoctorByCnicOrEmail(doctorCnicOrEmail);

		if (pat.getAccountBalance() >= doc.getHourlyCharges()) {
			Appointment apt;
			apt.scheduleAppointment(doc, pat, appointmentType, payMethod, slot);
		}
		else {
			cout << "************************************************" << endl;
			cout << "Error, Patient Account Balance Is Low!" << endl;
			cout << "************************************************" << endl;
		}	
	}

	void getFeedback() {
		getPatientAppointments();
		string cnicOrEmail, review;
		int rating;
		cout << "Enter Doctor CNIC/Email for Feedback: ";
		cin >> cnicOrEmail;
		cout << "Enter Rating (0-5): ";
		cin >> rating;
		cout << "Enter Review: ";
		cin >> review;
		

		if (rating < 0 || rating > 5) {
			cout << "Invalid Rating, Please try again! ";
		}
		else {
			Patient pat;
			Admin a;
			pat = a.getPatientByUsername(loggedInPatientUsername);
			string patCnicOrEmail = pat.getEmail() != "" ? pat.getEmail() : pat.getCnic();

			Feedback feedback;
			feedback.setRating(rating);
			feedback.setReview(review);
			feedback.saveFeedback(cnicOrEmail, patCnicOrEmail);
		}
	}


	void printDoctorTableHeading() {
		printPrettyTable("NAME", stringColumnWidth);
		printPrettyTable("CNIC", stringColumnWidth);
		printPrettyTable("EMAIL", stringColumnWidth + 5);
		printPrettyTable("Category", stringColumnWidth);
		printPrettyTable("EXPERIENCE", stringColumnWidth);
		printPrettyTable("CHARGES", stringColumnWidth);
		printPrettyTable("HOURS", stringColumnWidth);
		printPrettyTable("HOSPITAL", stringColumnWidth);
		printPrettyTable("CITY", stringColumnWidth);
		printPrettyTable("RATING", stringColumnWidth);
		printPrettyTable("BALANCE", stringColumnWidth);
	}
	void printDoctorData(Doctor doctor) {
		printPrettyTable(doctor.getName(), stringColumnWidth);
		printPrettyTable(doctor.getCnic(), stringColumnWidth);
		printPrettyTable(doctor.getEmail(), stringColumnWidth + 5);
		printPrettyTable(doctor.getCategory().getName(), stringColumnWidth);
		printPrettyTable(doctor.getExperienceInYears(), stringColumnWidth);
		printPrettyTable(doctor.getHourlyCharges(), stringColumnWidth);
		printPrettyTable(doctor.getAvailabilituHours(), stringColumnWidth);
		printPrettyTable(doctor.getHospitalName(), stringColumnWidth);
		printPrettyTable(doctor.getCity(), stringColumnWidth);
		printPrettyTable(doctor.getAvgRating(), stringColumnWidth);
		printPrettyTable(doctor.getBalance(), stringColumnWidth);
	}

	void printAppointmentTableHeading() {
		printPrettyTable("ID", stringColumnWidth);
		printPrettyTable("Doc. CNIC/Email", stringColumnWidth * 2);
		printPrettyTable("Doc. Name", stringColumnWidth);
		printPrettyTable("Pat. CNIC/Email", stringColumnWidth * 2);
		printPrettyTable("Pat. Name", stringColumnWidth);
		printPrettyTable("Type", stringColumnWidth);
		printPrettyTable("Status", stringColumnWidth);
		printPrettyTable("Day/Time", stringColumnWidth);
	}
	void printAppointmentData(Appointment appt) {
		printPrettyTable(appt.getApptId(), stringColumnWidth);
		printPrettyTable(
			(appt.getDoc().getEmail() != "" ? appt.getDoc().getEmail() : appt.getDoc().getCnic())
			, stringColumnWidth * 2);
		printPrettyTable(appt.getDoc().getName(), stringColumnWidth);
		printPrettyTable(
			(appt.getPat().getEmail() != "" ? appt.getPat().getEmail() : appt.getPat().getCnic())
			, stringColumnWidth * 2);
		printPrettyTable(appt.getPat().getName(), stringColumnWidth);

		printPrettyTable(appt.getType(), stringColumnWidth);
		printPrettyTable(appt.getStatus(), stringColumnWidth);
		printPrettyTable(appt.getTime(), stringColumnWidth);
	}

};

