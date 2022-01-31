#include "localsearch.h"
#define KEYS 140
#define ROW 10
#define COL 14

void swap (Gendata *data, Keyboard *keyb){

	vector <int> auxKeyb;
	vector <unsigned int> rmvCost;
	list <int> emptyPos;

	list<int>::iterator it;

	long long iniCost;
	long long newCost = 0;
	long long finalCost = 0;
	long long deltaFi;
	long long bestDeltaFi = -1;
	long long ins1;
	long long ins2;
	
	long rmv1;
	long rmv2;

	bool imp = 1;
	bool imp1 = 1;

	int pos1 = 0;
	int pos2 = 0;
	int char2;
	int temp;
	int t = 0;

	for (int i = 0; i < data->size; i++){
		rmvCost.push_back(0);
	}

	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb.push_back(keyb->grid[i]);
	}

	for(int i = 0; i < keyb->ksize; i++){
		if(auxKeyb[i] < 0){
			emptyPos.push_back(i);
		}
	}

	iniCost = keyb->cost;
	
	while (bestDeltaFi < 0){
		for (int i = 0; i < data->size; i++){
	
			imp = 0;
			imp1 = 0;
			newCost = 0;
			bestDeltaFi = 0;
			deltaFi = 0;

			removecost (data, rmvCost, keyb);
			rmv1 = rmvCost[i];
			
			for (int j = 0; j < data->size; j++){
				if (j != i){

					rmv2 = rmvCost[j];

					temp = keyb->assignment[i];
					keyb->assignment[i] = keyb->assignment[j];
					keyb->assignment[j] = temp;
				
					ins1 = costcalc (data, i, keyb);
					ins2 = costcalc (data, j, keyb); 
	
					deltaFi = - rmv1 - rmv2 + ins1 + ins2;

					if (deltaFi < 0){
						if (deltaFi < bestDeltaFi){
							bestDeltaFi = deltaFi;
							char2 = j;
							pos1 = keyb->assignment[i];
							pos2 = keyb->assignment[j];
							imp = 1;
						}
					}				
					keyb->assignment[j] = keyb->assignment[i];
					keyb->assignment[i] = temp;
				}
			}
			
			deltaFi = 0;
			
			for(it = emptyPos.begin(); it != emptyPos.end(); it++){
				rmv1 = rmvCost[i];

				temp = keyb->assignment[i];
				keyb->assignment[i] = *it;

				ins1 = costcalc (data, i, keyb);

				deltaFi = - rmv1 + ins1;
				
				if (deltaFi < 0){
					if (deltaFi < bestDeltaFi){
						bestDeltaFi = deltaFi;
						pos1 = *it;
						pos2 = temp;
						imp = 1;
						imp1 = 1;
					}
				}

				keyb->assignment[i] = temp;
			}//for

			if (imp > 0){
				if (imp1 > 0){
					keyb->assignment[i] = pos1;

					auxKeyb[pos1] = i;
					auxKeyb[pos2] = -1;

					newCost = iniCost + bestDeltaFi;
					iniCost = newCost;
					
					emptyPos.remove(pos1);
					emptyPos.push_back(pos2);

				}

				else{
					keyb->assignment[i] = pos1;
					keyb->assignment[char2] = pos2;

					temp = auxKeyb[pos1];
					auxKeyb[pos1] = auxKeyb[pos2];
					auxKeyb[pos2] = temp;

					newCost = iniCost + bestDeltaFi;
					iniCost = newCost;
				}//else
			}
		}//for 'i'
	}//while

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = auxKeyb[i];
	}

	newCost = iniCost;
	cout << "New Cost(Swap): " << newCost << endl;
	keyb->cost = newCost;
}

