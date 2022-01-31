#include "localsearch.h"
#include "cpuTime.h"
#include <ctime>
#define KEYS 140
#define ROW 10
#define COL 14

void swap (Gendata *data, Keyboard *keyb, Stats *stat){

	double begin;
	double end;

	double elapTm;
	
	begin = cpuTime();

	vector <int> auxKeyb;
	vector <unsigned int> rmvCost;
	//list <int> emptyPos;

	list<int>::iterator it;

	long long iniCost;
	long long deltaFi;
	long long bestDeltaFi = 0;
	long long ins1;
	long long ins2;
	
	long rmv1;
	long rmv2;

	bool imp = 0;
	//bool imp1 = 0;

	int pos1 = 0;
	int pos2 = 0;
	int char1;
	int char2;
	int temp;

	for (int i = 0; i < data->size; i++){
		rmvCost.push_back(0);
	}
	
	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb.push_back(keyb->grid[i]);
	}

/*	for(int i = 0; i < keyb->ksize; i++){
		if(auxKeyb[i] < 0){
			emptyPos.push_back(i);
		}
	}*/

	iniCost = keyb->cost;
	
	removecost (data, rmvCost, keyb);
	
	for (int i = 0; i < data->size; i++){

		deltaFi = 0;
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
						char1 = i;
						char2 = j;
						pos1 = keyb->assignment[i];
						pos2 = keyb->assignment[j];
						imp = 1;
						//imp1 = 0;
					}
				}				
				keyb->assignment[j] = keyb->assignment[i];
				keyb->assignment[i] = temp;
			}
		}
		
/*		deltaFi = 0;
		
		for(it = emptyPos.begin(); it != emptyPos.end(); it++){

			temp = keyb->assignment[i];
			keyb->assignment[i] = *it;

			ins1 = costcalc (data, i, keyb);

			deltaFi = - rmv1 + ins1;
			
			if (deltaFi < 0){
				if (deltaFi < bestDeltaFi){
					bestDeltaFi = deltaFi;
					char1 = i;
					pos1 = *it;
					pos2 = temp;
					imp = 1;
					imp1 = 1;
				}
			}
			keyb->assignment[i] = temp;
		}//for*/
	}//for i

	if (imp > 0){
		//if (imp1 < 1){

			keyb->assignment[char1] = pos1;
			keyb->assignment[char2] = pos2;

			temp = auxKeyb[pos1];
			auxKeyb[pos1] = auxKeyb[pos2];
			auxKeyb[pos2] = temp;

			keyb->cost = iniCost + bestDeltaFi;
		//}
/*
		else{
			keyb->assignment[char1] = pos1;

			temp = auxKeyb[pos1];
			auxKeyb[pos1] = auxKeyb[pos2];
			auxKeyb[pos2] = temp;

			keyb->cost = iniCost + bestDeltaFi;
			
			emptyPos.remove(pos1);
			emptyPos.push_back(pos2);

			emptyPos.sort();
		}//else*/
	}

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = auxKeyb[i];
	}

/*	cout << "New Cost(Swap): " << keyb->cost << endl;

	long long testCost;
	testCost = costcalc(data, -2, keyb);
	cout << "\nCusto calculado final (swap): " << testCost << endl;*/
	
/*	printSol(data, keyb, auxKeyb);
	cout << endl;*/

	end = cpuTime();
	elapTm = end - begin;

	stat->swapTime += elapTm;
}

