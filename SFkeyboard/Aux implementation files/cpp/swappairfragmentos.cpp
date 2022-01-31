void swapPair (Gendata *data, Keyboard *keyb, Stats *stat){ //nova versão (com equação de Taillard 1995)
	
	double begin;
	double end;

	double elapTm;
	
	begin = cpuTime();

	vector <int> auxKeyb;
	vector <long long> rmvCost;
	vector <long long> rmvCost2;

	SPairs spairs;

	vector <SPairs> vecpairs;

	long long iniCost;
	//long long testCost;

	long long fdeltaFi;
	long long deltaFi;
	long long bestDeltaFi = 0;

	long long ins1;
	long long ins2;
	long long insp1;
	long long insp2;

	long long rmv1;
	long long rmv2;
	long long rmvp1;
	long long rmvp2;

	bool impv = 0;
	bool imph = 0;

	int temp;
	int pos1, pos2;

	// double begin;
	// double end;

	// double elapTm;
	
	// begin = cpuTime();

	// vector <int> auxKeyb;
	// vector <long long> rmvCost;

	// list<int>::iterator it;

	// long long iniCost;
	// long long deltaFi;
	// long long bestDeltaFi = 0;
	// long long ins1;
	// long long ins2;
	
	// SPairs spairs;
	// vector <SPairs> vecpairs;
	
	// long long rmv1;
	// long long rmv2;

	// bool imp = 0;
	// bool impv = 0;
	// //bool imph = 0;

	// int pos1 = 0;
	// int pos2 = 0;
	// int char1;
	// int char2;
	// int selem1 = 0;
	// int selem2 = 0;
	// int temp;

	for (int i = 0; i < data->size; i++){
		rmvCost.push_back(0);
	}

	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb.push_back(0);
	}

	for (int i = 0; i < keyb->ksize - 1; i++){
		if (keyb->grid[i] > -1){
			spairs.pos = i;
			spairs.vert = 0;
			spairs.horiz = 0;

			if (floor((i + keyb->kcols) / keyb->kcols) < keyb->krows){
				if (keyb->grid[i + keyb->kcols] > -1){
					spairs.vpair = i + keyb->kcols;
					spairs.vert = 1;
				}
			}
			if ((i + 1) % keyb->kcols > 0){
				if (keyb->grid[i + 1] > -1){
					spairs.hpair = i + 1;
					spairs.horiz = 1;
				}
			}
			vecpairs.push_back(spairs);
		}
	}

	cout << "\nVector of chars: " << endl;
	for (int i = 0; i < vecpairs.size(); i++){
		cout << "\nmainchar: " << data->char_list[keyb->grid[vecpairs[i].pos]] << " pos: " << vecpairs[i].pos <<
		"  vpair: " << data->char_list[keyb->grid[vecpairs[i].vpair]] << " pos: " << vecpairs[i].vpair <<
		"  hpair: " << data->char_list[keyb->grid[vecpairs[i].hpair]] << " pos: " << vecpairs[i].hpair;
	}
	cout << endl;

	iniCost = keyb->cost;
	
	removecost (data, rmvCost, keyb);

	for (int i = 0; i < vecpairs.size(); i++){
		
		deltaFi = 0;
		rmv1 = rmvCost[keyb->grid[vecpairs[i].pos]];

		for (int j = i + 1; j < vecpairs.size(); j++){
			if (vecpairs[i].vert > 0 && vecpairs[j].vert > 0){
				if (vecpairs[j].pos != vecpairs[i].vpair){

					rmv2 = rmvCost[keyb->grid[vecpairs[j].pos]];

					temp = keyb->assignment[keyb->grid[vecpairs[i].pos]];
					keyb->assignment[keyb->grid[vecpairs[i].pos]] = keyb->assignment[keyb->grid[vecpairs[j].pos]];
					keyb->assignment[keyb->grid[vecpairs[j].pos]] = temp;

					ins1 = costcalc (data, keyb->grid[vecpairs[i].pos], keyb);
					ins2 = costcalc (data, keyb->grid[vecpairs[j].pos], keyb);
					
					deltaFi = - rmv1 - rmv2 + ins1 + ins2;

					fdeltaFi = deltaFi;

					removecost (data, rmvCost2, keyb);
					
					rmvp1 = rmvCost2[keyb->grid[vecpairs[i].vpair]];
					rmvp2 = rmvCost2[keyb->grid[vecpairs[j].vpair]];

					temp = keyb->assignment[keyb->grid[vecpairs[i].vpair]];
					keyb->assignment[keyb->grid[vecpairs[i].vpair]] = keyb->assignment[keyb->grid[vecpairs[j].vpair]];
					keyb->assignment[keyb->grid[vecpairs[j].vpair]] = temp;

					insp1 = costcalc (data, keyb->grid[vecpairs[i].vpair], keyb);
					insp2 = costcalc (data, keyb->grid[vecpairs[j].vpair], keyb);

					deltaFi = fdeltaFi - rmvp1 - rmvp2 + insp1 + insp2;

					if (deltaFi < 0){
						if (deltaFi < bestDeltaFi){
							bestDeltaFi = deltaFi;
							pos1 = i;
							pos2 = j;
							impv = 1;
							imph = 0;
						}
					}

					temp = keyb->assignment[keyb->grid[vecpairs[j].vpair]];
					keyb->assignment[keyb->grid[vecpairs[j].vpair]] = keyb->assignment[keyb->grid[vecpairs[i].vpair]];
					keyb->assignment[keyb->grid[vecpairs[i].vpair]] = temp;
				}
				// else{
				// 	rmv2 = rmvCost[keyb->grid[vecpairs[j].pos]];

				// 	temp = keyb->assignment[keyb->grid[vecpairs[i].pos]];
				// 	keyb->assignment[keyb->grid[vecpairs[i].pos]] = keyb->assignment[keyb->grid[vecpairs[j].pos]];
				// 	keyb->assignment[keyb->grid[vecpairs[j].pos]] = temp;

				// 	ins1 = costcalc (data, keyb->grid[vecpairs[i].pos], keyb);
				// 	ins2 = costcalc (data, keyb->grid[vecpairs[j].pos], keyb);

				// 	deltaFi = - rmv1 - rmv2 + ins1 + ins2;
				// 	fdeltaFi = deltaFi;
					
				// 	removecost (data, rmvCost2, keyb);
				// }
			}

			// if (vecpairs[i].vert < 1 || vecpairs[j].vert < 1){
			// 	rmv2 = rmvCost[keyb->grid[vecpairs[j].pos]];

			// 	temp = keyb->assignment[keyb->grid[vecpairs[i].pos]];
			// 	keyb->assignment[keyb->grid[vecpairs[i].pos]] = keyb->assignment[keyb->grid[vecpairs[j].pos]];
			// 	keyb->assignment[keyb->grid[vecpairs[j].pos]] = temp;

			// 	ins1 = costcalc (data, keyb->grid[vecpairs[i].pos], keyb);
			// 	ins2 = costcalc (data, keyb->grid[vecpairs[j].pos], keyb);

			// 	deltaFi = - rmv1 - rmv2 + ins1 + ins2;
			// 	fdeltaFi = deltaFi;
				
			// 	removecost (data, rmvCost2, keyb);
			// }
			
			// if (vecpairs[i].horiz > 0 && vecpairs[j].horiz > 0){
			// 	if (vecpairs[j].pos != vecpairs[i].hpair){

			// 		rmvp1 = rmvCost2[keyb->grid[vecpairs[i].hpair]];
			// 		rmvp2 = rmvCost2[keyb->grid[vecpairs[j].hpair]];

			// 		temp = keyb->assignment[keyb->grid[vecpairs[i].hpair]];
			// 		keyb->assignment[keyb->grid[vecpairs[i].hpair]] = keyb->assignment[keyb->grid[vecpairs[j].hpair]];
			// 		keyb->assignment[keyb->grid[vecpairs[j].hpair]] = temp;

			// 		insp1 = costcalc (data, keyb->grid[vecpairs[i].hpair], keyb);
			// 		insp2 = costcalc (data, keyb->grid[vecpairs[j].hpair], keyb);

			// 		deltaFi = fdeltaFi - rmvp1 - rmvp2 + insp1 + insp2;

			// 		if (deltaFi < 0){
			// 			if (deltaFi < bestDeltaFi){
			// 				bestDeltaFi = deltaFi;
			// 				pos1 = i;
			// 				pos2 = j;
			// 				impv = 0;
			// 				imph = 1;
			// 			}
			// 		}

			// 		temp = keyb->assignment[keyb->grid[vecpairs[j].pos]];
			// 		keyb->assignment[keyb->grid[vecpairs[j].pos]] = keyb->assignment[keyb->grid[vecpairs[i].pos]];
			// 		keyb->assignment[keyb->grid[vecpairs[i].pos]] = temp;

			// 		temp = keyb->assignment[keyb->grid[vecpairs[j].hpair]];
			// 		keyb->assignment[keyb->grid[vecpairs[j].hpair]] = keyb->assignment[keyb->grid[vecpairs[i].hpair]];
			// 		keyb->assignment[keyb->grid[vecpairs[i].hpair]] = temp;
			// 	}
			// 	else{
			// 		temp = keyb->assignment[keyb->grid[vecpairs[j].pos]];
			// 		keyb->assignment[keyb->grid[vecpairs[j].pos]] = keyb->assignment[keyb->grid[vecpairs[i].pos]];
			// 		keyb->assignment[keyb->grid[vecpairs[i].pos]] = temp;
			// 	}
			// }

			// if (vecpairs[i].horiz < 1 || vecpairs[j].horiz < 1){
			// 	temp = keyb->assignment[keyb->grid[vecpairs[j].pos]];
			// 	keyb->assignment[keyb->grid[vecpairs[j].pos]] = keyb->assignment[keyb->grid[vecpairs[i].pos]];
			// 	keyb->assignment[keyb->grid[vecpairs[i].pos]] = temp;
			// }
		}//for j
	}//for i

	if (impv > 0){
		
		temp = keyb->assignment[keyb->grid[vecpairs[pos1].pos]];
		keyb->assignment[keyb->grid[vecpairs[pos1].pos]] = keyb->assignment[keyb->grid[vecpairs[pos2].pos]];
		keyb->assignment[keyb->grid[vecpairs[pos2].pos]] = temp;

		// temp = keyb->assignment[keyb->grid[vecpairs[pos1].vpair]];
		// keyb->assignment[keyb->grid[vecpairs[pos1].vpair]] = keyb->assignment[keyb->grid[vecpairs[pos2].vpair]];
		// keyb->assignment[keyb->grid[vecpairs[pos2].vpair]] = temp;

		temp = keyb->grid[vecpairs[pos1].pos];
		keyb->grid[vecpairs[pos1].pos] = keyb->grid[vecpairs[pos2].pos];
		keyb->grid[vecpairs[pos2].pos] = temp;
		
		// temp = keyb->grid[vecpairs[pos1].vpair];
		// keyb->grid[vecpairs[pos1].vpair] = keyb->grid[vecpairs[pos2].vpair];
		// keyb->grid[vecpairs[pos2].vpair] = temp;
		
		keyb->cost = iniCost + bestDeltaFi;
	}

	// else if (imph > 0){
		
	// 	temp = keyb->assignment[keyb->grid[vecpairs[pos1].pos]];
	// 	keyb->assignment[keyb->grid[vecpairs[pos1].pos]] = keyb->assignment[keyb->grid[vecpairs[pos2].pos]];
	// 	keyb->assignment[keyb->grid[vecpairs[pos2].pos]] = temp;

	// 	temp = keyb->assignment[keyb->grid[vecpairs[pos1].hpair]];
	// 	keyb->assignment[keyb->grid[vecpairs[pos1].hpair]] = keyb->assignment[keyb->grid[vecpairs[pos2].hpair]];
	// 	keyb->assignment[keyb->grid[vecpairs[pos2].hpair]] = temp;

	// 	temp = keyb->grid[vecpairs[pos1].pos];
	// 	keyb->grid[vecpairs[pos1].pos] = keyb->grid[vecpairs[pos2].pos];
	// 	keyb->grid[vecpairs[pos2].pos] = temp;
		
	// 	temp = keyb->grid[vecpairs[pos1].hpair];
	// 	keyb->grid[vecpairs[pos1].hpair] = keyb->grid[vecpairs[pos2].hpair];
	// 	keyb->grid[vecpairs[pos2].hpair] = temp;
		
	// 	keyb->cost = iniCost + bestDeltaFi;
	// }
	
	for (int i = 0; i < auxKeyb.size(); i++){
		auxKeyb[i] = keyb->grid[i];
	}

	vecpairs.clear();

	cout << "\nNew Cost(2pswap): " << keyb->cost << endl;

	long long testCost;
	testCost = costcalc(data, -2, keyb);
	cout << "Custo calculado final (2pswap): " << testCost << endl;
	
	// printSol(data, keyb, auxKeyb);
	// cout << endl;

	end = cpuTime();
	elapTm = end - begin;
	
	stat->spPairTime += elapTm;
 }
	// for (int i = 0; i < vecpairs.size(); i++){
	// 	deltaFi = 0;
	// 	rmv1 = rmvCost[i];	

	// 	for (int j = i + 1; j < vecpairs.size(); j++){
	// 		if (vecpairs[i].vert > 0 && vecpairs[j].vert > 0){
	// 			if (vecpairs[j].keyp != vecpairs[i].vpairp){
	// 				rmv2 = rmvCost[vecpairs[j].keyc];

	// 				temp = keyb->assignment[vecpairs[i].keyc];
	// 				keyb->assignment[vecpairs[i].keyc] = keyb->assignment[vecpairs[j].keyc];
	// 				keyb->assignment[vecpairs[j].keyc] = temp;
				
	// 				ins1 = costcalc (data, vecpairs[i].keyc, keyb);
	// 				ins2 = costcalc (data, vecpairs[j].keyc, keyb); 

	// 				deltaFi = - rmv1 - rmv2 + ins1 + ins2;

	// 				if (deltaFi < 0){
	// 					if (deltaFi < bestDeltaFi){
	// 						bestDeltaFi = deltaFi;
	// 						cout << "\nbestDeltaFi1: " << bestDeltaFi << endl;
	// 						selem1 = i;
	// 						selem2 = j;
	// 						pos1 = keyb->assignment[vecpairs[i].keyc];
	// 						pos2 = keyb->assignment[vecpairs[j].keyc];
	// 						imp = 1;
	// 						//imp1 = 0;
	// 					}
	// 				}				
	// 				keyb->assignment[vecpairs[j].keyc] = keyb->assignment[vecpairs[i].keyc];
	// 				keyb->assignment[vecpairs[i].keyc] = temp;
	// 			}
	// 		}
	// 	}
	// }

	

	// for (int i = 0; i < data->size; i++){

	// 	deltaFi = 0;
	// 	rmv1 = rmvCost[i];
		
	// 	for (int j = i + 1; j < data->size; j++){
	// 		if (j != i){
	// 			rmv2 = rmvCost[j];

	// 			temp = keyb->assignment[i];
	// 			keyb->assignment[i] = keyb->assignment[j];
	// 			keyb->assignment[j] = temp;
			
	// 			ins1 = costcalc (data, i, keyb);
	// 			ins2 = costcalc (data, j, keyb); 

	// 			deltaFi = - rmv1 - rmv2 + ins1 + ins2;

	// 			if (deltaFi < 0){
	// 				if (deltaFi < bestDeltaFi){
	// 					bestDeltaFi = deltaFi;
	// 					cout << "\nbestDeltaFi2: " << bestDeltaFi << endl;
	// 					char1 = i;
	// 					char2 = j;
	// 					pos1 = keyb->assignment[i];
	// 					pos2 = keyb->assignment[j];
	// 					imp = 1;
	// 					//imp1 = 0;
	// 				}
	// 			}				
	// 			keyb->assignment[j] = keyb->assignment[i];
	// 			keyb->assignment[i] = temp;
	// 		}
	// 	}
	// }//for i

