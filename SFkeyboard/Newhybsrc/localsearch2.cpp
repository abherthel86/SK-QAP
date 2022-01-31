#include "localsearch2.h"
#include "cpuTime.h"
#include <ctime>
#define KEYS 140
#define ROW 10
#define COL 14

void swap (Gendata *data, Keyboard *keyb, Stats *stat){

// 	double begin;
// 	double end;

// 	double elapTm;
	
// 	begin = cpuTime();

// 	vector <int> auxKeyb;
// 	vector <long long> rmvCost;
// 	//list <int> emptyPos;

// 	list<int>::iterator it;

// 	long long iniCost;
// 	long long deltaFi;
// 	long long bestDeltaFi = 0;
// 	long long ins1;
// 	long long ins2;
	
// 	long long rmv1;
// 	long long rmv2;

// 	bool imp = 0;
// 	//bool imp1 = 0;

// 	int pos1 = 0;
// 	int pos2 = 0;
// 	int char1;
// 	int char2;
// 	int temp;

// 	for (int i = 0; i < data->size; i++){
// 		rmvCost.push_back(0);
// 	}
	
// 	for (int i = 0; i < keyb->ksize; i++){
// 		auxKeyb.push_back(keyb->grid[i]);
// 	}

// 	iniCost = keyb->cost;
	
// 	removecost (data, rmvCost, keyb);

// 	cout << "\nRemove Cost Vec: ";
// 	for (int i = 0; i < rmvCost.size(); i++){
// 		cout << rmvCost[i] << " ";
// 	}
// 	cout << endl;
	
// 	for (int i = 0; i < data->size - 5; i++){

// 		deltaFi = 0;
// 		rmv1 = rmvCost[i];
		
// 		for (int j = 0; j < data->size - 5; j++){
// 			if (j != i){
// 				rmv2 = rmvCost[j];

// 				temp = keyb->assignment[i];
// 				keyb->assignment[i] = keyb->assignment[j];
// 				keyb->assignment[j] = temp;
			
// 				ins1 = costcalc (data, i, keyb);
// 				ins2 = costcalc (data, j, keyb); 

// 				deltaFi = - rmv1 - rmv2 + ins1 + ins2;

// 				if (deltaFi < 0){
// 					if (deltaFi < bestDeltaFi){
// 						bestDeltaFi = deltaFi;
// 						char1 = i;
// 						char2 = j;
// 						pos1 = keyb->assignment[i];
// 						pos2 = keyb->assignment[j];
// 						imp = 1;
// 						//imp1 = 0;
// 					}
// 				}				
// 				keyb->assignment[j] = keyb->assignment[i];
// 				keyb->assignment[i] = temp;
// 			}
// 		}
// 	}//for i

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

// //	cout << "New Cost(Swap): " << keyb->cost << endl;

// //	long long testCost;
// //	testCost = costcalc(data, -2, keyb);
// //	cout << "\nCusto calculado final (swap): " << testCost << endl;

// 	keyb->cost = costcalc(data, -2, keyb);

// 	printSol(data, keyb, auxKeyb);
// 	cout << endl;

// 	end = cpuTime();
// 	elapTm = end - begin;

// 	stat->swapTime += elapTm;


	double begin;
	double end;

	double elapTm;
	
	begin = cpuTime();

	vector <int> auxKeyb;
	//list <int> emptyPos;

	list<int>::iterator it;

	long long iniCost;
	long long newCost;
	long long deltaFi;
	long long bestDeltaFi = 0;
	
	bool imp = 0;
	//bool imp1 = 0;

	int pos1 = 0;
	int pos2 = 0;
	int char1;
	int char2;
	int temp;

	
	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb.push_back(keyb->grid[i]);
	}

	iniCost = keyb->cost;

	for (int i = 0; i < data->size - 5; i++){

		deltaFi = 0;
		
		for (int j = 0; j < data->size - 5; j++){
			if (j != i){

				temp = keyb->assignment[i];
				keyb->assignment[i] = keyb->assignment[j];
				keyb->assignment[j] = temp;
				
				newCost = costcalc(data, -2, keyb);

				deltaFi = newCost - iniCost;

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
	}//for i

	if (imp > 0){
		keyb->assignment[char1] = pos1;
		keyb->assignment[char2] = pos2;

		temp = auxKeyb[pos1];
		auxKeyb[pos1] = auxKeyb[pos2];
		auxKeyb[pos2] = temp;

		keyb->cost = iniCost + bestDeltaFi;
	}

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = auxKeyb[i];
	}

	//cout << "New Cost(Swap): " << keyb->cost << endl;

	// long long testCost;
	// testCost = costcalc(data, -2, keyb);
	// cout << "\nCusto calculado final (swap): " << testCost << endl;

	//keyb->cost = costcalc(data, -2, keyb);

	//printSol(data, keyb, auxKeyb);
	//cout << endl;

	//getchar();

	end = cpuTime();
	elapTm = end - begin;

	stat->swapTime += elapTm;
}


