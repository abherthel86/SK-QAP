//Main original para otimização
#include "cpuTime.h"
#include "functions.h"
#include "localsearch.h"
#define KEYS 140

using namespace std;

int main (int argc, char *argv[]) {

	double t1 = 0;
	double t2 = 0;
	double deltaT = 0;

	double globalTime;

	double runTime = 0;
	double seed = 0;
	int cols = 14;
	Gendata data;
	Keyboard keyb;
	Stats stat;
	Strows strow;
	vector < vector < vector < vector <int> > > > newBMatrix;
	stShRow shRow;
	long long bks;

	readData (argc, argv, &data, &keyb, &bks);
	//makeNewBMat (&data, &keyb, newBMatrix);

	seed = time(0);
	srand(seed);
	//cout << "\nSeed: " << setprecision(15) << seed << endl;

	vector <int> bestSol;
	vector <int> bestGlobalSol;
	
	//vector <stShRow> vecShSol;
	//vector <int> shSol;

	//vector <Strows> rowPool;
	//vector <int> valCharList;
	//vector <int> auxVec;
	//vector <int> rowAsgn;
	//vector <int> rowPattern;

	//vector< vector<int> > sizeRows;
	//vector< vector<int> > charPoolPos;
	//vector< vector<int> > yMat;
	
	//vector <int> occRows;
	//vector <double> shifts;
 	//double maxShift = 20;
	//long long twoRowsCost;

	int pertChoice = 0;
	int iterILS;
	//int maxIterILS = 3 * data.size;
	int maxIterILS = 10 * data.size;
	int mscount = 0;
	int msMax = 15;
	//long long msMax = numeric_limits<long long>::max();
	int numRows = 0;
	int centerRow;

	vector < vector < vector <long long> > > costMatrix;
	vector < vector <int> > coexMatrix;

	long long bestSolCost;
	long long bestGlobalCost = numeric_limits<long long>::max();
	//ifstream infile ("BestSolList.txt");

	//hashValues (&data, valCharList);

/*	for (int i = 0; i <= maxShift; i++){
		shifts.push_back(double(i*(1/maxShift)));
	}*/
	//cout << "\n" << shifts[10] << endl;

	for (int i = 0; i < keyb.ksize; i++){
		bestGlobalSol.push_back(0);
	}

	// for (int i = 0; i < data.size; i++){
	// 	charPoolPos.push_back(auxVec);
	// }

	initTime (&stat);
	//------
	//optAssign (&data, &keyb);
	//newItInst(&data, &keyb);
	//newPtInst(&data, &keyb);

/*	qwertyAssign (&data, &keyb);

	long long qCost = qwertyCalc (&data, &keyb);

	cout << "\nCost of Qwerty: " << qCost << endl;*/



//******************ini
						// ****cout << "BKS: " << bks << endl;
						// getchar();

						while (mscount < msMax){
							
							t1 = get_wall_time();
					    	//gettimeofday(&a, 0);
							
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

								//if (keyb.cost <= bks){

								// 	t2 = get_wall_time();
								// 	deltaT = t2 - t1;

								// 	cout << "\n----------";
								// 	cout << "\nBest Global Solution Cost: " << keyb.cost;
								// 	cout << "\nGlobal Time: " << deltaT;
								// 	cout << "\n----------" << endl;
								// 	break;
								// }

								if (keyb.cost < bestSolCost) {
									for (int i = 0; i < keyb.ksize; i++){
										bestSol[i] = keyb.grid[i];
									}

									bestSolCost = keyb.cost;
							
									iterILS = 0;

									pertCount(pertChoice, &stat);
								}

							 	perturbation(&data, &keyb, &pertChoice);
							 	iterILS++;
							}
							
						
							// if (keyb.cost <= bks){
							// 	break;
							// }

							for (int i = 0; i < keyb.ksize; i++){
								keyb.grid[i] = bestSol[i];
							}

							if (bestSolCost < bestGlobalCost){
								bestGlobalCost = bestSolCost;
								bestGlobalSol = bestSol;
							}
//*******end

		//___________________________begin comment___________________________
		cout <<"\n\nBest Solution Cost: " << bestSolCost << endl;
						// cout << "\n-----x-----" << "\n1Best Solution: " << endl;
						// printSol(&data, &keyb, bestSol);

		//cout << "\n\nRVND Stats: Swap Count: " << stat.swapSt << " Time: " << stat.swapTime << "s - Swap Pair Count: " << stat.spPairSt << " Time: " << stat.spPairTime << "s - Move Contour Count: " << stat.mvContSt << " Time: " << stat.mvContTime << "s" << endl;

		//cout << "Perturbation 1 Count: " << stat.pert1St << " Perturbation 2 Count: " << stat.pert2St << endl;
		
		t2 = get_wall_time();
		deltaT = t2 - t1;

		runTime += deltaT;

		//cout << "\nElapsed Time: " << deltaT << " seconds" << endl << endl;

		//cout << "CPU Time: " << runTime << " seconds" << endl << endl;
		//_______________________________end comment________________________________

//****************ini
					
						 	mscount++;
 							//printSol(&data, &keyb, bestGlobalSol);

						}

						for (int i = 0; i < keyb.ksize; i++){
							keyb.grid[i] = bestGlobalSol[i];
						}

						keyb.cost = bestGlobalCost;
						
						cout << "\n-----x-----" << "\nBest Solution: " << endl;
						printSol(&data, &keyb, bestGlobalSol);

						cout << "\n-----x-----";
						cout << "\nBest Global Solution Cost: " << bestGlobalCost;
						cout << "\nGlobal Time: " << runTime;
						cout << "\n-----x-----" << endl;
