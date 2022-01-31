#include "functions.h"
#define ROW 10
#define COL 14
#define  KEYS 140

void readData (int argc, char** argv, Gendata *data, Keyboard *keyb){

	if (argc < 4) {
		cout << "\nMissing Parameters\n";
		cout << " ./exeSFkey [Instance] [Char_list] [Distance_matrix]" << endl;				
		exit(1);
	}																												//Verifica a quantidade de parâmetros passados na hora de executar o programa

	if (argc > 4) {
		cout << "\nToo many parameters\n";
		cout << " ./exeSFkey [Instance] [Char_list] [Distance_matrix]" << endl;
		exit(1);
	}

	string file;
	string aux;
	int size;
	int ksize;

	char *instance;	
 	instance = argv[1];		//O primeiro parâmetro passado é armazenado em 'instance'

	char *charlist;
	charlist = argv[2];		//O segundo parametro é armazenado em 'charlist'

	char *dmatrix;
	dmatrix = argv[3];		//O terceiro parametro é armazenado em 'dmatrix', que é a matriz de distancia

	ifstream in(instance, ios::in);		//Aqui a gente inicializa a leitura do primeiro parametro criando o objeto 'in' 
    
   	if( !in ) {
		cout << "Cannot open file.\n";		//Mensagem de erro caso nao seja possivel inicializar
		exit (1);
	}

	in >> file;
	in >> file;					//Cada linha dessa está lendo o que tiver entre cada espaço. No começo tem 'n = 29', entao sao 3 comandos para chegar até o 29
	in >> size;

	ifstream inn (charlist, ios::in);		//Aqui a gente inicializa a leitura do segundo parametro criando o objeto 'inn' 

	if( !inn ) {
		cout << "Cannot open file.\n";
		exit (1);
	}
	
	ifstream din (dmatrix, ios::in);		//Aqui a gente inicializa a leitura do terceiro parametro criando o objeto 'din' 

	if( !din ) {
		cout << "Cannot open file.\n";
		exit (1);
	}

	din >> file;
	din >> file;
	din >> ksize;

	data->freq_matrix = new long long *[size];			
	for (int i = 0; i < size; i++){
		data->freq_matrix[i] = new long long [size];
	}

	data->char_list = new char [size];		//Inicializações de vetores com alocação dinamica de memoria

	data->b_matrix = new int *[ksize];
	for (int i = 0; i < ksize; i++){
		data->b_matrix[i] = new int [ksize];
	}

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			in >> file;										//Leitura do arquivo
			data->freq_matrix[i][j] = stoi(file);			//Aqui a gente converte de char* para int para armazenar em data->freq_matrix	

		}
	}

	data->size = size;
	keyb->ksize = ksize;

	for (int i = 0; i < size; i++){
		inn >> data->char_list[i];
	}

	// for (int i = 0; i < size; i++){
	// 	cout << data->char_list[i]<<" ";	
	// }
	// cout << endl;

	for (int i = 0; i < ksize; i++){
		for (int j = 0; j < ksize; j++){
			din >> file;
			data->b_matrix[i][j] = stoi(file);
		}
	}
}

