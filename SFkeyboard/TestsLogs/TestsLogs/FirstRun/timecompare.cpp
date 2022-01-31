//calculate solution gap means
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
	string line;
	string instance;

	string file;

	double t1 = 0;
	double t2 = 0;
	double tGap;
	double tDif = 0;

	ifstream infile1 ("MTT1.txt");
	ifstream infile2 ("MTT2.txt");

	if (infile1.is_open()){
		while (getline (infile1, line)){

			infile1 >> instance;
			infile1 >> t1;
			
			if(infile2.is_open()){
		    	while (getline (infile2, line)){
					infile2 >> file;
					infile2 >> t2;

					tDif = t2 - t1;
					tGap = (tDif/t1)*100;
					cout << instance << " T1: " << t1 << " T2: " << t2 << " Increase: " << tGap << " %%" << endl;
 					break;
				}
			}
		}

		infile1.close();
		infile2.close();
		cout << endl;
	}

	else cout << "Unable to open file"; 

	return 0;
}