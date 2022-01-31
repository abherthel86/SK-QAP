
#include "cpuTime.h"
#include "functions.h"
#include "localsearch.h"
#define KEYS 140

using namespace std;

int main (int argc, char *argv[]) {

	double t1 = 0;
	double t2 = 0;
	double deltaT = 0;

	double runTime = 0;

	Gendata data;
	Keyboard keyb;
	Stats stat;
	Strows strow;

	readData (argc, argv, &data, &keyb);

	srand (time(0));


	vector <int> bestSol;
	vector <int> bestGlobalSol;

	vector <Strows> rowPool;
	vector <int> valCharList;
	vector <int> auxVec;
	vector <int> rowAsgn;
	vector <int> rowPattern;

	vector< vector<int> > sizeRows;
	vector< vector<int> > charPoolPos;
	vector< vector<int> > yMat;
	
	int pertChoice = 0;
	int iterILS;
	//int maxIterILS = 3 * data.size;
	int maxIterILS = 5;
	int mscount = 0;
	//int msMax = 10;
	int msMax = 2;
	int numRows = 0;
	//int maxDifRows = 0;
	int centerRow;
		
	vector < vector < vector <long long> > > costMatrix;
	vector < vector <int> > coexMatrix;

	long long bestSolCost;
	long long bestGlobalCost = numeric_limits<long long>::max();
	
	hashValues (&data, valCharList);
	
	for (int i = 0; i < keyb.ksize; i++){
		bestGlobalSol.push_back(0);
	}

	for (int i = 0; i < data.size; i++){
		charPoolPos.push_back(auxVec);
	}

	initTime (&stat);

	while (mscount < msMax){
		
		t1 = cpuTime();

		iterILS = 0;
		pertChoice = 0;

		initSol (&data, &keyb);
		initStat (&stat);

		for (int i = 0; i < keyb.ksize; i++){
			bestSol.push_back(0);
		}
		
		for (int i = 0; i < keyb.ksize; i++){
			bestSol[i] = keyb.grid[i];
		}

		bestSolCost = keyb.cost;
		 
		while (iterILS <= maxIterILS){

			SF_RVND (&data, &keyb, &stat);

			addRowPool (&data, &keyb, &strow, rowPool, valCharList, sizeRows, charPoolPos);

			if (keyb.cost < bestSolCost) {
				for (int i = 0; i < keyb.ksize; i++){
					bestSol[i] = keyb.grid[i];
				}

				bestSolCost = keyb.cost;
		
				iterILS = 0;

				switch (pertChoice){
					case 0:
						break;
					case 1: 
						stat.pert1St++;
						break;

					case 2:
						stat.pert2St++;
						break;

					default:
						cout << "Out of range" << endl;
						break;
				}
				pertChoice = 0;
			}

			perturbation(&data, &keyb, &pertChoice);
			iterILS++;
		}

		//cout << "\n-----x-----" << "\nBest Solution: " << endl;
		
		//printSol(&data, &keyb, bestSol);

		if (bestSolCost < bestGlobalCost){
			bestGlobalCost = bestSolCost;
			bestGlobalSol = bestSol;
		}

/*		cout <<"\n\nBest Solution Cost: " << bestSolCost << endl;

		cout << "\n\nRVND Stats: Swap Count: " << stat.swapSt << " Time: " << stat.swapTime << "s - Swap Pair Count: " << stat.spPairSt << " Time: " << stat.spPairTime << "s - Move Contour Count: " << stat.mvContSt << " Time: " << stat.mvContTime << "s" << endl;

		cout << "Perturbation 1 Count: " << stat.pert1St << " Perturbation 2 Count: " << stat.pert2St << endl;*/
		
		t2 = cpuTime();
		deltaT = t2 - t1;

		runTime += deltaT;
		
		cout << "\nElapsed Time: " << deltaT << " seconds" << endl << endl;

		cout << "CPU Time: " << runTime << " seconds" << endl << endl;

		mscount++;
	}
	
	for (int i = 0; i < keyb.krows; i++){
		for (int j = 0; j < keyb.kcols; j++){
			int elem1 = i * keyb.kcols + j;
			if (bestGlobalSol[elem1] > -1){
				numRows++;
				rowAsgn.push_back(i);
				break;
			}
		}
	}

	for (int i = 0; i < rowAsgn.size(); i++){
		for (int j = 0; j < keyb.kcols; j++){
			int elem1 = rowAsgn[i] * keyb.kcols + j;
			if (bestGlobalSol[elem1] == data.size - 1){
				centerRow = i;
				break;
			}
		}
	}

	cout << "\nCenter Row: " << centerRow << endl;

	// if (centerRow > floor(numRows/2)){
	// 	reverse(rowAsgn.begin(), rowAsgn.end());
	// 	reverse(bestGlobalSol.begin(), bestGlobalSol.end());

	// 	cout << "\nNew Solution: " << endl;
	// 	printSol(&data, &keyb, bestGlobalSol);
	// 	long long testCost = costcalc(&data, -2, &keyb);
	// 	cout << "\nNew Cost: " << testCost << endl;
	// }

	// rowPattern.push_back(0);
	// int counter = 1;

	// while(rowPattern.size() < numRows){
	// 	rowPattern.insert (rowPattern.begin(), counter);
	// 	if (rowPattern.size() < numRows){
	// 		rowPattern.push_back(counter);
	// 		//rowPattern.push_back(counter * 10);
	// 	}
	// 	counter++;
	// }

	// cout << "\nSolution Rows:" << endl;
	// for (int i = 0; i < rowPattern.size(); i++){
	// 	cout << rowPattern[i] << " ";
	// }
	// cout << endl;

	cout << "\n-----x-----" << "\nBest Global Solution: " << endl;
	
	printSol(&data, &keyb, bestGlobalSol);

	cout <<"\n\nBest Global Solution Cost: " << bestGlobalCost << endl;

	// cout << "\nRow Pool final:" << rowPool.size() << endl;

	// for (int i = 0; i < rowPool.size(); i++){
	// 	cout << i << ": ";
	// 	for (int j = 0; j < rowPool[i].row.size(); j++){
	// 		if (rowPool[i].row[j] < 0){
	// 			cout << " * ";
	// 		}
	// 		else{
	// 			cout << " " << data.char_list[rowPool[i].row[j]] << " ";
	// 		}
	// 	}
	// 	//cout << " - Hash: " << rowPool[i].rowHash;
	// 	//cout << " - Row Size: " << rowPool[i].asgnchars;
	// 	//cout << " => Pos: " << rowPool[i].pos;
	// 		for (int k = 0; k < rowPool[i].posiVec.size; k++){

	// 		}
	// 	cout << endl;
	// }
	
	makeCoexMatrix (&data, valCharList, rowPool, coexMatrix);				//Usar vector para coexMatrix
	
	rowCostMatrix (&data, &keyb, rowPool, costMatrix, coexMatrix, numRows);

	cout << "\nRow Pool final:" << rowPool.size() << endl;

	for (int i = 0; i < rowPool.size(); i++){
		cout << i << ": ";
		for (int j = 0; j < rowPool[i].row.size(); j++){
			// if (rowPool[i].row[j] < 0){
			// 	cout << " * ";
			// }
			//else{
				cout << " " << data.char_list[rowPool[i].row[j]] << " ";
			//}
		}
		//cout << " => Cost: " << rowPool[i].rowCost;
		//cout << " - Row Size: " << rowPool[i].asgnchars;
		//cout << " => Pos: " << rowPool[i].pos;
		// cout << "=> Position Vector: ";
		// 	for (int k = 0; k < rowPool[i].posiVec.size(); k++){
		// 		cout << rowPool[i].posiVec[k] << " ";
		// 	}

		cout << endl;
	}
	// for (int k = 0; k < sizeRows.size(); k++){
	// 	sort(sizeRows[k].begin(), sizeRows[k].end() );
	// 	sizeRows[k].erase( unique( sizeRows[k].begin(), sizeRows[k].end() ), sizeRows[k].end() );
	// 	for (int l = 0; l < sizeRows[k].size(); l++){
	// 		if (sizeRows[k][l] > numRows - 1){
	// 			sizeRows[k].erase(sizeRows[k].begin() + l);
	// 		}
	// 	}
	// }

	makeYMatrix(&data, &keyb, rowPool, yMat, sizeRows, numRows, centerRow);

	cout << "\nSize of Row Vector: " << endl;
	for (int k = 0; k < sizeRows.size(); k++){
		if (sizeRows[k].size() < 1){
			continue;
		}
		else{
			cout << k << ": ";
		}
		for (int l = 0; l < sizeRows[k].size(); l++){
			cout << sizeRows[k][l] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "\nPatterns by Char: " << endl;
	for (int k = 0; k < charPoolPos.size(); k++){
		cout << data.char_list[k] << ": ";
		
		for (int l = 0; l < charPoolPos[k].size(); l++){
			cout << charPoolPos[k][l] << " ";
		}
		cout << endl;
	}
	cout << endl;

	/*------SET PARTITIONING------*/
	
	//Creating environment and model 
	char var[100];
	IloEnv env;
	IloModel model(env, "SKQAP");

	//Creating variables
	
	IloArray <IloArray<IloBoolVarArray> > x(env, rowPool.size()); 	

	for (int i = 0; i < rowPool.size(); i++) {
		IloArray <IloBoolVarArray> array2D(env, rowPool.size());
		x[i] = array2D;
		for (int j = 0; j < rowPool.size(); j++) {
			IloBoolVarArray array(env, numRows);
			x[i][j] = array;
		}
	}

	for (int i = 0; i < rowPool.size() - 1; i++) {
		for (int j = i + 1; j < rowPool.size(); j++) {
			for (int k = 1; k < numRows; k++) {
				if (coexMatrix[i][j] > 0){
					sprintf(var, "x_%d_%d_%d", i, j, k);
					x[i][j][k].setName(var);
					model.add(x[i][j][k]);
				}
 			}
		}
	}

	IloArray <IloBoolVarArray> y(env, rowPool.size());

	for (int i = 0; i < rowPool.size(); i++){
		y[i] = IloBoolVarArray (env, rowPool.size());
	}
	 
	for (int i = 0; i < rowPool.size(); i++){
		for (int l = 0; l < numRows; l++){
			if (yMat[i][l] > 0){
				sprintf(var, "y_%d_%d", i, l);
				y[i][l].setName(var);
				model.add(y[i][l]);
			}
		}
	}

	//Creating objective function
	
	 IloExpr objFunction(env);

	for (int i = 0; i < rowPool.size() - 1; i++){
		for (int j = i + 1; j < rowPool.size(); j++){
			for (int k = 1; k < numRows; k++){
				if (coexMatrix[i][j] > 0){
					objFunction += (double)costMatrix[i][j][k]*x[i][j][k];
				}
			}
		}
	}

	for (int i = 0; i < rowPool.size(); i++){
		for (int l = 0; l < numRows; l++){
			if (yMat[i][l] > 0){
				objFunction += (double)(rowPool[i].rowCost)*(y[i][l]);
			}
		}
	}

	//Creating constraints
	//Constraint 1

	for (int c = 0; c < charPoolPos.size(); c++){
		IloExpr exp(env);
		sprintf (var, "Constraint1_%d", c);
		for (int i = 0; i < charPoolPos[c].size(); i++){
			int selRow = charPoolPos[c][i];
			for (int l = 0; l < numRows; l++){
				if (yMat[selRow][l] > 0){
					exp += y[selRow][l];
				}
			}
		}
		IloRange cons = (exp == 1);
		cons.setName(var);
		model.add(cons);
	}

	//Constraint 2
	
	for (int i = 0; i < rowPool.size() - 1; i++){
		for (int j = i + 1; j < rowPool.size(); j++){
			for (int k = 1; k < numRows; k++){
				for (int l = 0; l < numRows; l++){
					if (coexMatrix[i][j] > 0){
						if (yMat[i][l] > 0){
							if (l + k < numRows){
								if(yMat[j][l + k] > 0){
									IloExpr exp(env);
									sprintf (var, "Constraint2_%d_%d_%d_%d", i, j, k, l);

									exp = x[i][j][k] - y[i][l] - y[j][l + k];

									IloRange cons = (exp >= 0);
									cons.setName(var);
									model.add(cons);
								}
							}
						}
					}
				}
			}
		}
	}

	//Constraint 3
	
	for (int i = 0; i < rowPool.size() - 1; i++){
		for (int j = i + 1; j < rowPool.size(); j++){
			for (int k = 1; k < numRows; k++){
				for (int l = 0; l < numRows; l++){
					if (coexMatrix[i][j] > 0){
						if (yMat[i][l] > 0){
							if (l - k > 0){
								if(yMat[j][l - k] > 0){
									IloExpr exp(env);
									sprintf (var, "Constraint3_%d_%d_%d_%d", i, j, k, l);

									exp = x[i][j][k] - y[i][l] - y[j][l - k];

									IloRange cons = (exp >= 0);
									cons.setName(var);
									model.add(cons);
								}
							}
						}
					}
				}
			}
		}
	}

	model.add(IloMinimize(env, objFunction));

	IloCplex cplex(model);
	cplex.exportModel("SKQAP.lp");

	/*------------*/

	for (int i = 0; i < keyb.ksize; i++){
		delete [] data.b_matrix[i];
	}
	for (int i = 0; i < data.size; i++){
		delete [] data.freq_matrix[i];
	}
	delete [] data.b_matrix;
	delete [] data.freq_matrix;
	delete [] data.char_list;
	delete [] keyb.grid;
	delete [] keyb.assignment;

	return 0;
}
