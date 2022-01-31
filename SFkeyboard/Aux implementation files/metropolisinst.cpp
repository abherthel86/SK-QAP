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
	int col = 14;
	int row = 10;
	int size = row * col;
	int counter = 0;
	double side = sqrt(3)/3;
	double height = 0.5;
	double delta2;
	double delta1;


	cout << "n = " << size << endl;

	// cout << "Relatorio: " << endl;
	// cout << "\ncol: " << col << " row: " << row << " size: " << size << endl;
	// cout << "a: " << side << endl;
	// cout << "h: " << height << endl;

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			// int i = 8;
			// int j = 13;
			int irow = (i/col)%2;
			int jrow = (j/col)%2;

			//cout << "irow: " << irow << " jrow: " << jrow << end;

			if (i == j){
				bij = 0;
				cout << setw(4) << std::right << bij << " ";
				counter++;
			}
			
			else if (irow == 0 && jrow == 0){
				
				delta1 = 0;
				delta2 = 0;
				bij = floor((1000/4.9)*log2(sqrt(pow(((floor(i/col)*((3*side)/2))-floor(j/col)*((3*side)/2)), 2)+pow(((floor(i%col)*2*height + delta1)-(floor(j%col)*2*height + delta2)), 2))+1));
				cout << setw(4) << std::right << bij << " ";
				counter++;
			}


			else if (irow == 0 && jrow > 0){

				delta1 = 0;
				delta2 = height;
				bij = floor((1000/4.9)*log2(sqrt(pow(((floor(i/col)*((3*side)/2))-floor(j/col)*((3*side)/2)), 2)+pow(((floor(i%col)*2*height + delta1)-(floor(j%col)*2*height + delta2)), 2))+1));
				cout << setw(4) << std::right << bij << " ";
				counter++;
			}
			

			else if (irow > 0 && jrow == 0){

				delta1 = height;
				delta2 = 0;
				bij = floor((1000/4.9)*log2(sqrt(pow(((floor(i/col)*((3*side)/2))-floor(j/col)*((3*side)/2)), 2)+pow(((floor(i%col)*2*height + delta1)-(floor(j%col)*2*height + delta2)), 2))+1));
				cout << setw(4) << std::right << bij << " ";
				counter++;
			}
			
			else if (irow > 0 && jrow > 0){
				delta1 = height;
				delta2 = height;
				
				bij = floor((1000/4.9)*log2(sqrt(pow(((floor(i/col)*((3*side)/2))-floor(j/col)*((3*side)/2)), 2)+pow(((floor(i%col)*2*height + delta1)-(floor(j%col)*2*height + delta2)), 2))+1));
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