//create Hybrid Instances
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
	
int main () { 

	//std::ios::sync_with_stdio(false);

	//locale loc("en_US.UTF-8");

	std::locale loc("");
	std::locale::global (loc);

	//wcout.imbue(loc);

	wfstream infile1("CharEnglish3.txt");
	wfstream infile2("CharPortuguese3.txt");
	wfstream infile3("English3.txt");
	wfstream infile4("Portuguese3.txt");

	infile1.imbue(loc);
	infile2.imbue(loc);
	infile3.imbue(loc);
	infile4.imbue(loc);

	// CPairs charpair;
	// FChar fchar;

	vector<wchar_t>  charVec1;
	vector<wchar_t>  charVec2;
	vector<wchar_t>  newCharVec;
	//vector<wchar_t>  wordVec;
	//vector<CPairs> pairVec;
	//vector<FChar> charfreqList;
	vector< vector <long long> > freq1;
	vector<long long> frow;
	vector< vector <long long> > freq2;
	vector< vector <long long> > newFreq;

	vector< vector <long long> > spaceRow;

	//vector<long long> freqRow;
	
	wstring word;
	wstring line;
	wstring file;

	std::vector<wchar_t>::iterator it;
	std::vector<wchar_t>::iterator it2;

	int counter;
	int p1;
	int p2;
	int p3;
	int p4;
	int next;
	int n;

	wchar_t cchar;

	//wchar_t	wrdchars;

	bool exists;
	long long freq;
	long long f1 = 0;
	long long f2 = 0;

	if (infile1.is_open()){
		while (infile1 >> cchar){		
			charVec1.push_back(cchar);
			newCharVec.push_back(cchar);
		}
		infile1.close();
	}

	//For Randoms:
	//Eng
	
	charVec1.erase(charVec1.begin() + 27, charVec1.end());
	newCharVec.erase(newCharVec.begin() + 27, newCharVec.end());

	// wcout << "Char Vector1: ";
	// for (int i = 0; i < charVec1.size(); i++){
	// 	wcout << charVec1[i] << " ";
	// }
	// wcout << endl;

	// getchar();

	if (infile2.is_open()){
		while (infile2 >> cchar){		
			charVec2.push_back(cchar);
		}
		infile2.close();
	}

	//Spa
	//charVec2.erase(charVec2.begin() + 32, charVec2.end());

	//Fre

	//charVec2.erase(charVec2.begin() + 38, charVec2.end());


	// wcout << "Char Vector2: size: " << charVec2.size() << " vec: " ;
	// for (int i = 0; i < charVec2.size(); i++){
	// 	wcout << charVec2[i] << " ";
	// }
	// wcout << endl;

	// getchar();

	//else cout << "Unable to open file"; 

//For all instances

	// for (int i = 0; i < charVec2.size(); i++){
	// 	exists = 0;
	// 	for (int j = 0; j < charVec1.size(); j++){
	// 		if(charVec2[i] == charVec1[j]){
	// 			exists = 1;
	// 			break;
	// 		}
	// 	}
	// 	if(exists < 1){
	// 		newCharVec.push_back(charVec2[i]);
	// 	}
	// }

//For CharENSP2.txt
//_________________________________________________
//For Real Instances/1space char

	// for (int i = 0; i < charVec2.size(); i++){
	// 	exists = 0;
	// 	for (int j = 0; j < charVec1.size(); j++){
	// 		if(charVec2[i] == charVec1[j]){
	// 			exists = 1;
	// 			break;
	// 		}
	// 	}
	// 	if(exists < 1){
	// 		// wchar_t K = charVec2[i];
	// 		// wcout << "New Char: " << charVec2[i] << " " << K << endl;
	// 		// getchar();
	// 		for(it = newCharVec.begin(); it != newCharVec.end(); it++){
	// 			//wcout << *it << endl;
	// 			if(*it == '_'){
	// 				//it--;
	// 				//it2 = it--;
	// 				newCharVec.insert(it--, charVec2[i]);
	// 				//wcout << *it << endl;
	// 				it++;
	// 				break;
	// 			}
	// 		}
	// 	}
	// }

//For Random Instances

	for (int i = 0; i < charVec2.size(); i++){
		exists = 0;
		for (int j = 0; j < charVec1.size(); j++){
			if(charVec2[i] == charVec1[j]){
				exists = 1;
				break;
			}
		}
		if(exists < 1){
			newCharVec.push_back(charVec2[i]);
		}
	}

//_________________________________________________

// //CHAR LIST
// //______________________________________________

	// wcout.clear();
	// for (int i = 0; i < newCharVec.size(); i++){
	// 	wcout << newCharVec[i] << " ";
	// }
	// wcout << endl;

// //_______________________________________________
 	// getchar();

	for (int j = 0; j < charVec1.size(); j++){
		frow.push_back(0);
	}

	for(int i = 0; i < charVec1.size(); i++){
		freq1.push_back(frow);
	}	

	if (infile3.is_open()){
		infile3 >> file;
		infile3 >> file;
		infile3 >> n;
		
		for(int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				infile3 >> freq;
				freq1[i][j] = freq;
			}
		}	
		infile3.close();
	}

	// wcout.clear();
	// wcout << "Freq mat1: n = " << n << endl;
	// for (int i = 0; i < n; i++){
	// 	for (int j = 0; j < n; j++){
	// 		wcout << setw(10) << freq1[i][j] << " ";
	// 	}
	// 	wcout << endl;
	// }
	// wcout << endl;
	
	frow.clear();

	for (int j = 0; j < charVec2.size(); j++){
		frow.push_back(0);
	}

	for(int i = 0; i < charVec2.size(); i++){
		freq2.push_back(frow);
	}	

	if (infile4.is_open()){
		infile4 >> file;
		infile4 >> file;
		infile4 >> n;
		
		for(int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				infile4 >> freq;
				freq2[i][j] = freq;
			}
		}	

		infile4.close();
	}

	// wcout.clear();
	// wcout << "Freq mat2: n = " << n << endl;
	// for (int i = 0; i < n; i++){
	// 	for (int j = 0; j < n; j++){
	// 		wcout << setw(7) << freq2[i][j] << " ";
	// 	}
	// 	wcout << endl;
	// }
	// wcout << endl;

	frow.clear();

	for (int j = 0; j < newCharVec.size(); j++){
		frow.push_back(0);
	}

	for(int i = 0; i < newCharVec.size(); i++){
		newFreq.push_back(frow);
	}	
