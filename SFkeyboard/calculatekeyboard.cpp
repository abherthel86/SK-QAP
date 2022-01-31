//Calculate Keyboard
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

if(argc > 4){
	cout << "Too many parameters." << endl;
	exit(1);
}

if(argc < 4){
	cout << "Missing parameters." << endl;
	exit(1);
}

char instance;
char chara;	
int size;
int ksize;
long long freq;
long long dist;
string file;

vector<int> grid;
vector<int> assignment;


int rows = 4;
int cols = 10;

ifstream in1(argv[1]);
ifstream in2(argv[2]);
ifstream in3(argv[3]);

vector<long long> frow;
vector<char> charlist;
vector< vector <long long> > freq_matrix;
vector< vector <long long> > b_matrix;

vector< vector <long long> > keyb;

//long long refval = numeric_limits<long long>::max();

if (in1.is_open()){
	in1 >> file;
	in1 >> file;
	in1 >> size;
	
	for (int j = 0; j < size; j++){
		frow.push_back(0);
	}

	for(int i = 0; i < size; i++){
		freq_matrix.push_back(frow);
	}
	
	for(int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			in1 >> freq;
			freq_matrix[i][j] = freq;
		}
	}	
	in1.close();
}

frow.clear();

for (int i = 0; i < size < i++){
	for (int j = 0; j < size; j++){
		
	}
}

if (in2.is_open()){
	in2 >> file;
	in2 >> file;
	in2 >> ksize;
	
	for (int j = 0; j < ksize; j++){
		frow.push_back(0);
	}

	for(int i = 0; i < ksize; i++){
		b_matrix.push_back(frow);
	}
	
	for(int i = 0; i < ksize; i++){
		for (int j = 0; j < ksize; j++){
			in2 >> dist;
			b_matrix[i][j] = dist;
		}
	}	
	in2.close();
}

if (in3.is_open()){
	
	for (int j = 0; j < size; j++){
		in3 >> chara;
		charlist.push_back(chara);
	}
	in3.close();
}

frow.clear();

for(int j = 0; j < cols; j++){
	frow.push_back(-1);	
}

for (int i = 0; i < rows; i++){
	keyb.push_back(frow);
}

//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
//D E L A ' T S N U Q  I  P  R  O  C  X  V  M  Y  F  B  G  H  J  W  Z  K  _  _  _  _  _
	
	for (int i = 0; i < ksize; i++){
		grid[i] = -1;
	}
	
	for (int i = 0; i < size; i++){
		assignment[i] = -1;
	}
	
	grid[1] = 25;
	grid[2] = 22;
	grid[3] = 14;
	grid[4] = 13;
	grid[5] = 7;
	grid[6] = 6;
	grid[7] = 0;
	grid[8] = 4;
	grid[9] = 23;
	grid[11] = 26;
	grid[12] = 19;
	grid[13] = 17;
	grid[14] = 10;
	grid[15] = 5;
	grid[16] = 1;
	grid[17] = 8;
	grid[18] = 9;
	grid[19] = 15;
	grid[21] = 24;
	grid[22] = 18;
	grid[23] = 21;
	grid[24] = 11;
	grid[25] = 3;
	grid[26] = 12;
	grid[27] = 2;
	grid[28] = 16;
	grid[29] = 20;
	grid[33] = 27;
	grid[34] = 28;
	grid[35] = 29;
	grid[36] = 30;
	grid[37] = 31;

	assignment[0] = 7;
	assignment[1] = 16;
	assignment[2] = 27;
	assignment[3] = 25;
	assignment[4] = 8;
	assignment[5] = 15;
	assignment[6] = 6;
	assignment[7] = 5;
	assignment[8] = 17;
	assignment[9] = 18;
	assignment[10] = 14;
	assignment[11] = 24;
	assignment[12] = 26;
	assignment[13] = 4;
	assignment[14] = 3;
	assignment[15] = 19;
	assignment[16] = 28;
	assignment[17] = 13;
	assignment[18] = 22;
	assignment[19] = 12;
	assignment[20] = 29;
	assignment[21] = 23;
	assignment[22] = 2;
	assignment[23] = 9;
	assignment[24] = 21;
	assignment[25] = 1;
	assignment[26] = 11;
	assignment[27] = 33;
	assignment[28] = 34;
	assignment[29] = 35;
	assignment[30] = 36;
	assignment[31] = 37;

	int count = 0;
	
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			if (i == 0 && j == 0){
				cout << " ";
			}
			if (i == 1 && j == 0){
				cout << " ";
			}
			if (grid[count] != -1)
				cout << setw(3) << charlist[grid[count]];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}

	// for (int i = 0; i < krows; i++){
	// 	for (int j = 0; j < kcols; j++){
	// 		if (i == 0 && j == 0){
	// 			cout << " ";
	// 		}
	// 		if (grid[count] != -1)
	// 			cout << setw(3) << charlist[grid[count]];
	// 		else
	// 			cout<< setw(3) << "*";
	// 		count++;
	// 	}
	// 	cout << endl;
	// }

}