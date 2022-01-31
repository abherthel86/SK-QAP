//calculate solution gap means
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
	string line;
	string instance;

	string file;

	// double t1 = 0;
	// double t2 = 0;
	// double tGap;
	// double tDif = 0;

	// ifstream infile1 ("MTT1.txt");
	// ifstream infile2 ("MTT2.txt");

	// if (infile1.is_open()){
	// 	while (getline (infile1, line)){

	// 		infile1 >> instance;
	// 		infile1 >> t1;
			
	// 		if(infile2.is_open()){
	// 	    	while (getline (infile2, line)){
	// 				infile2 >> file;
	// 				infile2 >> t2;

	// 				tDif = t2 - t1;
	// 				tGap = (tDif/t1)*100;
	// 				cout << instance << " T1: " << t1 << " T2: " << t2 << " Increase: " << tGap << " %%" << endl;
 // 				break;
	// 			}
	// 		}
	// 	}

	// 	infile1.close();
	// 	infile2.close();
	// 	cout << endl;
	// }

	// else cout << "Unable to open file"; 

	double t1 = 0;
	double t2 = 0;
	double t3 = 0;
	double tGap1;
	double tGap2;
	double tDif1 = 0;
	double tDif2 = 0;

	bool increase1 = 0;
	bool increase2 = 0;

	ifstream infile1 ("MTT3.txt");
	ifstream infile2 ("MTT4.txt");
	ifstream infile3 ("MTT5-2.txt");

	if (infile1.is_open()){
		while (getline (infile1, line)){

			infile1 >> instance;
			infile1 >> t1;
			
			if(infile2.is_open()){
		    	while (getline (infile2, line)){
					infile2 >> file;
					infile2 >> t2;

					if(infile3.is_open()){
				    	while (getline (infile3, line)){
							infile3 >> file;
							infile3 >> t3;

							if (t3 < t1){
								tDif1 = t1 - t3;
								tGap1 = (tDif1/t3)*100;
								increase1 = 0;
							}
							else{
								tDif1 = t3 - t1;
								tGap1 = (tDif1/t1)*100;
								increase1 = 1;
							}

							if (t3 < t2){
								tDif2 = t2 - t3;
								tGap2 = (tDif2/t3)*100;
								increase2 = 0;
							}
							else{
								tDif2 = t3 - t2;
								tGap2 = (tDif2/t2)*100;
								increase2 = 1;
							}

							cout << instance << " T1: " << t1 << " T3: " << t3;

							if (increase1 > 0){
								cout << " Increase: " << tGap1 << " %%";
							}
							else {
								cout << " Decrease: " << tGap1 << " %%";
							}

							cout << " - T2: " << t2 << " T3: " << t3;

							if (increase2 > 0){
								cout << " Increase: " << tGap2 << " %%" << endl;
							}
							else{
								cout << " Decrease: " << tGap2 << " %%" << endl;
							}

		 					break;
 						}
					} 
					break;
				}
			}
		}

		infile1.close();
		infile2.close();
		infile3.close();

		cout << endl;
	}

	else cout << "Unable to open file"; 

	return 0;
}