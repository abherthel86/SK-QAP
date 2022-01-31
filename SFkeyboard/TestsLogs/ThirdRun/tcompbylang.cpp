//calculate solution gap means
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
	string line;
	string instance;

	string file;

	double tGap;
	double langtGap;
	double meanGap;

	int counter = 0;

	ifstream infile ("tcompT1T2.txt");

	if (infile.is_open()){
		while (getline (infile, line)){
			counter = 0;
			langtGap = 0;
			while (counter < 6){
				infile >> instance;

				infile >> file;
				infile >> file;
				infile >> file;
				infile >> file;
				infile >> file;

				infile >> tGap;
				infile >> file;

				langtGap += tGap;
				counter++;
			}

			meanGap = langtGap/6;
			cout << instance << " - Time Gap Mean by instance: " <<  meanGap << " %%" << endl;
		}

		infile.close();
		cout << endl;
	}

	else cout << "Unable to open file"; 
	
	// ifstream infile ("tcompT3T4T5.txt");

	// if (infile.is_open()){
	// 	while (getline (infile, line)){
	// 		counter = 0;
	// 		langtGap = 0;
	// 		while (counter < 6){
	// 			infile >> instance;

	// 			infile >> file;
	// 			infile >> file;
	// 			infile >> file;
	// 			infile >> file;
	// 			infile >> file;

	// 			infile >> tGap;
	// 			infile >> file;

	// 			langtGap += tGap;
	// 			counter++;
	// 		}

	// 		meanGap = langtGap/6;
	// 		cout << instance << " - Time Gap Mean by instance: " <<  meanGap << " %%" << endl;
	// 	}

	// 	infile.close();
	// 	cout << endl;
	// }

	// else cout << "Unable to open file";
	
	return 0;
}