//_________________________________________________

	//For Real Instances

	// for (int i = 0; i < newCharVec.size()-1; i++){
	// 	for (int k = 0; k < charVec1.size()-1; k++){
	// 		if (newCharVec[i] == charVec1[k]){
	// 			for (int j = 0; j < newCharVec.size()-1; j++){
	// 				for (int l = 0; l < charVec1.size()-1; l++){
	// 					if (newCharVec[j] == charVec1[l]){
	// 						//wcout << newCharVec[i] << "-" << newCharVec[j] << " " << charVec2[k] << "-" << charVec2[l] << ": " << freq2[k][l] << endl;
	// 						newFreq[i][j] = freq1[k][l];
	// 					}
	// 				}
	// 			} 
	// 		}
	// 	}
	// }
	
	//For Random Instances

	for (int i = 0; i < newCharVec.size(); i++){
		for (int k = 0; k < charVec1.size(); k++){
			if (newCharVec[i] == charVec1[k]){
				for (int j = 0; j < newCharVec.size(); j++){
					for (int l = 0; l < charVec1.size(); l++){
						if (newCharVec[j] == charVec1[l]){
							//wcout << newCharVec[i] << "-" << newCharVec[j] << " " << charVec2[k] << "-" << charVec2[l] << ": " << freq2[k][l] << endl;
							newFreq[i][j] = freq1[k][l];
						}
					}
				} 
			}
		}
	}	
