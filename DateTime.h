#pragma once
#include <iostream>
#include <ctime>


class DateTime
{

public: DateTime(){}
public: 
	tm* getToday() {
	time_t now = std::time(0);   
	tm* today = std::localtime(&now);
	return today;
}
};

