#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <stdlib.h>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <cmath>
#include <limits>
#include <float.h>
#include <iomanip>

using namespace std;


int main () { 

	long long bij;
	int col = 9;
	int row = 4;
	int size = row * col;
	int counter = 0;

	cout << "n = " << size << endl;

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){

			int irow = floor(i/col);
			int jrow = floor(j/col);

			if (i == j){
				bij = 0;
				cout << setw(4) << std::right << bij << " ";
				counter++;
			}
			
			else if (irow != 2 && jrow != 2){
				bij = floor((1000/4.9)*log2(sqrt(pow(((floor(i/col))-floor(j/col)), 2)+pow((((i%col))-(j%col)), 2))+1));
				cout << setw(4) << std::right << bij << " ";
				counter++;
			}

			else if (irow != 2 && jrow == 2){
				bij = floor((1000/4.9)*log2(sqrt(pow(((floor(i/col))-floor(j/col)), 2)+pow(((i%col)-((j%col)+0.5)), 2))+1));
				cout << setw(4) << std::right << bij << " ";
				counter++;
			}
			
			else if (irow == 2 && jrow != 2){
				bij = floor((1000/4.9)*log2(sqrt(pow(((floor(i/col))-floor(j/col)), 2)+pow((((i%col)+0.5)-(j%col)), 2))+1));
				cout << setw(4) << std::right << bij << " ";
				counter++;
			}

			else if (irow == 2 && jrow == 2){
				bij = floor((1000/4.9)*log2(sqrt(pow(((floor(i/col))-floor(j/col)), 2)+pow((((i%col)+0.5)-((j%col)+ 0.5)), 2))+1));
				cout << setw(4) << std::right << bij << " ";
				counter++;
			}

			if (counter == size){
				counter = 0;
				cout << endl;
			}
		}
	}

	cout << endl;

	return 0;
}