//_________________________________________________

	//int sn = newCharVec.size() - 1;

	// wcout.clear();
	// wcout << "n = " << newCharVec.size() << endl;
	// for (int i = 0; i < newCharVec.size(); i++){
	// 	for (int j = 0; j < newCharVec.size(); j++){
	// 		wcout << setw(7) << newFreq[i][j] << " ";
	// 	}
	// 	wcout << endl;
	// }
	// wcout << endl;

	// getchar();
//_________________________________________________

//For Real Instances

	// for (int i = 0; i < charVec2.size()-1; i++){
	// 	for (int k = 0; k < charVec1.size()-1; k++){
	// 		if(charVec2[i] == charVec1[k]){
	// 			for (int j = 0; j < charVec2.size()-1; j++){
	// 				for (int l = 0; l < charVec1.size()-1; l++){
	// 					if(charVec2[j] == charVec1[l]){
	// 						// if (i == charVec2.size() && k == charVec1.size()){
	// 						// 	newFreq[sn][l] = freq2[i][j]+freq1[k][l];
	// 						// 	newFreq[l][sn] = freq2[j][i]+freq1[l][k];
	// 						// }
	// 						//wcout << "i: " << i << " j: " << j <<  " k: " << k << " l: " << l << " " <<endl;

	// 						//wcout << charVec2[i] << "-" << charVec2[j] << ": " << freq2[i][j] << " " << charVec1[k] << "-" << charVec1[l] << ": " << freq1[k][l] << " " << freq2[i][j]+freq1[k][l] << endl;
							
	// 						newFreq[k][l] = freq2[i][j]+freq1[k][l];
							
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// }


//For Random Instances

	for (int i = 0; i < charVec2.size(); i++){
		for (int k = 0; k < charVec1.size(); k++){
			if(charVec2[i] == charVec1[k]){
				for (int j = 0; j < charVec2.size(); j++){
					for (int l = 0; l < charVec1.size(); l++){
						if(charVec2[j] == charVec1[l]){
							// if (i == charVec2.size() && k == charVec1.size()){
							// 	newFreq[sn][l] = freq2[i][j]+freq1[k][l];
							// 	newFreq[l][sn] = freq2[j][i]+freq1[l][k];
							// }
							//wcout << "i: " << i << " j: " << j <<  " k: " << k << " l: " << l << " " <<endl;

							//wcout << charVec2[i] << "-" << charVec2[j] << ": " << freq2[i][j] << " " << charVec1[k] << "-" << charVec1[l] << ": " << freq1[k][l] << " " << freq2[i][j]+freq1[k][l] << endl;
							
							newFreq[k][l] = freq2[i][j]+freq1[k][l];
							
						}
					}
				}
			}
		}
	}
//_________________________________________________

	//int i = charVec2.size() - 1;
	//int k = charVec1.size() - 1;
	//int sn = newCharVec.size() - 1;

	// wcout.clear();
	// wcout << "n = " << newCharVec.size() << endl;
	// for (int i = 0; i < newCharVec.size(); i++){
	// 	for (int j = 0; j < newCharVec.size(); j++){
	// 		wcout << setw(7) << newFreq[i][j] << " ";
	// 	}
	// 	wcout << endl;
	// }
	// wcout << endl;


//________For Real Instances (1 space char)__________

	// int i = charVec2.size()-1;
	// int k = charVec1.size()-1;
	// int sn = newCharVec.size()-1;

	// for (int j = 0; j < charVec2.size(); j++){
	// 	for (int l = 0; l < charVec1.size(); l++){
	// 		if(charVec2[j] == charVec1[l]){
	// 			// wcout << j << " " << l << " " << charVec2[j] << " " << charVec1[l] << endl; 
	// 			// wcout << "1. " << freq1[k][l] << " " << freq2[i][j] << "->" << freq2[i][j]+freq1[k][l] << endl;
	// 			// wcout << "2. " << freq1[l][k] << " " << freq2[j][i] << "->" << freq2[j][i]+freq1[l][k] << endl;
	// 			newFreq[l][sn] = freq2[j][i]+freq1[l][k];
	// 			newFreq[sn][l] = freq2[i][j]+freq1[k][l];
	// 		}
	// 	}
	// } 


	//Skip for Random Instances


