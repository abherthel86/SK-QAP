// reading a text file
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
  string line;
  string instance;

  int counter;

  long long globalMean = 0;
  long long globalTotal;
  long long globalCost = 0;

  ifstream infile ("GlobalCostsT1.txt");

  if (infile.is_open()){
    while (getline (infile, line)){
      counter = 1;
      globalTotal = 0;
      while (counter <= 10){
        infile >> instance;
        infile >> globalCost;
        globalTotal += globalCost;
        counter++;
      }
      globalMean = globalTotal/10;
      cout << instance << " - Mean Cost: " <<  globalMean << endl;
    }
    infile.close();
    cout << endl;
  }

  else cout << "Unable to open file"; 

  return 0;
}