//calculate solution gap means
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
	string line;
	string instance;
	string file;

	int counter;

	float meanGap = 0;
	float totalGap;
	float gap;

	ifstream infile ("GMeanT5-2.txt");

	if (infile.is_open()){
		while (getline (infile, line)){
			counter = 0;
			totalGap = 0;

			while (counter < 6){
				infile >> instance;
				infile >> file;
				infile >> file;
				infile >> file;
				infile >> gap;
				//cout << "\nGap: " << gap << endl;
				totalGap += gap;
				//cout << "Total Gap: " << totalGap << endl;
				counter++;
			}
			meanGap = totalGap/(float)6;

			cout << instance << " - Gap Mean by instance: " <<  meanGap << endl;
		}
		infile.close();
		cout << endl;
	}

	else cout << "Unable to open file"; 

	return 0;
}