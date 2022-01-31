// void swapPair (Gendata *data, Keyboard *keyb, Stats *stat){ //velho

// 	double begin;
// 	double end;

// 	double elapTm;
	
// 	begin = cpuTime();

// 	vector <int> auxKeyb;
// 	vector <unsigned int> rmvCost;

// 	long long iniCost;
// 	long long deltaFi;
// 	long long bestDeltaFi = 0;
// 	long long ins1;
// 	long long ins2;
// 	long long insp1;
// 	long long insp2;

// 	long rmv1;
// 	long rmv2;
// 	long rmvp1;
// 	long rmvp2;

// 	bool impv = 0;
// 	bool imph = 0;
// 	bool vert;
// 	bool horz;

// 	int hpos1, vpos1, hpos2, vpos2, pos1, pos2;
// 	int pair1, pair2;
// 	int char1, char2, charPair1, charPair2;
// 	int temp;

// 	for (int i = 0; i < data->size; i++){
// 		rmvCost.push_back(0);
// 	}

// 	for (int i = 0; i < keyb->ksize; i++){
// 		auxKeyb.push_back(keyb->grid[i]);
// 	}

// 	iniCost = keyb->cost;
	
// 	for (int i = 0; i < keyb->ksize - 1; i++){
		
// /*		if (auxKeyb[i] == data->size - 1){
// 			continue;
// 		}*/
		
// 		deltaFi = 0;
		
// 		if (auxKeyb[i] > -1){

// 			vert = 0;
// 			horz = 0;
// 			vpos1 = 0;
// 			hpos1 = 0;

// 			if (floor((i + keyb->kcols) / keyb->kcols) < keyb->krows){
// 				if (auxKeyb[i + keyb->kcols] > -1){
// 					vpos1 = i + keyb->kcols;
// 					vert = 1;
// 				}
// 				if (auxKeyb[i + keyb->kcols] == data->size -1){
// 					vert = 0;
// 				}
// 			}
// 			if ((i + 1) % keyb->kcols > 0){
// 				if (auxKeyb[i + 1] > -1){
// 					hpos1 = i + 1;
// 					horz = 1;
// 				}
// 				if (auxKeyb[i + 1] == data->size -1){
// 					horz = 0;
// 				}
// 			}

// 			if (vert == 0 && horz == 0){
// 				continue;
// 			}

// 			for (int j = i + 1; j < keyb->ksize; j++){
// /*				if (auxKeyb[j] == data->size - 1){
// 					continue;
// 				}*/
// 				if (auxKeyb[j] > -1){

// 					if (auxKeyb[j + keyb->kcols] == data->size -1){
// 						vert = 0;
// 					}
// 					if (auxKeyb[j + 1] == data->size -1){
// 						horz = 0;
// 					}
// 					if (vert == 1){
// 						if (j != vpos1){
// 							if (floor((j + keyb->kcols) / keyb->kcols) < keyb->krows){
// 								if (auxKeyb[j + keyb->kcols] > -1){
// 									removecost (data, rmvCost, keyb);

// 									vpos2 = j + keyb->kcols;

// 									rmv1 = rmvCost[auxKeyb[i]];
// 									rmv2 = rmvCost[auxKeyb[j]];

// 									temp = keyb->assignment[auxKeyb[i]];
// 									keyb->assignment[auxKeyb[i]] = keyb->assignment[auxKeyb[j]];
// 									keyb->assignment[auxKeyb[j]] = temp;
									
// 									ins1 = costcalc (data, auxKeyb[i], keyb);
// 									ins2 = costcalc (data, auxKeyb[j], keyb);

// 									deltaFi = - rmv1 - rmv2 + ins1 + ins2;

// 									removecost (data, rmvCost, keyb);
									
// 									rmvp1 = rmvCost[auxKeyb[vpos1]];
// 									rmvp2 = rmvCost[auxKeyb[vpos2]];

// 									temp = keyb->assignment[auxKeyb[vpos1]];
// 									keyb->assignment[auxKeyb[vpos1]] = keyb->assignment[auxKeyb[vpos2]];
// 									keyb->assignment[auxKeyb[vpos2]] = temp;

// 									insp1 = costcalc (data, auxKeyb[vpos1], keyb);
// 									insp2 = costcalc (data, auxKeyb[vpos2], keyb);

// 									deltaFi += - rmvp1 - rmvp2 + insp1 + insp2;

// 									if (deltaFi < 0){
// 										if (deltaFi < bestDeltaFi){

// 											bestDeltaFi = deltaFi;
// 											char1 = auxKeyb[i];
// 											char2 = auxKeyb[j];
// 											pos1 = i;
// 											pos2 = j;
// 											pair1 = vpos1;
// 											pair2 = vpos2;
// 											charPair1 = auxKeyb[vpos1];
// 											charPair2 = auxKeyb[vpos2];
// 											impv = 1;
// 											imph = 0;
// 										}
// 									}

																
// 									temp = keyb->assignment[auxKeyb[j]];
// 									keyb->assignment[auxKeyb[j]] = keyb->assignment[auxKeyb[i]];
// 									keyb->assignment[auxKeyb[i]] = temp;

