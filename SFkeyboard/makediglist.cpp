//Make digraph frequency list
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

bool myfunction (int i,int j) { return (i>j); }

int main (int argc, char* argv[]) {

if(argc > 3){
	cout << "Too many parameters." << endl;
	exit(1);
}

if(argc < 3){
	cout << "Missing parameters." << endl;
	exit(1);
}

char instance;	
int size;
int rsize;
int digsize;
long long freq;
long long highVal = 0;
string file;

ifstream in1(argv[1]);
ifstream in2(argv[2]);

vector<long long> frow;
vector< vector <long long> > freq_matrix;
pair<int, int> digraph;
vector< pair<int, int> > diglist;

vector<long long> frequencylist;

struct orderedList {

	vector< pair<int, int> > ordDig;
	vector<long long> ordDigFreq;

}ordList;

vector<char> char_list;

if (in1.is_open()){
	in1 >> file;
	in1 >> file;
	in1 >> size;
	
	rsize = size-1;

	for (int j = 0; j < size-1; j++){
		frow.push_back(0);
	}

	for(int i = 0; i < size-1; i++){
		freq_matrix.push_back(frow);
	}
	
	for(int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if(i == size - 1 || j == size -1){
				in1 >> file;
			}
			else{
				in1 >> freq;
				freq_matrix[i][j] = freq;
			}
		}
	}	
	in1.close();
}

for (int i = 0; i < size-1; i++){
	char_list.push_back(0);
}

if (in2.is_open()){
	for (int i = 0; i < size-1; i++){
		in2 >> char_list[i];
	}
	in2.close();
}


digsize = ((rsize*rsize) - rsize) / 2;

for (int i = 0; i < rsize; i++){
	for (int j = i + 1; j < rsize; j++){
		frequencylist.push_back(freq_matrix[i][j]);
		digraph.first = i;
		digraph.second = j;
		diglist.push_back(digraph);
	}
}

//cout << "\nDigraph list size: " << digsize << endl;

// cout << "\nCharacter List: " << endl;

// for (int i = 0; i < size-1; i++){
// 	cout << char_list[i] << " ";
// }

// cout << endl;


// cout << "\nFreq	matrix" << endl;

// for (int i = 0; i < size-1; i++){
// 	for (int j = 0; j < size-1; j++){
// 		cout << setw(7) << right << freq_matrix[i][j] << " ";
// 	}
// 	cout << endl;
// }

// for (int j = 0; j < rsize; j++){
// 	for (int k = j + 1; k < rsize; k++){
// 		digraph.first = j;
// 		digraph.second = k;
// 		diglist.push_back(digraph);
// 	}
// }

// cout << "\nDigraph list: " << endl;
// int c = 0; 
// for (int i = 0; i < digsize; i++){
// 	cout << "\nPair " << c << ": " << diglist[i].first << ": " << char_list[diglist[i].first] << " " << diglist[i].second << ": " << char_list[diglist[i].second] << endl;
// 	c++;
// 	getchar();
// }

int pos = 0;
//int eliminpos = 0;
while (!frequencylist.empty()){
	highVal = 0;
	// for (int i = 0; i < rsize; i++){
	// 	for (int j = i + 1; j < rsize; j++){
	// 		if(freq_matrix[i][j] > highVal){
	// 			highVal = freq_matrix[i][j];
	// 			digraph.first = i;
	// 			digraph.second = j;
	// 		}
	// 	}
	// }
	for (int i = 0; i < frequencylist.size(); i++){
		// if(freq_matrix[diglist[i].first][diglist[i].second] > highVal){
		// 	highVal = freq_matrix[diglist[i].first][diglist[i].second];
		// 	digraph.first = diglist[i].first;
		// 	digraph.second = diglist[i].second;
		// }
		if(frequencylist[i] >= highVal){
			highVal = frequencylist[i];
			//pos = digsize - (((rsize - digraph.first)*(rsize - 1 - digraph.first)) / 2) + (digraph.second - digraph.first - 1) - eliminpos;
			pos = i;
			digraph.first = diglist[pos].first;
			digraph.second = diglist[pos].second;
		}

	}	

	ordList.ordDig.push_back(digraph);
	ordList.ordDigFreq.push_back(highVal);
	//pos = digsize - (((rsize - digraph.first)*(rsize - 1 - digraph.first)) / 2) + (digraph.second - digraph.first - 1) - eliminpos;
	//cout << "\nHighest Frequency: " << char_list[diglist[pos].first] << " " << char_list[diglist[pos].second] << " -> " << highVal << endl;
	//cout << "\nPosition to be erased: " << pos;
	//getchar();
	diglist.erase(diglist.begin() + pos);
	frequencylist.erase(frequencylist.begin() + pos);
	//cout << "\nNew Size of list: " << diglist.size();
	//getchar();
	//eliminpos++;

	// cout << "\nDigraph list: " << endl;
	// int c = 0; 
	// for (int i = 0; i < digsize; i++){
	// 	cout << "\nPair " << c << ": " << diglist[i].first << ": " << char_list[diglist[i].first] << " " << diglist[i].second << ": " << char_list[diglist[i].second] << endl;
	// 	c++;
	// 	//getchar();
	// }
}

	// frequencylist.clear();

	// for (int i = 0; i < rsize; i++){
	// 	for (int j = i + 1; j < rsize; j++){
	// 		frequencylist.push_back(freq_matrix[i][j]);
	// 	}
	// }
	// sort(frequencylist.begin(), frequencylist.end(), myfunction);
	//getchar();

	// cout << "\nFirst F List: " << endl;
	// int counter = 0;
	// for (int i = 0; i < frequencylist.size(); i++){
	// 	cout << counter << ": " << frequencylist[i] << endl;
	// 	counter++;
	// }
	
	int counter = 0;

	// cout << "\nOrdered F List: " << endl;
	// for (int i = 0; i < ordList.ordDig.size(); i++){
	// 	//cout << counter << ": " << frequencylist[i];
		
	// 	cout << counter << ": " << char_list[ordList.ordDig[i].first] << " " << char_list[ordList.ordDig[i].second] << ": " << frequencylist[i] << " " << ordList.ordDigFreq[i] << endl;
	// 	counter++;
	// }

	cout << "\nOrdered F List: " << endl;
	for (int i = 0; i < ordList.ordDig.size(); i++){
		//cout << counter << ": " << frequencylist[i];	
		cout << char_list[ordList.ordDig[i].first] << "-" << char_list[ordList.ordDig[i].second] << " " << ordList.ordDigFreq[i] << endl;

	}


}