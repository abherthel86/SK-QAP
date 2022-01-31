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

int main () { 
	 
	//std::ios::sync_with_stdio(false);
	std::locale loc("");
	std::locale::global (loc);
  //wcin.imbue(loc);
	//locale loc("en_US.UTF-8");
	wcout.imbue(loc);

	wfstream infile("smallptcorpus.txt");

	infile.imbue(loc);

	vector<wchar_t>  charVec;

	wstring word;
	wstring line;
	wstring file;

	std::wstring::iterator it;

	int counter;
	int charnumber;

	wchar_t fchar;

	bool exists;

	if (infile.is_open()){
		while (getline (infile, line)){
			infile >> word;
			charnumber = charVec.size();

			for (it = word.begin(); it != word.end(); it++) {
				fchar = *it;
				exists = 0;
				if (isupper(fchar, loc)){
					fchar = tolower(fchar, loc);
				}

				if (charnumber > 0){
					for (int i = 0; i < charnumber; i++){
						if (fchar == charVec[i]){
							exists = 1;
							break;
						}
					}
					if (exists < 1){
						charVec.push_back(fchar);
					}
				}
				else if (charnumber <= 0){
					charVec.push_back(fchar);
				}
			}

			infile >> file;
		}

		charVec.push_back(' ');

		for (int i = 0; i < charVec.size(); i++){
			//charVec[i] = toupper(charVec[i], loc);
			wcout << charVec[i] << " ";
		}
		wcout << endl;
	    infile.close();
	}

	else cout << "Unable to open file"; 

	return 0;
}