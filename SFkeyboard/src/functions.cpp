#include "functions.h"
#define ROW 10
#define COL 14
#define  KEYS 140


void readData (int argc, char** argv, Gendata *data, Keyboard *keyb, long long *bks){

	if (argc < 5) {
		cout << "\nMissing Parameters\n";
		cout << " ./exeSFkey [Instance] [Char_list] [Distance_matrix]" << endl;				
		exit(1);
	}																												//Verifica a quantidade de parâmetros passados na hora de executar o programa

	if (argc > 5) {
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

	char *bestks;
	bestks = argv[4];

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

	ifstream bksin (bestks, ios::in);		//Aqui a gente inicializa a leitura do quarto parametro criando o objeto 'bksin' 

	if( !bksin ) {
		cout << "Cannot open file.\n";
		exit (1);
	}

	bksin >> *bks;

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
	
	//vector <int> aux_grid;
	vector <int> assigned_char;
	list <int> aux_charl;
	vector <int> auxKeyb;
	
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
		keyb->kcols = 10;
		keyb->krows = 3;
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
		auxKeyb.push_back(0);
	}

	for (int i = 0; i < data->size; i++){
		aux_charl.push_back(i);
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}
		
	//srand(time(NULL));
	
	center = data->size - 1;
	//cout << "\nCenter Key: " << data->char_list[center] << endl;
	keyb->grid[center_key] = center;
	//aux_grid[center_key] = center;
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
				//cout << "Char: " << data->char_list[*it] << endl;
				
				keyb->assignment[*it] = key;
				keyb->grid[key] = *it;	
				//aux_grid[key] = *it;
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
				//if(aux_grid[j] == -1){
				if (keyb->grid[j] < 0){
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
		keyb->grid[optkey] = *it2;
		//aux_grid[optkey] = *it2;
		assigned_char.push_back(*it2);
		aux_charl.erase(it2);
	}

	for (int i = 0; i < auxKeyb.size(); i++){
		auxKeyb[i] = keyb->grid[i];
	}

//Print Solution

	// cout << "\nInitial Solution: " << endl;

	// printSol(data, keyb, auxKeyb);

	// cout << endl;
	
	cost = costcalc(data, -2, keyb);
	keyb->cost = cost;

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

void printSolHex (Gendata *data, Keyboard *keyb, vector<int>& auxKeyb){
	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		int index = i%2;
		if (index > 0){
			cout << setw(2) << " ";
		}
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
	int counter;

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

	for (int i = 0; i < keyb->kcols; i++){
		sizeRows.push_back(auxVec);
	}
	
	for (int i = 0; i < assignRows.size(); i++){

		strow->pos = i;
		strow->asgnchars = 0;
		strow->row.clear();
		strow->posiVec.clear();
		strow->rowHash = 1;
		strow->posiHash = 1;
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
				strow->posiVec.push_back(k);
				strow->asgnchars++;
				strow->row.push_back(keyb->grid[elem2]);
				strow->rowHash *= valCharList[keyb->grid[elem2]];
				strow->posiHash *= valCharList[k];
				//charRows[keyb->grid[elem2]].push_back(strow->pos);

			}
		}

		sizeRows[strow->asgnchars].push_back(strow->pos);
		//sizeRows[strow->asgnchars].push_back(strow->pos * 10);

		for (int k = 0; k < strow->row.size() - 1; k++){
			for (int l = k + 1; l < strow->row.size(); l++){
				pos1 = strow->posiVec[k];
				pos2 = strow->posiVec[l];
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
	bool newRow = 1;

	if (rowPool.size() > 0){
		for (int i = 0; i < rowPool.size(); i++){
			if ((strow->rowHash == rowPool[i].rowHash) && (strow->posiHash == rowPool[i].posiHash) && (strow->fchar == rowPool[i].fchar) && (strow->lchar == rowPool[i].lchar)){
				newRow = 0;
			}
		}
	}

	return newRow;
}

void makeCoexMatrix (Gendata *data, vector<int>& valCharList, vector<Strows>& rowPool, vector< vector<int> >& coexMatrix){

	Strows currRow;
	long n = rowPool.size();

	vector <int> coexMatRow;

	for (int i = 0; i < n; i++){
		coexMatRow.push_back(1);
	}

	for (int i = 0; i < n; i++){
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
	int rowDif = 0;

	vector < vector <long long> > costMat2d;
	vector <long long> costMatRow;

	vector <int> posvec1;
	vector <int> posvec2;


	for (int k = 0; k < solSize; k++){
		costMatRow.push_back(0);
	}
	for (int j = 0; j < rowPool.size(); j++){
		costMat2d.push_back(costMatRow);
	}
	for (int i = 0; i < rowPool.size(); i++){
		costMatrix.push_back(costMat2d);
	}

	for (int i = 0; i < rowPool.size(); i++){
		for (int j = i+1; j < rowPool.size(); j++){
			//if (i != j){
				rowCost = 0;

				if (coexMatrix[i][j] < 1){
					continue;
				}
				for (int k = 1; k < solSize; k++){
					rowDif = keyb->kcols * k;
					for (int l = 0; l < rowPool[i].row.size(); l++){
						for (int m = 0; m < rowPool[j].row.size(); m++){
							schar1 = rowPool[i].row[l];
							schar2 = rowPool[j].row[m];

							spos1 = rowPool[i].posiVec[l];
							spos2 = rowPool[j].posiVec[m] + rowDif;
							//cout << "\npos1: " << spos1 << " pos2: " << spos2;
							//cout << " char1: " << data->char_list[schar1] << " char2: " << data->char_list[schar2] << " FMat: " << data->freq_matrix[schar1][schar2] << " bMat: " << data->b_matrix[spos1][spos2];
							rowCost = data->freq_matrix[schar1][schar2]*data->b_matrix[spos1][spos2];
							costMatrix[i][j][k] += rowCost;
							costMatrix[j][i][k] += rowCost;
						}
					}
				}
			//}
		}
	}
	// cout << "\nCost Matrix" << endl;
	// for (int k = 0; k < solSize; k++){
	// 	cout << "k = " << k << endl;
	// 	for (int i = 0; i < costMatrix.size(); i++){
	// 		for (int j = 0; j < costMatrix[i].size(); j++){
	// 			cout << setw(15) << std::left << costMatrix[i][j][k] << " ";
	// 		}
	// 		cout << endl;
	// 	}
	// }
}

void makeYMatrix (Gendata *data, Keyboard *keyb, vector<Strows>& rowPool, vector< vector<int> >& yMat, vector< vector<int> >& sizeRows, int numRows){

	vector<int> vec ;
	int rpos;
	int centerRow;
	int centerRow2;

	for (int j = 0; j < numRows; j++){
		vec.push_back(0);
	}

	for (int i = 0; i < rowPool.size(); i++){
		yMat.push_back(vec);
	}
	
	centerRow = floor(numRows/2);
	//centerRow2 = centerRow - 1;
	for (int i = 1; i < sizeRows.size(); i++){
		int nMax = sizeRows[i].size();
		for (int j = 0; j < nMax; j++){
			if (sizeRows[i].size() < 1){
				continue;
			}
			else {
				sizeRows[i].push_back(numRows - sizeRows[i][j] - 1);
			}
		}
		sort(sizeRows[i].begin(), sizeRows[i].end() );
		sizeRows[i].erase( unique( sizeRows[i].begin(), sizeRows[i].end() ), sizeRows[i].end() );
	}
	// for (int i = 1; i < sizeRows.size(); i++){
	// 	int nMax = sizeRows[i].size();
	// 	for (int j = 0; j < nMax; j++){
	// 		if (sizeRows[i].size() < 1){
	// 			continue;
	// 		}
	// 		if (centerRow > sizeRows[i][j]){
	// 			cDist = centerRow - sizeRows[i][j];
	// 			if (centerRow + cDist <= numRows){
	// 				sizeRows[i].push_back(centerRow + cDist);
	// 			}
	// 		}
	// 		else if (centerRow < sizeRows[i][j]){
	// 			cDist = sizeRows[i][j] - centerRow;
	// 			if (centerRow - cDist >= 0){
	// 				sizeRows[i].push_back(centerRow - cDist);
	// 			}
	// 		}
	// 	}



	// 	for (int l = 0; l < sizeRows[i].size(); l++){
	// 		if (sizeRows[i][l] > numRows - 1){
	// 			sizeRows[i].erase(sizeRows[i].begin() + l);
	// 		}
	// 	}	
	// }

	for (int i = 0; i < rowPool.size(); i++){
		for (int j = 0; j < sizeRows[rowPool[i].asgnchars].size(); j++){
			yMat[i][sizeRows[rowPool[i].asgnchars][j]] = 1;
		}
	}

	// cout << "\nY Mat: " << endl;

	// for (int i = 0; i < yMat.size(); i++){
	// 	for (int j = 0; j < yMat[i].size(); j++){
	// 		cout << yMat[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
}

void addBestSol (Gendata *data, Keyboard *keyb, Strows *strow, vector<Strows>& rowPool, vector<int>& valCharList, vector< vector<int> >& sizeRows, vector< vector<int> >& charPoolPos){
	int elem1;
	int elem2;
	int centerRow = -1;

	long long rCost;
	
	int pos1;
	int pos2;
	int counter;

	vector <int> assignRows;
	vector <int> auxVec;
	//vector <int> keyPos;

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
		strow->posiVec.clear();
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
				strow->posiVec.push_back(k);
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
				pos1 = strow->posiVec[k];
				pos2 = strow->posiVec[l];
				rCost = data->freq_matrix[strow->row[k]][strow->row[l]]*data->b_matrix[pos1][pos2];
				strow->rowCost += rCost;
			}
		}

		rowPool.push_back(*strow);
		for (int k = 0; k < strow->row.size(); k++){
			charPoolPos[strow->row[k]].push_back(rowPool.size() - 1);
		}
	}	
}