void initSol (Gendata *data, Keyboard *keyb){
	
	vector <int> aux_grid;
	vector <int> assigned_char;
	list <int> aux_charl;

	long long cost = 0;
	long long temp_cost /*= 0*/;
	long long min_cost, min_cost1 /*= LONG_MAX*/;
	long long temp_cost1;
	
	bool assign = 0;
	
	int optkey, optletter;
	int aux_sum, sum = 0;
	int center;
	int center_key = 0;
	int count;
	
	list<int>::iterator it;
	list<int>::iterator it2;

	if (keyb->ksize < 40){
		keyb->kcols = 6;
		keyb->krows = 5;
	}

	else{
		keyb->kcols = COL;
		keyb->krows = ROW;
	}

	center_key = (keyb->kcols * ceil((keyb->krows)/2)) + ceil((keyb->kcols)/2) - 1;

	keyb->grid = new int [keyb->ksize];
	
	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = -1;
	}
		
	for (int i = 0; i < keyb->ksize; i++){
		aux_grid.push_back(-1);
	}

	for (int i = 0; i < data->size; i++){
		aux_charl.push_back(i);
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}
		
	srand(time(NULL));
	
	center = data->size - 1;
	//cout << "\nCenter Key: " << data->char_list[center] << endl;
	aux_grid[center_key] = center;
	keyb->assignment[center] = center_key;
	assigned_char.push_back(center);
	aux_charl.remove(center);

	int rcand = 0;
	int key = 0;
	int h = 0;
	int inichar;

	if (keyb->ksize < 40){
		inichar = 2;
	}
	else{
		inichar = 5;
	}

	while (aux_charl.size() > data->size - inichar){
 
		rcand = rand() % aux_charl.size();
		
		for (it = aux_charl.begin(); it != aux_charl.end(); it++){
			if(rcand == *it){

				switch(h){
					case 0:
						key = center_key - keyb->kcols;
						break;
					case 1:
						key = center_key - 1;
						break;
					case 2:
						key = center_key + 1;
						break;
					case 3:
						key = center_key + keyb->kcols;
						break;
					default:
						key = 0;
						break;
				}

				keyb->assignment[*it] = key;	
				aux_grid[key] = *it;
				assigned_char.push_back(*it);
				aux_charl.erase(it);
				h++;
				break;
			}
		}
	}

	while (!aux_charl.empty()){
		
		optkey = 0;
		min_cost = LONG_MAX;

		for (it = aux_charl.begin(); it != aux_charl.end(); it++){

			for (int j = 0; j < keyb->ksize; j++){
				if (aux_grid[j] == -1){
					temp_cost = 0;	
					
					for (int k = 0; k < assigned_char.size(); k++){
						temp_cost += (data->freq_matrix[*it][assigned_char[k]] * data->b_matrix[j][keyb->assignment[assigned_char[k]]]);
					}	//for 'k'

					temp_cost = temp_cost / 2;

					if (temp_cost < min_cost){
						min_cost = temp_cost;
						optkey = j;
						it2 = it;
						//cout << "\nMin Cost: " << min_cost << "\nChosen char: " << data->char_list[*it] << "\nChosen key: " << j << "\n";
					}
				}
			}	//for 'j'

		}	//for 'i'
		
		keyb->assignment[*it2] = optkey;	
		aux_grid[optkey] = *it2;
		assigned_char.push_back(*it2);
		aux_charl.erase(it2);
	}

//Print Solution
	// cout << "Initial Solution: " << endl;
	
	// count = 0;
	// for (int i = 0; i < keyb->krows; i++){
	// 	for (int j = 0; j < keyb->kcols; j++){
	// 		if (aux_grid[count] != -1)
	// 			cout << setw(3) << data->char_list[aux_grid[count]];
	// 		else
	// 			cout<< setw(3) << "*";
	// 		count++;

	// 	}
	// 	cout<<endl;
	// }

	cost = costcalc(data, -2, keyb);
	keyb->cost = cost;

	for (int i = 0; i < keyb->ksize; i++)
		keyb->grid[i] = aux_grid[i];

	//cout << "Initial Solution Cost: " << keyb->cost << endl;
}

long long costcalc (Gendata *data, int k, Keyboard *keyb){

	long long costc = 0;
	int pos = 0;
	int next = 0;

	if ( k == -2){		//CUSTO TOTAL
		for (int i = 0; i < data->size; i++){

			pos = keyb->assignment[i];

			for (int j = 0; j < data->size; j++){
				if (j != i){
					next = keyb->assignment[j];
					costc += ( data->freq_matrix[i][j] * data->b_matrix[pos][next]);
				}
			}//for 'j'		
		}// for 'i'
		costc = costc / 2;
	}//if

	else if (k == -1){
		costc = 0;
	}
	
	else{		//CUSTO PARA UM
		pos = keyb->assignment[k];	

		for (int j = 0; j < data->size; j++){
			if (j != k){
				next = keyb->assignment[j];
				costc += ( data->freq_matrix[k][j] * data->b_matrix[pos][next]);
			}
		}//for 'j'	
	}

	return costc;
}

