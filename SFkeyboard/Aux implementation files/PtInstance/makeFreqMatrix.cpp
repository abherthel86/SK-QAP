//create Portuguese Instance
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
	wchar_t char1;
	wchar_t char2;
	long long freq;
};

struct FChar{
	wchar_t schar;
	long long charfreq;
};

bool compareByLength(const FChar &a, const FChar &b)
{
    return a.charfreq > b.charfreq;
}

int main () { 

	//std::ios::sync_with_stdio(false);

	//locale loc("en_US.UTF-8");

	std::locale loc("");
	std::locale::global (loc);

	wcout.imbue(loc);

	wfstream infile1("smallptcorpus.txt");
	wfstream infile2("CharPortuguese.txt");

	infile1.imbue(loc);
	infile2.imbue(loc);

	CPairs charpair;
	FChar fchar;

	vector<wchar_t>  charVec;
	vector<wchar_t>  wordVec;
	vector<CPairs> pairVec;
	vector<FChar> charfreqList;
	vector< vector <long long> > freqVec;
	vector<long long> freqRow;
	
	wstring word;
	wstring line;
	wstring file;

	std::wstring::iterator it;

	int counter;
	int pos1;
	int pos2;
	int next;

	wchar_t cchar;

	wchar_t	wrdchars;

	bool exists;
	long long freq = 0;

	if (infile2.is_open()){
		while (infile2 >> wrdchars){		
			charVec.push_back(wrdchars);
		}
		//charVec.push_back('_');
		infile2.close();
	}

	else cout << "Unable to open file"; 

	// wcout << L"Char Vector: ";
	// for (int i = 0; i < charVec.size(); i++){
	// 	wcout << charVec[i] << " ";
	// }
	// wcout << endl;

	for (int i = 0; i < charVec.size(); i++){
		for (int j = 0; j < charVec.size(); j++){
			freqRow.push_back(0);
		}
		freqVec.push_back(freqRow);
		fchar.schar = charVec[i];
		charfreqList.push_back(fchar);
	}
	wcout.clear();

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
	if (infile1.is_open()){
		while (getline (infile1, line)){
		// counter = 1;
		// while (counter <= 7){
			infile1 >> word;

			wordVec.clear();
			
			wordVec.push_back('_');
			for (it = word.begin(); it != word.end(); it++){
				cchar = *it;
				wordVec.push_back(cchar);
			}
			wordVec.push_back('_');
			
			infile1 >> freq;

			for (int i = 0; i < wordVec.size(); i++){
				if (i + 1 < wordVec.size()){
					charpair.char1 = wordVec[i];
					charpair.char2 = wordVec[i + 1];
					charpair.freq = freq;
					pairVec.push_back(charpair);
				}
			}

			//wcout << L"Pair Vector: ";

			// for (int i = 0; i < pairVec.size(); i++){
			// 	wcout <<"(" << pairVec[i].char1 << "-"<< pairVec[i].char2 << "),";
			// }


			//wcout << endl;
			wcout.clear();

		 	counter++;
		// }

		}
		for (int i = 0; i < pairVec.size(); i++){
			pairVec[i].char1 = toupper(pairVec[i].char1, loc);
			pairVec[i].char2 = toupper(pairVec[i].char2, loc);

			for (int j = 0; j < charVec.size(); j++){
				if (pairVec[i].char1 == charVec[j]){
					pos1 = j;
				}
				if (pairVec[i].char2 == charVec[j]){
					pos2 = j;
				}
			}
			// for (int j = 0; j < charVec.size(); j++){
			// 	if (pairVec[i].char2 == charVec[j]){
			// 		pos2 = j;
			// 		break;
			// 	}
			// }
			// wcout <<"(" << pairVec[i].char1 << pairVec[i].char2 << ") - (" << pos1 << pos2 << ")" << endl;

			// wcout << L"Freq: " << pairVec[i].freq << endl;
			freqVec[pos1][pos2] += pairVec[i].freq;
			freqVec[pos2][pos1] += pairVec[i].freq;
		}



		wcout << L"n = " << charfreqList.size() << endl;
		for(int i = 0; i < freqVec.size(); i++){
			for(int j = 0; j < freqVec.size(); j++){
				if (i == j){
					freqVec[i][j] = 0;
				}
				wcout << setw(10) << std::right << freqVec[i][j] << " ";
			}
			wcout << endl;
		}

		wcout << endl;
		wcout.clear();

		// wcout << "\nVector Size: " << charVec.size() << endl;
		for (int i = 0; i < freqVec.size(); i++){
			fchar.charfreq = 0;
			if (i == 0){
				wcout << fchar.charfreq << endl;
			}
			for (int j = 0; j < freqVec.size(); j++){
				fchar.charfreq += freqVec[i][j];
				if (i == 0){
					wcout << freqVec[i][j] << endl << fchar.charfreq << endl;
				}
			}
			charfreqList[i].charfreq = fchar.charfreq;
		}

		//std::sort(charfreqList.begin(), charfreqList.end() - 1, compareByLength);
		
		wcout << L"Char Frequency list: ";
		for (int i = 0; i < charfreqList.size(); i++){
			wcout << charfreqList[i].schar << " :" << charfreqList[i].charfreq << endl;
		}
		wcout << endl;
		
		infile1.close();
	}

	else cout << "Unable to open file"; 

	return 0;
}