void makeNewBMat (Gendata *data, Keyboard *keyb, vector < vector < vector < vector <int> > > >& newBMatrix){
	
	int bij = 0;
	int element;
	double maxShift = 20;
	double fpos = 1;
	vector <double> rowShift;
	vector <int> v1;
	vector < vector <int> > v2;
	vector < vector < vector <int> > > v3;

	for (int i = 0; i <= maxShift; i++){
		rowShift.push_back(double(i*(1/maxShift)));
	} 

	// cout << "\nShifts: ";
	// for (int i = 0; i < rowShift.size(); i++){
	// 	cout << rowShift[i] << " ";
	// }

	cout << endl;
	for (int i = 0; i < rowShift.size(); i++){
		v1.push_back(0);
	}
	for (int i = 0; i < rowShift.size(); i++){
		v2.push_back(v1);
	}
	for(int i = 0; i < KEYS; i++){
		v3.push_back(v2);
	}
	for(int i = 0; i < KEYS; i++){
		newBMatrix.push_back(v3);
	}

	for (int i = 0; i < KEYS; i++){
		for (int j = 0; j < KEYS; j++){
			for (int k = 0; k < rowShift.size(); k++){
				for (int l = 0; l < rowShift.size(); l++){
					//if(floor(i/COL) != floor(j/COL)){
							//floor((1000/4.9)*(trunc(log2((trunc(sqrt(pow((floor(9/cols)-floor(64/cols)),2) + pow((((9%cols)+0)-((64%cols)+0)),2))*100)/100)+1)*1000)/1000))
						bij = floor((1000/4.9)*(floorf(log2((floorf(sqrt(pow((floor(i/COL)-floor(j/COL)),2) + pow((((i%COL)+rowShift[k])-((j%COL)+rowShift[l])),2))*1000.00)/1000.00)+1)*1000)/1000));
						newBMatrix[i][j][k][l] = bij;
						//cout << "\nTeste2: " << bij << endl;
						//break;
					//}
					// else{
					// 	bij = floor((1000/4.9)*(roundf(log2(sqrt(pow((floor(i/COL)-floor(j/COL)),2) + pow(((i%COL)-(j%COL)),2))+1) )*100)/100 );
					// 	newBMatrix[i][j][k][l] = bij;
					// }
				}
			}
		}
	}

	//cout << "\nTeste: " << newBMatrix[1][3][0][10];
}

