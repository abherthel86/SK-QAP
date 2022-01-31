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

	// ifstream infile ("GMeanT10x6n.txt");
	// ofstream offile;
	
	// offile.open ("GLT10x6n.txt", ios::out | ios::app);
	
	// if (infile.is_open()){
	// 	while (getline (infile, line)){
	// 		counter = 0;
	// 		totalGap = 0;
	// 		while (counter < 6){
	// 			infile >> instance;
	// 			infile >> file;
	// 			infile >> file;
	// 			infile >> file;
				
	// 			infile >> gap;
				
	// 			//cout << "\nGap: " << gap << endl;
	// 			totalGap += gap;
	// 			//cout << "Total Gap: " << totalGap << endl;
	// 			counter++;
	// 		}
	// 		//meanGap = (totalGap/(float)6);
	// 		meanGap = (totalGap/(float)6)*100;
			
	// 		offile << instance << " " <<  meanGap << "%%" << endl;
	// 	}
	// 	offile.close();
	// 	infile.close();
	// 	cout << endl;
	// }

	// else cout << "Unable to open file"; 
//Times

	ifstream infile ("MTT10x6n.txt");
	ofstream offile;
	
	offile.open ("TBLT10x6n.txt", ios::out | ios::app);
	
	if (infile.is_open()){
		while (getline (infile, line)){
			counter = 0;
			totalGap = 0;
			while (counter < 6){
				infile >> instance;
				
				infile >> gap;
				
				//cout << "\nGap: " << gap << endl;
				totalGap += gap;
				//cout << "Total Gap: " << totalGap << endl;
				counter++;
			}
			meanGap = (totalGap/(float)6);
			
			offile << instance << " " <<  meanGap << endl;
		}
		offile.close();
		infile.close();
		cout << endl;
	}

	else cout << "Unable to open file"; 

	return 0;
}