void swapPair (Gendata *data, Keyboard *keyb){

	vector <int> auxKeyb;
	vector <unsigned int> rmvCost;

	long long iniCost;
	long long newCost = 0;
	long long finalCost = 0;
	long long deltaFi;
	long long bestDeltaFi = -1;
	long long ins1;
	long long ins2;
	
	long rmv1;
	long rmv2;

	bool impv;
	bool imph;
	bool vert;
	bool horz;

	int hpos1 = 0;
	int vpos1 = 0;
	int hpos2 = 0;
	int vpos2 = 0;
	int pos1 = 0;
	int pos2 = 0;
	int pair2 = 0;
	int char2;
	int charPair2;
	int temp;
	int t = 0;

	for (int i = 0; i < data->size; i++){
		rmvCost.push_back(0);
	}

	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb.push_back(keyb->grid[i]);
	}

	iniCost = keyb->cost;

	while (bestDeltaFi < 0){
		for (int i = 0; i < keyb->ksize - 1; i++){

			impv = 0;
			imph = 0;
			newCost = 0;
			bestDeltaFi = 0;
			deltaFi = 0;

			removecost (data, rmvCost, keyb);

			if (auxKeyb[i] > -1){

				vert = 0;
				horz = 0;
				vpos1 = 0;
				hpos1 = 0;

				if (floor((i + keyb->kcols) / keyb->kcols) < keyb->krows){
					if (auxKeyb[i + keyb->kcols] > -1){
						vpos1 = i + keyb->kcols;
						vert = 1;
					}
				}
				if ((i + 1) % keyb->kcols < keyb->kcols){
					if (auxKeyb[i + 1] > -1){
						hpos1 = i + 1;
						horz = 1;
					}
				}

				if (vert == 0 && horz == 0){
					continue;
				}
				
				for (int j = i + 1; j < keyb->ksize; j++){
					if (auxKeyb[j] > -1){
						vpos2 = 0;
						hpos2 = 0;
						if (vert == 1){
							if (j != vpos1){
								if (floor((j + keyb->kcols) / keyb->kcols) < keyb->krows){
									if (auxKeyb[j + keyb->kcols] > -1){
										vpos2 = j + keyb->kcols;

										rmv1 = rmvCost[auxKeyb[i]] + rmvCost[auxKeyb[vpos1]] - 2 * data->freq_matrix[auxKeyb[i]][auxKeyb[vpos1]] * data->b_matrix[i][vpos1];
										rmv2 = rmvCost[auxKeyb[j]] + rmvCost[auxKeyb[vpos2]] - 2 * data->freq_matrix[auxKeyb[j]][auxKeyb[vpos2]] * data->b_matrix[j][vpos2];

										temp = keyb->assignment[auxKeyb[i]];
										keyb->assignment[auxKeyb[i]] = keyb->assignment[auxKeyb[j]];
										keyb->assignment[auxKeyb[j]] = temp;			

										temp = keyb->assignment[auxKeyb[vpos1]];
										keyb->assignment[auxKeyb[vpos1]] = keyb->assignment[auxKeyb[vpos2]];
										keyb->assignment[auxKeyb[vpos2]] = temp;

										ins1 = costcalc (data, auxKeyb[i], keyb) + costcalc (data, auxKeyb[vpos1], keyb) - 2 * data->freq_matrix[auxKeyb[i]][auxKeyb[vpos1]] * data->b_matrix[i][vpos1];
										ins2 = costcalc (data, auxKeyb[j], keyb) + costcalc (data, auxKeyb[vpos2], keyb) - 2 * data->freq_matrix[auxKeyb[j]][auxKeyb[vpos2]] * data->b_matrix[j][vpos2];

										deltaFi = - rmv1 - rmv2 + ins1 + ins2;

										if (deltaFi < 0){
											if (deltaFi < bestDeltaFi){
												bestDeltaFi = deltaFi;
												char2 = auxKeyb[j];
												pos2 = j;
												pair2 = vpos2;
												charPair2 = auxKeyb[vpos2];
												impv = 1;
											}
										}
										
										temp = keyb->assignment[auxKeyb[j]];
										keyb->assignment[auxKeyb[j]] = keyb->assignment[auxKeyb[i]];
										keyb->assignment[auxKeyb[i]] = temp;

										temp = keyb->assignment[auxKeyb[vpos2]];
										keyb->assignment[auxKeyb[vpos2]] = keyb->assignment[auxKeyb[vpos1]];
										keyb->assignment[auxKeyb[vpos1]] = temp;
									}
								}
							}
						}

						if (horz == 1){
							if (j != hpos1){
								if ((j + 1) % keyb->kcols < keyb->kcols){
									if (auxKeyb[i + 1] > -1){
										hpos2 = j + 1;

										rmv1 = rmvCost[auxKeyb[i]] + rmvCost[auxKeyb[hpos1]] - 2 * data->freq_matrix[auxKeyb[i]][auxKeyb[hpos1]] * data->b_matrix[i][hpos1];
										rmv2 = rmvCost[auxKeyb[j]] + rmvCost[auxKeyb[hpos2]] - 2 * data->freq_matrix[auxKeyb[j]][auxKeyb[hpos2]] * data->b_matrix[j][hpos2];

										temp = keyb->assignment[auxKeyb[i]];
										keyb->assignment[auxKeyb[i]] = keyb->assignment[auxKeyb[j]];
										keyb->assignment[auxKeyb[j]] = temp;
										
										temp = keyb->assignment[auxKeyb[hpos1]];
										keyb->assignment[auxKeyb[hpos1]] = keyb->assignment[auxKeyb[hpos2]];
										keyb->assignment[auxKeyb[hpos2]] = temp;

										ins1 = costcalc (data, auxKeyb[i], keyb) + costcalc (data, auxKeyb[hpos1], keyb) - 2 * data->freq_matrix[auxKeyb[i]][auxKeyb[hpos1]] * data->b_matrix[i][hpos1];
										ins2 = costcalc (data, auxKeyb[j], keyb) + costcalc (data, auxKeyb[hpos2], keyb) - 2 * data->freq_matrix[auxKeyb[j]][auxKeyb[hpos2]] * data->b_matrix[j][hpos2];

										deltaFi = - rmv1 - rmv2 + ins1 + ins2;

										if (deltaFi < 0){
											if (deltaFi < bestDeltaFi){
												bestDeltaFi = deltaFi;
												char2 = auxKeyb[j];
												pos2 = j;
												pair2 = hpos2;
												charPair2 = auxKeyb[hpos2];
												impv = 0;
												imph = 1;
											}
										}

										temp = keyb->assignment[auxKeyb[j]];
										keyb->assignment[auxKeyb[j]] = keyb->assignment[auxKeyb[i]];
										keyb->assignment[auxKeyb[i]] = temp;

										temp = keyb->assignment[auxKeyb[hpos2]];
										keyb->assignment[auxKeyb[hpos2]] = keyb->assignment[auxKeyb[hpos1]];
										keyb->assignment[auxKeyb[hpos1]] = temp;	
									}
								}
							}
						}	
					}
				}//for 'j'

				if (impv > 0){
					
					keyb->assignment[auxKeyb[i]] = pos2;
					keyb->assignment[char2] = i;
					
					keyb->assignment[auxKeyb[vpos1]] = pair2;
					keyb->assignment[charPair2] = vpos1;
					
					temp = auxKeyb[i];
					auxKeyb[i] = auxKeyb[pos2];
					auxKeyb[pos2] = temp;

					temp = auxKeyb[vpos1];
					auxKeyb[vpos1] = auxKeyb[pair2];
					auxKeyb[pair2] = temp;

					newCost = iniCost + bestDeltaFi;
					iniCost = newCost;
				}
				else if (imph > 0){
					
					keyb->assignment[auxKeyb[i]] = pos2;
					keyb->assignment[char2] = i;
					
					keyb->assignment[auxKeyb[hpos1]] = pair2;
					keyb->assignment[charPair2] = hpos1;
					
					temp = auxKeyb[i];
					auxKeyb[i] = auxKeyb[pos2];
					auxKeyb[pos2] = temp;

					temp = auxKeyb[hpos1];
					auxKeyb[hpos1] = auxKeyb[pair2];
					auxKeyb[pair2] = temp;

					newCost = iniCost + bestDeltaFi;
					iniCost = newCost;				
				}
			}
		}//for 'i'
	}//while

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = auxKeyb[i];
	}
	
	newCost = iniCost;
	cout << "New Cost(Swap Pair): " << newCost << endl;
	keyb->cost = newCost;
}

