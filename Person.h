#pragma once
#include <iostream>
using std::string;

class Person
{
private:
	int personId;
	string name;
	string cnic;
	string email;
	string username;
	string password;

public:
	Person() {
	}
public:
	Person(string name, string cnic, string email, string username, string password) {
		name = name;
		cnic = cnic;
		email = email;
		username = username;
		password = password;
		personId = 0;
	}

public:
	virtual bool login(string username, string password) { 
		return false;
	}


public:
	void setPersonId(int personId) { this->personId = personId; }
	int getPersonId() { return this->personId; }
	void setName(string name) { this->name = name; }
	string getName() { return this->name; }
	void setCnic(string cnic) { this->cnic = cnic; }
	string getCnic() { return this->cnic; }
	void setEmail(string email) { this->email = email; }
	string getEmail() { return this->email; }
	void setUsername(string username) { this->username = username; }
	string getUsername() { return this->username; }
	void setPassword(string password) { this->password = password; }
	string getPassword() { return this->password; }

};

