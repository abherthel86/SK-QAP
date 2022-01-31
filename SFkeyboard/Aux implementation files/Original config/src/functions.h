#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

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
#include <ilcplex/ilocplex.h>
#include <stdlib.h>
#include <iostream>
#include <locale.h>
#include <sys/time.h>
#include <ctime>
#include <unistd.h>

using namespace std;

struct Gendata{

	int size;
	long long **freq_matrix;
	int **b_matrix;
	char *char_list;
};

struct Keyboard{

	int *grid;
	long long cost;
	int *assignment;
	int ksize;
	int kcols;
	int krows;
};

struct Stats{

	long swapSt;
	long spPairSt;
	long mvContSt;
	long pert1St;
	long pert2St;
	long pert3St;
	long pert4St;

	double swapTime;
	double spPairTime;
	double mvContTime;
};

struct Strows{
	vector<int> row;
	vector<int> posiVec;

	int asgnchars;
	int pos;
	long long rowHash;
	long long rowCost;
	long long posiHash;
	int fchar;
	int lchar;
};

struct SPairs{
	int pos;
	int vpair;
	int hpair;

	bool vert;
	bool horiz;
};

struct stShRow{
	vector <int> shiftRow;
	vector <int> posRow;
	long long rowCost;
	vector <long long> twoRowCost;
	long long relCost;
	double shift;
};

typedef struct Gendata DATA;
typedef struct Keyboard KEYB;

void readData(int argc, char** argv, Gendata*, Keyboard*);
void initSol(Gendata*, Keyboard*);
long long costcalc (Gendata*, int, Keyboard*);
void removecost (Gendata*, vector<long long>&, Keyboard*);
void contourSet (Gendata*, Keyboard*, list<int>&, vector<int>&, int);
void rmvContour (Keyboard*, list<int>&, vector<int>&, int);
void printSol (Gendata *data, Keyboard *keyb, vector<int>& auxKeyb);
void printSolNum (Gendata *data, Keyboard *keyb, vector<int>& auxKeyb);
bool verifyContour (Gendata *data, Keyboard *keyb, list<int>& contourPos, vector<int>& aux_keyb, int k);
void initStat (Stats *stat);
void initTime (Stats *stat);
void hashValues (Gendata *data, vector<int>& valCharList);
void addRowPool (Gendata *data, Keyboard *keyb, Strows *strow, vector<Strows>& rowPool, vector<int>& valCharList, vector< vector<int> >& sizeRows, vector< vector<int> >& charPoolPos);
bool verifyRow (Strows *strow, vector<Strows>& rowPool);
void makeCoexMatrix (Gendata *data, vector<int>& valCharList, vector<Strows>& rowPool, vector< vector<int> >& coexMatrix);
void rowCostMatrix (Gendata *data, Keyboard *keyb, vector<Strows>& rowPool, vector< vector< vector<long long> > >& costMatrix, vector< vector<int> >& coexMatrix, int numRows);
void makeYMatrix (Gendata *data, Keyboard *keyb, vector<Strows>& rowPool, vector< vector<int> >& yMat, vector< vector<int> >& sizeRows, int numRows);
void addBestSol (Gendata *data, Keyboard *keyb, Strows *strow, vector<Strows>& rowPool, vector<int>& valCharList, vector< vector<int> >& sizeRows, vector< vector<int> >& charPoolPos);
void makeNewBMat (Gendata *data, Keyboard *keyb, vector < vector < vector < vector <int> > > >& newBMatrix);
void printShiftedSol (Gendata *data, Keyboard *keyb, vector<int>& auxKeyb);
void shiftSol (Gendata *data, Keyboard *keyb, vector < vector < vector < vector <int> > > >& newBMatrix, vector <stShRow>& vecShSol, stShRow *shRow, vector <int>& occRows, vector <double>& shifts);
void pertCount (int pertChoice, Stats *stat);
double get_wall_time();
//void calcRowCost (Gendata *data, Keyboard *keyb, );

//void calcRelCost (Gendata *data, Keyboard *keyb, );

#endif