void removecost (Gendata *data, vector<long long>& rmvcost, Keyboard *keyb){

	int pos = 0;
	int next = 0;
	
	for (int i = 0; i < rmvcost.size(); i++){
		rmvcost[i] = 0;
	}

	for (int i = 0; i < data->size; i++){
		pos = keyb->assignment[i];
		for (int j = 0; j < data->size; j++){
			if (j != i){
				next = keyb->assignment[j];
				rmvcost[i] += ( data->freq_matrix[i][j] * data->b_matrix[pos][next] );
			}
		}//for 'j'	
	}//for 'i'
}

void contourSet (Gendata *data, Keyboard *keyb, list<int>& contourPos, vector<int>& aux_keyb, int k){
	
	int element = 0;
	int row = 0;
	int col = 0;
	
	list <int>::iterator it;

	if (k < 0){
		for (int i = 0; i < data->size; i++){

			row = floor(keyb->assignment[i] / keyb->kcols);
			col = keyb->assignment[i] % keyb->kcols;
			
			if (row - 1 >= 0){
				if (col - 1 >= 0){
					if (aux_keyb[keyb->assignment[i] - keyb->kcols - 1] == -1){
						contourPos.push_back(keyb->assignment[i] - keyb->kcols - 1);
					}
				}

				if (aux_keyb[keyb->assignment[i] - keyb->kcols] == -1)
					contourPos.push_back(keyb->assignment[i] - keyb->kcols);

				if (col + 1 < keyb->kcols){
					if (aux_keyb[keyb->assignment[i] - keyb->kcols + 1] == -1){
						contourPos.push_back(keyb->assignment[i] - keyb->kcols + 1);
					}
				}
			}

			if (col - 1 >= 0){
				if (aux_keyb[keyb->assignment[i] - 1] == -1){
					contourPos.push_back(keyb->assignment[i] - 1);
				}	
			}

			if (col + 1 < keyb->kcols){
				if (aux_keyb[keyb->assignment[i] + 1] == -1){
					contourPos.push_back(keyb->assignment[i] + 1);
				}
			}

			if (row + 1 < keyb->krows){
				if (col - 1 >= 0){
					if (aux_keyb[keyb->assignment[i] + keyb->kcols - 1] == -1){
						contourPos.push_back(keyb->assignment[i] + keyb->kcols - 1);
					}					
				}
				
				if (aux_keyb[keyb->assignment[i] + keyb->kcols] == -1)
					contourPos.push_back(keyb->assignment[i] + keyb->kcols);

				if (col + 1 < keyb->kcols){
					if (aux_keyb[keyb->assignment[i] + keyb->kcols + 1] == -1){
						contourPos.push_back(keyb->assignment[i] + keyb->kcols + 1);
					}
				}				
			}
		}
	
		contourPos.sort();
		//sort(contourPos.begin(), contourPos.end());
		//contourPos.erase(unique(contourPos.begin(), contourPos.end()), contourPos.end());
	}

	else{
		contourPos.clear();
		
		row = floor(keyb->assignment[k] / keyb->kcols);
		col = keyb->assignment[k] % keyb->kcols;

		if (row - 1 >= 0){
			if (col - 1 >= 0){
				if (aux_keyb[keyb->assignment[k] - keyb->kcols - 1] == -1){
					contourPos.push_back(keyb->assignment[k] - keyb->kcols - 1);
				}
			}

			if (aux_keyb[keyb->assignment[k] - keyb->kcols] == -1)
				contourPos.push_back(keyb->assignment[k] - keyb->kcols);

			if (col + 1 < keyb->kcols){
				if (aux_keyb[keyb->assignment[k] - keyb->kcols + 1] == -1){
					contourPos.push_back(keyb->assignment[k] - keyb->kcols + 1);
				}
			}
		}

		if (col - 1 >= 0){
			if (aux_keyb[keyb->assignment[k] - 1] == -1){
				contourPos.push_back(keyb->assignment[k] - 1);
			}	
		}
		
		if (col + 1 < keyb->kcols){
			if (aux_keyb[keyb->assignment[k] + 1] == -1){
				contourPos.push_back(keyb->assignment[k] + 1);
			}
		}

		if (row + 1 < keyb->krows){
			if (col - 1 >= 0){
				if (aux_keyb[keyb->assignment[k] + keyb->kcols - 1] == -1){
					contourPos.push_back(keyb->assignment[k] + keyb->kcols - 1);
				}					
			}
			
			if (aux_keyb[keyb->assignment[k] + keyb->kcols] == -1)
				contourPos.push_back(keyb->assignment[k] + keyb->kcols);

			if (col + 1 < keyb->kcols){
				if (aux_keyb[keyb->assignment[k] + keyb->kcols + 1] == -1){
					contourPos.push_back(keyb->assignment[k] + keyb->kcols + 1);
				}
			}				
		}
	}
}