void printShiftedSol (Gendata *data, Keyboard *keyb, vector<int>& auxKeyb){
	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			if (i == 3 && j == 0){
				if (auxKeyb[count] != -1)
					cout << setw(5.5) << data->char_list[auxKeyb[count]];
				else{
					cout<< setw(5.5) << "*";
				}
				count++;
			}
			else{
				if (auxKeyb[count] != -1)
					cout << setw(5) << data->char_list[auxKeyb[count]];
				else{
					cout<< setw(5) << "*";
				}
				count++;
			}


		}
		cout << endl;
	}
}

void shiftSol (Gendata *data, Keyboard *keyb, vector < vector < vector < vector <int> > > >& newBMatrix, vector <stShRow>& vecShSol, stShRow *shRow, vector <int>& occRows, vector <double>& shifts){

	long long shCost = 0;
	long long shCost2 = 0;
	long long rCost;
	long long rlCost;

	long long bestShCost = keyb->cost;
	long long bestGlobalShCost = numeric_limits<long long>::max();
	long long currRelCost;
	long long imp;

 	int elem1;
 	int pos1;
 	int pos2;
	int count = 0;
	int bestk = 0;
	int bestl = 0;
	int counter = 0;

	vector <double> rowShift;
	vector <long> rowCost;
	occRows.clear();

	vecShSol.clear();
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			elem1 = i * keyb->kcols + j;
			if (keyb->grid[elem1] > -1){
				occRows.push_back(i);
				break;
			}
		}
	}
	
	for (int i = 0; i < occRows.size(); i++){
		for (int j = 0; j < keyb->kcols; j++){
			elem1 = occRows[i] * keyb->kcols + j;
			//shSol.push_back(keyb->grid[elem1]);
			if(keyb->grid[elem1] > -1){
				shRow->shiftRow.push_back(keyb->grid[elem1]);
				shRow->posRow.push_back(elem1);
			}
		}
		shRow->rowCost = 0;
		shRow->shift = 0;
		vecShSol.push_back(*shRow);
		shRow->shiftRow.clear();
		shRow->posRow.clear();
	}
