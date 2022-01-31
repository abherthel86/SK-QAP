void SFpert1 (Gendata *data, Keyboard *keyb){
	//1.permutacao entre duas linhas alocadas
	vector <int> assignrows;
	vector <int> auxKeyb;

	int r1;
	int r2;
	int index;
	int temp;
	int pos;
	int pos1;
	int pos2;
	int element1;
	int element2;
	int centerKey;

	centerKey = keyb->assignment[data->size - 1];

	for(int i = 0; i < keyb->krows; i++){
		if(i == floor(centerKey/keyb->kcols)){
			continue;
		}
		for(int j = 0; j < keyb->kcols; j++){
			pos = i * keyb->kcols + j;
			if (keyb->grid[pos] > -1){
				assignrows.push_back(i);
				break;
			}
		}
	}
	
	index = rand() % assignrows.size();

	for(int i = 0; i < assignrows.size(); i++){
		if(index == i){
			r1 = assignrows[i];
			assignrows.erase(assignrows.begin() + index);
			break;
		}
	}

	index = rand() % assignrows.size();

	for(int i = 0; i < assignrows.size(); i++){
		if(index == i){
			r2 = assignrows[i];
			assignrows.erase(assignrows.begin() + index);
			break;
		}
	}

	for(int i = 0; i < keyb->kcols; i++){
		pos1 = r1 * keyb->kcols + i;
		pos2 = r2 * keyb->kcols + i;

		element1 = keyb->grid[pos1]; 
		element2 = keyb->grid[pos2];

		if(element1 < 0){
			if(element2 < 0){
				continue;
			}
			else{
				keyb->assignment[element2] = pos1;

				temp = keyb->grid[pos1];
				keyb->grid[pos1] = keyb->grid[pos2];
				keyb->grid[pos2] = temp;
			}
		}
		else if(element1 > -1){
			if(element2 < 0){
				keyb->assignment[element1] = pos2;

				temp = keyb->grid[pos1];
				keyb->grid[pos1] = keyb->grid[pos2];
				keyb->grid[pos2] = temp;
			}
			else{
				temp = keyb->assignment[element1];
				keyb->assignment[element1] = keyb->assignment[element2];
				keyb->assignment[element2] = temp;

				temp = keyb->grid[pos1];
				keyb->grid[pos1] = keyb->grid[pos2];
				keyb->grid[pos2] = temp;
			}
		}
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
	cout << "\nCusto perturbacao: " << keyb->cost << endl;*/
}

void SFpert2 (Gendata *data, Keyboard *keyb){
	//2.permutacao entre duas colunas
	vector <int> assigncols;
	vector <int> auxKeyb;

	int c1;
	int c2;
	int index;
	int temp;
	int pos;
	int pos1;
	int pos2;
	int element1;
	int element2;
	int centerKey;

	centerKey = keyb->assignment[data->size - 1];

	for(int i = 0; i < keyb->kcols; i++){
		if(i == centerKey % keyb->kcols){
			continue;
		}
		for(int j = 0; j < keyb->krows; j++){
			pos = j * keyb->kcols + i;
			if (keyb->grid[pos] > -1){
				assigncols.push_back(i);
				break;
			}
		}
	}

	index = rand() % assigncols.size();

	for(int i = 0; i < assigncols.size(); i++){
		if(index == i){
			c1 = assigncols[i];
			assigncols.erase(assigncols.begin() + index);
			break;
		}
	}
	
	index = rand() % assigncols.size();

	for(int i = 0; i < assigncols.size(); i++){
		if(index == i){
			c2 = assigncols[i];
			assigncols.erase(assigncols.begin() + index);
			break;
		}
	}

	for(int i = 0; i < keyb->krows; i++){
		pos1 = i * keyb->kcols + c1;
		pos2 = i * keyb->kcols + c2;

		element1 = keyb->grid[pos1]; 
		element2 = keyb->grid[pos2];

		if(element1 < 0){
			if(element2 < 0){
				continue;
			}
			else{
				keyb->assignment[element2] = pos1;

				temp = keyb->grid[pos1];
				keyb->grid[pos1] = keyb->grid[pos2];
				keyb->grid[pos2] = temp;
			}
		}
		else if(element1 > -1){
			if(element2 < 0){
				keyb->assignment[element1] = pos2;

				temp = keyb->grid[pos1];
				keyb->grid[pos1] = keyb->grid[pos2];
				keyb->grid[pos2] = temp;
			}
			else{
				temp = keyb->assignment[element1];
				keyb->assignment[element1] = keyb->assignment[element2];
				keyb->assignment[element2] = temp;

				temp = keyb->grid[pos1];
				keyb->grid[pos1] = keyb->grid[pos2];
				keyb->grid[pos2] = temp;
			}
		}
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
void SFpert3 (Gendata *data, Keyboard *keyb){
	//3.caracteres alocados nos arredores do caractere central.
	vector <int> movSet;
	vector <int> auxKeyb;

	int centerKey;
	int pos;
	int pos1;
	int pos2;
	int char1;
	int char2;
	int temp;
	int limit;

	centerKey = keyb->assignment[data->size - 1];

	pos = centerKey - keyb->kcols - 1;
	movSet.push_back(pos);

	pos = centerKey - keyb->kcols;
	movSet.push_back(pos);

	pos = centerKey - keyb->kcols + 1;
	movSet.push_back(pos);

	pos = centerKey - 1;
	movSet.push_back(pos);

	pos = centerKey + 1;
	movSet.push_back(pos);

	pos = centerKey + keyb->kcols - 1;
	movSet.push_back(pos);	

	pos = centerKey + keyb->kcols;
	movSet.push_back(pos);	

	pos = centerKey + keyb->kcols + 1;
	movSet.push_back(pos);

	limit = floor(movSet.size()/2);
 
	for (int i = 0; i < floor(movSet.size()/2); i++){
		pos1 = movSet[i];
		pos2 = movSet[i + limit];
		char1 = keyb->grid[pos1];
		char2 = keyb->grid[pos2];

		if (keyb->grid[pos1] < 0){
			if(keyb->grid[pos2] < 0){
				continue;
			}
			else{
				keyb->assignment[char2] = pos1;

				temp = keyb->grid[pos1];
				keyb->grid[pos1] = keyb->grid[pos2];
				keyb->grid[pos2] = temp;
			}
		}
		else if (keyb->grid[pos1] > -1){
			if (keyb->grid[pos2] < 0){
				keyb->assignment[char1] = pos2;

				temp = keyb->grid[pos1];
				keyb->grid[pos1] = keyb->grid[pos2];
				keyb->grid[pos2] = temp;
			}
			else{
				temp = keyb->assignment[char1];
				keyb->assignment[char1] = keyb->assignment[char2];
				keyb->assignment[char2] = temp;

				temp = keyb->grid[pos1];
				keyb->grid[pos1] = keyb->grid[pos2];
				keyb->grid[pos2] = temp;
			}
		}
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