void rmvContour (Keyboard *keyb, list<int>& contourPos, vector<int>& aux_keyb, int k){

	int element = 0;
	int row = 0;
	int col = 0;
	
	list <int>::iterator it;

	row = floor(k / keyb->kcols);
	col = k % keyb->kcols;

	if (row - 1 >= 0){
		if (col - 1 >= 0){
			if (aux_keyb[k - keyb->kcols - 1] == -1){
				for(it = contourPos.begin(); it != contourPos.end(); it++){
					if(*it == k - keyb->kcols - 1){
						contourPos.erase(it);
						break;
					}
				}
			}
		}

		if (aux_keyb[k - keyb->kcols] == -1){
			for(it = contourPos.begin(); it != contourPos.end(); it++){
				if(*it == k - keyb->kcols){
					contourPos.erase(it);
					break;
				}
			}
		}

		if (col + 1 < keyb->kcols){
			if (aux_keyb[k - keyb->kcols + 1] == -1){
				for(it = contourPos.begin(); it != contourPos.end(); it++){
					if(*it == k - keyb->kcols + 1){
						contourPos.erase(it);
						break;
					}
				}
			}
		}
	}

	if (col - 1 >= 0){
		if (aux_keyb[k - 1] == -1){
			for(it = contourPos.begin(); it != contourPos.end(); it++){
				if(*it == k - 1){
					contourPos.erase(it);
					break;
				}
			}
		}	
	}
	
	if (col + 1 < keyb->kcols){
		if (aux_keyb[k + 1] == -1){
			for(it = contourPos.begin(); it != contourPos.end(); it++){
				if(*it == k + 1){
					contourPos.erase(it);
					break;
				}
			}
		}
	}

	if (row + 1 < keyb->krows){
		if (col - 1 >= 0){
			if (aux_keyb[k + keyb->kcols - 1] == -1){
				for(it = contourPos.begin(); it != contourPos.end(); it++){
					if(*it == k + keyb->kcols - 1){
						contourPos.erase(it);
						break;
					}
				}
			}					
		}
		
		if (aux_keyb[k + keyb->kcols] == -1){
			for(it = contourPos.begin(); it != contourPos.end(); it++){
				if(*it == k + keyb->kcols){
					contourPos.erase(it);
					break;
				}
			}
		}

		if (col + 1 < keyb->kcols){
			if (aux_keyb[k + keyb->kcols + 1] == -1){
				for(it = contourPos.begin(); it != contourPos.end(); it++){
					if(*it == k + keyb->kcols + 1){
						contourPos.erase(it);
						break;
					}
				}
			}
		}				
	}
}

void printSol (Gendata *data, Keyboard *keyb, vector<int>& auxKeyb){
	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			if (auxKeyb[count] != -1)
				cout << setw(3) << data->char_list[auxKeyb[count]];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}
}

