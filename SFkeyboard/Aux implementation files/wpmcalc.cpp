//Calculation in Words per Minute
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
#include <limits>
#include <float.h>
#include <iomanip>

using namespace std;
	
struct CPairs{
	char char1;
	char char2;
	long long freq;
	float probi;
};

struct FChar{
	char schar;
	long long charfreq;
};

int main() { 

	//std::ios::sync_with_stdio(false);

	//locale loc("en_US.UTF-8");

	std::locale loc("");
	std::locale::global (loc);

	wcout.imbue(loc);

	wfstream infile1("frequencywpm.txt"); //frequency of characters
	wfstream infile2("charlistwpm.txt"); //used characters
	wfstream infile3("hexmatrixwpm.txt"); //physical layout
	wfstream infile4("metropolislay.txt"); //character layout

	infile1.imbue(loc);
	infile2.imbue(loc);
	infile3.imbue(loc);
	infile4.imbue(loc);

	CPairs charpair;
	FChar fchar;

	vector<char>  charVec;
	vector<CPairs> pairVec;
	vector<FChar> charfreqList;
	vector< vector <long long> > freqVec;
	vector<long long> freqRow;

	vector <long long> keyRow;
	vector< vector <long long> > keyMat;

	vector <double> distRow;
	vector< vector <double> > distMat;

	vector<int> charpos;
	vector<int> spacepos;

	vector<int> bSpaces;
	wstring line;
	wstring file;

	std::wstring::iterator it;

	int counter;
	int pos1;
	int pos2;
	int next;

	int krow = 7;
	int kcol = 7;
	int keys = krow * kcol;

	//int nsp = 4; //number of spaces
	int nsp = 1;

	wchar_t cchar;
	wchar_t	keychar;

	bool exists;
	long long freq = 0;
	long long totalfreq = 0;
	double dist;
	float cost;
	float wpm;

	if (infile2.is_open()){
		while (infile2 >> cchar){		
			charVec.push_back(cchar);
		}
		//charVec.push_back('_');
		infile2.close();
	}

	else cout << "Unable to open file"; 

	// cout << "\nChar Vector: ";
	// for (int i = 0; i < charVec.size(); i++){
	// 	cout << charVec[i] << " ";
	// }
	// cout << endl;

	for (int i = 0; i < charVec.size() - (nsp - 1); i++){
		for (int j = 0; j < charVec.size() - (nsp - 1); j++){
			freqRow.push_back(0);
		}
		freqVec.push_back(freqRow);
	}

	for (int i = 0; i < charVec.size(); i++){
		for (int j = 0; j < charVec.size(); j++){
			charpair.char1 = charVec[i];
			charpair.char2 = charVec[j];
			charpair.freq = 0;
			charpair.probi = 0;
			pairVec.push_back(charpair);
		}
	}
	// for (int i = 0; i < charVec.size(); i++){
	// 	for (int j = 0; j < charVec.size(); j++){
	// 		cout << setw(5) << freqVec[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	// getchar();

	// int counterr = 1;
	// cout << "\nCharacter pairs: " << endl;
	// for (int i = 0; i < pairVec.size(); i++){
	// 	cout << pairVec[i].char1 << "-" << pairVec[i].char2 << endl;
	// 	counterr++;
	// }

	// getchar();

	// for (int i = 0; i < charVec.size(); i++){
	// 	wcout << i << " ";
	// }
	// wcout << endl;

	// for (int i = 0; i < charVec.size(); i++){
	// 	wcout << std::right << setw(3) << i << " ";
	// 	for (int j = 0; j < charVec.size(); j++){
	// 		wcout << setw(3) << freqVec[i][j] << " ";
	// 	}
	// 	wcout << endl;
	// }
	counter = 0;
	int row = 0;
	if (infile1.is_open()){
		while (getline (infile1, line)){
			if (row < charVec.size() - (nsp - 1)){
				freqRow[row] = 0;
				for (int i = 0; i < charVec.size() - (nsp - 1); i++){
					infile1 >> freq;
					pairVec[counter].freq = freq;
					freqRow[row] += freq;
					freqVec[row][i] = freq;
					counter++;
				}
				// cout << "\nRow Frequency (" << row << "): " << freqRow[row] << endl;
				// getchar();
				totalfreq += freqRow[row];
				row++;
			}

		}
		// cout << "\nTest" << endl;
		// getchar();
		infile1.close();
	}

	// cout << "\nTotal Frequency: " << totalfreq << endl;
	// getchar();

	// for (int i = 0; i < charVec.size(); i++){
	// 	for (int j = 0; j < charVec.size(); j++){
	// 		cout << setw(5) << freqVec[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	// getchar();

	// cout << "\nVector of pairs:" << endl; 
	// for (int i = 0; i < pairVec.size(); i++){
	// 	cout << pairVec[i].char1 << "-" << pairVec[i].char2 << " - " << pairVec[i].freq << endl;
	// }
	// getchar();


	for (int i = 0; i < pairVec.size(); i++){
		pairVec[i].probi = (float)pairVec[i].freq/(float)totalfreq;

		// cout << pairVec[i].char1 << "-" << pairVec[i].char2 << " - " << std::fixed << std::setprecision(5) << pairVec[i].probi << endl;
		// getchar();
	}

	for (int i = 0; i < krow; i++){
		for (int j = 0; j < kcol; j++){
			keyRow.push_back(-1);
		}
		keyMat.push_back(keyRow);
	}

	// for (int i = 0; i < krow; i++){
	// 	for (int j = 0; j < kcol; j++){
	// 		cout << setw(5) << keyMat[i][j] << " ";
	// 	}
	// 	cout<< endl;
	// }
	// getchar();
	
	for (int i = 0; i < keys; i++){
		for (int j = 0; j < keys; j++){
			distRow.push_back(0);
		}
		distMat.push_back(distRow);
	}
	// for (int i = 0; i < keys; i++){
	// 	for (int j = 0; j < keys; j++){
	// 		cout << setw(5) << distMat[i][j] << " ";
	// 	}
	// 	cout<< endl;
	// }

	infile3 >> file;
	infile3 >> file;					//Cada linha dessa está lendo o que tiver entre cada espaço. No começo tem 'n = 29', entao sao 3 comandos para chegar até o 29
	infile3 >> file;
	
	if (infile3.is_open()){
		while (!infile3.eof()){
			for (int i = 0; i < keys; i++){
				for (int j = 0; j < keys; j++){
					infile3 >> dist;
					distMat[i][j] = dist / 1000;
					// cout << "i: " << i << "; j: " << j << " Dist: " << distMat[i][j] << endl;
					// getchar();
				}
			}
			// cout << "\nRow Frequency (" << row << "): " << freqRow[row] << endl;
			// getchar();
			infile3 >> file;
		}
		// cout << "\nTest" << endl;
		// getchar();
	}
	infile3.close();

// 	for (int i = 0; i < keys; i++){
// 		for (int j = 0; j < keys; j++){
// 			cout << setw(5) << std::fixed << std::setprecision(3) << distMat[i][j] << " ";
// 		}
// 		cout<< endl;
// 	}

// getchar();

	if (infile4.is_open()){
		while (!infile4.eof()){
			for (int i = 0; i < krow; i++){
				for (int j = 0; j < kcol; j++){
					infile4 >> keychar;
					if (keychar == '*'){
						continue;
					}
					for (int k = 0; k < charVec.size(); k++){
						if (charVec[k] == keychar){
							keyMat[i][j] = k;
							// cout << "\ni: " << i << " j: " << j << "char read: " << keychar << " char compared: " << charVec[k];
							// getchar();
						}
					}
					// cout << "i: " << i << "; j: " << j << " Dist: " << distMat[i][j] << endl;
					// getchar();
				}
			}
			// cout << "\nRow Frequency (" << row << "): " << freqRow[row] << endl;
			// getchar();
			infile4 >> file;
		}
		// cout << "\nTest" << endl;
		// getchar();
	}
	infile4.close();

	// for (int i = 0; i < krow; i++){
	// 	for (int j = 0; j < kcol; j++){
	// 		cout << setw(5) << charVec[keyMat[i][j]] << " ";
	// 	}
	// 	cout<< endl;
	// }
	// getchar();


	cost = 0;
	wpm = 0;
//cost for one space
	for (int i = 0; i < keys; i++){
		for (int j = 0; j < keys; j++){
			//if (charVec[keyMat[floor(i/kcol)][i%kcol]] != charVec[keyMat[floor(j/kcol)][j%kcol]]){
				if(keyMat[floor(i/kcol)][i%kcol] > -1 && keyMat[floor(j/kcol)][j%kcol] > -1){
					cost += freqVec[keyMat[floor(i/kcol)][i%kcol]][keyMat[floor(j/kcol)][j%kcol]]/(float)totalfreq * distMat[i][j];
					// cout << "\n i: " << i << " - j: " << j << " - char1: " << charVec[keyMat[floor(i/kcol)][i%kcol]] << " - char2: " << charVec[keyMat[floor(j/kcol)][j%kcol]] << 
					// "\nprobi: " << std::fixed << std::setprecision(6) << freqVec[keyMat[floor(i/kcol)][i%kcol]][keyMat[floor(j/kcol)][j%kcol]]/(float)totalfreq << " dist: " << distMat[i][j];
					// cout << "\nNew value: " << freqVec[keyMat[floor(i/kcol)][i%kcol]][keyMat[floor(j/kcol)][j%kcol]]/(float)totalfreq * distMat[i][j] << "\nCurrent cost: " << cost << endl;
					// getchar();
				}
			//}
			// else if (charVec[keyMat[floor(i/kcol)][i%kcol]] == charVec[keyMat[floor(j/kcol)][j%kcol]]){
			// 	if(keyMat[floor(i/kcol)][i%kcol] > -1 && keyMat[floor(j/kcol)][j%kcol] > -1){
			// 		cost += freqVec[keyMat[floor(i/kcol)][i%kcol]][keyMat[floor(j/kcol)][j%kcol]]/(float)totalfreq * 0.127;
			// 	}
			// }
		}
	}

	for (int i = 0; i < charVec.size(); i++){
		cost += freqVec[i][i]/(float)totalfreq * 0.127;
	}
	
//cost for multiple spaces

	// for (int i = 0; i < keys; i++){
	// 	if (i == 14 || i == 15 || i == 18 || i == 19){
	// 		spacepos.push_back(i);
	// 	}
	// 	else{
	// 		charpos.push_back(i);
	// 	}
	// }

	// for (int i = 0; i < charpos.size(); i++){
	// 	bSpaces.push_back(0);
	// }
	
	// float min_space;
	// int assignedSpace;
	// float temp_space = 0;
	// for (int i = 0; i < keys; i++){
	// 	min_space = numeric_limits<float>::max();
	// 	for (int j = 0; j < spacepos.size(); j++){
	// 		if (i == 14 || i == 15 || i == 18 || i == 19){
	// 			if (i == spacepos[j]){
	// 				assignedSpace = spacepos[j];
	// 				//cout << "\ni: " << i << " - curr space: " << spacepos[j] << " ";
	// 				continue;
	// 			}
	// 			else{
	// 				continue;
	// 			}
	// 		}
	// 		else{
	// 			temp_space = distMat[i][spacepos[j]];

	// 			if (temp_space < min_space){
	// 				min_space = temp_space;
	// 				assignedSpace = spacepos[j];
	// 			}
	// 		}
	// 	}
	// 	// cout << "\nChar position: " << charpos[i] << "; Space: " << assignedSpace;
	// 	// getchar();
	// 	bSpaces[i] = assignedSpace;
	// 	// getchar();
	// }
	
	// // cout << "\nBest Spaces: " << endl;
	// // for (int i = 0; i < bSpaces.size(); i++){
	// // 	cout << "\ni: " << i << " - best space: " << bSpaces[i] << " ";
	// // }
	// // cout << endl;
	// // getchar();

	// // cout << "\nChar positions: ";
	// // for(int i = 0; i < charpos.size(); i++){
	// // 	cout << charpos[i] << " ";
	// // }
	// // cout << endl;
	// // cout << "\nSpace positions: ";
	// // for(int i = 0; i < spacepos.size(); i++){
	// // 	cout << spacepos[i] << " ";
	// // }
	// // cout << endl;

	// // getchar();

	// for (int i = 0; i < keys; i++){
	// 	for (int j = 0; j < keys; j++){
	// 		if (keyMat[floor(i/kcol)][i%kcol] < charVec.size() - nsp){
	// 			if (keyMat[floor(j/kcol)][j%kcol] < charVec.size() - nsp){
	// 				if (keyMat[floor(i/kcol)][i%kcol] != keyMat[floor(j/kcol)][j%kcol]){
	// 					if(keyMat[floor(i/kcol)][i%kcol] > -1 && keyMat[floor(j/kcol)][j%kcol] > -1){
	// 						cost += freqVec[keyMat[floor(i/kcol)][i%kcol]][keyMat[floor(j/kcol)][j%kcol]]/(float)totalfreq * distMat[i][j];
	// 						// cout << "\n i: " << i << " - j: " << j << " - char1: " << charVec[keyMat[floor(i/kcol)][i%kcol]] << " - char2: " << charVec[keyMat[floor(j/kcol)][j%kcol]] << 
	// 						// "\nprobi: " << freqVec[keyMat[floor(i/kcol)][i%kcol]][keyMat[floor(j/kcol)][j%kcol]]/(float)totalfreq << " dist: " << distMat[i][j];
	// 						// cout << "\nNew value: " << freqVec[keyMat[floor(i/kcol)][i%kcol]][keyMat[floor(j/kcol)][j%kcol]]/(float)totalfreq * distMat[i][j] << "\nCurrent cost: " << cost << endl;
	// 						// getchar();
	// 					}
	// 				}
	// 				else if (keyMat[floor(i/kcol)][i%kcol] == keyMat[floor(j/kcol)][j%kcol]){
	// 					if(keyMat[floor(i/kcol)][i%kcol] > -1 && keyMat[floor(j/kcol)][j%kcol] > -1){
	// 						cost += (freqVec[keyMat[floor(i/kcol)][i%kcol]][keyMat[floor(j/kcol)][j%kcol]]/(float)totalfreq) * 0.127;
	// 					}
	// 				}	
	// 			}
	// 			//no caso em que j não tem caractere, temos que analisar se best space desse caractere i é igual a j. Se sim, adiciona o espaço, se n for, continua o loop.
	// 			else if (bSpaces[i] == j){
	// 				cost += (freqVec[keyMat[floor(i/kcol)][i%kcol]][charVec.size() - nsp]/(float)totalfreq) * distMat[i][j];
	// 				// cout << "\n i: " << i << " - bestSpace: " << j << " - char1: " << charVec[keyMat[floor(i/kcol)][i%kcol]] << " - char2: " << charVec[keyMat[floor(j/kcol)][j%kcol]] << 
	// 				// "\nprobi: " << freqVec[keyMat[floor(i/kcol)][i%kcol]][charVec.size() - nsp]/(float)totalfreq << " dist: " << distMat[i][j];
	// 				// cout << "\nNew value: " << freqVec[keyMat[floor(i/kcol)][i%kcol]][charVec.size() - nsp]/(float)totalfreq * distMat[i][j] << "\nCurrent cost: " << cost << endl;
	// 				// getchar();
	// 			}
	// 			else {
	// 				continue;
	// 			}
	// 		}//no caso em que i é espaço e j é caractere. Usar valor de espaço com caractere em j, se i for o melhor espaço pra posição j
	// 		else if (keyMat[floor(j/kcol)][j%kcol] < charVec.size() - nsp){
	// 			if(bSpaces[j] == i){
	// 				cost += (freqVec[charVec.size() - nsp][keyMat[floor(j/kcol)][j%kcol]]/(float)totalfreq) * distMat[i][j];
	// 				// cout << "\n bestSpace: " << i << " - char position: " << j << " - char1: " << charVec[keyMat[floor(i/kcol)][i%kcol]] << " - char2: " << charVec[keyMat[floor(j/kcol)][j%kcol]] << 
	// 				// "\nprobi: " << (freqVec[charVec.size() - nsp][keyMat[floor(j/kcol)][j%kcol]]/(float)totalfreq) << " dist: " << distMat[i][j];
	// 				// cout << "\nNew value: " << (freqVec[charVec.size() - nsp][keyMat[floor(j/kcol)][j%kcol]]/(float)totalfreq) * distMat[i][j] << "\nCurrent cost: " << cost << endl;
	// 				// getchar();
	// 			}
	// 		}
	// 	}

	// 	// for (int c = 0; c < spacepos.size(); c++){
	// 	// 	k = spacepos[c];			
	// 	// 	if (i != j){
	// 	// 		if(distMat[i][j] < minspacecost){
	// 	// 			minspacecost = distMat[i][j];
	// 	// 		}
	// 	// 	}
	// 	// 	else if (i == j){
	// 	// 		cost += 0;
	// 	// 	}
	// 	// }
	// }

//Final lines of code
	cout << "\nCost: " << cost;
	
	wpm = 60 / (5 * cost);

	cout << "\nWords per minute: " << std::fixed << std::setprecision(5) << wpm << endl; 

	return 0;
}