// 	if (imp > 0){
// 		keyb->assignment[char1] = pos1;
// 		keyb->assignment[char2] = pos2;

// 		temp = auxKeyb[pos1];
// 		auxKeyb[pos1] = auxKeyb[pos2];
// 		auxKeyb[pos2] = temp;

// 		keyb->cost = iniCost + bestDeltaFi;
// 	}

// 	for (int i = 0; i < keyb->ksize; i++){
// 		keyb->grid[i] = auxKeyb[i];
// 	}

// 	vecpairs.clear();

// 	cout << "\n\nNew Cost(2pswap): " << keyb->cost << endl;

// 	long long testCost;
// 	testCost = costcalc(data, -2, keyb);
// 	cout << "Custo calculado final (2pswap): " << testCost << endl;
	
// 	printSol(data, keyb, auxKeyb);
// 	cout << endl;
	
// 	auxKeyb.clear();

// 	end = cpuTime();
// 	elapTm = end - begin;
	
// 	stat->spPairTime += elapTm;

// }
	// double begin;
	// double end;

	// double elapTm;
	
	// begin = cpuTime();

	// vector <int> auxKeyb;
	// vector <long long> rmvCost;
	// vector <long long> rmvCost2;

	// SPairs spairs;

	// vector <SPairs> vecpairs;

	// long long iniCost;

	// long long fdeltaFi = 0;
	// long long sdeltaFi = 0;
	// long long deltaFi;
	// long long bestDeltaFi = -1;
	// long long delta2 = 0;
	// long long fSwapCost = 0;
	// long long sSwapCost = 0;
	// long long newCost = 0;

	// long long ins1;
	// long long ins2;

	// long long rmv1;
	// long long rmv2;

	// long long constVal;
	
	// bool impv = 0;
	// bool imph = 0;

	// int temp;
	// int char1, char2, char3, char4;
	// int key1, key2, key3, key4;
	// int pos1, pos2;

	// for (int i = 0; i < data->size; i++){
	// 	rmvCost.push_back(0);
	// }

	// for (int i = 0; i < keyb->ksize; i++){
	// 	auxKeyb.push_back(0);
	// }

	// 

	// iniCost = keyb->cost;

	// removecost (data, rmvCost, keyb);
	// cout << "Remove Costs: " << 
	// for (int i = 0; i < vecpairs.size(); i++){
		
	// 	fdeltaFi = 0;

	// 	char1 = keyb->grid[vecpairs[i].pos];
	// 	char3 = keyb->grid[vecpairs[i].vpair];

	// 	rmv1 = rmvCost[char1];

	// 	for (int j = i + 1; j < vecpairs.size(); j++){
	// 		if (vecpairs[i].vert > 0 && vecpairs[j].vert > 0){
	// 			if (vecpairs[j].pos != vecpairs[i].vpair){
					
	// 				char2 = keyb->grid[vecpairs[j].pos];
	// 				char4 = keyb->grid[vecpairs[j].vpair];
					
	// 				rmv2 = rmvCost[char2];

	// 				//troca
	// 				temp = keyb->assignment[char1];
	// 				keyb->assignment[char1] = keyb->assignment[char2];
	// 				keyb->assignment[char2] = temp;

	// 				ins1 = costcalc (data, char1, keyb);
	// 				ins2 = costcalc (data, char2, keyb);
					
	// 				fdeltaFi = - rmv1 - rmv2 + ins1 + ins2;

	// 				fSwapCost = iniCost + fdeltaFi;

	// 				//volta
	// 				temp = keyb->assignment[char2];
	// 				keyb->assignment[char2] = keyb->assignment[char1];
	// 				keyb->assignment[char1] = temp;
					
	// 				rmv1 = rmvCost[char3];
	// 				rmv2 = rmvCost[char4];

	// 				//troca par
	// 				// temp = keyb->assignment[char3];
	// 				// keyb->assignment[char3] = keyb->assignment[char4];
	// 				// keyb->assignment[char4] = temp;

	// 				// cout << "\nAssignment para const: " << endl;
					
	// 				// for (int a = 0; a < data->size; a++){
	// 				// 	cout << data->char_list[a] << ": " << keyb->assignment[a] << " || ";
	// 				// }

	// 				// cout << "Posicoes: 1: " << keyb->assignment[char1] << " 2: " << keyb->assignment[char2] <<
	// 				// " 3: " << keyb->assignment[char3] << " 4: " << keyb->assignment[char4] << endl;
					
	// 				// constVal = ((data->freq_matrix[char1][char3] - data->freq_matrix[char1][char4] + 
	// 				// 			data->freq_matrix[char2][char4] - data->freq_matrix[char2][char3])*
	// 				// 			(data->b_matrix[keyb->assignment[char2]][keyb->assignment[char3]] - 
	// 				// 			data->b_matrix[keyb->assignment[char2]][keyb->assignment[char4]] + 
	// 				// 			data->b_matrix[keyb->assignment[char1]][keyb->assignment[char4]] - 
	// 				// 			data->b_matrix[keyb->assignment[char1]][keyb->assignment[char3]]));

	// 				// ins1 = costcalc (data, char3, keyb);
	// 				// ins2 = costcalc (data, char4, keyb);

	// 				// sdeltaFi = - rmv1 - rmv2 + ins1 + ins2;

	// 				//volta par
	// 				// temp = keyb->assignment[char4];
	// 				// keyb->assignment[char4] = keyb->assignment[char3];
	// 				// keyb->assignment[char3] = temp;

	// 				//sSwapCost = fSwapCost + sdeltaFi + constVal;
	// 				//delta2 = sSwapCost - iniCost;

	// 				//cout << "\nPares selecionados: " << data->char_list[char1] << "//" << data->char_list[char3] << " & " << data->char_list[char2] << "//" << data->char_list[char4];

	// 				//cout<< "\ndelta: " << delta2 << endl;

	// 				if (fdeltaFi < 0){
	// 					if (fdeltaFi < bestDeltaFi){

	// 						//cout << "\nPares selecionados: " << data->char_list[keyb->grid[vecpairs[i].pos]] << "//" << data->char_list[keyb->grid[vecpairs[i].vpair]] << " & " << data->char_list[keyb->grid[vecpairs[j].pos]] << "//" << data->char_list[keyb->grid[vecpairs[j].vpair]];
	// 						//cout<< "\ndeltaFi: " << sdeltaFi;

	// 						//cout << "\nPosicoes: " << vecpairs[i].pos << "//" << vecpairs[i].vpair << " & " << vecpairs[j].pos << "//" << vecpairs[j].vpair;
	// 						//cout << "\nFrequencias: " << data->freq_matrix[char1][char3] << "//" << data->freq_matrix[char1][char4] << "//" << data->freq_matrix[char2][char4] << "//" << data->freq_matrix[char2][char3];
	// 						// cout << endl;

	// 						bestDeltaFi = fdeltaFi;
	// 						cout << "\nbestDeltaFi: " << bestDeltaFi << endl;
	// 						//newCost = sSwapCost;
	// 						newCost = fSwapCost;

	// 						pos1 = i;
	// 						pos2 = j;
	// 						impv = 1;
	// 						imph = 0;
	// 					}
	// 				}
	// 			}
	// 		}

	// 		// if (vecpairs[i].horiz > 0 && vecpairs[j].horiz > 0){
	// 		// 	if (vecpairs[j].pos != vecpairs[i].hpair){
	// 		// 		char1 = keyb->grid[vecpairs[i].pos];
	// 		// 		char2 = keyb->grid[vecpairs[j].pos];
	// 		// 		char3 = keyb->grid[vecpairs[i].hpair];
	// 		// 		char4 = keyb->grid[vecpairs[j].hpair];
					
	// 		// 		rmv2 = rmvCost[char2];

	// 		// 		//troca
	// 		// 		temp = keyb->assignment[char1];
	// 		// 		keyb->assignment[char1] = keyb->assignment[char2];
	// 		// 		keyb->assignment[char2] = temp;

	// 		// 		ins1 = costcalc (data, char1, keyb);
	// 		// 		ins2 = costcalc (data, char2, keyb);
					
	// 		// 		fdeltaFi = - rmv1 - rmv2 + ins1 + ins2;

	// 		// 		fSwapCost = iniCost + fdeltaFi;

	// 		// 		constVal = ((data->freq_matrix[keyb->grid[vecpairs[i].pos]][keyb->grid[vecpairs[i].hpair]] - data->freq_matrix[keyb->grid[vecpairs[i].pos]][keyb->grid[vecpairs[j].hpair]] + data->freq_matrix[keyb->grid[vecpairs[j].pos]][keyb->grid[vecpairs[j].hpair]] - data->freq_matrix[keyb->grid[vecpairs[j].pos]][keyb->grid[vecpairs[i].hpair]])*(data->b_matrix[keyb->assignment[keyb->grid[vecpairs[j].pos]]][keyb->assignment[keyb->grid[vecpairs[i].hpair]]] - data->b_matrix[keyb->assignment[keyb->grid[vecpairs[j].pos]]][keyb->assignment[keyb->grid[vecpairs[j].hpair]]] + data->b_matrix[keyb->assignment[keyb->grid[vecpairs[i].pos]]][keyb->assignment[keyb->grid[vecpairs[j].hpair]]] - data->b_matrix[keyb->assignment[keyb->grid[vecpairs[i].pos]]][keyb->assignment[keyb->grid[vecpairs[i].hpair]]]));

	// 		// 		//volta
	// 		// 		temp = keyb->assignment[char2];
	// 		// 		keyb->assignment[char2] = keyb->assignment[char1];
	// 		// 		keyb->assignment[char1] = temp;
					
	// 		// 		rmv1 = rmvCost[char3];
	// 		// 		rmv2 = rmvCost[char4];

	// 		// 		//troca par
	// 		// 		temp = keyb->assignment[char3];
	// 		// 		keyb->assignment[char3] = keyb->assignment[char4];
	// 		// 		keyb->assignment[char4] = temp;
					
	// 		// 		ins1 = costcalc (data, char3, keyb);
	// 		// 		ins2 = costcalc (data, char4, keyb);

	// 		// 		sdeltaFi = - rmv1 - rmv2 + ins1 + ins2;

	// 		// 		//volta par
	// 		// 		temp = keyb->assignment[char4];
	// 		// 		keyb->assignment[char4] = keyb->assignment[char3];
	// 		// 		keyb->assignment[char3] = temp;

	// 		// 		sSwapCost = fSwapCost + sdeltaFi + constVal;

	// 		// 		if (deltaFi < 0){
	// 		// 			if (deltaFi < bestDeltaFi){

	// 		// 				cout << "\nPares selecionados: " << data->char_list[char1] << "//" << data->char_list[char3] << " & " << data->char_list[char2] << "//" << data->char_list[char4];
	// 		// 				cout << endl;

	// 		// 				bestDeltaFi = deltaFi;
	// 		// 				newCost = sSwapCost;

	// 		// 				pos1 = i;
	// 		// 				pos2 = j;
	// 		// 				imph = 1;
	// 		// 				impv = 0;
	// 		// 			}
	// 		// 		}
	// 		// 	}
	// 		// }
	// 	}//for j
	// }//for i

	// if (impv > 0){
	// 	cout << "\nSwapped pairs: " << data->char_list[keyb->grid[vecpairs[pos1].pos]] << "//" << data->char_list[keyb->grid[vecpairs[pos1].vpair]] << " & " << data->char_list[keyb->grid[vecpairs[pos2].pos]] << "//" << data->char_list[keyb->grid[vecpairs[pos2].vpair]];
	// 	cout << "\nVert" << endl;
	// 	temp = keyb->assignment[keyb->grid[vecpairs[pos1].pos]];
	// 	keyb->assignment[keyb->grid[vecpairs[pos1].pos]] = keyb->assignment[keyb->grid[vecpairs[pos2].pos]];
	// 	keyb->assignment[keyb->grid[vecpairs[pos2].pos]] = temp;

	// 	// temp = keyb->assignment[keyb->grid[vecpairs[pos1].vpair]];
	// 	// keyb->assignment[keyb->grid[vecpairs[pos1].vpair]] = keyb->assignment[keyb->grid[vecpairs[pos2].vpair]];
	// 	// keyb->assignment[keyb->grid[vecpairs[pos2].vpair]] = temp;

	// 	temp = keyb->grid[vecpairs[pos1].pos];
	// 	keyb->grid[vecpairs[pos1].pos] = keyb->grid[vecpairs[pos2].pos];
	// 	keyb->grid[vecpairs[pos2].pos] = temp;
		
	// 	// temp = keyb->grid[vecpairs[pos1].vpair];
	// 	// keyb->grid[vecpairs[pos1].vpair] = keyb->grid[vecpairs[pos2].vpair];
	// 	// keyb->grid[vecpairs[pos2].vpair] = temp;
		
	// 	cout << "\nAssignment Final: " << endl;
	// 	for (int a = 0; a < data->size; a++){
	// 		cout << data->char_list[a] << ": " << keyb->assignment[a] << "  ";
	// 	}

	// 	keyb->cost = newCost;
	// }

	// // else if (imph > 0){
	// // 	cout << "\nHor" << endl;
	// // 	temp = keyb->assignment[keyb->grid[vecpairs[pos1].pos]];
	// // 	keyb->assignment[keyb->grid[vecpairs[pos1].pos]] = keyb->assignment[keyb->grid[vecpairs[pos2].pos]];
	// // 	keyb->assignment[keyb->grid[vecpairs[pos2].pos]] = temp;

	// // 	temp = keyb->assignment[keyb->grid[vecpairs[pos1].hpair]];
	// // 	keyb->assignment[keyb->grid[vecpairs[pos1].hpair]] = keyb->assignment[keyb->grid[vecpairs[pos2].hpair]];
	// // 	keyb->assignment[keyb->grid[vecpairs[pos2].hpair]] = temp;

	// // 	temp = keyb->grid[vecpairs[pos1].pos];
	// // 	keyb->grid[vecpairs[pos1].pos] = keyb->grid[vecpairs[pos2].pos];
	// // 	keyb->grid[vecpairs[pos2].pos] = temp;
		
	// // 	temp = keyb->grid[vecpairs[pos1].hpair];
	// // 	keyb->grid[vecpairs[pos1].hpair] = keyb->grid[vecpairs[pos2].hpair];
	// // 	keyb->grid[vecpairs[pos2].hpair] = temp;
		
	// // 	keyb->cost = newCost;
	// // }