//calculate solution cost and time means
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
  string line;
  string instance;

  int counter;

  long long meanCost = 0;
  long long totalCost;
  long long globalCost = 0;

  double meanTime = 0;
  double totalTime = 0;
  double globalTime = 0;

  ifstream infile ("GlobalStatsT1.txt");

  if (infile.is_open()){
    while (getline (infile, line)){
      counter = 1;
      totalCost = 0;
      totalTime = 0;

      while (counter <= 10){
        infile >> instance;
        infile >> globalCost;
        infile >> globalTime;
        totalCost += globalCost;
        totalTime += globalTime;
        counter++;
      }
      meanCost = totalCost/10;
      meanTime = totalTime/10;
      
      cout << instance << " - Mean Cost: " <<  meanCost << " - Mean Time: " <<  meanTime << endl;
    }
    infile.close();
    cout << endl;
  }

  else cout << "Unable to open file"; 

  return 0;
}