//________For 5 space chars (QWERTY format)__________

 // // 	newCharVec.erase (newCharVec.end()-4, newCharVec.end());

 // // 	wcout.clear();
	// // for (int i = 0; i < newCharVec.size(); i++){
	// // 	wcout << newCharVec[i] << " ";
	// // }
	// // wcout << endl;
	// // getchar();

	// int i = charVec2.size();
	// int k = charVec1.size();
	// int sn = newCharVec.size();


	// for (int j = 0; j < charVec2.size(); j++){
	// 	for (int l = 0; l < charVec1.size(); l++){
	// 		if(charVec2[j] == charVec1[l]){
	// 			for(int a = 5 ; a > 0; a--){
	// 				newFreq[l][sn-a] = freq2[j][i-a]+freq1[l][k-a];
	// 				newFreq[sn-a][l] = freq2[i-a][j]+freq1[k-a][l];				
	// 			}
	// 			//wcout << j << " " << l << " " << charVec2[j] << " " << charVec1[l] << endl; 
	// 			//wcout << "1. " << freq1[k][l] << " " << freq2[i][j] << "->" << freq2[i][j]+freq1[k][l] << endl;
	// 			//wcout << "2. " << freq1[l][k] << " " << freq2[j][i] << "->" << freq2[j][i]+freq1[l][k] << endl;
	// 		}
	// 	}
	// }		

	// wcout.clear();
	// wcout << "n = " << newCharVec.size() << endl;
	// for (int i = 0; i < newCharVec.size(); i++){
	// 	for (int j = 0; j < newCharVec.size(); j++){
	// 		wcout << setw(7) << newFreq[i][j] << " ";
	// 	}
	// 	wcout << endl;
	// }
	// wcout << endl;

	// getchar();
//______________________________________________

//________For Real Instances/1 space char__________
	// for (int i = charVec1.size() - 1; i < newCharVec.size() - 1; i++){
	// 	for (int k = 0; k < charVec2.size(); k++){
	// 		if (newCharVec[i] == charVec2[k]){
	// 			for (int j = 0; j < newCharVec.size(); j++){
	// 				for (int l = 0; l < charVec2.size(); l++){
	// 					if (newCharVec[j] == charVec2[l]){
	// 						//wcout << newCharVec[i] << "-" << newCharVec[j] << " " << charVec2[k] << "-" << charVec2[l] << ": " << freq2[k][l] << endl;
	// 						newFreq[i][j] = freq2[k][l];
	// 						newFreq[j][i] = freq2[k][l];
	// 					}
	// 				}
	// 			} 
	// 		}
	// 	}
	// }


//________For Random intances__________
	for (int i = charVec1.size(); i < newCharVec.size(); i++){
		for (int k = 0; k < charVec2.size(); k++){
			if (newCharVec[i] == charVec2[k]){
				for (int j = 0; j < newCharVec.size(); j++){
					for (int l = 0; l < charVec2.size(); l++){
						if (newCharVec[j] == charVec2[l]){
							//wcout << newCharVec[i] << "-" << newCharVec[j] << " " << charVec2[k] << "-" << charVec2[l] << ": " << freq2[k][l] << endl;
							newFreq[i][j] = freq2[k][l];
							newFreq[j][i] = freq2[k][l];
						}
					}
				} 
			}
		}
	}
//______________________________________________


//CHAR LIST
//______________________________________________

	// wcout.clear();
	// for (int i = 0; i < newCharVec.size(); i++){
	// 	wcout << newCharVec[i] << " ";
	// }
	// wcout << endl;

//_______________________________________________
//getchar();	

//INSTANCE MATRIX
//_______________________________________________

	wcout.clear();
	wcout << "n = " << newCharVec.size() << endl;
	for (int i = 0; i < newCharVec.size(); i++){
		for (int j = 0; j < newCharVec.size(); j++){
			wcout << setw(7) << newFreq[i][j] << " ";
		}
		wcout << endl;
	}
	wcout << endl;

//_______________________________________________


//	else cout << "Unable to open file"; 

	return 0;
}


