//calculate solution cost and time means
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
  string line;
  string instance;
  string file;

  int counter;

  double meanTime = 0;
  double totalTime = 0;
  double globalTime = 0;

  ifstream infile ("GlobalStatsT5x3n.txt");
  ofstream offile;
  offile.open ("MTT5x3n.txt", ios::out | ios::app);
  
  if (infile.is_open()){
    while (getline (infile, line)){
      counter = 1;
      totalTime = 0;

      while (counter <= 10){
        infile >> instance;
        infile >> file;
        infile >> globalTime;

        totalTime += globalTime;
        counter++;
      }
      meanTime = totalTime/10;
      
      offile << instance << " " << meanTime << endl;
    }
    offile.close();
    infile.close();
    cout << endl;
  }

  else cout << "Unable to open file"; 

  return 0;
}