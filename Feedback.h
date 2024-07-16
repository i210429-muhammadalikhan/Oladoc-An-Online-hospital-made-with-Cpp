#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <stdlib.h>

using namespace std;

class Feedback
{
private:
	string review;
	int rating;

public: Feedback() {}

public:
	void setReview(string review) { this->review = review; }
	string getReview() { return this->review; }
	void setRating(int rating) { this->rating = rating; }
	int getRating() { return this->rating; }

	void saveFeedback(string docCnicOrEmail, string patCnicOrEmail) {

		int size;
		fstream fbCount;
		fbCount.open("data/feedback_count.txt", ios::in);
		fbCount >> size;
		fbCount.close();

		fstream fbFile;
		fbFile.open("data/feedback.txt", ios::app);

		if (fbFile.is_open()) {

			fbFile
				<< "\n"
				<< docCnicOrEmail << ","
				<< patCnicOrEmail << ","
				<< this->getRating() << ","
				<< this->getReview();

			fbFile.close();

			// UPDATE SIZE IN FILE
			fbCount.open("data/feedback_count.txt", ios::out);
			fbCount << (size + 1);
			fbCount.close();
		}
	}
	
	float getAvgRatingOfDoctor(string cnicOrEmail) {
		
		fstream apptFile;
		apptFile.open("data/feedback.txt", ios::in);
			
			string docCNICorEmail;
			string patCNICorEmail;
			string rating;
			string line;

			int count = 0;
			int avgRating = 0;
			while (getline(apptFile, line)) {
				stringstream ss(line);
				getline(ss, docCNICorEmail, ',');
				getline(ss, patCNICorEmail, ',');
				getline(ss, rating, ',');
				
				if (docCNICorEmail == cnicOrEmail) {
					avgRating += stoi(rating);
					count++;
				}
			}
		apptFile.close();
		if (count != 0)
			return avgRating / count;
		else
			return 0;	
	}

};

