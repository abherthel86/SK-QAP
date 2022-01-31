//calculate gaps
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
	string line;
	string instance1;
	string instance2;

	int counter;
	int instChoice = 1;
	int instCount = 1;

	//long long meanCost = 0;
	//long long totalCost;
	long long globalCost = 0;
	long long bestCost = 0;
	long long costDif = 0;

	float solGap = 0;
	double globalTime;

	ifstream infile1 ("BestSolList.txt");
	ifstream infile2 ("GlobalStatsT5.txt");

	if (infile1.is_open()){
		while (getline (infile1, line)){

			counter = 0;
			
			infile1 >> instance1;
			infile1 >> bestCost;
			
			if(infile2.is_open()){
		    	while (counter < 10 && getline (infile2, line)){
					infile2 >> instance2;
					
					infile2 >> globalCost;
					infile2 >> globalTime;
					costDif = globalCost - bestCost;

					solGap = (float)costDif/(float)bestCost;

					cout << instance1 << " " <<  solGap << endl;
		
					counter++;
				}
			}
			//cout << instance1 << " - Gap: " <<  solGap << endl;
		}

		infile1.close();
		infile2.close();
		cout << endl;
	}

	else cout << "Unable to open file"; 

	return 0;
}