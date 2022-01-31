void swapPair (Gendata *data, Keyboard *keyb, Stats *stat){
	double begin;
	double end;

	double elapTm;
	
	begin = cpuTime();

	vector <int> auxKeyb;
	vector <unsigned int> rmvCost;
	vector <unsigned int> rmvCost2;

	SPairs spairs;

	vector <SPairs> vecpairs;

	// vector< pair<int, int> > vPairs;
	// vector< pair<int, int> > hPairs;
	
	// pair<int, int> swapPair;
	// pair<int, int> pair1;
	// pair<int, int> pair2;

	long long iniCost;
	long long testCost;

	long long deltaFi;
	long long deltaFi2;
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

	int temp;
	int pos1, pos2;

	for (int i = 0; i < data->size; i++){
		rmvCost.push_back(0);
		rmvCost2.push_back(0);
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
	
	iniCost = keyb->cost;
	
	removecost (data, rmvCost, keyb);

	for (int i = 0; i < vecpairs.size(); i++){
		
		deltaFi = 0;
		rmv1 = rmvCost[keyb->grid[vecpairs[i].pos]];

		for (int j = i + 1; j < vPairs.size(); j++){
			if (vPairs[j].first == vPairs[i].second){
				continue;
			}
			rmv2 = rmvCost[keyb->grid[vPairs[j].first]];
			
			temp = keyb->assignment[keyb->grid[vPairs[i].first]];
			keyb->assignment[keyb->grid[vPairs[i].first]] = keyb->assignment[keyb->grid[vPairs[j].first]];
			keyb->assignment[keyb->grid[vPairs[j].first]] = temp;

			ins1 = costcalc (data, keyb->grid[vPairs[i].first], keyb);
			ins2 = costcalc (data, keyb->grid[vPairs[j].first], keyb);

			deltaFi = - rmv1 - rmv2 + ins1 + ins2;
			
			removecost (data, rmvCost2, keyb);
			
			rmvp1 = rmvCost2[keyb->grid[vPairs[i].second]];
			rmvp2 = rmvCost2[keyb->grid[vPairs[j].second]];

			temp = keyb->assignment[keyb->grid[vPairs[i].second]];
			keyb->assignment[keyb->grid[vPairs[i].second]] = keyb->assignment[keyb->grid[vPairs[j].second]];
			keyb->assignment[keyb->grid[vPairs[j].second]] = temp;

			insp1 = costcalc (data, keyb->grid[vPairs[i].second], keyb);
			insp2 = costcalc (data, keyb->grid[vPairs[j].second], keyb);

			deltaFi += - rmvp1 - rmvp2 + insp1 + insp2;
			//cout << "\nDelta Fi com segundo swap: " << deltaFi << endl;

			if (deltaFi < 0){
				if (deltaFi < bestDeltaFi){
					bestDeltaFi = deltaFi;
					pos1 = i;
					pos2 = j;
					impv = 1;
					imph = 0;
				}
			}
			deltaFi -= - rmvp1 - rmvp2 + insp1 + insp2;

			temp = keyb->assignment[keyb->grid[vPairs[j].first]];
			keyb->assignment[keyb->grid[vPairs[j].first]] = keyb->assignment[keyb->grid[vPairs[i].first]];
			keyb->assignment[keyb->grid[vPairs[i].first]] = temp;

			temp = keyb->assignment[keyb->grid[vPairs[j].second]];
			keyb->assignment[keyb->grid[vPairs[j].second]] = keyb->assignment[keyb->grid[vPairs[i].second]];
			keyb->assignment[keyb->grid[vPairs[i].second]] = temp;
		}//for j
	}//for i

	for (int i = 0; i < hPairs.size(); i++){
		
		deltaFi = 0;

	 	rmv1 = rmvCost[keyb->grid[hPairs[i].first]];

		for (int j = i + 2; j < hPairs.size(); j++){

			rmv2 = rmvCost[keyb->grid[hPairs[j].first]];
			
			temp = keyb->assignment[keyb->grid[hPairs[i].first]];
			keyb->assignment[keyb->grid[hPairs[i].first]] = keyb->assignment[keyb->grid[hPairs[j].first]];
			keyb->assignment[keyb->grid[hPairs[j].first]] = temp;
			
			ins1 = costcalc (data, keyb->grid[hPairs[i].first], keyb);
			ins2 = costcalc (data, keyb->grid[hPairs[j].first], keyb);

			deltaFi = - rmv1 - rmv2 + ins1 + ins2;
			
			removecost (data, rmvCost2, keyb);
			
			rmvp1 = rmvCost2[keyb->grid[hPairs[i].second]];
			rmvp2 = rmvCost2[keyb->grid[hPairs[j].second]];

			temp = keyb->assignment[keyb->grid[hPairs[i].second]];
			keyb->assignment[keyb->grid[hPairs[i].second]] = keyb->assignment[keyb->grid[hPairs[j].second]];
			keyb->assignment[keyb->grid[hPairs[j].second]] = temp;

			insp1 = costcalc (data, keyb->grid[hPairs[i].second], keyb);
			insp2 = costcalc (data, keyb->grid[hPairs[j].second], keyb);

			deltaFi += - rmvp1 - rmvp2 + insp1 + insp2;

			if (deltaFi < 0){
				if (deltaFi < bestDeltaFi){
					bestDeltaFi = deltaFi;
					pos1 = i;
					pos2 = j;
					impv = 0;
					imph = 1;
				}
			}
			temp = keyb->assignment[keyb->grid[hPairs[j].first]];
			keyb->assignment[keyb->grid[hPairs[j].first]] = keyb->assignment[keyb->grid[hPairs[i].first]];
			keyb->assignment[keyb->grid[hPairs[i].first]] = temp;

			temp = keyb->assignment[keyb->grid[hPairs[j].second]];
			keyb->assignment[keyb->grid[hPairs[j].second]] = keyb->assignment[keyb->grid[hPairs[i].second]];
			keyb->assignment[keyb->grid[hPairs[i].second]] = temp;
		}//for j
	}//for i

	if (impv > 0){
		
		temp = keyb->assignment[keyb->grid[vPairs[pos1].first]];
		keyb->assignment[keyb->grid[vPairs[pos1].first]] = keyb->assignment[keyb->grid[vPairs[pos2].first]];
		keyb->assignment[keyb->grid[vPairs[pos2].first]] = temp;

		temp = keyb->assignment[keyb->grid[vPairs[pos1].second]];
		keyb->assignment[keyb->grid[vPairs[pos1].second]] = keyb->assignment[keyb->grid[vPairs[pos2].second]];
		keyb->assignment[keyb->grid[vPairs[pos2].second]] = temp;

		temp = keyb->grid[vPairs[pos1].first];
		keyb->grid[vPairs[pos1].first] = keyb->grid[vPairs[pos2].first];
		keyb->grid[vPairs[pos2].first] = temp;
		
		temp = keyb->grid[vPairs[pos1].second];
		keyb->grid[vPairs[pos1].second] = keyb->grid[vPairs[pos2].second];
		keyb->grid[vPairs[pos2].second] = temp;
		
		keyb->cost = iniCost + bestDeltaFi;
	}

	else if (imph > 0){

		temp = keyb->assignment[keyb->grid[hPairs[pos1].first]];
		keyb->assignment[keyb->grid[hPairs[pos1].first]] = keyb->assignment[keyb->grid[hPairs[pos2].first]];
		keyb->assignment[keyb->grid[hPairs[pos2].first]] = temp;

		temp = keyb->assignment[keyb->grid[hPairs[pos1].second]];
		keyb->assignment[keyb->grid[hPairs[pos1].second]] = keyb->assignment[keyb->grid[hPairs[pos2].second]];
		keyb->assignment[keyb->grid[hPairs[pos2].second]] = temp;

		temp = keyb->grid[hPairs[pos1].first];
		keyb->grid[hPairs[pos1].first] = keyb->grid[hPairs[pos2].first];
		keyb->grid[hPairs[pos2].first] = temp;
		
		temp = keyb->grid[hPairs[pos1].second];
		keyb->grid[hPairs[pos1].second] = keyb->grid[hPairs[pos2].second];
		keyb->grid[hPairs[pos2].second] = temp;

		keyb->cost = iniCost + bestDeltaFi;
	}
	
	for (int i = 0; i < auxKeyb.size(); i++){
		auxKeyb[i] = keyb->grid[i];
	}

	vPairs.clear();
	hPairs.clear();
	
	cout << "\nNew Cost(Swap Pair): " << keyb->cost << endl;

	testCost = costcalc(data, -2, keyb);
	cout << "\nCusto calculado final sp: " << testCost << endl;
	
	cout<< "\nAssignment SP: " << endl;
	for(int i = 0; i < data->size; i++){
		cout << data->char_list[i] << ": " << keyb->assignment[i] << "  ";
	}
	
	cout << endl << "\nSolucao SP" << endl;
	printSol(data, keyb, auxKeyb);
	cout << endl;

	end = cpuTime();
	elapTm = end - begin;
	
	stat->spPairTime += elapTm;
}