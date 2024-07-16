#pragma once
#include <string>

using namespace std;

class SpecializationCategory
{
private:
	string name;


public:
	SpecializationCategory() {}
public:
	SpecializationCategory(string name) {
		name = name;
	}

public:
	void setName(string name) { this->name = name; }
	string getName() { return this->name; }
};

