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
				else{
					rmv2 = rmvCost[keyb->grid[vecpairs[j].pos]];

					temp = keyb->assignment[keyb->grid[vecpairs[i].pos]];
					keyb->assignment[keyb->grid[vecpairs[i].pos]] = keyb->assignment[keyb->grid[vecpairs[j].pos]];
					keyb->assignment[keyb->grid[vecpairs[j].pos]] = temp;

					ins1 = costcalc (data, keyb->grid[vecpairs[i].pos], keyb);
					ins2 = costcalc (data, keyb->grid[vecpairs[j].pos], keyb);

					deltaFi = - rmv1 - rmv2 + ins1 + ins2;
					fdeltaFi = deltaFi;
					
					removecost (data, rmvCost2, keyb);
				}
			}

			if (vecpairs[i].vert < 1 || vecpairs[j].vert < 1){
				rmv2 = rmvCost[keyb->grid[vecpairs[j].pos]];

				temp = keyb->assignment[keyb->grid[vecpairs[i].pos]];
				keyb->assignment[keyb->grid[vecpairs[i].pos]] = keyb->assignment[keyb->grid[vecpairs[j].pos]];
				keyb->assignment[keyb->grid[vecpairs[j].pos]] = temp;

				ins1 = costcalc (data, keyb->grid[vecpairs[i].pos], keyb);
				ins2 = costcalc (data, keyb->grid[vecpairs[j].pos], keyb);

				deltaFi = - rmv1 - rmv2 + ins1 + ins2;
				fdeltaFi = deltaFi;
				
				removecost (data, rmvCost2, keyb);
			}
			
			if (vecpairs[i].horiz > 0 && vecpairs[j].horiz > 0){
				if (vecpairs[j].pos != vecpairs[i].hpair){

					rmvp1 = rmvCost2[keyb->grid[vecpairs[i].hpair]];
					rmvp2 = rmvCost2[keyb->grid[vecpairs[j].hpair]];

					temp = keyb->assignment[keyb->grid[vecpairs[i].hpair]];
					keyb->assignment[keyb->grid[vecpairs[i].hpair]] = keyb->assignment[keyb->grid[vecpairs[j].hpair]];
					keyb->assignment[keyb->grid[vecpairs[j].hpair]] = temp;

					insp1 = costcalc (data, keyb->grid[vecpairs[i].hpair], keyb);
					insp2 = costcalc (data, keyb->grid[vecpairs[j].hpair], keyb);

					deltaFi = fdeltaFi - rmvp1 - rmvp2 + insp1 + insp2;

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
				else{
					temp = keyb->assignment[keyb->grid[vecpairs[j].pos]];
					keyb->assignment[keyb->grid[vecpairs[j].pos]] = keyb->assignment[keyb->grid[vecpairs[i].pos]];
					keyb->assignment[keyb->grid[vecpairs[i].pos]] = temp;
				}
			}

			if (vecpairs[i].horiz < 1 || vecpairs[j].horiz < 1){
				temp = keyb->assignment[keyb->grid[vecpairs[j].pos]];
				keyb->assignment[keyb->grid[vecpairs[j].pos]] = keyb->assignment[keyb->grid[vecpairs[i].pos]];
				keyb->assignment[keyb->grid[vecpairs[i].pos]] = temp;
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