void moveContour (Gendata *data, Keyboard *keyb){

	vector <int> auxKeyb;
	vector <int> contourInter;
	vector <unsigned int> rmvCost;

	list <int> contourPos;	
	list <int> newContour;
	list <int>::iterator it;

	long long iniCost;
	long long newCost;
	long long f_Cost;
	long long s_Cost;
	long long deltaFi;
	long long bestDeltaFi = -1;
	long long ins;
	long long rmv;

	bool imp = 1;
	bool f_imp;
	bool s_imp;
	bool ns_imp;

	int f_pos1, f_pos2, ns_pos1, ns_pos2, s_pos1, s_pos2, pos1, pos2;
	int f_char, ns_char, s_char, charac;
	int temp;
	int posFi;

	for (int i = 0; i < data->size; i++){
		rmvCost.push_back(0);
	}

	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb.push_back(keyb->grid[i]);
	}

	contourSet(data, keyb, contourPos, auxKeyb, -1);
	
	iniCost = keyb->cost;
	
	while (imp > 0){
		
		imp = 0;
		newContour.clear();

		for (int i = 0; i < data->size - 1; i++){

			f_imp = 0;
			s_imp = 0;
			ns_imp = 0;
			bestDeltaFi = 0;
			deltaFi = 0;

			removecost (data, rmvCost, keyb);

			for (it = contourPos.begin(); it!= contourPos.end(); it++){

				temp = keyb->assignment[i];
				keyb->assignment[i] = *it;
				
				rmv = rmvCost[i];
				ins = costcalc (data, i, keyb);

				deltaFi = - rmv + ins;

				if (deltaFi < 0){
					if (deltaFi < bestDeltaFi){

						bestDeltaFi = deltaFi; 
						pos1 = *it;
						pos2 = temp;
						charac = i;

						if (imp > 0){
							s_imp = 1;
						}
						if (imp < 1){
							imp = 1;
							f_imp = 1;
						}
					}
				}			
				
				keyb->assignment[i] = temp;
			}//for 'it'
			
			if (newContour.size() > 0){
				deltaFi = 0;

				posFi = keyb->assignment[f_char];
				keyb->assignment[f_char] = f_pos1;

				removecost (data, rmvCost, keyb);

				rmv = rmvCost[i];

				for (it = newContour.begin(); it != newContour.end(); it++){
				
					temp = keyb->assignment[i];
					keyb->assignment[i] = *it;
								
					ins = costcalc (data, i, keyb);

					deltaFi = - rmv + ins;
					
					if (deltaFi < 0){
						if (deltaFi < bestDeltaFi){
							bestDeltaFi = deltaFi;
							ns_pos1 = *it;
							ns_pos2 = temp;
							ns_char = i;

							ns_imp = 1;
							f_imp = 0;
							s_imp = 0;
						}			
					}
				keyb->assignment[i] = temp;
			}

				keyb->assignment[f_char] = posFi;
			}

			if(f_imp > 0){
				f_pos1 = pos1;
				f_pos2 = pos2;
				f_char = charac;

				auxKeyb[f_pos1] = f_char;
				auxKeyb[f_pos2] = -1;

				f_Cost = iniCost + bestDeltaFi;
				newCost = f_Cost;

				contourPos.remove(f_pos1);

				keyb->assignment[i] = f_pos1;

				contourSet(data, keyb, newContour, auxKeyb, f_char);
				
				keyb->assignment[i] = f_pos2;
				
				if(verifyContour(data, keyb, contourPos, auxKeyb, f_pos2) == 1){
					newContour.push_back(f_pos2);
				}

				newContour.sort();

				contourInter.clear();
				newContour.erase(unique(newContour.begin(), newContour.end()), newContour.end());
				set_intersection (contourPos.begin(), contourPos.end(), newContour.begin(), newContour.end(), back_inserter(contourInter) );
				newContour.erase (set_difference (newContour.begin(), newContour.end(), contourInter.begin(), contourInter.end(), newContour.begin() ), newContour.end() );
				
				rmvContour(keyb, contourPos, auxKeyb, f_pos2);
			}

			else if(ns_imp > 0){
				
				keyb->assignment[f_char] = f_pos1;

				auxKeyb[ns_pos1] = ns_char;
				auxKeyb[ns_pos2] = -1;

				iniCost = f_Cost;
				f_Cost = iniCost + bestDeltaFi;
				newCost = f_Cost;

				contourPos.merge(newContour);
				contourPos.sort();
				contourPos.remove(ns_pos1);

				keyb->assignment[i] = ns_pos1;

				contourSet(data, keyb, newContour, auxKeyb, ns_char);
				
				keyb->assignment[i] = ns_pos2;
				
				if(verifyContour(data, keyb, contourPos, auxKeyb, ns_pos2) == 1){
					newContour.push_back(ns_pos2);
				}

				newContour.sort();
				contourInter.clear();
				newContour.erase(unique(newContour.begin(), newContour.end()), newContour.end());
				set_intersection (contourPos.begin(), contourPos.end(), newContour.begin(), newContour.end(), back_inserter(contourInter) );
				newContour.erase (set_difference (newContour.begin(), newContour.end(), contourInter.begin(), contourInter.end(), newContour.begin() ), newContour.end() );
				
				rmvContour(keyb, contourPos, auxKeyb, ns_pos2);

				f_pos1 = ns_pos1;
				f_pos2 = ns_pos2;
				f_char = ns_char;
			}

			else if(s_imp > 0){
				s_pos1 = pos1;
				s_pos2 = pos2;
				s_char = charac;
				
				keyb->assignment[f_char] = f_pos1;

				auxKeyb[s_pos1] = s_char;
				auxKeyb[s_pos2] = -1;

				iniCost = f_Cost;
				s_Cost = f_Cost + bestDeltaFi + ((data->freq_matrix[f_char][s_char])*(data->b_matrix[f_pos1][s_pos1] - data->b_matrix[f_pos2][s_pos1] + data->b_matrix[f_pos2][s_pos2] - data->b_matrix[f_pos1][s_pos2]));
				f_Cost = s_Cost;
				newCost = s_Cost;
				s_Cost = 0;

				contourPos.merge(newContour);
				contourPos.sort();
				contourPos.remove(s_pos1);
			
				keyb->assignment[i] = s_pos1;

				contourSet(data, keyb, newContour, auxKeyb, s_char);
				
				keyb->assignment[i] = s_pos2;

				if(verifyContour(data, keyb, contourPos, auxKeyb, s_pos2) == 1){
					newContour.push_back(s_pos2);
				}

				newContour.sort();
				contourInter.clear();
				newContour.erase(unique(newContour.begin(), newContour.end()), newContour.end());
				set_intersection (contourPos.begin(), contourPos.end(), newContour.begin(), newContour.end(), back_inserter(contourInter) );
				newContour.erase (set_difference (newContour.begin(), newContour.end(), contourInter.begin(), contourInter.end(), newContour.begin() ), newContour.end() );
				
				rmvContour(keyb, contourPos, auxKeyb, s_pos2);

				f_pos1 = s_pos1;
				f_pos2 = s_pos2;
				f_char = s_char;
			}
		}//for 'i'

		if(imp > 0){
			keyb->assignment[f_char] = f_pos1;
			iniCost = newCost;
		}
		contourPos.merge(newContour);
		contourPos.sort();
	}//while

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = auxKeyb[i];
	}

	cout << "Final Cost(Move Contour): " << newCost << endl;
	keyb->cost = newCost;
}//end moveContour