//Talvez nao precise do row Cost
	for (int i = 0; i < vecShSol.size(); i++){
		rCost = 0;
		for (int j = 0; j < vecShSol[i].shiftRow.size(); j++){
			for (int k = 0; k < vecShSol[i].shiftRow.size(); k++){
				if(j != k){
					pos1 = vecShSol[i].posRow[j];
					pos2 = vecShSol[i].posRow[k];
					rCost = data->freq_matrix[vecShSol[i].shiftRow[j]][vecShSol[i].shiftRow[k]]*data->b_matrix[pos1][pos2];
					vecShSol[i].rowCost += rCost;	
				}
			}
		}
		//cout << "\nCost of Row " << i << ": " << vecShSol[i].rowCost;
	}

	long long relatCost;
	for (int i = 0; i < vecShSol.size(); i++){
		relatCost = 0;
		for (int j = 0; j < vecShSol.size(); j++){
			rlCost = 0;
			if (i != j){
				for (int k = 0; k < vecShSol[i].shiftRow.size(); k++){
					for (int l = 0; l < vecShSol[j].shiftRow.size(); l++){
						pos1 = vecShSol[i].posRow[k];
						pos2 = vecShSol[j].posRow[l];
						//cout << "\nFreq between " << data->char_list[vecShSol[i].shiftRow[k]] << " and " << data->char_list[vecShSol[j].shiftRow[l]] << " pos1: " << pos1 << " pos2: " << pos2;
						rlCost += data->freq_matrix[vecShSol[i].shiftRow[k]][vecShSol[j].shiftRow[l]]*data->b_matrix[pos1][pos2];
						
					}
				}
			}
			relatCost += rlCost;
			vecShSol[i].twoRowCost.push_back(rlCost);
			//cout << "\nCost between " << i << " and " << j << ": " << rlCost;
		}
		vecShSol[i].relCost = relatCost;
		//cout << "\nRelative cost of " << i << ": " << relatCost;
	}
	cout << endl;

	// for (int i = 0; i < vecShSol.size(); i++){
	// 	shCost = 0;
	// 	for (int s = 0; s < shifts.size(); s++){
	// 		vecShSol[i].shift = shifts[s];
	// 	// 	cout << "\nShift: " << shifts[s];

	// 		for (int j = 0; j < vecShSol.size(); j++){
	// 			currRelCost = 0;
	// 			if(i != j){
	// 				for (int z = 0; z < shifts.size(); z++){
	// 					for (int k = 0; k < vecShSol[i].shiftRow.size(); k++){
	// 						for (int l = 0; l < vecShSol[j].shiftRow.size(); l++){
	// 							//cout << "\nFreq: " << data->char_list[vecShSol[i].shiftRow[k]] << " " << data->char_list[vecShSol[j].shiftRow[l]] << ": " << data->freq_matrix[vecShSol[i].shiftRow[k]][vecShSol[j].shiftRow[l]];
	// 							//cout << "\nBMatrix (antes): " << vecShSol[i].posRow[k] << " " << vecShSol[j].posRow[l] << ": " << newBMatrix[vecShSol[i].posRow[k]][vecShSol[j].posRow[l]][0][vecShSol[j].shift]<< endl;
	// 							//cout << "\nBMatrix: " << vecShSol[i].posRow[k] << " " << vecShSol[j].posRow[l] << ": " << newBMatrix[vecShSol[i].posRow[k]][vecShSol[j].posRow[l]][s][vecShSol[j].shift]<< endl;
	// 							//getchar();
	// 							currRelCost += (data->freq_matrix[vecShSol[i].shiftRow[k]][vecShSol[j].shiftRow[l]]*newBMatrix[vecShSol[i].posRow[k]][vecShSol[j].posRow[l]][s][z]);
	// 							shCost += (data->freq_matrix[vecShSol[i].shiftRow[k]][vecShSol[j].shiftRow[l]]*newBMatrix[vecShSol[i].posRow[k]][vecShSol[j].posRow[l]][s][z]);
	// 						}
	// 					}
	// 					cout << "\nNew Cost between " << i << " and " << j << ": " << currRelCost;
						
	// 				}
	// 			}
	// 		}
	// 		cout << "\nSh Cost: " << shCost << endl;
	// 		cout << "\nRelative Cost: " << vecShSol[i].relCost;
	// 		if (shCost < vecShSol[i].relCost){
	// 			cout << "\nNew Cost: " << shCost << " shift: " << vecShSol[i].shift;
	// 			vecShSol[i].relCost = shCost;
	// 			vecShSol[i].shift = shifts[s];
	// 			vecShSol[j].shift = shift[z];
	// 		}
	// 	}
	// }

	//cout << "\nShifted Cost1: " << shCost << endl;

}

