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
	//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39
	//E A O S R I D N T M  C  U  P  L  V  F  Ã  G  B  Q  Ç  H  É  Á  Í  Z  J  X  Ê  Ó  Õ  Ú  À  W  -  Â  Y  K  Ô  _

	//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
	//E A O S R I D N T M  C  U  P  L  V  F  G  B  Q  H  Z  J  X  W  Y  K  _

	//0 + 22 + 28
	//1 + 16 + 23 + 32 + 35
	//2 + 29 + 30 + 38
	//5 + 24
	//10 + 20
	//11 + 31

	long long fmat [size][size] = {0};

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			fmat[i][j] = freq_matrix[i][j];
		}
	}

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if(i == 0){
				fmat[0][j] = freq_matrix[0][j] + freq_matrix[22][j] + freq_matrix[28][j];
				fmat[j][0] = freq_matrix[j][0] + freq_matrix[j][22] + freq_matrix[j][28];
			}
			else if(i == 1){
				fmat[1][j] = freq_matrix[1][j] + freq_matrix[16][j] + freq_matrix[23][j] + freq_matrix[32][j] + freq_matrix[35][j];
				fmat[j][1] = freq_matrix[j][1] + freq_matrix[j][16] + freq_matrix[j][23] + freq_matrix[j][32] + freq_matrix[j][35];
			}
			else if(i == 2){
				fmat[2][j] = freq_matrix[2][j] + freq_matrix[29][j] + freq_matrix[30][j] + freq_matrix[38][j];
				fmat[j][2] = freq_matrix[j][2] + freq_matrix[j][29] + freq_matrix[j][30] + freq_matrix[j][38];
			}
			else if(i == 5){
				fmat[5][j] = freq_matrix[5][j] + freq_matrix[24][j];
				fmat[j][5] = freq_matrix[j][5] + freq_matrix[j][24];
			}
			else if(i == 10){
				fmat[10][j] = freq_matrix[10][j] + freq_matrix[20][j];
				fmat[j][10] = freq_matrix[j][10] + freq_matrix[j][20];
			}
			else if(i == 11){
				fmat[11][j] = freq_matrix[11][j] + freq_matrix[31][j];
				fmat[j][11] = freq_matrix[j][11] + freq_matrix[j][31];
			}
			else{
				continue;
			}
		}
	}

	cout << "n = " << 27 << endl;

	for(int i = 0; i < size; i++){
		if (i == 16 || i == 20 || i == 22 || i == 23 || i == 24 || i == 28 || i == 29 || i == 30 || i == 31 || i == 32 || i == 34 || i == 35 || i == 38){
			continue;
		}
		else{
			for(int j = 0; j < size; j++){
				if (i == j){
					fmat[i][j] = 0;
				}
				if (j == 16 || j == 20 || j == 22 || j == 23 || j == 24 || j == 28 || j == 29 || j == 30 || j == 31 || j == 32 || j == 34 || j == 35 || j == 38){
					continue;
				}
				else{
					cout << setw(9) << std::right << fmat[i][j] << " ";
				}
			}
			cout << endl;
		}

	}
}