void swapPair (Gendata *data, Keyboard *keyb, Stats *stat){ //nova versão (com equação de Stutzle e Dorigo)

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
	//long long newCost = numeric_limits<long long>::max();
	long long newCost;
	long long constVal;
	//long long testCost;

	long long fdeltaFi;
	long long sdeltaFi;
	long long deltaFi;
	long long bestDeltaFi = 0;

	long long f_Cost = 0;
	long long s_Cost = 0;

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

	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb.push_back(0);
	}

	for (int i = 0; i < keyb->ksize - 10; i++){
		if (keyb->grid[i] > -1){
			spairs.pos = i;
			spairs.vert = 0;
			spairs.horiz = 0;

			if (floor((i + keyb->kcols) / keyb->kcols) < keyb->krows){
				if (keyb->grid[i + keyb->kcols] > -1 && i + keyb->kcols < 30){

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

	iniCost = keyb->cost;
	
	for (int i = 0; i < vecpairs.size(); i++){
		
		deltaFi = 0;

		for (int j = i + 1; j < vecpairs.size(); j++){
			if (vecpairs[i].vert > 0 && vecpairs[j].vert > 0){
				if (vecpairs[j].pos != vecpairs[i].vpair){


					temp = keyb->assignment[keyb->grid[vecpairs[i].pos]];
					keyb->assignment[keyb->grid[vecpairs[i].pos]] = keyb->assignment[keyb->grid[vecpairs[j].pos]];
					keyb->assignment[keyb->grid[vecpairs[j].pos]] = temp;
					
					temp = keyb->assignment[keyb->grid[vecpairs[i].vpair]];
					keyb->assignment[keyb->grid[vecpairs[i].vpair]] = keyb->assignment[keyb->grid[vecpairs[j].vpair]];
					keyb->assignment[keyb->grid[vecpairs[j].vpair]] = temp;
	
					newCost = costcalc(data, -2, keyb);

					deltaFi = newCost - iniCost;

					if (deltaFi < 0){
						if (deltaFi < bestDeltaFi){
							bestDeltaFi = deltaFi;
							pos1 = i;
							pos2 = j;
							impv = 1;
							imph = 0;
						}
					}

					temp = keyb->assignment[keyb->grid[vecpairs[j].pos]];
					keyb->assignment[keyb->grid[vecpairs[j].pos]] = keyb->assignment[keyb->grid[vecpairs[i].pos]];
					keyb->assignment[keyb->grid[vecpairs[i].pos]] = temp;

					temp = keyb->assignment[keyb->grid[vecpairs[j].vpair]];
					keyb->assignment[keyb->grid[vecpairs[j].vpair]] = keyb->assignment[keyb->grid[vecpairs[i].vpair]];
					keyb->assignment[keyb->grid[vecpairs[i].vpair]] = temp;
				}
			}

			if (vecpairs[i].horiz > 0 && vecpairs[j].horiz > 0){
				if (vecpairs[j].pos != vecpairs[i].hpair){

					temp = keyb->assignment[keyb->grid[vecpairs[i].pos]];
					keyb->assignment[keyb->grid[vecpairs[i].pos]] = keyb->assignment[keyb->grid[vecpairs[j].pos]];
					keyb->assignment[keyb->grid[vecpairs[j].pos]] = temp;

					temp = keyb->assignment[keyb->grid[vecpairs[i].hpair]];
					keyb->assignment[keyb->grid[vecpairs[i].hpair]] = keyb->assignment[keyb->grid[vecpairs[j].hpair]];
					keyb->assignment[keyb->grid[vecpairs[j].hpair]] = temp;

					newCost = costcalc(data, -2, keyb);

					deltaFi = newCost - iniCost;

					if (deltaFi < 0){
						if (deltaFi < bestDeltaFi){
							bestDeltaFi = deltaFi;
							pos1 = i;
							pos2 = j;
							impv = 0;
							imph = 1;
						}
					}

					temp = keyb->assignment[keyb->grid[vecpairs[j].pos]];
					keyb->assignment[keyb->grid[vecpairs[j].pos]] = keyb->assignment[keyb->grid[vecpairs[i].pos]];
					keyb->assignment[keyb->grid[vecpairs[i].pos]] = temp;

					temp = keyb->assignment[keyb->grid[vecpairs[j].hpair]];
					keyb->assignment[keyb->grid[vecpairs[j].hpair]] = keyb->assignment[keyb->grid[vecpairs[i].hpair]];
					keyb->assignment[keyb->grid[vecpairs[i].hpair]] = temp;
				}
			}
		}//for j
	}//for i

	if (impv > 0){
		temp = keyb->assignment[keyb->grid[vecpairs[pos1].pos]];
		keyb->assignment[keyb->grid[vecpairs[pos1].pos]] = keyb->assignment[keyb->grid[vecpairs[pos2].pos]];
		keyb->assignment[keyb->grid[vecpairs[pos2].pos]] = temp;

		temp = keyb->assignment[keyb->grid[vecpairs[pos1].vpair]];
		keyb->assignment[keyb->grid[vecpairs[pos1].vpair]] = keyb->assignment[keyb->grid[vecpairs[pos2].vpair]];
		keyb->assignment[keyb->grid[vecpairs[pos2].vpair]] = temp;

		temp = keyb->grid[vecpairs[pos1].pos];
		keyb->grid[vecpairs[pos1].pos] = keyb->grid[vecpairs[pos2].pos];
		keyb->grid[vecpairs[pos2].pos] = temp;
		
		temp = keyb->grid[vecpairs[pos1].vpair];
		keyb->grid[vecpairs[pos1].vpair] = keyb->grid[vecpairs[pos2].vpair];
		keyb->grid[vecpairs[pos2].vpair] = temp;
		
		keyb->cost = iniCost + bestDeltaFi;
	}

	else if (imph > 0){
		temp = keyb->assignment[keyb->grid[vecpairs[pos1].pos]];
		keyb->assignment[keyb->grid[vecpairs[pos1].pos]] = keyb->assignment[keyb->grid[vecpairs[pos2].pos]];
		keyb->assignment[keyb->grid[vecpairs[pos2].pos]] = temp;

		temp = keyb->assignment[keyb->grid[vecpairs[pos1].hpair]];
		keyb->assignment[keyb->grid[vecpairs[pos1].hpair]] = keyb->assignment[keyb->grid[vecpairs[pos2].hpair]];
		keyb->assignment[keyb->grid[vecpairs[pos2].hpair]] = temp;

		temp = keyb->grid[vecpairs[pos1].pos];
		keyb->grid[vecpairs[pos1].pos] = keyb->grid[vecpairs[pos2].pos];
		keyb->grid[vecpairs[pos2].pos] = temp;
		
		temp = keyb->grid[vecpairs[pos1].hpair];
		keyb->grid[vecpairs[pos1].hpair] = keyb->grid[vecpairs[pos2].hpair];
		keyb->grid[vecpairs[pos2].hpair] = temp;
		
		keyb->cost = iniCost + bestDeltaFi;
	}
	
	for (int i = 0; i < auxKeyb.size(); i++){
		auxKeyb[i] = keyb->grid[i];
	}

	vecpairs.clear();

	//cout << "\nNew Cost(2pswap): " << keyb->cost << endl;

	// long long testCost;
	// testCost = costcalc(data, -2, keyb);
	// cout << "Custo calculado final (2pswap): " << testCost << endl;
	// getchar();
	//keyb->cost = costcalc(data, -2, keyb);
	//printSol(data, keyb, auxKeyb);
	//cout << endl;

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
	vector <long long> rmvCost;

	list <int> contourPos;	
	list <int> newContour;
	list <int>::iterator it;

	long long iniCost;
	long long newCost = 0;
	long long bCost = 0;
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
	//newCost = iniCost;

	for (int i = 0; i < data->size - 5; i++){

		// f_imp = 0;
		// s_imp = 0;
		// ns_imp = 0;
		imp = 0;		
		bestDeltaFi = 0;
		deltaFi = 0;
		bCost = 0;

		for (it = contourPos.begin(); it!= contourPos.end(); it++){

			temp = keyb->assignment[i];
			keyb->assignment[i] = *it;
			
			bCost = costcalc(data, -2, keyb);

			deltaFi = bCost - iniCost;

			if (deltaFi < 0){
				if (deltaFi < bestDeltaFi){
					bestDeltaFi = deltaFi; 
					pos1 = *it;
					pos2 = temp;
					charac = i;
					imp = 1;

					// if (imp > 0){
					// 	s_imp = 1;
					// }
					// if (imp < 1){
					// 	imp = 1;
					// 	f_imp = 1;
					// }
				}
			}			
			keyb->assignment[i] = temp;
		}//for 'it'
		
		// if (newContour.size() > 0){
		// 	deltaFi = 0;

		// 	posFi = keyb->assignment[f_char];
		// 	keyb->assignment[f_char] = f_pos1;

		// 	removecost (data, rmvCost, keyb);

		// 	rmv = rmvCost[i];

		// 	for (it = newContour.begin(); it != newContour.end(); it++){
			
		// 		temp = keyb->assignment[i];
		// 		keyb->assignment[i] = *it;
							
		// 		bCost = costcalc(data, -2, keyb);

		// 		deltaFi = bCost - iniCost;
				
		// 		if (deltaFi < 0){
		// 			if (deltaFi < bestDeltaFi){
		// 				bestDeltaFi = deltaFi;
		// 				ns_pos1 = *it;
		// 				ns_pos2 = temp;
		// 				ns_char = i;

		// 				ns_imp = 1;
		// 				f_imp = 0;
		// 				s_imp = 0;
		// 			}			
		// 		}
		// 		keyb->assignment[i] = temp;
		// 	}
		// 	keyb->assignment[f_char] = posFi;
		// }

		// if(f_imp > 0){
		// 	f_pos1 = pos1;
		// 	f_pos2 = pos2;
		// 	f_char = charac;

		// 	auxKeyb[f_pos1] = f_char;
		// 	auxKeyb[f_pos2] = -1;

		// 	f_Cost = iniCost + bestDeltaFi;
		// 	newCost = f_Cost;

		// 	contourPos.remove(f_pos1);

		// 	keyb->assignment[i] = f_pos1;

		// 	contourSet(data, keyb, newContour, auxKeyb, f_char);
			
		// 	keyb->assignment[i] = f_pos2;
			
		// 	if(verifyContour(data, keyb, contourPos, auxKeyb, f_pos2) == 1){
		// 		newContour.push_back(f_pos2);
		// 	}

		// 	newContour.sort();

		// 	contourInter.clear();
		// 	newContour.erase(unique(newContour.begin(), newContour.end()), newContour.end());
		// 	set_intersection (contourPos.begin(), contourPos.end(), newContour.begin(), newContour.end(), back_inserter(contourInter) );
		// 	newContour.erase (set_difference (newContour.begin(), newContour.end(), contourInter.begin(), contourInter.end(), newContour.begin() ), newContour.end() );
			
		// 	rmvContour(keyb, contourPos, auxKeyb, f_pos2);
		// }

		if(imp > 0){
			f_pos1 = pos1;
			f_pos2 = pos2;
			f_char = charac;

			auxKeyb[f_pos1] = f_char;
			auxKeyb[f_pos2] = -1;

			f_Cost = iniCost + bestDeltaFi;
			newCost = f_Cost;

			contourPos.remove(f_pos1);

			//keyb->assignment[i] = f_pos1;

			//contourSet(data, keyb, newContour, auxKeyb, f_char);
			
			//keyb->assignment[i] = f_pos2;
			
			if(verifyContour(data, keyb, contourPos, auxKeyb, f_pos2) == 1){
				contourPos.push_back(f_pos2);
			}

			contourPos.sort();
			contourPos.erase(unique(contourPos.begin(), contourPos.end()), contourPos.end());
			// contourInter.clear();
			// newContour.erase(unique(newContour.begin(), newContour.end()), newContour.end());
			// set_intersection (contourPos.begin(), contourPos.end(), newContour.begin(), newContour.end(), back_inserter(contourInter) );
			// newContour.erase (set_difference (newContour.begin(), newContour.end(), contourInter.begin(), contourInter.end(), newContour.begin() ), newContour.end() );
			
			//rmvContour(keyb, contourPos, auxKeyb, f_pos2);

			keyb->assignment[f_char] = f_pos1;
			iniCost = newCost;
		}

		for (int i = 0; i < keyb->ksize; i++){
			keyb->grid[i] = auxKeyb[i];
		}
	}//for i
	// 	else if(ns_imp > 0){
			
	// 		keyb->assignment[f_char] = f_pos1;

	// 		auxKeyb[ns_pos1] = ns_char;
	// 		auxKeyb[ns_pos2] = -1;

	// 		iniCost = f_Cost;
	// 		f_Cost = iniCost + bestDeltaFi;
	// 		newCost = f_Cost;

	// 		contourPos.merge(newContour);
	// 		contourPos.sort();
	// 		contourPos.remove(ns_pos1);

	// 		keyb->assignment[i] = ns_pos1;

	// 		contourSet(data, keyb, newContour, auxKeyb, ns_char);
			
	// 		keyb->assignment[i] = ns_pos2;
			
	// 		if(verifyContour(data, keyb, contourPos, auxKeyb, ns_pos2) == 1){
	// 			newContour.push_back(ns_pos2);
	// 		}

	// 		newContour.sort();
	// 		contourInter.clear();
	// 		newContour.erase(unique(newContour.begin(), newContour.end()), newContour.end());
	// 		set_intersection (contourPos.begin(), contourPos.end(), newContour.begin(), newContour.end(), back_inserter(contourInter) );
	// 		newContour.erase (set_difference (newContour.begin(), newContour.end(), contourInter.begin(), contourInter.end(), newContour.begin() ), newContour.end() );
			
	// 		rmvContour(keyb, contourPos, auxKeyb, ns_pos2);
			
	// 		f_pos1 = ns_pos1;
	// 		f_pos2 = ns_pos2;
	// 		f_char = ns_char;
	// 		cout << "\nb" << endl;
	// 		getchar();
	// 	}

	// 	else if(s_imp > 0){
	// 		s_pos1 = pos1;
	// 		s_pos2 = pos2;
	// 		s_char = charac;
			
	// 		keyb->assignment[f_char] = f_pos1;

	// 		auxKeyb[s_pos1] = s_char;
	// 		auxKeyb[s_pos2] = -1;

	// 		iniCost = f_Cost;
	// 		s_Cost = f_Cost + bestDeltaFi + ((data->freq_matrix[f_char][s_char])*(data->b_matrix[f_pos1][s_pos1] - data->b_matrix[f_pos2][s_pos1] + data->b_matrix[f_pos2][s_pos2] - data->b_matrix[f_pos1][s_pos2]));
	// 		f_Cost = s_Cost;
	// 		newCost = s_Cost;
	// 		s_Cost = 0;

	// 		contourPos.merge(newContour);
	// 		contourPos.sort();
	// 		contourPos.remove(s_pos1);
		
	// 		keyb->assignment[i] = s_pos1;

	// 		contourSet(data, keyb, newContour, auxKeyb, s_char);
			
	// 		keyb->assignment[i] = s_pos2;

	// 		if(verifyContour(data, keyb, contourPos, auxKeyb, s_pos2) == 1){
	// 			newContour.push_back(s_pos2);
	// 		}

	// 		newContour.sort();
	// 		contourInter.clear();
	// 		newContour.erase(unique(newContour.begin(), newContour.end()), newContour.end());
	// 		set_intersection (contourPos.begin(), contourPos.end(), newContour.begin(), newContour.end(), back_inserter(contourInter) );
	// 		newContour.erase (set_difference (newContour.begin(), newContour.end(), contourInter.begin(), contourInter.end(), newContour.begin() ), newContour.end() );
			
	// 		rmvContour(keyb, contourPos, auxKeyb, s_pos2);

	// 		f_pos1 = s_pos1;
	// 		f_pos2 = s_pos2;
	// 		f_char = s_char;
	// 		cout << "\nc" << endl;
	// 		getchar();
	// 	}
	// }//for 'i'



	keyb->cost = iniCost;

	// cout << "\nNew Cost(mc): " << keyb->cost << endl;
	
	// long long testCost;
	// testCost = costcalc(data, -2, keyb);
	// cout << "\nCusto real final (mc): " << testCost << endl;
	//getchar();

	// cout<< "\n4Assignment (final): " << endl;
	// for(int i = 0; i < data->size; i++){
	// 	cout << data->char_list[i] << ": " << keyb->assignment[i] << "  ";
	// }
	// cout << endl;
	// cout << "\nSolution from MC: " << endl;
	// printSol(data, keyb, auxKeyb);

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
		//nbr = 1;
		//nbr = 2;
		//nbr = 3;
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
				//cout << "\nSWAP" << keyb->cost << endl;
				break;

			case 2:
				swapPair (data, keyb, stat);
				//cout << "\n2PSWAP: " << keyb->cost << endl;
				break;

			case 3:
				moveContour (data, keyb, stat);
				//cout << "\nMC: " << keyb->cost << endl;				
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
	

	//cout << "\nFinal Cost(RVND): " << bestCost << endl;
	// long long testCost = 0;
	// testCost = costcalc(data, -2, keyb);
	// cout << "\nCusto calculado final (rvnd): " << testCost << endl;
	// getchar();


	// for (int i = 0; i < keyb->ksize; i++){
	// 	auxKeyb[i] = keyb->grid[i];
	// }
	
	// cout << endl << "\nFinal Solution" << endl;
	// printSol(data, keyb, auxKeyb);
	// cout << endl;

	
}

void SFpert1 (Gendata *data, Keyboard *keyb){
	//1.Ejection chain

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

	for (int i = 0; i < data->size -5; i++){
		auxCharList.push_back(i);
	}

	limit = 3;																	//mudança de 4 para 3
	pertChars = 3 + rand() % limit;												// mudança de 2 para 3

	//cout << "\nP1 Pert chars: " << pertChars << endl; 
	
	while (pertSet.size() < pertChars){ 										
		movChar = rand() % (data->size -6);
		for(it = auxCharList.begin(); it != auxCharList.end(); it++){
			if(movChar == *it){
				pertSet.push_back(*it);
				auxCharList.erase(it);
				break;
			}
		}
	}
	//cout << "\nP1 Pert Set: " << pertSet.size() << endl;

	for (int i = 0; i < pertSet.size() - 1; i++){
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

	for (int i = 0; i < data->size - 5; i++){
		auxCharList.push_back(i);
	}

	limit = 2;
	pertPairs = 2 + rand() % limit;
	//cout << "\nP2 Pert Pairs: " << pertPairs << endl;

	while (pertSet.size() < 2 * pertPairs){
		movChar = rand() % (data->size - 6);

		for(it = auxCharList.begin(); it != auxCharList.end(); it++){
			if(movChar == *it){
				pertSet.push_back(*it);
				auxCharList.erase(it);
				break;
			}
		}
	}
	//cout << "\nP2 Pert Set: " << pertSet.size() << endl;

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

	pert = 1 + rand() % 2;

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
}
