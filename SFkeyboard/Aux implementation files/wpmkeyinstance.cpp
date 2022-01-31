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

	float bij;
	float dij;
	//int col = 10;
	//int row = 4;
	//int col = 7;
	//int row = 7;
	int col = 7;
	int row = 7;
	int size = row * col;
	int counter = 0;
	//float width = 2.1;
	int width = 1;
	cout << "n = " << size << endl;

//QWERTY grid with row 1 shifted in 0,5 * width

// 	for (int i = 0; i < size; i++){
// 		for (int j = 0; j < size; j++){
// /*			int i = 0;
// 			int j = 10;*/

// 			if (i == j){
// 				bij = 0;
// 				cout << setw(4) << std::right << bij << " ";
// 				counter++;
// 			}

// 			else if (floor(i/col) < 1){
// 				if (floor(j/col) < 1){
// 					bij = (1/4.9) * log2((sqrt(pow((floor(i/col) - floor(j/col)) * width, 2) + pow((floor(i % col) - floor(j % col)) * width, 2)))/(width) + 1);
// 					cout << setw(4) << std::right << bij << " ";
// 					counter++;
// 				}
// 				else if (floor(j/col) == 1){
// 					bij = (1/4.9) * log2((sqrt(pow((floor(i/col) - floor(j/col)) * width, 2) + pow(((floor(i % col) - floor(j % col)) * width) - (width/2), 2)))/(width) + 1);
// 					cout << setw(4) << std::right << bij << " ";
// 					counter++;
// 				}
// 				else if (floor(j/col) > 1){
// 					bij = (1/4.9) * log2((sqrt(pow((floor(i/col) - floor(j/col)) * width, 2) + pow((floor(i % col) - floor(j % col)) * width, 2)))/(width) + 1);
// 					cout << setw(4) << std::right << bij << " ";
// 					counter++;
// 				}
// 			}

// 			else if (floor(i/col) == 1){
// 				if (floor(j/col) < 1){
// 					bij = (1/4.9) * log2((sqrt(pow((floor(i/col) - floor(j/col)) * width, 2) + pow(((floor(i % col) - floor(j % col)) * width) + (width/2), 2)))/(width) + 1);
// 					cout << setw(4) << std::right << bij << " ";
// 					counter++;
// 				}
// 				else if (floor(j/col) == 1){
// 					bij = (1/4.9) * log2((sqrt(pow((floor(i/col) - floor(j/col)) * width, 2) + pow(((floor(i % col) - floor(j % col)) * width), 2)))/(width) + 1);
// 					cout << setw(4) << std::right << bij << " ";
// 					counter++;
// 				}
// 				else if (floor(j/col) > 1){
// 					bij = (1/4.9) * log2((sqrt(pow((floor(i/col) - floor(j/col)) * width, 2) + pow(((floor(i % col) - floor(j % col)) * width) + (width/2), 2)))/(width) + 1);
// 					cout << setw(4) << std::right << bij << " ";
// 					counter++;
// 				}
// 			}

// 			else if (floor(i/col) > 1){
// 				if (floor(j/col) < 1){
// 					bij = (1/4.9) * log2((sqrt(pow((floor(i/col) - floor(j/col)) * width, 2) + pow((floor(i % col) - floor(j % col)) * width, 2)))/(width) + 1);
// 					cout << setw(4) << std::right << bij << " ";
// 					counter++;
// 				}
// 				else if (floor(j/col) == 1){
// 					bij = (1/4.9) * log2((sqrt(pow((floor(i/col) - floor(j/col)) * width, 2) + pow(((floor(i % col) - floor(j % col)) * width) - (width/2), 2)))/(width) + 1);
// 					cout << setw(4) << std::right << bij << " ";
// 					counter++;
// 				}
// 				else if (floor(j/col) > 1){
// 					bij = (1/4.9) * log2((sqrt(pow((floor(i/col) - floor(j/col)) * width, 2) + pow((floor(i % col) - floor(j % col)) * width, 2)))/(width) + 1);
// 					cout << setw(4) << std::right << bij << " ";
// 					counter++;
// 				}
// 			}

// 			if (counter == size){
// 				counter = 0;
// 				cout << endl;
// 			}
// 		}
// 	}

//Regular grid (for float values, remove floor from bij)

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
/*			int i = 0;
			int j = 10;*/

			if (i == j){
				bij = 0;
				cout << setw(4) << std::right << bij << " ";
				counter++;
			}
			
			else{
				bij = floor((1000/4.9) * log2((sqrt(pow((floor(i/col) - floor(j/col)) * width, 2) + pow((floor(i % col) - floor(j % col)) * width, 2)))/(width) + 1));
				cout << setw(4) << std::right << bij << " ";
				//getchar();
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