// 									temp = keyb->assignment[auxKeyb[vpos2]];
// 									keyb->assignment[auxKeyb[vpos2]] = keyb->assignment[auxKeyb[vpos1]];
// 									keyb->assignment[auxKeyb[vpos1]] = temp;

// 								}
// 							}
// 						}
// 					}
					
// 					if (horz == 1){
// 						if (j != hpos1){
// 							if ((j + 1) % keyb->kcols > 0){
// 								if (auxKeyb[j + 1] > -1){

// 									removecost (data, rmvCost, keyb);

// 									hpos2 = j + 1;

// 									rmv1 = rmvCost[auxKeyb[i]];
// 									rmv2 = rmvCost[auxKeyb[j]];

// 									temp = keyb->assignment[auxKeyb[i]];
// 									keyb->assignment[auxKeyb[i]] = keyb->assignment[auxKeyb[j]];
// 									keyb->assignment[auxKeyb[j]] = temp;
									
// 									ins1 = costcalc (data, auxKeyb[i], keyb);
// 									ins2 = costcalc (data, auxKeyb[j], keyb);
									
// 									deltaFi = - rmv1 - rmv2 + ins1 + ins2;
									
// 									removecost (data, rmvCost, keyb);

// 									rmvp1 = rmvCost[auxKeyb[hpos1]];
// 									rmvp2 = rmvCost[auxKeyb[hpos2]];

// 									temp = keyb->assignment[auxKeyb[hpos1]];
// 									keyb->assignment[auxKeyb[hpos1]] = keyb->assignment[auxKeyb[hpos2]];
// 									keyb->assignment[auxKeyb[hpos2]] = temp;
									
// 									insp1 = costcalc (data, auxKeyb[hpos1], keyb);
// 									insp2 = costcalc (data, auxKeyb[hpos2], keyb);
									
// 									deltaFi += - rmvp1 - rmvp2 + insp1 + insp2;

// 									if (deltaFi < 0){
// 										if (deltaFi < bestDeltaFi){
											
// 											bestDeltaFi = deltaFi;
// 											char1 = auxKeyb[i];
// 											char2 = auxKeyb[j];
// 											pos1 = i;
// 											pos2 = j;
// 											pair1 = hpos1;
// 											pair2 = hpos2;
// 											charPair1 = auxKeyb[hpos1];
// 											charPair2 = auxKeyb[hpos2];
// 											impv = 0;
// 											imph = 1;
// 										}
// 									}

// 									temp = keyb->assignment[auxKeyb[j]];
// 									keyb->assignment[auxKeyb[j]] = keyb->assignment[auxKeyb[i]];
// 									keyb->assignment[auxKeyb[i]] = temp;

// 									temp = keyb->assignment[auxKeyb[hpos2]];
// 									keyb->assignment[auxKeyb[hpos2]] = keyb->assignment[auxKeyb[hpos1]];
// 									keyb->assignment[auxKeyb[hpos1]] = temp;	
// 								}
// 							}
// 						}
// 					}	
// 				}
// 			}//for 'j'
// 		}
// 	}//for 'i'

// 	if (impv > 0){
		
// 		keyb->assignment[char1] = pos2;
// 		keyb->assignment[char2] = pos1;
		
// 		keyb->assignment[charPair1] = pair2;
// 		keyb->assignment[charPair2] = pair1;
		
// 		temp = auxKeyb[pos1];
// 		auxKeyb[pos1] = auxKeyb[pos2];
// 		auxKeyb[pos2] = temp;

// 		temp = auxKeyb[pair1];
// 		auxKeyb[pair1] = auxKeyb[pair2];
// 		auxKeyb[pair2] = temp;

// 		keyb->cost = iniCost + bestDeltaFi;
// 	}

// 	else if (imph > 0){

// 		keyb->assignment[char1] = pos2;
// 		keyb->assignment[char2] = pos1;
		
// 		keyb->assignment[charPair1] = pair2;
// 		keyb->assignment[charPair2] = pair1;
		
// 		temp = auxKeyb[pos1];
// 		auxKeyb[pos1] = auxKeyb[pos2];
// 		auxKeyb[pos2] = temp;

// 		temp = auxKeyb[pair1];
// 		auxKeyb[pair1] = auxKeyb[pair2];
// 		auxKeyb[pair2] = temp;

// 		keyb->cost = iniCost + bestDeltaFi;
// 	}
	
// 	for (int i = 0; i < keyb->ksize; i++){
// 		keyb->grid[i] = auxKeyb[i];
// 	}
	
// /*	cout << "New Cost(Swap Pair): " << keyb->cost << endl;

// 	testCost = costcalc(data, -2, keyb);
// 	cout << "\nCusto calculado final sp: " << testCost << endl;*/
	
// /*	cout<< "\nAssignment SP: " << endl;
// 	for(int i = 0; i < data->size; i++){
// 		cout << data->char_list[i] << ": " << keyb->assignment[i] << "  ";
// 	}
	
// 	cout << endl << "\nSolucao SP" << endl;
// 	printSol(data, keyb, auxKeyb);
// 	cout << endl;*/
// 	end = cpuTime();
// 	elapTm = end - begin;
	
// 	stat->spPairTime += elapTm;
// }