void swapPair (Gendata *data, Keyboard *keyb, Stats *stat){

	double begin;
	double end;

	double elapTm;
	
	begin = cpuTime();

	vector <int> auxKeyb;
	vector <unsigned int> rmvCost;

	long long iniCost;
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
	
	for (int i = 0; i < keyb->ksize - 1; i++){
		
/*		if (auxKeyb[i] == data->size - 1){
			continue;
		}*/
		
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
			if ((i + 1) % keyb->kcols > 0){
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
/*				if (auxKeyb[j] == data->size - 1){
					continue;
				}*/
				if (auxKeyb[j] > -1){

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
									removecost (data, rmvCost, keyb);

									vpos2 = j + keyb->kcols;

									rmv1 = rmvCost[auxKeyb[i]];
									rmv2 = rmvCost[auxKeyb[j]];

									temp = keyb->assignment[auxKeyb[i]];
									keyb->assignment[auxKeyb[i]] = keyb->assignment[auxKeyb[j]];
									keyb->assignment[auxKeyb[j]] = temp;
									
									ins1 = costcalc (data, auxKeyb[i], keyb);
									ins2 = costcalc (data, auxKeyb[j], keyb);

									deltaFi = - rmv1 - rmv2 + ins1 + ins2;

									removecost (data, rmvCost, keyb);
									
									rmvp1 = rmvCost[auxKeyb[vpos1]];
									rmvp2 = rmvCost[auxKeyb[vpos2]];

									temp = keyb->assignment[auxKeyb[vpos1]];
									keyb->assignment[auxKeyb[vpos1]] = keyb->assignment[auxKeyb[vpos2]];
									keyb->assignment[auxKeyb[vpos2]] = temp;

									insp1 = costcalc (data, auxKeyb[vpos1], keyb);
									insp2 = costcalc (data, auxKeyb[vpos2], keyb);

									deltaFi += - rmvp1 - rmvp2 + insp1 + insp2;

									if (deltaFi < 0){
										if (deltaFi < bestDeltaFi){

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
							if ((j + 1) % keyb->kcols > 0){
								if (auxKeyb[j + 1] > -1){

									removecost (data, rmvCost, keyb);

									hpos2 = j + 1;

									rmv1 = rmvCost[auxKeyb[i]];
									rmv2 = rmvCost[auxKeyb[j]];

									temp = keyb->assignment[auxKeyb[i]];
									keyb->assignment[auxKeyb[i]] = keyb->assignment[auxKeyb[j]];
									keyb->assignment[auxKeyb[j]] = temp;
									
									ins1 = costcalc (data, auxKeyb[i], keyb);
									ins2 = costcalc (data, auxKeyb[j], keyb);
									
									deltaFi = - rmv1 - rmv2 + ins1 + ins2;
									
									removecost (data, rmvCost, keyb);

									rmvp1 = rmvCost[auxKeyb[hpos1]];
									rmvp2 = rmvCost[auxKeyb[hpos2]];

									temp = keyb->assignment[auxKeyb[hpos1]];
									keyb->assignment[auxKeyb[hpos1]] = keyb->assignment[auxKeyb[hpos2]];
									keyb->assignment[auxKeyb[hpos2]] = temp;
									
									insp1 = costcalc (data, auxKeyb[hpos1], keyb);
									insp2 = costcalc (data, auxKeyb[hpos2], keyb);
									
									deltaFi += - rmvp1 - rmvp2 + insp1 + insp2;

									if (deltaFi < 0){
										if (deltaFi < bestDeltaFi){
											
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
	}

	else if (imph > 0){

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
	}
	
	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = auxKeyb[i];
	}
	
/*	cout << "New Cost(Swap Pair): " << keyb->cost << endl;

	testCost = costcalc(data, -2, keyb);
	cout << "\nCusto calculado final sp: " << testCost << endl;*/
	
/*	cout<< "\nAssignment SP: " << endl;
	for(int i = 0; i < data->size; i++){
		cout << data->char_list[i] << ": " << keyb->assignment[i] << "  ";
	}
	
	cout << endl << "\nSolucao SP" << endl;
	printSol(data, keyb, auxKeyb);
	cout << endl;*/
	end = cpuTime();
	elapTm = end - begin;
	
	stat->spPairTime += elapTm;
}

void moveContour (Gendata *data, Keyboard *keyb, Stats *stat){

	double begin;
	double end;

	double elapTm;
	
	begin = cpuTime();

	vector <int> auxKeyb;
	vector <int> contourInter;
	vector <unsigned int> rmvCost;

	list <int> contourPos;	
	list <int> newContour;
	list <int>::iterator it;

	long long iniCost;
	long long newCost = 0;
	long long f_Cost = 0;
	long long s_Cost = 0;
	long long deltaFi;
	long long bestDeltaFi = -1;
	long long ins;
	long long rmv;

	bool imp = 0;
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

	for (int i = 0; i < data->size; i++){

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

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = auxKeyb[i];
	}

	keyb->cost = iniCost;
/*
	long long testCost;
	testCost = costcalc(data, -2, keyb);
	cout << "\nCusto calculado final (mc): " << testCost << endl;*/

/*	cout<< "\n4Assignment (final): " << endl;
	for(int i = 0; i < data->size; i++){
		cout << data->char_list[i] << ": " << keyb->assignment[i] << "  ";
	}
	cout << endl;*/

	end = cpuTime();
	elapTm = end - begin;
	
	stat->mvContTime += elapTm;
}//end moveContour

void SF_RVND (Gendata *data, Keyboard *keyb, Stats *stat){
	
	int nbr = 0;
	int pos = 0;
	int counter;

	long long bestCost = keyb->cost;

	list<int> nbrList;
	list<int> usedNbr;

	list<int>::iterator it;
	
	vector <int> auxKeyb;

	for ( int i = 1; i <= 3; i++ ) {
		nbrList.push_back(i);
	}
	
	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb.push_back(keyb->grid[i]);
	}
	
	while (!nbrList.empty()) {
		
		nbr = 1 + rand() % nbrList.size();
		counter = 1;

		for (it = nbrList.begin(); it != nbrList.end(); it++) {
			if (counter == nbr) {
				nbr = *it;
				break;
			}
			counter++;
		}

		switch (nbr) {
			case 1:
				swap (data, keyb, stat);
				break;

			case 2:
				swapPair (data, keyb, stat);
				break;

			case 3:
				moveContour (data, keyb, stat);
				break;

			default:
				cout << "Out of range" << endl;
				break;
		}
		
		if (keyb->cost < bestCost) {
			bestCost = keyb->cost;
			if (nbrList.size() < 3) {
				nbrList.merge(usedNbr);
				usedNbr.clear();
			}
			switch (nbr) {
				case 1:
					stat->swapSt++;
					break;

				case 2:
					stat->spPairSt++;
					break;

				case 3:
					stat->mvContSt++;
					break;

				default:
					cout << "Out of range" << endl;
					break;
			}
		}

		else {
			nbrList.remove(nbr);
			usedNbr.push_back(nbr);
		}
	}

/*	long long testCost = 0;
	testCost = costcalc(data, -2, keyb);
	cout << "\nCusto calculado final (rvnd): " << testCost << endl;
*/

/*	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb[i] = keyb->grid[i];
	}
	
	cout << endl << "\nFinal Solution" << endl;
	printSol(data, keyb, auxKeyb);
	cout << endl;*/

//	cout << "\nFinal Cost(RVND): " << bestCost << endl;
	//cout << "\nSwap(RVND): " << swapcounter << endl;
}

void SFpert1 (Gendata *data, Keyboard *keyb){
	//1.Trocas entre n caracteres aleatórios

	vector <int> auxKeyb;

	list <int> auxCharList;
	vector <int> pertSet;
	list <int>::iterator it;
	
	int limit;
	int pertChars;
	int movChar;
	int temp;
	int char1;
	int char2;
	int firstpos;

	for (int i = 0; i < data->size - 1; i++){
		auxCharList.push_back(i);
	}

	limit = 4;
	pertChars = 2 + rand() % limit;

	//cout << "\nPert chars: " << pertChars << endl; 
	
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

	for(int i = 0; i < pertSet.size() - 1; i++){
		char1 = pertSet[i];
		char2 = pertSet[i + 1];
		
		temp = keyb->assignment[char1];
		keyb->assignment[char1] = keyb->assignment[char2];
		keyb->assignment[char2] = temp;

		temp = keyb->grid[keyb->assignment[char1]];
		keyb->grid[keyb->assignment[char1]] = keyb->grid[keyb->assignment[char2]];
		keyb->grid[keyb->assignment[char2]] = temp;
	}

	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb.push_back(keyb->grid[i]);
	}

	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb[i] = keyb->grid[i];
	}

	keyb->cost = costcalc(data, -2, keyb);

/*	cout << endl << "\nSolucao Perturbada3: " << endl;
	printSol(data, keyb, auxKeyb);

	cout << endl;
	cout << "\nCusto perturbacao: " << keyb->cost << endl;*/
}

void SFpert2 (Gendata *data, Keyboard *keyb){
	//2.Swap entre n pares de caracteres aleatórios

	vector <int> auxKeyb;

	list <int> auxCharList;
	vector <int> pertSet;
	list <int>::iterator it;
	
	int limit;
	int pertPairs;
	int movChar;
	int temp;
	int char1;
	int char2;

	for (int i = 0; i < data->size - 1; i++){
		auxCharList.push_back(i);
	}

	limit = 2;
	pertPairs = 2 + rand() % limit;

	while (pertSet.size() < 2 * pertPairs){
		movChar = rand() % data->size;

		for(it = auxCharList.begin(); it != auxCharList.end(); it++){
			if(movChar == *it){
				pertSet.push_back(*it);
				auxCharList.erase(it);
				break;
			}
		}
	}

	while(!pertSet.empty()){

		char1 = pertSet[0];
		char2 = pertSet[1];
		
		temp = keyb->assignment[char1];
		keyb->assignment[char1] = keyb->assignment[char2];
		keyb->assignment[char2] = temp;

		temp = keyb->grid[keyb->assignment[char1]];
		keyb->grid[keyb->assignment[char1]] = keyb->grid[keyb->assignment[char2]];
		keyb->grid[keyb->assignment[char2]] = temp;

		pertSet.erase(pertSet.begin(), pertSet.begin() + 2);
	}


	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb.push_back(keyb->grid[i]);
	}

	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb[i] = keyb->grid[i];
	}

	keyb->cost = costcalc(data, -2, keyb);

/*	cout << endl << "\nSolucao Perturbada2: " << endl;
	printSol(data, keyb, auxKeyb);

	cout << endl;
	cout << "\nCusto perturbacao2: " << keyb->cost << endl;*/
}

void perturbation (Gendata *data, Keyboard *keyb, int *pertC){

	int pert = 0;
	int pos = 0;

/*	vector <int> auxKeyb;
	
	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb.push_back(keyb->grid[i]);
	}
		*/	
	pert = 1 + rand() % 2;
	//pert = 2;
	
	switch (pert) {
		case 1:
			SFpert1 (data, keyb);
			*pertC = 1;
			break;

		case 2:
			SFpert2 (data, keyb);
			*pertC = 2;
			break;

		default:
			cout << "Out of range" << endl;
			break;
	}
	
	//keyb->cost = costcalc(data, -2, keyb);

/*	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb[i] = keyb->grid[i];
	}
	
	cout << endl << "\nPerturbed solution" << endl;
	printSol(data, keyb, auxKeyb);
	cout << endl;*/

	//cout << "\nFinal Cost(Pert): " << keyb->cost << endl;
}