//*****************end
	
	//___________________________begin comment___________________________
	//shiftSol (&data, &keyb, newBMatrix, vecShSol, &shRow, occRows, shifts);
	// cout << "\nshifts size: " << shifts.size();
	// cout << "\nvecShSol size: " << vecShSol.size();
	//cout << "\nShifted Solution Cost: " << keyb.cost << endl;

	//cout << "\n-----x-----" << "\nBest Global Solution: " << endl;
	
	//printSol(&data, &keyb, bestGlobalSol);

	//cout << endl;
	//printShiftedSol(&data, &keyb, bestGlobalSol);
	//gettimeofday(&b, 0);
	//globalTime = b - a;

/*	cout << "\n-----x-----";
	cout << "\nBest Global Solution Cost: " << bestGlobalCost;
	cout << "\nGlobal Time: " << runTime;
	cout << "\n-----x-----" << endl;*/

	// /*------------*/

	// //MIP - Deslocamento SK-QAP

	// //Creating environment and model 
	// char var[100];
	// IloEnv env;
	// IloModel model(env, "ShiftSKQAP");

	// //Creating variables
	// IloArray <IloArray <IloArray <IloBoolVarArray> > > x(env, shifts.size());	

	// for (int i = 0; i < occRows.size(); i++){

	// 	IloArray <IloArray <IloBoolVarArray> > array3D(env, shifts.size());
	// 	x[i] = array3D;
	// 	//getchar();
	// 	for (int j = i + 1; j < occRows.size(); j++){
	// 		IloArray <IloBoolVarArray> array2D(env, shifts.size());

	// 		x[i][j] = array2D;
	// 		for (int k = 0; k < shifts.size(); k++){
	// 			IloBoolVarArray array(env, shifts.size());
	// 			x[i][j][k] = array;
	// 		}
	// 	}	
	// }

	// for (int i = 0; i < occRows.size(); i++){
	// 	for (int j = i + 1; j < occRows.size(); j++){
	// 		for (int k = 0; k < shifts.size(); k++){
	// 			for (int l = 0; l < shifts.size(); l++){
	// 				sprintf(var, "x_%d_%d_%d_%d", i, j, k, l);
	// 				x[i][j][k][l].setName(var);
	// 				model.add(x[i][j][k][l]);
	// 			}
 // 			}
	// 	}
	// }

	// IloArray <IloBoolVarArray> y(env, shifts.size());

	// for (int i = 0; i < occRows.size(); i++){
	// 	y[i] = IloBoolVarArray (env, shifts.size());
	// }
	 
	// for (int i = 0; i < occRows.size(); i++){
	// 	for (int k = 0; k < shifts.size(); k++){
	// 		sprintf(var, "y_%d_%d", i, k);
	// 		y[i][k].setName(var);
	// 		model.add(y[i][k]);
	// 	}
	// }

	// //Creating objective function
	
	// IloExpr objFunction(env);

	// for (int i = 0; i < occRows.size(); i++){
	// 	for (int j = i + 1; j < occRows.size(); j++){
	// 		twoRowsCost = 0;
	// 		for (int k = 0; k < shifts.size(); k++){
	// 			for (int l = 0; l < shifts.size(); l++){
	// 				for (int m = 0; m < vecShSol[i].shiftRow.size(); m++){
	// 					for (int n = 0; n < vecShSol[j].shiftRow.size(); n++){
	// 						twoRowsCost += (data.freq_matrix[vecShSol[i].shiftRow[m]][vecShSol[j].shiftRow[n]]*newBMatrix[vecShSol[i].posRow[m]][vecShSol[j].posRow[n]][k][l]);
	// 					}
	// 				}
	// 				objFunction += (double)twoRowsCost*x[i][j][k][l];
	// 			}
	// 		}
	// 	}
	// }

	// for (int i = 0; i < occRows.size(); i++){
	// 	objFunction += (double)((vecShSol[i].rowCost)/2);
	// }

	// model.add(IloMinimize(env, objFunction));

	// //Creating constraints
	// //Constraint 1

	// for (int i = 0; i < occRows.size(); i++){
	// 	IloExpr exp(env);
	// 	sprintf (var, "Constraint1_%d", i);
	// 	for (int k = 0; k < shifts.size(); k++){
	// 		exp += y[i][k];
	// 	}
	// 	IloRange cons = (exp == 1);
	// 	cons.setName(var);
	// 	model.add(cons);
	// }

	// //Constraint 2
	
	// for (int i = 0; i < occRows.size(); i++){
	// 	for (int j = i + 1; j < occRows.size(); j++){
	// 		for (int k = 0; k < shifts.size(); k++){
	// 			for (int l = 0; l < shifts.size(); l++){
	// 				IloExpr exp(env);
	// 				sprintf (var, "Constraint2_%d_%d_%d_%d", i, j, k, l);

	// 				exp = x[i][j][k][l] - y[i][k] - y[j][l];

	// 				IloRange cons = (exp >= - 1);
	// 				cons.setName(var);
	// 				model.add(cons);
	// 			}
	// 		}
	// 	}
	// }


	// IloCplex ShiftSKQAP(model);
	// ShiftSKQAP.exportModel("ShiftSKQAP.lp");

	// ShiftSKQAP.solve();
	// cout << "\nObj Val: " << setprecision(15) << ShiftSKQAP.getObjValue() << endl;

	// env.end();
	// /*------------*/
	//_______________________________end comment________________________________

	//infile.close();


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