void swapPair (Gendata *data, Keyboard *keyb){

	vector <int> auxKeyb;
	vector <unsigned int> rmvCost;

	long long iniCost;
	long long testCost;
	long long newCost;
	long long finalCost;
	long long deltaFi;
	long long bestDeltaFi = 0;
	long long ins1;
	long long ins2;
	long long insp1;
	long long insp2;

	long rmv1;
	long rmv2;
	long rmvp1;
	long rmvp2;

	bool impv = 0;
	bool imph = 0;
	bool vert;
	bool horz;

	int hpos1, vpos1, hpos2, vpos2, pos1, pos2;
	int pair1, pair2;
	int char1, char2, charPair1, charPair2;
	int temp;

	for (int i = 0; i < data->size; i++){
		rmvCost.push_back(0);
	}

	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb.push_back(keyb->grid[i]);
	}

	iniCost = keyb->cost;
	
	//removecost (data, rmvCost, keyb);
	cout << "\nCusto Inicial SP: " << iniCost << endl;
	
	for (int i = 0; i < keyb->ksize - 1; i++){
		
		if (auxKeyb[i] == data->size - 1){
			continue;
		}
		
		removecost (data, rmvCost, keyb);

		deltaFi = 0;
		
		if (auxKeyb[i] > -1){

			vert = 0;
			horz = 0;
			vpos1 = 0;
			hpos1 = 0;

			if (floor((i + keyb->kcols) / keyb->kcols) < keyb->krows){
				if (auxKeyb[i + keyb->kcols] > -1){
					vpos1 = i + keyb->kcols;
					vert = 1;
				}
				if (auxKeyb[i + keyb->kcols] == data->size -1){
					vert = 0;
				}
			}
			if ((i + 1) % keyb->kcols < keyb->kcols){
				if (auxKeyb[i + 1] > -1){
					hpos1 = i + 1;
					horz = 1;
				}
				if (auxKeyb[i + 1] == data->size -1){
					horz = 0;
				}
			}

			if (vert == 0 && horz == 0){
				continue;
			}
			
			for (int j = i + 1; j < keyb->ksize; j++){
				if (auxKeyb[j] == data->size - 1){
					continue;
				}
				if (auxKeyb[j] > -1){
					
					vpos2 = 0;
					hpos2 = 0;

					if (auxKeyb[j + keyb->kcols] == data->size -1){
						vert = 0;
					}
					if (auxKeyb[j + 1] == data->size -1){
						horz = 0;
					}
					if (vert == 1){
						if (j != vpos1){
							if (floor((j + keyb->kcols) / keyb->kcols) < keyb->krows){
								if (auxKeyb[j + keyb->kcols] > -1){
									vpos2 = j + keyb->kcols;

									rmv1 = rmvCost[auxKeyb[i]];
									rmv2 = rmvCost[auxKeyb[j]];

									temp = keyb->assignment[auxKeyb[i]];
									keyb->assignment[auxKeyb[i]] = keyb->assignment[auxKeyb[j]];
									keyb->assignment[auxKeyb[j]] = temp;
									
									ins1 = costcalc (data, auxKeyb[i], keyb);
									ins2 = costcalc (data, auxKeyb[j], keyb);
									
									removecost (data, rmvCost, keyb);

									rmvp1 = rmvCost[auxKeyb[vpos1]];
									rmvp2 = rmvCost[auxKeyb[vpos2]];

									temp = keyb->assignment[auxKeyb[vpos1]];
									keyb->assignment[auxKeyb[vpos1]] = keyb->assignment[auxKeyb[vpos2]];
									keyb->assignment[auxKeyb[vpos2]] = temp;

									insp1 = costcalc (data, auxKeyb[vpos1], keyb);
									insp2 = costcalc (data, auxKeyb[vpos2], keyb);

									deltaFi = - rmvp1 - rmvp2 + insp1 + insp2 - rmv1 - rmv2 + ins1 + ins2;

									if (deltaFi < 0){
										if (deltaFi < bestDeltaFi){
											cout << "\nV Pares escolhidos: " << data->char_list[auxKeyb[i]] << " e " << data->char_list[auxKeyb[vpos1]] << " com " <<  data->char_list[auxKeyb[j]] << " e " << data->char_list[auxKeyb[vpos2]] << " " << vpos2 << endl;
											
											bestDeltaFi = deltaFi;
											char1 = auxKeyb[i];
											char2 = auxKeyb[j];
											pos1 = i;
											pos2 = j;
											pair1 = vpos1;
											pair2 = vpos2;
											charPair1 = auxKeyb[vpos1];
											charPair2 = auxKeyb[vpos2];
											impv = 1;
											imph = 0;
											cout << "\nV best delta fi: " << bestDeltaFi << endl;
										}
									}
									
									temp = keyb->assignment[auxKeyb[j]];
									keyb->assignment[auxKeyb[j]] = keyb->assignment[auxKeyb[i]];
									keyb->assignment[auxKeyb[i]] = temp;

									temp = keyb->assignment[auxKeyb[vpos2]];
									keyb->assignment[auxKeyb[vpos2]] = keyb->assignment[auxKeyb[vpos1]];
									keyb->assignment[auxKeyb[vpos1]] = temp;
								}
							}
						}
					}
					
					if (horz == 1){
						if (j != hpos1){
							if ((j + 1) % keyb->kcols < keyb->kcols){
								if (auxKeyb[j + 1] > -1){

									//removecost (data, rmvCost, keyb);

									hpos2 = j + 1;

									//rmv1 = rmvCost[auxKeyb[i]];
									//rmv2 = rmvCost[auxKeyb[j]];

									temp = keyb->assignment[auxKeyb[i]];
									keyb->assignment[auxKeyb[i]] = keyb->assignment[auxKeyb[j]];
									keyb->assignment[auxKeyb[j]] = temp;
									
									//ins1 = costcalc (data, auxKeyb[i], keyb);
									//ins2 = costcalc (data, auxKeyb[j], keyb);

									removecost (data, rmvCost, keyb);

									rmvp1 = rmvCost[auxKeyb[hpos1]];
									rmvp2 = rmvCost[auxKeyb[hpos2]];

									temp = keyb->assignment[auxKeyb[hpos1]];
									keyb->assignment[auxKeyb[hpos1]] = keyb->assignment[auxKeyb[hpos2]];
									keyb->assignment[auxKeyb[hpos2]] = temp;
									
									insp1 = costcalc (data, auxKeyb[hpos1], keyb);
									insp2 = costcalc (data, auxKeyb[hpos2], keyb);
									
									deltaFi = - rmvp1 - rmvp2 + insp1 + insp2 - rmv1 - rmv2 + ins1 + ins2;

									if (deltaFi < 0){
										if (deltaFi < bestDeltaFi){
											cout << "\nH Pares escolhidos: " << data->char_list[auxKeyb[i]] << " e " << data->char_list[auxKeyb[hpos1]] << " com " <<  data->char_list[auxKeyb[j]] << " e " << data->char_list[auxKeyb[hpos2]] << endl;

											bestDeltaFi = deltaFi;
											char1 = auxKeyb[i];
											char2 = auxKeyb[j];
											pos1 = i;
											pos2 = j;
											pair1 = hpos1;
											pair2 = hpos2;
											charPair1 = auxKeyb[hpos1];
											charPair2 = auxKeyb[hpos2];
											impv = 0;
											imph = 1;
											cout << "\nH best delta fi: " << bestDeltaFi << endl;

										}
									}

									temp = keyb->assignment[auxKeyb[j]];
									keyb->assignment[auxKeyb[j]] = keyb->assignment[auxKeyb[i]];
									keyb->assignment[auxKeyb[i]] = temp;

									temp = keyb->assignment[auxKeyb[hpos2]];
									keyb->assignment[auxKeyb[hpos2]] = keyb->assignment[auxKeyb[hpos1]];
									keyb->assignment[auxKeyb[hpos1]] = temp;	
								}
							}
						}
					}	
				}
			}//for 'j'
		}
	}//for 'i'

	if (impv > 0){
		
		//cout << "\nV Caractere iterado " << data->char_list[auxKeyb[pos1]] << "\nPar: " << data->char_list[auxKeyb[pos2]] << endl;

		keyb->assignment[char1] = pos2;
		keyb->assignment[char2] = pos1;
		
		keyb->assignment[charPair1] = pair2;
		keyb->assignment[charPair2] = pair1;
		
		temp = auxKeyb[pos1];
		auxKeyb[pos1] = auxKeyb[pos2];
		auxKeyb[pos2] = temp;

		temp = auxKeyb[pair1];
		auxKeyb[pair1] = auxKeyb[pair2];
		auxKeyb[pair2] = temp;

		keyb->cost = iniCost + bestDeltaFi;
		cout << "\nV Novo custo: " << keyb->cost << endl;
	}

	else if (imph > 0){
		//cout << "\nH Caractere iterado " << data->char_list[auxKeyb[pos1]] << " e " << data->char_list[auxKeyb[pair1]] << "\nPar: " << data->char_list[auxKeyb[pos2]] << endl;

		keyb->assignment[char1] = pos2;
		keyb->assignment[char2] = pos1;
		
		keyb->assignment[charPair1] = pair2;
		keyb->assignment[charPair2] = pair1;
		
		temp = auxKeyb[pos1];
		auxKeyb[pos1] = auxKeyb[pos2];
		auxKeyb[pos2] = temp;

		temp = auxKeyb[pair1];
		auxKeyb[pair1] = auxKeyb[pair2];
		auxKeyb[pair2] = temp;

		keyb->cost = iniCost + bestDeltaFi;
		cout << "\nH Novo custo: " << keyb->cost << endl;
	}
	
	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = auxKeyb[i];
	}
	
	cout << "New Cost(Swap Pair): " << keyb->cost << endl;

	testCost = costcalc(data, -2, keyb);
	cout << "\nCusto calculado final sp: " << testCost << endl;
	
	cout<< "\nAssignment SP: " << endl;
	for(int i = 0; i < data->size; i++){
		cout << data->char_list[i] << ": " << keyb->assignment[i] << "  ";
	}
	
	cout << endl << "\nSolucao SP" << endl;
	printSol(data, keyb, auxKeyb);
	cout << endl;

}

	int nbr = 1;
	vector<int> auxKeyb; 
	long long bestCost = 999999999999;
	long long testCost;
	int t = 1;
	
	cout << "\nCusto Inicial vnd: " << keyb->cost << endl;

	while (t < 5){
		cout << "\nValor de nbr: " << nbr << endl;

		switch (nbr){
/*			case 1:
				cout << "\nSwap escolhido" << endl;
				swap (data, keyb);
				break;
*/
			case 1:
				cout << "\nSwap Pair escolhido" << endl;
				swapPair (data, keyb);
				break;

/*			case 1:
				cout << "\nMover Contorno escolhido" << endl;
				moveContour (data, keyb);
				break;*/
/*
			default:
				cout << "Out of range" << endl;
				break;*/
		}
		if (keyb->cost < bestCost) {
			bestCost = keyb->cost;
			cout << "\nBest Cost: " << bestCost << endl;
			nbr = 1;
/*			testCost = costcalc(data, -2, keyb);
			cout << "\nCusto calculado vnd: " << testCost << endl;*/
		}
		else{
			cout << "\nElse" << endl;
			nbr++;
		}
		t++;
	//	cout << "\nTeste vnd" << endl;
	}
	cout << "\nBest cost Final: " << bestCost << endl;

	testCost = costcalc(data, -2, keyb);
	cout << "\nCusto calculado final vnd: " << testCost << endl;

	cout<< "\nAssignment vnd (final): " << endl;
	for(int i = 0; i < data->size; i++){
		cout << data->char_list[i] << ": " << keyb->assignment[i] << "  ";
	}
	cout << endl;

	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb.push_back(keyb->grid[i]);
	}

	cout << "\nSolução: " << endl;
	printSol(data, keyb, auxKeyb);
	cout << endl;