void pertCount (int pertChoice, Stats *stat){

	switch (pertChoice){
		case 0:
			break;
		case 1: 
			stat->pert1St++;
			break;

		case 2:
			stat->pert2St++;
			break;

		default:
			cout << "Out of range" << endl;
			break;
	}

	pertChoice = 0;
}

double get_wall_time(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        //  Handle error
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

long long qwertyCalc (Gendata *data, Keyboard *keyb){

	long long costc = 0;
	int pos = 0;
	int next = 0;
	int sPos;
	int currCol;

	long long minSCost;
	long long currCost;

	for (int i = 0; i < data->size - 5; i++){

		pos = keyb->assignment[i];

		for (int j = 0; j < data->size - 5; j++){
			if (j != i){
				//cout << "i: " << data->char_list[i] << " j: " << data->char_list[j] << endl;
				next = keyb->assignment[j];

				costc += ( data->freq_matrix[i][j] * data->b_matrix[pos][next]);
			}
		}//for 'j'		
	}// for 'i'

	costc = costc / 2;
	cout << "\nPrel cost: " << costc;


	for (int i = 0; i < data->size - 5; i++){

		pos = keyb->assignment[i];

		switch (pos % keyb->kcols){
			case 0:
				next = keyb->assignment[data->size - 5];
				costc += ( data->freq_matrix[i][data->size - 5] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[data->size - 5] << " freq: " << data->freq_matrix[i][data->size - 5] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
			case 1:
				next = keyb->assignment[data->size - 5];
				costc += ( data->freq_matrix[i][data->size - 5] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[26] << " freq: " << data->freq_matrix[i][26] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
			case 2:
				next = keyb->assignment[data->size - 5];
				costc += ( data->freq_matrix[i][data->size - 5] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[26] << " freq: " << data->freq_matrix[i][26] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
			case 3:
				next = keyb->assignment[data->size - 5];
				costc += ( data->freq_matrix[i][data->size - 5] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[26] << " freq: " << data->freq_matrix[i][26] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
			case 4:
				next = keyb->assignment[data->size - 4];
				costc += ( data->freq_matrix[i][data->size - 4] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[27] << " freq: " << data->freq_matrix[i][27] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
			case 5:
				next = keyb->assignment[data->size - 3];
				costc += ( data->freq_matrix[i][data->size - 3] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[28] << " freq: " << data->freq_matrix[i][28] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
			case 6:
				next = keyb->assignment[data->size - 2];
				costc += ( data->freq_matrix[i][data->size - 2] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[29] << " freq: " << data->freq_matrix[i][29] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
			case 7:
				next = keyb->assignment[data->size - 1];
				costc += ( data->freq_matrix[i][data->size - 1] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[data->size - 1] << " freq: " << data->freq_matrix[i][data->size - 5] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
			case 8:
				next = keyb->assignment[data->size - 1];
				costc += ( data->freq_matrix[i][data->size - 1] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[29] << " freq: " << data->freq_matrix[i][29] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
			case 9:
				next = keyb->assignment[data->size - 1];
				costc += ( data->freq_matrix[i][data->size - 1] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[29] << " freq: " << data->freq_matrix[i][29] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
		}
	}// for 'i'

	return costc;
}


void metropolisAssign (Gendata *data, Keyboard *keyb){
//Eng and EnFr
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
//T H E O F A N D I W  S  R  Y  U  B  C  V  M  L  P  K  G  J  Q  X  Z
//Fre
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
//D E L A T S N U Q I  P  R  O  C  X  V  M  Y  F  B  G  H  J  W  Z  K
//Spa
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
//D E Q U N O A L S Y  P  R  M  T  C  I  H  B  G  V  F  Z  J  K  X  W

	keyb->kcols = 14;
	keyb->krows = 10;

	keyb->grid = new int [keyb->ksize];

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = -1;
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}

//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
//T H E O F A N D I W  S  R  Y  U  B  C  V  M  L  P  K  G  J  Q  X  Z  _

	keyb->grid[2] = 21;
	keyb->grid[3] = 16;
	keyb->grid[14] = 20;
	keyb->grid[15] = 6;
	keyb->grid[16] = 7;
	keyb->grid[17] = 18;
	keyb->grid[18] = 24;
	keyb->grid[29] = 8;
	keyb->grid[30] = 5;
	keyb->grid[31] = 2;
	keyb->grid[32] = 12;
	keyb->grid[42] = 15;
	keyb->grid[43] = 1;
	keyb->grid[44] = 26;
	keyb->grid[45] = 11;
	keyb->grid[46] = 19;
	keyb->grid[57] = 9;
	keyb->grid[58] = 0;
	keyb->grid[59] = 10;
	keyb->grid[60] = 17;
	keyb->grid[70] = 25;
	keyb->grid[71] = 4;
	keyb->grid[72] = 3;
	keyb->grid[73] = 13;
	keyb->grid[74] = 23;
	keyb->grid[86] = 22;
	keyb->grid[87] = 1;

	int k; 

	for (int i = 0; i < keyb->ksize; i++){
		if (keyb->grid[i] > -1){
			k = keyb->grid[i];
			keyb->assignment[k] = i;
		}
	}

	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			// if (i == j){
			// 	cout << " ";
			// }
			if (keyb->grid[count] != -1)
				cout << setw(3) << data->char_list[keyb->grid[count]];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}
}


void bestSpVec (Gendata *data, Keyboard *keyb, vector<int>& bSpaces, vector<int>& spaceVec, vector<int>& charVec){

	int space1, space2, space3, space4;
	int pos;
	int assignedSpace;

	long long min_space;
	long long temp_space;


	space1 = 28;
	space2 = 29;
	space3 = 32;
	space4 = 33;

	spaceVec.push_back(space1);
	spaceVec.push_back(space2);
	spaceVec.push_back(space3);
	spaceVec.push_back(space4);
	
	for (int i = 0; i < keyb->ksize; i++){
		if(i == 28 || i == 29 || i == 32 || i == 33){
			continue;
		}
		else if ((i%COL) < 6 && (floor(i/COL) < 5)){
			charVec.push_back(i);
		}
	}
	for (int i = 0; i < charVec.size(); i++){
		bSpaces.push_back(0);
	}

	// cout << "\nInside bestSp function" << endl;
	// cout << "\nSpace Keys: ";
	// for (int i = 0; i < spaceVec.size(); i++){
	// 	cout << spaceVec[i] << " ";
	// }
	// cout << endl;

	// cout << "\nCharacter Keys: ";
	// for (int i = 0; i < charVec.size(); i++){
	// 	cout << charVec[i] << " ";
	// }
	// cout << endl;

	// cout << "\nBSpace vector size = " << bSpaces.size() << endl;

	// getchar();

	for (int i = 0; i < charVec.size(); i++){
		min_space = LONG_MAX;
		for (int j = 0; j < spaceVec.size(); j++){
			temp_space = data->b_matrix[charVec[i]][spaceVec[j]];
			
			if (temp_space < min_space){
				min_space = temp_space;
				assignedSpace = spaceVec[j];
			}
		}
		bSpaces[i] = assignedSpace;
		// cout << "\ncharVec[i]: " << charVec[i] << " bestSpace: " << assignedSpace << "\nValue: " << min_space << endl; 
		// getchar();
	}
	// cout << "\nSpaces Vector: " << endl;
	// int counter = 0;
	// for (int i = 0; i < bSpaces.size(); i++){

	// 	if (i != 28 && i != 29 && i != 32 && i != 33){
	// 		counter++;
	// 		cout << i << " : " << bSpaces[i] << " ";
	// 		getchar();
	// 	}
	// 	else{
	// 		counter++;
	// 	}
	// }
	// cout << endl;
	// getchar();
}

void initSol2 (Gendata *data, Keyboard *keyb, vector<int>& spaceKeys, vector<int>& charKeys, vector<int>& bSpaces){
	
	//vector <int> aux_grid;
	vector <int> assigned_char;
	list <int> aux_charl;
	vector <int> auxKeyb;
	// vector <int> spaceKeys;
	// vector <int> charKeys;

	long long cost = 0;
	long long temp_cost /*= 0*/;
	long long min_cost, min_cost1 /*= LONG_MAX*/;
	long long temp_cost1;
	
	bool assign = 0;
	
	int optkey, optletter;
	int aux_sum, sum = 0;
	int space1 = 0;
	int space2 = 0;
	int space3 = 0;
	int space4 = 0;
	int count;
	int assignedSpace;
	
	list<int>::iterator it;
	list<int>::iterator it2;

	if (keyb->ksize < 40){
		keyb->kcols = 10;
		keyb->krows = 3;
	}

	else{
		keyb->kcols = COL;
		keyb->krows = ROW;
	}


	keyb->grid = new int [keyb->ksize];
	
	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = -1;
	}
		
	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb.push_back(-1);
	}

	for (int i = 0; i < data->size; i++){
		aux_charl.push_back(i);
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}
		
	//srand(time(NULL));
	
	//center = data->size - 1;

	for (int i = 0; i < spaceKeys.size(); i++){
		keyb->grid[spaceKeys[i]] = data->size - 1 - i;
		keyb->assignment[data->size - 1 - i] = spaceKeys[i];
		aux_charl.remove(data->size - 1 - i);
	}

	// cout << "\nList of available characters: " << endl;
	// for(it = aux_charl.begin(); it != aux_charl.end(); it++){
	// 	cout << data->char_list[*it] << " ";
	// }

	// getchar();

	// cout << "\nInitial Solution so far: " << endl;

	// for (int i = 0; i < auxKeyb.size(); i++){
	// 	auxKeyb[i] = keyb->grid[i];
	// }

	// printSol(data, keyb, auxKeyb);

	// cout << endl;

	// getchar();

	int rcand = 0;
	int key = 0;
	int h = 0;
	int inichar = 6;
	int pos; 

	// if (keyb->ksize < 40){
	// 	inichar = 2;
	// }
	// else{
	// 	inichar = 6;
	// }
	
	//int counter = 0;
	
	while (aux_charl.size() > data->size - inichar - spaceKeys.size()){
 
		rcand = rand() % aux_charl.size();
		// rcand = counter;
		// counter++;
		// cout << "\nRandom char selected: " << data->char_list[rcand];
		
		for (it = aux_charl.begin(); it != aux_charl.end(); it++){
			if(rcand == *it){

				switch(h){
					case 0:
						key = 16;
						break;
					case 1:
						key = 17;
						break;
					case 2:
						key = 30;
						break;
					case 3:
						key = 31;
						break;
					case 4:
						key = 44;
						break;
					case 5:
						key = 45;
						break;
					default:
						key = 0;
						break;
				}
				// cout << "Char: " << data->char_list[*it] << endl;
				// getchar();

				keyb->assignment[*it] = key;
				keyb->grid[key] = *it;	
				//aux_grid[key] = *it;
				assigned_char.push_back(*it);
				aux_charl.erase(it);
				h++;
				break;
			}
		}
	}

	// cout << "\nList of available characters: " << endl;
	// for(it = aux_charl.begin(); it != aux_charl.end(); it++){
	// 	cout << data->char_list[*it] << " ";
	// }
	// cout << endl;
	// getchar();

	// cout << "\nInitial Solution so far: " << endl;

	// for (int i = 0; i < auxKeyb.size(); i++){
	// 	auxKeyb[i] = keyb->grid[i];
	// }

	// printSol(data, keyb, auxKeyb);

	// cout << endl;

	// getchar();

	int posi;
	while (!aux_charl.empty()){
		
		optkey = 0;
		min_cost = LONG_MAX;

		for (it = aux_charl.begin(); it != aux_charl.end(); it++){
			
			//pos = keyb->assignment[i];
			
			for (int j = 0; j < charKeys.size(); j++){
				posi = charKeys[j];
				if (keyb->grid[posi] < 0){
					temp_cost = 0;	
					
					for (int k = 0; k < assigned_char.size(); k++){
						temp_cost += (data->freq_matrix[*it][assigned_char[k]] * data->b_matrix[posi][keyb->assignment[assigned_char[k]]]);
					}	//for 'k'

					temp_cost = temp_cost / 2;
					temp_cost += (data->freq_matrix[*it][data->size - 1] * data->b_matrix[posi][bSpaces[j]]);

					// cout << "\nCusto temporario: " << temp_cost; 

					// cout << "\nCusto temporario com espaço: " << temp_cost;
					// cout << "\nChar atual: " << data->char_list[*it] << " " << "\nTecla atual: " << j << endl;
					// cout << "\nEspaco: " << bSpaces[j] << " Valor da matriz de dist: " << data->b_matrix[j][bSpaces[j]] << " Valor da matriz de freq: " << data->freq_matrix[*it][data->size - 1];
					// cout << endl;
					// getchar();

					// if (charKeys[j] == 0 || charKeys[j] == 1 || charKeys[j] == 56 || charKeys[j] == 57){
					// 	//cout << "\nCusto temporario com espaço: " << temp_cost;
					// 	//cout << "\nChar atual: " << data->char_list[*it] << " " << "\nTecla atual: " << posi << endl;
					// 	//cout << "\nEspaco: " << bSpaces[j] << " Valor da matriz de dist: " << data->b_matrix[posi][bSpaces[j]] << " Valor da matriz de freq: " << data->freq_matrix[*it][data->size - 1];
					// 	//cout << endl;
					// }

					if (temp_cost < min_cost){
						min_cost = temp_cost;
						optkey = charKeys[j];
						it2 = it;
					}
				}
			}	//for 'j'
			//cout << "\nMin Cost: " << min_cost << "\nChosen char: " << data->char_list[*it2] << "\nChosen key: " << optkey << "\n";

		}	//for 'it'
		
		keyb->assignment[*it2] = optkey;
		keyb->grid[optkey] = *it2;
		//aux_grid[optkey] = *it2;
		assigned_char.push_back(*it2);
		aux_charl.erase(it2);

		// cout << "\nInitial Solution (so far): " << endl;

		// for (int i = 0; i < auxKeyb.size(); i++){
		// 	auxKeyb[i] = keyb->grid[i];
		// }

		// printSol(data, keyb, auxKeyb);

		// cout << endl;

		// getchar();
		
		// cout << "\nCusto temporario: " << temp_cost; 

		// cout << "\nCusto temporario com espaço: " << temp_cost;
		// cout << "\nChar atual: " << data->char_list[*it] << " " << "\nTecla atual: " << j << endl;
		// cout << "\nEspaco: " << bSpaces[j] << " Valor da matriz de dist: " << data->b_matrix[j][bSpaces[j]] << " Valor da matriz de freq: " << data->freq_matrix[*it][data->size - 1];
		// cout << endl;
		// getchar();
	}

	for (int i = 0; i < auxKeyb.size(); i++){
		auxKeyb[i] = keyb->grid[i];
	}

//Print Solution

	cout << "\nInitial Solution (final): " << endl;

	for (int i = 0; i < auxKeyb.size(); i++){
		auxKeyb[i] = keyb->grid[i];
	}

	printSol(data, keyb, auxKeyb);

	cout << endl;

	//cost = costcalc(data, -2, keyb);
	cost = multispaceCalc(data, keyb);
	keyb->cost = cost;

	//cout << "Initial Solution Cost: " << keyb->cost << endl;
}

long long multispaceCalc (Gendata *data, Keyboard *keyb){

	long long costc = 0;
	int pos = 0;
	int next = 0;
	int sPos;
	int currCol;

	int nspaces = 4;
	int space;
	
	long long minSCost;
	long long currCost;
	long long minValue;

	for (int i = 0; i < data->size - nspaces; i++){

		pos = keyb->assignment[i];

		for (int j = 0; j < data->size - nspaces; j++){
			if (j != i){
				//cout << "i: " << data->char_list[i] << " j: " << data->char_list[j] << endl;
				next = keyb->assignment[j];

				costc += ( data->freq_matrix[i][j] * data->b_matrix[pos][next]);
			}
		}//for 'j'		
	}// for 'i'

	costc = costc / 2;
	//cout << "\nPrel cost: " << costc;


	for (int i = 0; i < data->size - nspaces; i++){
		pos = keyb->assignment[i];
		minValue = numeric_limits<long long>::max();
		for (int j = data->size - nspaces; j < data->size; j++){
			space = keyb->assignment[j];
			if (data->b_matrix[pos][space] < minValue){
				sPos = space;
				minValue = data->b_matrix[pos][space];
			}
		}
		// cout << "\nBest value: " << minValue << "\nBest Position: " << sPos << endl; 
		// getchar();
		costc += (data->freq_matrix[i][data->size - nspaces] * data->b_matrix[pos][sPos]);

	}// for 'i'

	return costc;
}