void printSolNum (Gendata *data, Keyboard *keyb, vector<int>& auxKeyb){
	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			if (auxKeyb[count] != -1)
				cout << setw(3) << auxKeyb[count];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}
}
bool verifyContour (Gendata *data, Keyboard *keyb, list<int>& contourPos, vector<int>& aux_keyb, int k){
	
	bool contour = 0;
	int row;
	int col;
	
	row = floor(k / keyb->kcols);
	col = k % keyb->kcols;

	if (row - 1 >= 0){
		if (col - 1 >= 0){
			if (aux_keyb[k - keyb->kcols - 1] != -1){
				contour = 1;
			}
		}

		if (aux_keyb[k - keyb->kcols] != -1){
			contour = 1;
		}

		if (col + 1 < keyb->kcols){
			if (aux_keyb[k - keyb->kcols + 1] != -1){
				contour = 1;
			}
		}
	}

	if (col - 1 >= 0){
		if (aux_keyb[k - 1] != -1){
			contour = 1;
		}	
	}
	
	if (col + 1 < keyb->kcols){
		if (aux_keyb[k + 1] != -1){
			contour = 1;
		}
	}

	if (row + 1 < keyb->krows){
		if (col - 1 >= 0){
			if (aux_keyb[k + keyb->kcols - 1] != -1){
				contour = 1;
			}					
		}
		
		if (aux_keyb[k + keyb->kcols] != -1)
			contour = 1;

		if (col + 1 < keyb->kcols){
			if (aux_keyb[k + keyb->kcols + 1] != -1){
				contour = 1;
			}
		}				
	}
	return contour;
}

void initStat (Stats *stat){

	stat->swapSt = 0;
	stat->spPairSt = 0;
	stat->mvContSt = 0;

	stat->pert1St = 0;
	stat->pert2St = 0;
	stat->pert3St = 0;
	stat->pert4St = 0;
}

void initTime (Stats *stat){

	stat->swapTime = 0;
	stat->spPairTime = 0;
	stat->mvContTime = 0;
}

void hashValues (Gendata *data, vector<int>& valCharList){

	bool prime;
	int i = 2;

	while (valCharList.size() < data->size){
		prime = true;
		for (int j = 2; j * j <= i; j++){
			if (i % j == 0){
				prime = false;
				break;
			}
		}
		if (prime){
			valCharList.push_back(i);
		}
		i++;
	}

	// cout << "\nLista de valores: ";
	// for (int i = 0; i < valCharList.size(); i++){
	// 	cout << valCharList[i] << " ";
	// }
	// cout << endl;
}

void addRowPool (Gendata *data, Keyboard *keyb, Strows *strow, vector<Strows>& rowPool, vector<int>& valCharList, vector< vector<int> >& sizeRows, vector< vector<int> >& charPoolPos){
	
	int elem1;
	int elem2;
	int centerRow = -1;

	long long rCost;
	
	int pos1;
	int pos2;

	vector <int> assignRows;
	vector <int> auxVec;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			elem1 = i * keyb->kcols + j;
			if (keyb->grid[elem1] > -1){
				assignRows.push_back(i);
				break;
			}
		}
	}

	// for (int i = 0; i < assignRows.size(); i++){
	// 	for (int j = 0; j < keyb->kcols; j++){
	// 		elem1 = assignRows[i] * keyb->kcols + j;
	// 		if (keyb->grid[elem1] == data->size - 1){
	// 			centerRow = i;
	// 		}
	// 	}
	// }

	for (int i = 0; i < keyb->kcols; i++){
		sizeRows.push_back(auxVec);
	}
	
	for (int i = 0; i < assignRows.size(); i++){
		// if (i < centerRow){
		// 	strow->pos = centerRow - i; 
		// }
		// else if (i > centerRow){
		// 	strow->pos = i - centerRow; 
		// }
		// else if (i == centerRow){
		// 	strow->pos = 0;
		// }
		strow->pos = i;
		strow->asgnchars = 0;
		strow->row.clear();
		strow->rowHash = 1;
		strow->rowCost = 0;
		rCost = 0;

		for (int j = 0; j < keyb->kcols; j++){
			elem1 = assignRows[i] * keyb->kcols + j;
			if (keyb->grid[elem1] > -1){
				strow->fchar = keyb->grid[elem1];
				break;
			}

		}
		
		for (int j = keyb->kcols - 1; j >= 0; j--){
			elem1 = assignRows[i] * keyb->kcols + j;
			if (keyb->grid[elem1] > -1){
				if (keyb->grid[elem1] == strow->fchar){
					strow->lchar = -1;
				}
				else{
					strow->lchar = keyb->grid[elem1];
				}
				break;
			}
		}

		for (int k = 0; k < keyb->kcols; k++){
			elem2 = assignRows[i] * keyb->kcols + k;
			if (keyb->grid[elem2] > -1){
				strow->asgnchars++;
				strow->row.push_back(keyb->grid[elem2]);
				strow->rowHash *= valCharList[keyb->grid[elem2]];
				//charRows[keyb->grid[elem2]].push_back(strow->pos);

			}
		}

		sizeRows[strow->asgnchars].push_back(strow->pos);
		//sizeRows[strow->asgnchars].push_back(strow->pos * 10);

		for (int k = 0; k < strow->row.size() - 1; k++){
			for (int l = k + 1; l < strow->row.size(); l++){
				pos1 = keyb->assignment[strow->row[k]];
				pos2 = keyb->assignment[strow->row[l]];
				rCost = data->freq_matrix[strow->row[k]][strow->row[l]]*data->b_matrix[pos1][pos2];
				strow->rowCost += rCost;
			}
		}

		if (verifyRow (strow, rowPool) == 1){
			rowPool.push_back(*strow);
			for (int k = 0; k < strow->row.size(); k++){
				charPoolPos[strow->row[k]].push_back(rowPool.size() - 1);
			}
		}
	}
}

