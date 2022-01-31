//addBestSol (&data, &keyb, &strow, rowPool, valCharList, sizeRows, charPoolPos);

	//addRowPool (&data, &keyb, &strow, rowPool, valCharList, sizeRows, charPoolPos);

	// for (int i = 0; i < keyb.krows; i++){
	// 	for (int j = 0; j < keyb.kcols; j++){
	// 		int elem1 = i * keyb.kcols + j;
	// 		if (bestGlobalSol[elem1] > -1){
	// 			numRows++;
	// 			rowAsgn.push_back(i);
	// 			break;
	// 		}
	// 	}
	// }
	// cout << "\nNumber of Rows: " << numRows << endl;
	
	// for (int i = 0; i < rowAsgn.size(); i++){
	// 	for (int j = 0; j < keyb.kcols; j++){
	// 		int elem1 = rowAsgn[i] * keyb.kcols + j;
	// 		if (bestGlobalSol[elem1] == data.size - 1){
	// 			centerRow = i;
	// 			break;
	// 		}
	// 	}
	// }

	//cout << "\nCenter Row: " << centerRow << endl;

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

//makeCoexMatrix (&data, valCharList, rowPool, coexMatrix);				//Usar vector para coexMatrix

	//rowCostMatrix (&data, &keyb, rowPool, costMatrix, coexMatrix, numRows);

	//cout << "\nRow Pool final:" << rowPool.size() << endl;

	// for (int i = 0; i < rowPool.size(); i++){
	// 	cout << i << ": ";
	// 	for (int j = 0; j < rowPool[i].row.size(); j++){
	// 		cout << " " << data.char_list[rowPool[i].row[j]] << " ";
	// 	}
	// 	//cout << " => Cost: " << rowPool[i].rowCost;
	// 	//cout << " => HashV: " << rowPool[i].rowHash;
	// 	//cout << " => HashP: " << rowPool[i].posiHash;
	// // 	cout << " - Row Size: " << rowPool[i].asgnchars;
	// // 	cout << " => Pos: " << rowPool[i].pos;
	// 	// cout << "=> Position Vector: ";
	// 	// 	for (int k = 0; k < rowPool[i].posiVec.size(); k++){
	// 	// 		cout << rowPool[i].posiVec[k] << " ";
	// 	// 	}

	// 	cout << endl;
	// }

	//makeYMatrix(&data, &keyb, rowPool, yMat, sizeRows, numRows);

	// cout << "\nSize of Row Vector: " << endl;
	// for (int k = 0; k < sizeRows.size(); k++){
	// 	if (sizeRows[k].size() < 1){
	// 		continue;
	// 	}
	// 	else{
	// 		cout << k << ": ";
	// 	}
	// 	for (int l = 0; l < sizeRows[k].size(); l++){
	// 		cout << sizeRows[k][l] << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;

	// cout << "\nPatterns by Char: " << endl;
	// for (int k = 0; k < charPoolPos.size(); k++){
	// 	cout << data.char_list[k] << ": ";
		
	// 	for (int l = 0; l < charPoolPos[k].size(); l++){
	// 		cout << charPoolPos[k][l] << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;

	/*------SET PARTITIONING------*/

	// //Creating environment and model 
	// char var[100];
	// IloEnv env;
	// IloModel model(env, "SKQAP");

	// //Creating variables
	
	// IloArray <IloArray<IloBoolVarArray> > x(env, rowPool.size()); 	

	// for (int i = 0; i < rowPool.size(); i++) {
	// 	IloArray <IloBoolVarArray> array2D(env, rowPool.size());
	// 	x[i] = array2D;
	// 	for (int j = i + 1; j < rowPool.size(); j++) {
	// 		IloBoolVarArray array(env, rowPool.size());
	// 		x[i][j] = array;
	// 	}
	// }

	// for (int i = 0; i < rowPool.size(); i++){
	// 	for (int j = i + 1; j < rowPool.size(); j++){
	// 		for (int k = 1; k < numRows; k++){
	// 			if (coexMatrix[i][j] > 0){
	// 				sprintf(var, "x_%d_%d_%d", i, j, k);
	// 				x[i][j][k].setName(var);
	// 				model.add(x[i][j][k]);
	// 			}
 // 			}
	// 	}
	// }

	// IloArray <IloBoolVarArray> y(env, rowPool.size());

	// for (int i = 0; i < rowPool.size(); i++){
	// 	y[i] = IloBoolVarArray (env, rowPool.size());
	// }
	 
	// for (int i = 0; i < rowPool.size(); i++){
	// 	for (int l = 0; l < numRows; l++){
	// 		if (yMat[i][l] > 0){
	// 			sprintf(var, "y_%d_%d", i, l);
	// 			y[i][l].setName(var);
	// 			model.add(y[i][l]);
	// 		}
	// 	}
	// }

	// //Creating objective function
	
	// IloExpr objFunction(env);

	// for (int i = 0; i < rowPool.size(); i++){
	// 	for (int j = i + 1; j < rowPool.size(); j++){
	// 		if (coexMatrix[i][j] > 0){
	// 			for (int k = 1; k < numRows; k++){
	// 			//if (coexMatrix[i][j] > 0){
	// 				objFunction += (double)costMatrix[i][j][k]*x[i][j][k];
	// 			}
	// 		}
	// 	}
	// }
	// cout << endl;
	// for (int i = 0; i < rowPool.size(); i++){
	// 	for (int l = 0; l < numRows; l++){
	// 		if (yMat[i][l] > 0){
	// 			objFunction += (double)(rowPool[i].rowCost)*(y[i][l]);
	// 		}
	// 	}
	// }

	// //Creating constraints
	// //Constraint 1

	// for (int c = 0; c < charPoolPos.size(); c++){
	// 	IloExpr exp(env);
	// 	sprintf (var, "Constraint1_%d", c);
	// 	for (int i = 0; i < charPoolPos[c].size(); i++){
	// 		int selRow = charPoolPos[c][i];
	// 		for (int l = 0; l < numRows; l++){
	// 			if (yMat[selRow][l] > 0){
	// 				exp += y[selRow][l];
	// 			}
	// 		}
	// 	}
	// 	IloRange cons = (exp == 1);
	// 	cons.setName(var);
	// 	model.add(cons);
	// }

	// //Constraint 2

	// for (int l = 0; l < numRows; l++){
	// 	IloExpr exp(env);
	// 	sprintf (var, "Constraint2_%d", l);
	// 	for (int i = 0; i < rowPool.size(); i++){
	// 		if (yMat[i][l] > 0){
	// 			exp += y[i][l];
	// 		}
	// 	}
	// 	IloRange cons = (exp == 1);
	// 	cons.setName(var);
	// 	model.add(cons);
	// }

	// //Constraint 3
	
	// for (int i = 0; i < rowPool.size(); i++){
	// 	for (int j = i + 1; j < rowPool.size(); j++){
	// 		for (int k = 1; k < numRows; k++){
	// 			for (int l = 0; l < numRows; l++){
	// 				if (coexMatrix[i][j] > 0){
	// 					if (yMat[i][l] > 0 && l + k < numRows && yMat[j][l + k] > 0){

	// 						IloExpr exp(env);
	// 						sprintf (var, "Constraint3_%d_%d_%d_%d", i, j, k, l);

	// 						exp = x[i][j][k] - y[i][l] - y[j][l + k];

	// 						IloRange cons = (exp >= - 1);
	// 						cons.setName(var);
	// 						model.add(cons);


	// 					}
	// 					if(yMat[j][l] > 0 && l + k < numRows && yMat[i][l + k] > 0){
	// 						IloExpr exp(env);
	// 						sprintf (var, "Constraint3_%d_%d_%d_%d", j, i, k, l);
							
	// 						exp = x[i][j][k] - y[j][l] - y[i][l + k];

	// 						IloRange cons = (exp >= - 1);
	// 						cons.setName(var);
	// 						model.add(cons);
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// }

	// //Constraint 4
	
	// for (int i = 0; i < rowPool.size(); i++){
	// 	for (int j = i + 1; j < rowPool.size(); j++){
	// 		for (int k = 1; k < numRows; k++){
	// 			for (int l = 0; l < numRows; l++){
	// 				if (coexMatrix[i][j] > 0){
	// 					if (yMat[i][l] > 0 && l - k > 0 && yMat[j][l - k] > 0){
	// 						IloExpr exp(env);
	// 						sprintf (var, "Constraint4_%d_%d_%d_%d", i, j, k, l);

	// 						exp = x[i][j][k] - y[i][l] - y[j][l - k];

	// 						IloRange cons = (exp >= - 1);
	// 						cons.setName(var);
	// 						//model.add(cons);


	// 					}
	// 					if(yMat[j][l] > 0 && l - k > 0 && yMat[i][l - k] > 0){
	// 						IloExpr exp(env);

	// 						sprintf (var, "Constraint4_%d_%d_%d_%d", j, i, k, l);

	// 						exp = x[i][j][k] - y[j][l] - y[i][l - k];

	// 						IloRange cons = (exp >= - 1);
	// 						cons.setName(var);
	// 						//model.add(cons);
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// }

	// //Constraint 5

	// for(int i = 0; i < rowPool.size(); i++){
	// 	for(int j = i + 1; j < rowPool.size(); j++){
	// 		if (coexMatrix[i][j] > 0){
	// 			IloExpr exp(env);
	// 			for(int k = 1; k < numRows; k++){

	// 				exp += 2*x[i][j][k];
	// 			}
	// 			for(int l = 0; l < numRows; l++){
	// 				if(yMat[i][l] > 0){
	// 					exp += - (y[i][l]);
	// 				}
	// 				if (yMat[j][l] > 0){
	// 					exp += - (y[j][l]);
	// 				}
					
	// 			}
	// 			sprintf (var, "Constraint5_%d_%d", i, j);
	// 			IloRange cons = (exp <= 0);
	// 			cons.setName(var);
	// 			model.add(cons);
	// 		}
	// 	}
	// }



	// IloCplex cplex(model);
	// cplex.exportModel("SKQAP.lp");

	// IloNumVarArray startVar(env);
	// IloNumArray startVal(env);
	// int l = 0;

	// for (int j = rowPool.size() - numRows; j < rowPool.size(); j++){
	// 	startVar.add(y[j][l]);
	// 	startVal.add(1);
	// 	cout << "\nL: " << l << endl;
	// 	l++;

	// }
	// cplex.addMIPStart(startVar, startVal);
	// startVal.end();
	// startVar.end();

	// model.add(IloMinimize(env, objFunction));

	// cplex.setParam(IloCplex::EpGap, 1e-15);
	// cplex.setParam(IloCplex::EpAGap, 1e-15);
	// cplex.setParam(IloCplex::EpInt, 1e-15);
	// cplex.solve();
	// cout << "\nObj Val: " << setprecision(15) << cplex.getObjValue() << endl;

	// env.end();
	/*------------*/