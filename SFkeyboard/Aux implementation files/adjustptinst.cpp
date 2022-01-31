//Adjust Portuguese Instance
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <cmath>
#include <limits>
#include <float.h>
#include <iomanip>
#include <ctime>
//#include <ilcplex/ilocplex.h>
#include <stdlib.h>
#include <iostream>
#include <locale.h>
#include <sys/time.h>
#include <ctime>
#include <unistd.h>

using namespace std;

int main (int argc, char* argv[]) {

if(argc > 2){
	cout << "Too many parameters." << endl;
	exit(1);
}

if(argc < 2){
	cout << "Missing parameters." << endl;
	exit(1);
}

char instance;	
int size;
long long freq;
string file;


//instance = *argv[1];

ifstream in(argv[1]);

vector<long long> frow;
vector< vector <long long> > freq_matrix;

long long refval = numeric_limits<long long>::max();

if (in.is_open()){
	in >> file;
	in >> file;
	in >> size;
	
	for (int j = 0; j < size; j++){
		frow.push_back(0);
	}

	for(int i = 0; i < size; i++){
		freq_matrix.push_back(frow);
	}
	
	for(int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			in >> freq;
			freq_matrix[i][j] = freq;
		}
	}	
	in.close();
}

// cout << "n = " << size << endl;
// for (int i = 0; i < size; i++){
// 	for (int j = 0; j < size; j++){
// 		cout << setw(7) << freq_matrix[i][j] << " ";
// 	}
// 	cout << endl;
// }
// cout << endl;
// getchar();

//cout << "\nFirst Ref Value: " << refval << endl;

// for (int i = 0; i < size; i++){
// 	for (int j = 0; j < size; j++){
// 		//cout << "\ni: " << i << "\nj: " << j << endl;
// 		if(freq_matrix[i][j] != 0 && freq_matrix[i][j] < refval){
// 			//cout << "\nMatrix value: " << freq_matrix[i][j] << endl;
// 			refval = freq_matrix[i][j];
// 			//cout << "\nNew Ref Value: " << refval << endl;
// 			//getchar();
// 		}
// 	}
// }

for (int i = 0; i < size; i++){
	for (int j = 0; j < size; j++){
		freq_matrix[i][j] = freq_matrix[i][j]/100;
	}
}
cout << "n = " << size << endl;
for (int i = 0; i < size; i++){
	for (int j = 0; j < size; j++){
		cout << setw(7) << std::right << freq_matrix[i][j] << " ";
	}
	cout << endl;
}

	return 0;
}