bool verifyRow (Strows *strow, vector<Strows>& rowPool){
	bool newRow = 0;

	if (rowPool.size() > 0){
		for (int i = 0; i < rowPool.size(); i++){
			if (strow->rowHash == rowPool[i].rowHash){
				if (strow->asgnchars == rowPool[i].asgnchars){
					if (strow->fchar == rowPool[i].fchar){
						if (strow->lchar == rowPool[i].lchar){
							newRow = 0;
							break;
						}
						else{
							newRow = 1;		
						}
					}
					else{
						newRow = 1;
					}
				}
				else{
					newRow = 1;
				}
			}
			else{
				newRow = 1;
			}
		}
	}
	else{
		newRow = 1;
	}

	return newRow;
}

void makeCoexMatrix (Gendata *data, vector<int>& valCharList, vector<Strows>& rowPool, vector< vector<int> >& coexMatrix){

	Strows currRow;
	long n = rowPool.size();

	vector <int> coexMatRow;

	for (int i = 0; i < n; i++){
		coexMatRow.clear();
		for (int j = 0; j < n; j++){
			coexMatRow.push_back(1);
		}
		coexMatrix.push_back(coexMatRow);
	}

	for (int i = 0; i < rowPool.size(); i++){
		for (int j = 0; j < rowPool.size(); j++){
			for (int k = 0; k < valCharList.size(); k++){
				if (rowPool[i].rowHash % valCharList[k] == 0 && rowPool[j].rowHash % valCharList[k] == 0){
					coexMatrix[i][j] = 0;
				}
			}
		}	
	}

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (i == j){
				coexMatrix[i][j] = 0;
			}
		}
	}

	// cout << "N: " << rowPool.size() << "\nMatrix: " << endl;
	// for (int i = 0; i < n; i++){
	// 	for (int j = 0; j < n; j++){
	// 		cout << coexMatrix[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;
}