void SFpert1 (Gendata *data, Keyboard *keyb){
	//1.movimentação de n caracteres para teclas vazias
	
	int pertChars;
	int movChar;
	int limit;
	int n = 0;
	int chosenPos;
	int newPos;
	int temp = 0;

	list<int> pertSet;
	list<int> auxCharList;

	list<int>::iterator it;

	vector <int> auxKeyb;
	vector<int> emptyPos;

	limit = ceil (data->size / 2);
	pertChars = 3 + rand() % limit;
	cout << "\nLimite: " << limit << " Caracteres Perturbados: " << pertChars << endl;
	cout << "\nTamanho pertSet: " << pertSet.size() << endl;

	for(int i = 0; i < keyb->ksize; i++){
		if(keyb->grid[i] < 0){
			emptyPos.push_back(i);
		}
	}
	
	for (int i = 0; i < data->size; i++){
		auxCharList.push_back(i);
	}
	
	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb.push_back(keyb->grid[i]);
	}

	while (pertSet.size() < pertChars){
		movChar = rand() % data->size;
		for(it = auxCharList.begin(); it != auxCharList.end(); it++){
			if(movChar == *it){
				pertSet.push_back(*it);
				auxCharList.erase(it);
				break;
			}
		}
	}

	cout << "\nCaracteres a perturbar: " << endl;
	for (it = pertSet.begin(); it != pertSet.end(); it++){
		cout << data->char_list[*it] << " ";
	}
	cout << endl;
	
	while(!pertSet.empty()){

		chosenPos = rand() % emptyPos.size();
		newPos = emptyPos[chosenPos];

		cout << "\nNova Posição: " << newPos << endl;
				
		temp = keyb->grid[keyb->assignment[pertSet.front()]];
		keyb->grid[keyb->assignment[pertSet.front()]] = keyb->grid[newPos];
		keyb->grid[newPos] = temp;
		
		keyb->assignment[pertSet.front()] = newPos;

		pertSet.pop_front();
		emptyPos.erase(emptyPos.begin() + chosenPos - 1);
	}
	
	keyb->cost = costcalc(data, -2, keyb);
	
	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb[i] = keyb->grid[i];
	}

	cout << endl << "\nSolucao Perturbada: " << endl;
	printSol(data, keyb, auxKeyb);
	cout << endl;
	cout << "\nCusto perturbacao: " << keyb->cost << endl;

}

