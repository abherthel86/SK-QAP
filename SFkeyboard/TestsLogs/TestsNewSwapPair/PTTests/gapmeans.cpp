//calculate solution gap means
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
	string line;
	string instance;

	int counter;

	float meanGap = 0;
	float totalGap;
	float gap;

	ifstream infile ("GapsPT15x4n.txt");
	ofstream offile;

	offile.open ("GMeanPT15x4n.txt", ios::out | ios::app);

	if (infile.is_open()){
		while (getline (infile, line)){
			counter = 0;
			totalGap = 0;

			while (counter < 10){
				infile >> instance;
				infile >> gap;
				//cout << "\nGap: " << gap << endl;
				totalGap += gap;
				//cout << "Total Gap: " << totalGap << endl;
				counter++;
			}
			meanGap = totalGap/(float)10;

			offile << instance << " - Gap Mean: " <<  meanGap << endl;
		}
		infile.close();
		offile.close();
		cout << endl;
	}

	else cout << "Unable to open file"; 

	return 0;
}