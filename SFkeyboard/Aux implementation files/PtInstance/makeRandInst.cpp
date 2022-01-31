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

struct S_Word{
	wstring sWord;
	long long wordFreq;
};

struct FChar{
	wchar_t schar;
	long long charfreq;
};

int main (){ 

	srand (time(0));

	std::locale loc("");
	std::locale::global (loc);

	wcout.imbue(loc);

	wfstream infile1("smallptcorpus.txt");
	wfstream infile2("CharPortuguese.txt");

	infile1.imbue(loc);
	infile2.imbue(loc);

	CPairs charpair;
	S_Word wordSt;
	FChar fchar;

	vector<wchar_t>  charVec;
	vector<wchar_t>  wordVec;
	vector<CPairs> pairVec;
	vector<FChar> charfreqList;
	vector< vector <long long> > freqVec;
	vector<long long> freqRow;
	vector<S_Word> wordList;

	wstring word;
	wstring line;
	wstring file;

	std::wstring::iterator it;

	int counter = 1;
	int rpos;
	int pos1;
	int pos2;
	int next;
	int lSize = 5000;
	int nRand = 1000;

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

	else cout << "Unable to open file" << endl; 
	
	if (infile1.is_open()){
		while (wordList.size() < lSize){
			infile1 >> wordSt.sWord;
			infile1 >> wordSt.wordFreq;
			wordList.push_back(wordSt);
			//counter++;
		}
		infile1.close();
	}
	else cout << "Unable to open file" << endl;

	// wcout << L"Word List: ";
	// for (int i = 0; i < wordList.size(); i++){
	// 	wcout << wordList[i].sWord << " " << wordList[i].wordFreq << endl;
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

	for (int i = 0; i < nRand; i++){
		rpos = rand() % lSize;
		word = wordList[rpos].sWord;
		freq = wordList[rpos].wordFreq;
		
		wordList.erase(wordList.begin() + rpos);

		//wcout << L"rpos: " << rpos << " word: " << word << " freq: " << freq << endl;

		wordVec.clear();

		wordVec.push_back('_');
		for (it = word.begin(); it != word.end(); it++){
			cchar = *it;
			wordVec.push_back(cchar);
		}
		wordVec.push_back('_');
		//nesse 'for' a variável de iteração era 'i'. Mudei para 'j' - precisa refazer as inst aleatórias
		for (int j = 0; j < wordVec.size(); j++){
			if (j + 1 < wordVec.size()){
				charpair.char1 = wordVec[j];
				charpair.char2 = wordVec[j + 1];
				charpair.freq = freq;
				pairVec.push_back(charpair);
			}
		}

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

		//wcout <<"(" << pairVec[i].char1 << pairVec[i].char2 << ") - (" << pos1 << pos2 << "): " << pairVec[i].freq << endl;

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


	return 0;
}