void rowCostMatrix (Gendata *data, Keyboard *keyb, vector<Strows>& rowPool, vector< vector< vector<long long> > >& costMatrix, vector< vector<int> >& coexMatrix, int numRows){

	long long rowCost = 0;
	long long indCost = 0;
	int schar1;
	int schar2;
	int spos1;
	int spos2;
	int inipos2;
	int posDif;
	int solSize = numRows;

	vector < vector <long long> > costMat2d;
	vector <long long> costMatRow;

	vector <int> posvec1;
	vector <int> posvec2;


	for (int i = 0; i < rowPool.size(); i++){
		for (int j = 0; j < rowPool.size(); j++){
			for (int k = 0; k < solSize; k++){
				costMatRow.push_back(0);
			}
			costMat2d.push_back(costMatRow);
		}
		costMatrix.push_back(costMat2d);
	}

	for (int i = 0; i < rowPool.size(); i++){
		for (int j = 0; j < rowPool.size(); j++){
			if (i != j){
				rowCost = 0;
				posvec1.clear();
				posvec2.clear();

				if (rowPool[i].row.size() > rowPool[j].row.size()){
					inipos2 = ceil((rowPool[i].row.size() - rowPool[j].row.size())/2);
					
					for(int r = 0; r < rowPool[i].row.size(); r++){
						posvec1.push_back(r);
						if(posvec2.size() > 0){
							if (posvec2.size() < rowPool[j].row.size()){
								posvec2.push_back(r);
							}
						}
						else if (r == inipos2){
							posvec2.push_back(r);							
						}
					}
				}
				else if (rowPool[i].row.size() < rowPool[j].row.size()){
					inipos2 = ceil((rowPool[j].row.size() - rowPool[i].row.size())/2);

					for(int r = 0; r < rowPool[j].row.size(); r++){
						posvec2.push_back(r);
						if(posvec1.size() > 0){
							if (posvec1.size() < rowPool[i].row.size()){
								posvec1.push_back(r);
							}
						}
						else if (r == inipos2){
							posvec1.push_back(r);
						}
					}
				}
				
				else{
					for(int r = 0; r < rowPool[i].row.size(); r++){
						posvec1.push_back(r);
						posvec2.push_back(r);
					}
				}

				if (coexMatrix[i][j] < 1){
					continue;
				}
				for (int l = 0; l < rowPool[i].row.size(); l++){
					for (int m = 0; m < rowPool[j].row.size(); m++){
						schar1 = rowPool[i].row[l];
						schar2 = rowPool[j].row[m];

						for (int k = 1; k < solSize; k++){
							spos1 = posvec1[l];
							spos2 = posvec2[m] + (keyb->kcols * k);
							
							rowCost = data->freq_matrix[schar1][schar2]*data->b_matrix[spos1][spos2];
							costMatrix[i][j][k] += rowCost;
						}
					}
				}
			}
		}
	}
}

void makeYMatrix (Gendata *data, Keyboard *keyb, vector<Strows>& rowPool, vector< vector<int> >& yMat, vector< vector<int> >& sizeRows, int numRows, int centerRow){

			// y[i][sizeRows[rowPool[i].asgnchars][l]].setName(var);
			// model.add(y[i][sizeRows[rowPool[i].asgnchars][l]]);	
	vector <int> vec ;
	int cDist;

	for (int i = 0; i < rowPool.size(); i++){
		vec.clear();
		for (int j = 0; j < numRows; j++){
			vec.push_back(0);
		}
		yMat.push_back(vec);
	}

	for (int i = 1; i < sizeRows.size(); i++){
		int nMax = sizeRows[i].size();
		for (int j = 0; j < nMax; j++){
			if (sizeRows[i].size() < 1){
				continue;
			}
			if (centerRow > sizeRows[i][j]){

				cDist = centerRow - sizeRows[i][j];
				if (centerRow + cDist <= numRows){
					sizeRows[i].push_back(centerRow + cDist);
				}
			}
			else if (centerRow < sizeRows[i][j]){
				cDist = sizeRows[i][j] - centerRow;
				if (centerRow - cDist >= 0){
					sizeRows[i].push_back(centerRow - cDist);
				}
			}
		}
		sort(sizeRows[i].begin(), sizeRows[i].end() );
		sizeRows[i].erase( unique( sizeRows[i].begin(), sizeRows[i].end() ), sizeRows[i].end() );

		for (int l = 0; l < sizeRows[i].size(); l++){
			if (sizeRows[i][l] > numRows - 1){
				sizeRows[i].erase(sizeRows[i].begin() + l);
			}
		}	
	}

	for (int i = 0; i < rowPool.size(); i++){
		for (int j = 0; j < sizeRows[rowPool[i].asgnchars].size(); j++){
			yMat[i][sizeRows[rowPool[i].asgnchars][j]] = 1;
		}
	}
	// cout << "\nNew Mat: " << endl;

	// for (int i = 0; i < yMat.size(); i++){
	// 	for (int j = 0; j < yMat[i].size(); j++){
	// 		cout << yMat[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
}

