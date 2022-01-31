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

void initSol2 (Gendata *data, Keyboard *keyb){
	
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
	int center_key = 15;
	int count;
	
	list<int>::iterator it;
	list<int>::iterator it2;

	keyb->kcols = 10;
	keyb->krows = 4;

	keyb->grid = new int [keyb->ksize];
	
	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = -1;
	}
		
	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb.push_back(0);
	}

	for (int i = 0; i < data->size - 1; i++){
		aux_charl.push_back(i);
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}
		
	//srand(time(NULL));
	
	keyb->grid[35] = data->size - 1;

	keyb->assignment[data->size - 1] = 35;

	assigned_char.push_back(data->size - 1);


	int rcand = 0;
	int key = 0;
	int h = 0;
	int inichar = 4;


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
	for (int i = 0; i < auxKeyb.size(); i++){
		auxKeyb[i] = keyb->grid[i];
	}
	cout << "\nInitial Solution pt 1: " << endl;

	printSol(data, keyb, auxKeyb);

	getchar();

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

	 cout << "\nInitial Solution: " << endl;

	 printSol(data, keyb, auxKeyb);

	cout << endl;
	
	cost = costcalc(data, -2, keyb);
	keyb->cost = cost;

	cout << "Initial Solution Cost: " << keyb->cost << endl;
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

void qwertyEnAssign (Gendata *data, Keyboard *keyb){
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
//T H E O F A N D I W S  R  Y  U  B  C  V  M  L  P  K  G  J  Q  X  Z  _
//Original QWERTY
	keyb->kcols = 10;
	keyb->krows = 4;

	keyb->grid = new int [keyb->ksize];

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = -1;
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}

	keyb->grid[0] = 23;
	keyb->grid[1] = 9;
	keyb->grid[2] = 2;
	keyb->grid[3] = 11;
	keyb->grid[4] = 0;
	keyb->grid[5] = 12;
	keyb->grid[6] = 13;
	keyb->grid[7] = 8;
	keyb->grid[8] = 3;
	keyb->grid[9] = 19;
	keyb->grid[10] = -1;
	keyb->grid[11] = 5;
	keyb->grid[12] = 10;
	keyb->grid[13] = 7;
	keyb->grid[14] = 4;
	keyb->grid[15] = 21;
	keyb->grid[16] = 1;
	keyb->grid[17] = 22;
	keyb->grid[18] = 20;
	keyb->grid[19] = 18;
	keyb->grid[20] = -1;
	keyb->grid[21] = -1;
	keyb->grid[22] = 25;
	keyb->grid[23] = 24;
	keyb->grid[24] = 15;
	keyb->grid[25] = 16;
	keyb->grid[26] = 14;
	keyb->grid[27] = 6;
	keyb->grid[28] = 17;
	keyb->grid[29] = -1;
	keyb->grid[30] = -1;
	keyb->grid[31] = -1;
	keyb->grid[32] = -1;
	keyb->grid[33] = 26;
	keyb->grid[34] = 27;
	keyb->grid[35] = 28;
	keyb->grid[36] = 29;
	keyb->grid[37] = 30;
	keyb->grid[38] = -1;
	keyb->grid[39] = -1;	

	keyb->assignment[0] = 4;
	keyb->assignment[1] = 16;
	keyb->assignment[2] = 2;
	keyb->assignment[3] = 8;
	keyb->assignment[4] = 14;
	keyb->assignment[5] = 11;
	keyb->assignment[6] = 27;
	keyb->assignment[7] = 13;
	keyb->assignment[8] = 7;
	keyb->assignment[9] = 1;
	keyb->assignment[10] = 12;
	keyb->assignment[11] = 3;
	keyb->assignment[12] = 5;
	keyb->assignment[13] = 6;
	keyb->assignment[14] = 26;
	keyb->assignment[15] = 24;
	keyb->assignment[16] = 25;
	keyb->assignment[17] = 28;
	keyb->assignment[18] = 19;
	keyb->assignment[19] = 9;
	keyb->assignment[20] = 18;
	keyb->assignment[21] = 15;
	keyb->assignment[22] = 17;
	keyb->assignment[23] = 0;
	keyb->assignment[24] = 23;
	keyb->assignment[25] = 22;
	keyb->assignment[26] = 33;
	keyb->assignment[27] = 34;
	keyb->assignment[28] = 35;
	keyb->assignment[29] = 36;
	keyb->assignment[30] = 37;

	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			if (i == 0 && j == 0){
				cout << " ";
			}
			if (keyb->grid[count] != -1)
				cout << setw(3) << data->char_list[keyb->grid[count]];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}
}

void qwertyItAssign (Gendata *data, Keyboard *keyb){
// //0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
// //E C H I L A N U P R  O  D  S  M  G  Q  T  V  F  Z  B  X  W  Y  K  J  _  _  _  _  _
	
// 	keyb->kcols = 10;
// 	keyb->krows = 4;

// 	keyb->grid = new int [keyb->ksize];

// 	for (int i = 0; i < keyb->ksize; i++){
// 		keyb->grid[i] = -1;
// 	}
	
// 	keyb->assignment = new int [data->size];

// 	for (int i = 0; i < data->size; i++){
// 		keyb->assignment[i] = -1;
// 	}

// 	keyb->grid[0] = 15;
// 	keyb->grid[1] = 22;
// 	keyb->grid[2] = 0;
// 	keyb->grid[3] = 9;
// 	keyb->grid[4] = 16;
// 	keyb->grid[5] = 23;
// 	keyb->grid[6] = 7;
// 	keyb->grid[7] = 3;
// 	keyb->grid[8] = 10;
// 	keyb->grid[9] = 8;
// 	keyb->grid[11] = 5;
// 	keyb->grid[12] = 12;
// 	keyb->grid[13] = 11;
// 	keyb->grid[14] = 18;
// 	keyb->grid[15] = 14;
// 	keyb->grid[16] = 2;
// 	keyb->grid[17] = 25;
// 	keyb->grid[18] = 24;
// 	keyb->grid[19] = 4;
// 	keyb->grid[22] = 19;
// 	keyb->grid[23] = 21;
// 	keyb->grid[24] = 1;
// 	keyb->grid[25] = 17;
// 	keyb->grid[26] = 20;
// 	keyb->grid[27] = 6;
// 	keyb->grid[28] = 13;
// 	keyb->grid[33] = 26;
// 	keyb->grid[34] = 27;
// 	keyb->grid[35] = 28;
// 	keyb->grid[36] = 29;
// 	keyb->grid[37] = 30;

// 	keyb->assignment[0] = 2;
// 	keyb->assignment[1] = 24;
// 	keyb->assignment[2] = 16;
// 	keyb->assignment[3] = 7;
// 	keyb->assignment[4] = 19;
// 	keyb->assignment[5] = 11;
// 	keyb->assignment[6] = 27;
// 	keyb->assignment[7] = 6;
// 	keyb->assignment[8] = 9;
// 	keyb->assignment[9] = 3;
// 	keyb->assignment[10] = 8;
// 	keyb->assignment[11] = 13;
// 	keyb->assignment[12] = 12;
// 	keyb->assignment[13] = 28;
// 	keyb->assignment[14] = 15;
// 	keyb->assignment[15] = 0;
// 	keyb->assignment[16] = 4;
// 	keyb->assignment[17] = 25;
// 	keyb->assignment[18] = 14;
// 	keyb->assignment[19] = 22;
// 	keyb->assignment[20] = 26;
// 	keyb->assignment[21] = 23;
// 	keyb->assignment[22] = 1;
// 	keyb->assignment[23] = 5;
// 	keyb->assignment[24] = 18;
// 	keyb->assignment[25] = 17;
// 	keyb->assignment[26] = 33;
// 	keyb->assignment[27] = 34;
// 	keyb->assignment[28] = 35;
// 	keyb->assignment[29] = 36;
// 	keyb->assignment[30] = 37;

// 	int count = 0;
	
// 	for (int i = 0; i < keyb->krows; i++){
// 		for (int j = 0; j < keyb->kcols; j++){
// 			if (i == 0 && j == 0){
// 				cout << " ";
// 			}
// 			if (keyb->grid[count] != -1)
// 				cout << setw(3) << data->char_list[keyb->grid[count]];
// 			else
// 				cout<< setw(3) << "*";
// 			count++;
// 		}
// 		cout << endl;
// 	}

//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
//T H E O F A N D I W  S  R  Y  U  B  C  V  M  L  P  K  G  J  Q  X  Z  _  _  _  _  _ 

	keyb->kcols = 10;
	keyb->krows = 4;

	keyb->grid = new int [keyb->ksize];

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = -1;
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}
	keyb->grid[0] = 23;
	keyb->grid[1] = 9;
	keyb->grid[2] = 2;
	keyb->grid[3] = 11;
	keyb->grid[4] = 0;
	keyb->grid[5] = 12;
	keyb->grid[6] = 13;
	keyb->grid[7] = 8;
	keyb->grid[8] = 3;
	keyb->grid[9] = 19;
	keyb->grid[11] = 5;
	keyb->grid[12] = 10;
	keyb->grid[13] = 7;
	keyb->grid[14] = 4;
	keyb->grid[15] = 21;
	keyb->grid[16] = 1;
	keyb->grid[17] = 22;
	keyb->grid[18] = 20;
	keyb->grid[19] = 18;
	keyb->grid[22] = 25;
	keyb->grid[23] = 24;
	keyb->grid[24] = 15;
	keyb->grid[25] = 16;
	keyb->grid[26] = 14;
	keyb->grid[27] = 6;
	keyb->grid[28] = 17;
	keyb->grid[33] = 27;
	keyb->grid[34] = 28;
	keyb->grid[35] = 29;
	keyb->grid[36] = 30;
	keyb->grid[37] = 31;

	keyb->assignment[0] = 4;
	keyb->assignment[1] = 15;
	keyb->assignment[2] = 2;
	keyb->assignment[3] = 8;
	keyb->assignment[4] = 13;
	keyb->assignment[5] = 10;
	keyb->assignment[6] = 27;
	keyb->assignment[7] = 12;
	keyb->assignment[8] = 7;
	keyb->assignment[9] = 1;
	keyb->assignment[10] = 11;
	keyb->assignment[11] = 3;
	keyb->assignment[12] = 5;
	keyb->assignment[13] = 6;
	keyb->assignment[14] = 26;
	keyb->assignment[15] = 24;
	keyb->assignment[16] = 25;
	keyb->assignment[17] = 28;
	keyb->assignment[18] = 18;
	keyb->assignment[19] = 9;
	keyb->assignment[20] = 17;
	keyb->assignment[21] = 14;
	keyb->assignment[22] = 16;
	keyb->assignment[23] = 0;
	keyb->assignment[24] = 23;
	keyb->assignment[25] = 22;
	keyb->assignment[26] = 19;
	keyb->assignment[27] = 33;
	keyb->assignment[28] = 34;
	keyb->assignment[29] = 35;
	keyb->assignment[30] = 36;
	keyb->assignment[31] = 37;


	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			if (i == 0 && j == 0){
				cout << " ";
			}
			if (keyb->grid[count] != -1)
				cout << setw(3) << data->char_list[keyb->grid[count]];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}
}

void qwertyPtAssign (Gendata *data, Keyboard *keyb){
// //0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
// //E A O S R I D N T M  C  U  P  L  V  F  G  B  Q  H  Z  J  X  W  Y  K  _  _  _  _  _
	
// 	keyb->kcols = 10;
// 	keyb->krows = 4;

// 	keyb->grid = new int [keyb->ksize];

// 	for (int i = 0; i < keyb->ksize; i++){
// 		keyb->grid[i] = -1;
// 	}
	
// 	keyb->assignment = new int [data->size];

// 	for (int i = 0; i < data->size; i++){
// 		keyb->assignment[i] = -1;
// 	}

// 	keyb->grid[0] = 18;
// 	keyb->grid[1] = 23;
// 	keyb->grid[2] = 0;
// 	keyb->grid[3] = 4;
// 	keyb->grid[4] = 8;
// 	keyb->grid[5] = 24;
// 	keyb->grid[6] = 11;
// 	keyb->grid[7] = 5;
// 	keyb->grid[8] = 2;
// 	keyb->grid[9] = 12;
// 	keyb->grid[11] = 1;
// 	keyb->grid[12] = 3;
// 	keyb->grid[13] = 6;
// 	keyb->grid[14] = 15;
// 	keyb->grid[15] = 16;
// 	keyb->grid[16] = 19;
// 	keyb->grid[17] = 21;
// 	keyb->grid[18] = 25;
// 	keyb->grid[19] = 13;
// 	keyb->grid[22] = 20;
// 	keyb->grid[23] = 22;
// 	keyb->grid[24] = 10;
// 	keyb->grid[25] = 14;
// 	keyb->grid[26] = 17;
// 	keyb->grid[27] = 7;
// 	keyb->grid[28] = 9;
// 	keyb->grid[33] = 26;
// 	keyb->grid[34] = 27;
// 	keyb->grid[35] = 28;
// 	keyb->grid[36] = 29;
// 	keyb->grid[37] = 30;

// 	keyb->assignment[0] = 2;
// 	keyb->assignment[1] = 11;
// 	keyb->assignment[2] = 8;
// 	keyb->assignment[3] = 12;
// 	keyb->assignment[4] = 3;
// 	keyb->assignment[5] = 7;
// 	keyb->assignment[6] = 13;
// 	keyb->assignment[7] = 27;
// 	keyb->assignment[8] = 4;
// 	keyb->assignment[9] = 28;
// 	keyb->assignment[10] = 24;
// 	keyb->assignment[11] = 6;
// 	keyb->assignment[12] = 9;
// 	keyb->assignment[13] = 19;
// 	keyb->assignment[14] = 25;
// 	keyb->assignment[15] = 14;
// 	keyb->assignment[16] = 15;
// 	keyb->assignment[17] = 26;
// 	keyb->assignment[18] = 0;
// 	keyb->assignment[19] = 16;
// 	keyb->assignment[20] = 22;
// 	keyb->assignment[21] = 17;
// 	keyb->assignment[22] = 23;
// 	keyb->assignment[23] = 1;
// 	keyb->assignment[24] = 5;
// 	keyb->assignment[25] = 18;
// 	keyb->assignment[26] = 33;
// 	keyb->assignment[27] = 34;
// 	keyb->assignment[28] = 35;
// 	keyb->assignment[29] = 36;
// 	keyb->assignment[30] = 37;

// 	int count = 0;
	
// 	for (int i = 0; i < keyb->krows; i++){
// 		for (int j = 0; j < keyb->kcols; j++){
// 			if (i == 0 && j == 0){
// 				cout << " ";
// 			}
// 			if (keyb->grid[count] != -1)
// 				cout << setw(3) << data->char_list[keyb->grid[count]];
// 			else
// 				cout<< setw(3) << "*";
// 			count++;
// 		}
// 		cout << endl;
// 	}

//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
//T H E O F A N D I W  S  R  Y  U  B  C  V  M  L  P  K  G  J  Q  X  Z  _  _  _  _  _ 
	

	keyb->kcols = 10;
	keyb->krows = 4;

	keyb->grid = new int [keyb->ksize];

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = -1;
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}
	keyb->grid[0] = 23;
	keyb->grid[1] = 9;
	keyb->grid[2] = 2;
	keyb->grid[3] = 11;
	keyb->grid[4] = 0;
	keyb->grid[5] = 12;
	keyb->grid[6] = 13;
	keyb->grid[7] = 8;
	keyb->grid[8] = 3;
	keyb->grid[9] = 19;
	keyb->grid[11] = 5;
	keyb->grid[12] = 10;
	keyb->grid[13] = 7;
	keyb->grid[14] = 4;
	keyb->grid[15] = 21;
	keyb->grid[16] = 1;
	keyb->grid[17] = 22;
	keyb->grid[18] = 20;
	keyb->grid[19] = 18;
	keyb->grid[22] = 25;
	keyb->grid[23] = 24;
	keyb->grid[24] = 15;
	keyb->grid[25] = 16;
	keyb->grid[26] = 14;
	keyb->grid[27] = 6;
	keyb->grid[28] = 17;
	keyb->grid[33] = 27;
	keyb->grid[34] = 28;
	keyb->grid[35] = 29;
	keyb->grid[36] = 30;
	keyb->grid[37] = 31;

	keyb->assignment[0] = 4;
	keyb->assignment[1] = 15;
	keyb->assignment[2] = 2;
	keyb->assignment[3] = 8;
	keyb->assignment[4] = 13;
	keyb->assignment[5] = 10;
	keyb->assignment[6] = 27;
	keyb->assignment[7] = 12;
	keyb->assignment[8] = 7;
	keyb->assignment[9] = 1;
	keyb->assignment[10] = 11;
	keyb->assignment[11] = 3;
	keyb->assignment[12] = 5;
	keyb->assignment[13] = 6;
	keyb->assignment[14] = 26;
	keyb->assignment[15] = 24;
	keyb->assignment[16] = 25;
	keyb->assignment[17] = 28;
	keyb->assignment[18] = 18;
	keyb->assignment[19] = 9;
	keyb->assignment[20] = 17;
	keyb->assignment[21] = 14;
	keyb->assignment[22] = 16;
	keyb->assignment[23] = 0;
	keyb->assignment[24] = 23;
	keyb->assignment[25] = 22;
	keyb->assignment[26] = 19;
	keyb->assignment[27] = 33;
	keyb->assignment[28] = 34;
	keyb->assignment[29] = 35;
	keyb->assignment[30] = 36;
	keyb->assignment[31] = 37;


	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			if (i == 0 && j == 0){
				cout << " ";
			}
			if (keyb->grid[count] != -1)
				cout << setw(3) << data->char_list[keyb->grid[count]];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}
}

void qwertynAssign (Gendata *data, Keyboard *keyb){

	//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
	//D E Q U N O A L S Y  P  R  M  T  C  I  H  B  G  V  F  Z  J  ñ  K  X  W  _  _  _  _  _
//QWERTYN original

	// vector<int> v1;
	// vector<int> v2;
	// vector<int> v3;
	// vector<int> v4;
	// vector<int> v5;

	// int sp;

	// keyb->kcols = 10;
	// keyb->krows = 4;

	// keyb->grid = new int [keyb->ksize];

	// for (int i = 0; i < keyb->ksize; i++){
	// 	keyb->grid[i] = -1;
	// }
	
	// keyb->assignment = new int [data->size];

	// for (int i = 0; i < data->size; i++){
	// 	keyb->assignment[i] = -1;
	// }

	// keyb->grid[0] = 2;
	// keyb->grid[1] = 26;
	// keyb->grid[2] = 1;
	// keyb->grid[3] = 11;
	// keyb->grid[4] = 13;
	// keyb->grid[5] = 9;
	// keyb->grid[6] = 3;
	// keyb->grid[7] = 15;
	// keyb->grid[8] = 5;
	// keyb->grid[9] = 10;
	// keyb->grid[10] = 6;
	// keyb->grid[11] = 8;
	// keyb->grid[12] = 0;
	// keyb->grid[13] = 20;
	// keyb->grid[14] = 18;
	// keyb->grid[15] = 16;
	// keyb->grid[16] = 22;
	// keyb->grid[17] = 24;
	// keyb->grid[18] = 7;
	// keyb->grid[19] = 23;
	// keyb->grid[22] = 21;
	// keyb->grid[23] = 25;
	// keyb->grid[24] = 14;
	// keyb->grid[25] = 19;
	// keyb->grid[26] = 17;
	// keyb->grid[27] = 4;
	// keyb->grid[28] = 12;
	// keyb->grid[33] = 27;
	// keyb->grid[34] = 28;
	// keyb->grid[35] = 29;
	// keyb->grid[36] = 30;
	// keyb->grid[37] = 31;

	// keyb->assignment[0] = 12;
	// keyb->assignment[1] = 2;
	// keyb->assignment[2] = 0;
	// keyb->assignment[3] = 6;
	// keyb->assignment[4] = 27;
	// keyb->assignment[5] = 8;
	// keyb->assignment[6] = 10;
	// keyb->assignment[7] = 18;
	// keyb->assignment[8] = 11;
	// keyb->assignment[9] = 5;
	// keyb->assignment[10] = 9;
	// keyb->assignment[11] = 3;
	// keyb->assignment[12] = 28;
	// keyb->assignment[13] = 4;
	// keyb->assignment[14] = 24;
	// keyb->assignment[15] = 7;
	// keyb->assignment[16] = 15;
	// keyb->assignment[17] = 26;
	// keyb->assignment[18] = 14;
	// keyb->assignment[19] = 25;
	// keyb->assignment[20] = 13;
	// keyb->assignment[21] = 22;
	// keyb->assignment[22] = 16;
	// keyb->assignment[23] = 19;
	// keyb->assignment[24] = 17;
	// keyb->assignment[25] = 23;
	// keyb->assignment[26] = 1;
	// keyb->assignment[27] = 33;
	// keyb->assignment[28] = 34;
	// keyb->assignment[29] = 35;
	// keyb->assignment[30] = 36;
	// keyb->assignment[31] = 37;
	
	// //  	cout << "\n0." << endl;
	// //  	getchar();

	// // long long bestSp;

	// // for (int i = 0; i < 33; i++){
	// // 	bestSp = numeric_limits<long long>::max();
	// // 	for (int j = 33; j < 38; j++){

	// // 		if(data->b_matrix[i][j] < bestSp){
	// // 			bestSp = data->b_matrix[i][j];
	// // 			sp = j;
	// // 		}
	// // 	}
	// // 	switch(sp){
	// // 		case 33:
	// // 			v1.push_back(i);
	// // 			break;

	// // 		case 34:
	// // 			v2.push_back(i);
	// // 			break;

	// // 		case 35:
	// // 			v3.push_back(i);
	// // 			break;
			
	// // 		case 36:
	// // 			v4.push_back(i);
	// // 			break;

	// // 		case 37:
	// // 			v5.push_back(i);
	// // 			break;
	// // 	}
	// // }
	// // cout << "\n1." << endl;
	// // getchar();

	// // cout << "\nv1: ";
	// // for (int i = 0; i < v1.size(); i++){
	// // 	cout << v1[i] << " ";
	// // }
	// // cout << endl;
	
	// // cout << "\nv2: ";
	// // for (int i = 0; i < v2.size(); i++){
	// // 	cout << v2[i] << " ";
	// // }
	// // cout << endl;	
	
	// // cout << "\nv3: ";
	// // for (int i = 0; i < v3.size(); i++){
	// // 	cout << v3[i] << " ";
	// // }
	// // cout << endl;	
	
	// // cout << "\nv4: ";
	// // for (int i = 0; i < v4.size(); i++){
	// // 	cout << v4[i] << " ";
	// // }
	// // cout << endl;
	
	// // cout << "\nv5: ";
	// // for (int i = 0; i < v5.size(); i++){
	// // 	cout << v5[i] << " ";
	// // }
	// // cout << endl;

	// int count = 0;
	
	// for (int i = 0; i < keyb->krows; i++){
	// 	for (int j = 0; j < keyb->kcols; j++){
	// 		if (i == 0 && j == 0){
	// 			cout << " ";
	// 		}
	// 		if (i == 1 && j == 0){
	// 			cout << " ";
	// 		}
	// 		if (keyb->grid[count] != -1)
	// 			cout << setw(3) << data->char_list[keyb->grid[count]];
	// 		else
	// 			cout<< setw(3) << "*";
	// 		count++;
	// 	}
	// 	cout << endl;
	// }

//QWERTYN Bilingual

//    Q  W  E  R  T  Y  U  I  O  P
//    A  S  D  F  G  H  J  K  L  n
//   *  *  Z  X  C  V  B  N  M  *
//   *  *  *  _  _  _  _  _  *  *

// Cost of Qwerty: 1415388952

	//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
	//T H E O F A N D I W  S  R  Y  U  B  C  V  M  L  P  K  G  J  Q  X  Z  n  _  _  _  _  _ 


	vector<int> v1;
	vector<int> v2;
	vector<int> v3;
	vector<int> v4;
	vector<int> v5;

	int sp;

	keyb->kcols = 10;
	keyb->krows = 4;

	keyb->grid = new int [keyb->ksize];

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = -1;
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}

	keyb->grid[0] = 23;
	keyb->grid[1] = 9;
	keyb->grid[2] = 2;
	keyb->grid[3] = 11;
	keyb->grid[4] = 0;
	keyb->grid[5] = 12;
	keyb->grid[6] = 13;
	keyb->grid[7] = 8;
	keyb->grid[8] = 3;
	keyb->grid[9] = 19;
	keyb->grid[10] = 5;
	keyb->grid[11] = 10;
	keyb->grid[12] = 7;
	keyb->grid[13] = 4;
	keyb->grid[14] = 21;
	keyb->grid[15] = 1;
	keyb->grid[16] = 22;
	keyb->grid[17] = 20;
	keyb->grid[18] = 18;
	keyb->grid[19] = 26;
	keyb->grid[22] = 25;
	keyb->grid[23] = 24;
	keyb->grid[24] = 15;
	keyb->grid[25] = 16;
	keyb->grid[26] = 14;
	keyb->grid[27] = 6;
	keyb->grid[28] = 17;
	keyb->grid[33] = 27;
	keyb->grid[34] = 28;
	keyb->grid[35] = 29;
	keyb->grid[36] = 30;
	keyb->grid[37] = 31;

	keyb->assignment[0] = 4;
	keyb->assignment[1] = 15;
	keyb->assignment[2] = 2;
	keyb->assignment[3] = 8;
	keyb->assignment[4] = 13;
	keyb->assignment[5] = 10;
	keyb->assignment[6] = 27;
	keyb->assignment[7] = 12;
	keyb->assignment[8] = 7;
	keyb->assignment[9] = 1;
	keyb->assignment[10] = 11;
	keyb->assignment[11] = 3;
	keyb->assignment[12] = 5;
	keyb->assignment[13] = 6;
	keyb->assignment[14] = 26;
	keyb->assignment[15] = 24;
	keyb->assignment[16] = 25;
	keyb->assignment[17] = 28;
	keyb->assignment[18] = 18;
	keyb->assignment[19] = 9;
	keyb->assignment[20] = 17;
	keyb->assignment[21] = 14;
	keyb->assignment[22] = 16;
	keyb->assignment[23] = 0;
	keyb->assignment[24] = 23;
	keyb->assignment[25] = 22;
	keyb->assignment[26] = 19;
	keyb->assignment[27] = 33;
	keyb->assignment[28] = 34;
	keyb->assignment[29] = 35;
	keyb->assignment[30] = 36;
	keyb->assignment[31] = 37;
	
	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			if (i == 0 && j == 0){
				cout << " ";
			}
			if (i == 1 && j == 0){
				cout << " ";
			}
			if (keyb->grid[count] != -1)
				cout << setw(3) << data->char_list[keyb->grid[count]];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}

}

void azertyAssign (Gendata *data, Keyboard *keyb){
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
//D E L A ' T S N U Q  I  P  R  O  C  X  V  M  Y  F  B  G  H  J  W  Z  K  _  _  _  _  _
//Original Azerty	
	// keyb->kcols = 10;
	// keyb->krows = 4;

	// keyb->grid = new int [keyb->ksize];

	// for (int i = 0; i < keyb->ksize; i++){
	// 	keyb->grid[i] = -1;
	// }
	
	// keyb->assignment = new int [data->size];

	// for (int i = 0; i < data->size; i++){
	// 	keyb->assignment[i] = -1;
	// }

	// keyb->grid[0] = 3;
	// keyb->grid[1] = 25;
	// keyb->grid[2] = 1;
	// keyb->grid[3] = 12;
	// keyb->grid[4] = 5;
	// keyb->grid[5] = 18;
	// keyb->grid[6] = 8;
	// keyb->grid[7] = 10;
	// keyb->grid[8] = 13;
	// keyb->grid[9] = 11;
	// keyb->grid[10] = 9;
	// keyb->grid[11] = 6;
	// keyb->grid[12] = 0;
	// keyb->grid[13] = 19;
	// keyb->grid[14] = 21;
	// keyb->grid[15] = 22;
	// keyb->grid[16] = 23;
	// keyb->grid[17] = 26;
	// keyb->grid[18] = 2;
	// keyb->grid[19] = 17;
	// keyb->grid[22] = 24;
	// keyb->grid[23] = 15;
	// keyb->grid[24] = 14;
	// keyb->grid[25] = 16;
	// keyb->grid[26] = 20;
	// keyb->grid[27] = 7;
	// keyb->grid[28] = 4;
	// keyb->grid[33] = 27;
	// keyb->grid[34] = 28;
	// keyb->grid[35] = 29;
	// keyb->grid[36] = 30;
	// keyb->grid[37] = 31;

	// keyb->assignment[0] = 12;
	// keyb->assignment[1] = 2;
	// keyb->assignment[2] = 18;
	// keyb->assignment[3] = 0;
	// keyb->assignment[4] = 28;
	// keyb->assignment[5] = 4;
	// keyb->assignment[6] = 11;
	// keyb->assignment[7] = 27;
	// keyb->assignment[8] = 6;
	// keyb->assignment[9] = 10;
	// keyb->assignment[10] = 7;
	// keyb->assignment[11] = 9;
	// keyb->assignment[12] = 3;
	// keyb->assignment[13] = 8;
	// keyb->assignment[14] = 24;
	// keyb->assignment[15] = 23;
	// keyb->assignment[16] = 25;
	// keyb->assignment[17] = 19;
	// keyb->assignment[18] = 5;
	// keyb->assignment[19] = 13;
	// keyb->assignment[20] = 26;
	// keyb->assignment[21] = 14;
	// keyb->assignment[22] = 24;
	// keyb->assignment[23] = 16;
	// keyb->assignment[24] = 22;
	// keyb->assignment[25] = 1;
	// keyb->assignment[26] = 17;
	// keyb->assignment[27] = 33;
	// keyb->assignment[28] = 34;
	// keyb->assignment[29] = 35;
	// keyb->assignment[30] = 36;
	// keyb->assignment[31] = 37;

	// int count = 0;
	
	// for (int i = 0; i < keyb->krows; i++){
	// 	for (int j = 0; j < keyb->kcols; j++){
	// 		if (i == 0 && j == 0){
	// 			cout << " ";
	// 		}
	// 		if (i == 1 && j == 0){
	// 			cout << " ";
	// 		}
	// 		if (keyb->grid[count] != -1)
	// 			cout << setw(3) << data->char_list[keyb->grid[count]];
	// 		else
	// 			cout<< setw(3) << "*";
	// 		count++;
	// 	}
	// 	cout << endl;
	// }

//Azerty En+Fr
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
//T H E O F A N D I W  S  R  Y  U  B  C  V  M  L  P  K  G  J  Q  X  '  Z  _  _  _  _  _ 

//    A  Z  E  R  T  Y  U  I  O  P
//    Q  S  D  F  G  H  J  K  L  M
//   *  *  W  X  C  V  B  N  '  *
//   *  *  *  _  _  _  _  _  *  *

// Cost of Qwerty: 15278765445

	keyb->kcols = 10;
	keyb->krows = 4;

	keyb->grid = new int [keyb->ksize];

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = -1;
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}

	keyb->grid[0] = 5;
	keyb->grid[1] = 26;
	keyb->grid[2] = 2;
	keyb->grid[3] = 11;
	keyb->grid[4] = 0;
	keyb->grid[5] = 12;
	keyb->grid[6] = 13;
	keyb->grid[7] = 8;
	keyb->grid[8] = 3;
	keyb->grid[9] = 19;
	keyb->grid[10] = 23;
	keyb->grid[11] = 10;
	keyb->grid[12] = 7;
	keyb->grid[13] = 4;
	keyb->grid[14] = 21;
	keyb->grid[15] = 1;
	keyb->grid[16] = 22;
	keyb->grid[17] = 20;
	keyb->grid[18] = 18;
	keyb->grid[19] = 17;
	keyb->grid[22] = 9;
	keyb->grid[23] = 24;
	keyb->grid[24] = 15;
	keyb->grid[25] = 16;
	keyb->grid[26] = 14;
	keyb->grid[27] = 6;
	keyb->grid[28] = 25;
	keyb->grid[33] = 27;
	keyb->grid[34] = 28;
	keyb->grid[35] = 29;
	keyb->grid[36] = 30;
	keyb->grid[37] = 31;

	keyb->assignment[0] = 4;
	keyb->assignment[1] = 15;
	keyb->assignment[2] = 2;
	keyb->assignment[3] = 8;
	keyb->assignment[4] = 13;
	keyb->assignment[5] = 0;
	keyb->assignment[6] = 27;
	keyb->assignment[7] = 12;
	keyb->assignment[8] = 7;
	keyb->assignment[9] = 22;
	keyb->assignment[10] = 11;
	keyb->assignment[11] = 3;
	keyb->assignment[12] = 5;
	keyb->assignment[13] = 6;
	keyb->assignment[14] = 26;
	keyb->assignment[15] = 24;
	keyb->assignment[16] = 25;
	keyb->assignment[17] = 19;
	keyb->assignment[18] = 18;
	keyb->assignment[19] = 9;
	keyb->assignment[20] = 17;
	keyb->assignment[21] = 14;
	keyb->assignment[22] = 16;
	keyb->assignment[23] = 10;
	keyb->assignment[24] = 23;
	keyb->assignment[25] = 28;
	keyb->assignment[26] = 1;
	keyb->assignment[27] = 33;
	keyb->assignment[28] = 34;
	keyb->assignment[29] = 35;
	keyb->assignment[30] = 36;
	keyb->assignment[31] = 37;

	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			if (i == 0 && j == 0){
				cout << " ";
			}
			if (i == 1 && j == 0){
				cout << " ";
			}
			if (keyb->grid[count] != -1)
				cout << setw(3) << data->char_list[keyb->grid[count]];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}
}

void hybEng (Gendata *data, Keyboard *keyb){
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
//T H E O F A N D I W S  R  Y  U  B  C  V  M  L  P  K  G  J  Q  X  Z  _
	
	keyb->kcols = 10;
	keyb->krows = 4;

	keyb->grid = new int [keyb->ksize];

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = -1;
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}

	// keyb->grid[0] = 24;
	// keyb->grid[1] = 21;
	// keyb->grid[2] = 7;
	// keyb->grid[3] = 6;
	// keyb->grid[4] = 5;
	// keyb->grid[5] = 18;
	// keyb->grid[6] = 17;
	// keyb->grid[7] = 12;
	// keyb->grid[8] = 22;
	// keyb->grid[10] = 25;
	// keyb->grid[11] = 16;
	// keyb->grid[12] = 15;
	// keyb->grid[13] = 8;
	// keyb->grid[14] = 2;
	// keyb->grid[15] = 11;
	// keyb->grid[16] = 3;
	// keyb->grid[17] = 4;
	// keyb->grid[18] = 14;
	// keyb->grid[21] = 20;
	// keyb->grid[22] = 9;
	// keyb->grid[23] = 1;
	// keyb->grid[24] = 0;
	// keyb->grid[25] = 10;
	// keyb->grid[26] = 13;
	// keyb->grid[27] = 19;
	// keyb->grid[28] = 23;
	// keyb->grid[33] = 26;
	// keyb->grid[34] = 27;
	// keyb->grid[35] = 28;
	// keyb->grid[36] = 29;
	// keyb->grid[37] = 30;

	// keyb->assignment[0] = 24;
	// keyb->assignment[1] = 23;
	// keyb->assignment[2] = 14;
	// keyb->assignment[3] = 16;
	// keyb->assignment[4] = 17;
	// keyb->assignment[5] = 4;
	// keyb->assignment[6] = 3;
	// keyb->assignment[7] = 2;
	// keyb->assignment[8] = 13;
	// keyb->assignment[9] = 22;
	// keyb->assignment[10] = 25;
	// keyb->assignment[11] = 15;
	// keyb->assignment[12] = 7;
	// keyb->assignment[13] = 26;
	// keyb->assignment[14] = 18;
	// keyb->assignment[15] = 12;
	// keyb->assignment[16] = 11;
	// keyb->assignment[17] = 6;
	// keyb->assignment[18] = 5;
	// keyb->assignment[19] = 27;
	// keyb->assignment[20] = 21;
	// keyb->assignment[21] = 1;
	// keyb->assignment[22] = 8;
	// keyb->assignment[23] = 28;
	// keyb->assignment[24] = 0;
	// keyb->assignment[25] = 10;
	// keyb->assignment[26] = 33;
	// keyb->assignment[27] = 34;
	// keyb->assignment[28] = 35;
	// keyb->assignment[29] = 36;
	// keyb->assignment[30] = 37;

//transladado

	keyb->grid[1] = 24;
	keyb->grid[2] = 21;
	keyb->grid[3] = 7;
	keyb->grid[4] = 6;
	keyb->grid[5] = 5;
	keyb->grid[6] = 18;
	keyb->grid[7] = 17;
	keyb->grid[8] = 12;
	keyb->grid[9] = 22;
	keyb->grid[11] = 25;
	keyb->grid[12] = 16;
	keyb->grid[13] = 15;
	keyb->grid[14] = 8;
	keyb->grid[15] = 2;
	keyb->grid[16] = 11;
	keyb->grid[17] = 3;
	keyb->grid[18] = 4;
	keyb->grid[19] = 14;
	keyb->grid[22] = 20;
	keyb->grid[23] = 9;
	keyb->grid[24] = 1;
	keyb->grid[25] = 0;
	keyb->grid[26] = 10;
	keyb->grid[27] = 13;
	keyb->grid[28] = 19;
	keyb->grid[29] = 23;
	keyb->grid[33] = 26;
	keyb->grid[34] = 27;
	keyb->grid[35] = 28;
	keyb->grid[36] = 29;
	keyb->grid[37] = 30;

	keyb->assignment[0] = 25;
	keyb->assignment[1] = 24;
	keyb->assignment[2] = 15;
	keyb->assignment[3] = 17;
	keyb->assignment[4] = 18;
	keyb->assignment[5] = 5;
	keyb->assignment[6] = 4;
	keyb->assignment[7] = 3;
	keyb->assignment[8] = 14;
	keyb->assignment[9] = 23;
	keyb->assignment[10] = 26;
	keyb->assignment[11] = 16;
	keyb->assignment[12] = 8;
	keyb->assignment[13] = 27;
	keyb->assignment[14] = 19;
	keyb->assignment[15] = 13;
	keyb->assignment[16] = 12;
	keyb->assignment[17] = 7;
	keyb->assignment[18] = 6;
	keyb->assignment[19] = 28;
	keyb->assignment[20] = 22;
	keyb->assignment[21] = 2;
	keyb->assignment[22] = 9;
	keyb->assignment[23] = 29;
	keyb->assignment[24] = 1;
	keyb->assignment[25] = 11;
	keyb->assignment[26] = 33;
	keyb->assignment[27] = 34;
	keyb->assignment[28] = 35;
	keyb->assignment[29] = 36;
	keyb->assignment[30] = 37;

	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			if (i == 0 && j == 0){
				cout << " ";
			}
			if (keyb->grid[count] != -1)
				cout << setw(3) << data->char_list[keyb->grid[count]];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}
}

void hybIt (Gendata *data, Keyboard *keyb){
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
//E C H I L A N U P R  O  D  S  M  G  Q  T  V  F  Z  B  X  W  Y  K  J  _  _  _  _  _
	
	keyb->kcols = 10;
	keyb->krows = 4;

	keyb->grid = new int [keyb->ksize];

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = -1;
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}

	// keyb->grid[0] = 21;
	// keyb->grid[1] = 17;
	// keyb->grid[2] = 8;
	// keyb->grid[3] = 9;
	// keyb->grid[4] = 0;
	// keyb->grid[5] = 12;
	// keyb->grid[6] = 11;
	// keyb->grid[7] = 18;
	// keyb->grid[10] = 23;
	// keyb->grid[11] = 20;
	// keyb->grid[12] = 13;
	// keyb->grid[13] = 5;
	// keyb->grid[14] = 16;
	// keyb->grid[15] = 10;
	// keyb->grid[16] = 1;
	// keyb->grid[17] = 2;
	// keyb->grid[18] = 24;
	// keyb->grid[20] = 22;
	// keyb->grid[21] = 19;
	// keyb->grid[22] = 14;
	// keyb->grid[23] = 4;
	// keyb->grid[24] = 3;
	// keyb->grid[25] = 6;
	// keyb->grid[26] = 7;
	// keyb->grid[27] = 15;
	// keyb->grid[28] = 25;
	// keyb->grid[33] = 26;
	// keyb->grid[34] = 27;
	// keyb->grid[35] = 28;
	// keyb->grid[36] = 29;
	// keyb->grid[37] = 30;

	// keyb->assignment[0] = 4;
	// keyb->assignment[1] = 16;
	// keyb->assignment[2] = 17;
	// keyb->assignment[3] = 24;
	// keyb->assignment[4] = 23;
	// keyb->assignment[5] = 13;
	// keyb->assignment[6] = 25;
	// keyb->assignment[7] = 26;
	// keyb->assignment[8] = 2;
	// keyb->assignment[9] = 3;
	// keyb->assignment[10] = 15;
	// keyb->assignment[11] = 6;
	// keyb->assignment[12] = 5;
	// keyb->assignment[13] = 12;
	// keyb->assignment[14] = 22;
	// keyb->assignment[15] = 27;
	// keyb->assignment[16] = 14;
	// keyb->assignment[17] = 1;
	// keyb->assignment[18] = 7;
	// keyb->assignment[19] = 21;
	// keyb->assignment[20] = 11;
	// keyb->assignment[21] = 0;
	// keyb->assignment[22] = 20;
	// keyb->assignment[23] = 10;
	// keyb->assignment[24] = 18;
	// keyb->assignment[25] = 28;
	// keyb->assignment[26] = 33;
	// keyb->assignment[27] = 34;
	// keyb->assignment[28] = 35;
	// keyb->assignment[29] = 36;
	// keyb->assignment[30] = 37;

//transladado
	// keyb->grid[1] = 21;
	// keyb->grid[2] = 17;
	// keyb->grid[3] = 8;
	// keyb->grid[4] = 9;
	// keyb->grid[5] = 0;
	// keyb->grid[6] = 12;
	// keyb->grid[7] = 11;
	// keyb->grid[8] = 18;
	// keyb->grid[11] = 23;
	// keyb->grid[12] = 20;
	// keyb->grid[13] = 13;
	// keyb->grid[14] = 5;
	// keyb->grid[15] = 16;
	// keyb->grid[16] = 10;
	// keyb->grid[17] = 1;
	// keyb->grid[18] = 2;
	// keyb->grid[19] = 24;
	// keyb->grid[21] = 22;
	// keyb->grid[22] = 19;
	// keyb->grid[23] = 14;
	// keyb->grid[24] = 4;
	// keyb->grid[25] = 3;
	// keyb->grid[26] = 6;
	// keyb->grid[27] = 7;
	// keyb->grid[28] = 15;
	// keyb->grid[29] = 25;
	// keyb->grid[33] = 26;
	// keyb->grid[34] = 27;
	// keyb->grid[35] = 28;
	// keyb->grid[36] = 29;
	// keyb->grid[37] = 30;

	// keyb->assignment[0] = 5;
	// keyb->assignment[1] = 17;
	// keyb->assignment[2] = 18;
	// keyb->assignment[3] = 25;
	// keyb->assignment[4] = 24;
	// keyb->assignment[5] = 14;
	// keyb->assignment[6] = 26;
	// keyb->assignment[7] = 27;
	// keyb->assignment[8] = 3;
	// keyb->assignment[9] = 4;
	// keyb->assignment[10] = 16;
	// keyb->assignment[11] = 7;
	// keyb->assignment[12] = 6;
	// keyb->assignment[13] = 13;
	// keyb->assignment[14] = 23;
	// keyb->assignment[15] = 28;
	// keyb->assignment[16] = 15;
	// keyb->assignment[17] = 2;
	// keyb->assignment[18] = 8;
	// keyb->assignment[19] = 22;
	// keyb->assignment[20] = 12;
	// keyb->assignment[21] = 1;
	// keyb->assignment[22] = 21;
	// keyb->assignment[23] = 11;
	// keyb->assignment[24] = 19;
	// keyb->assignment[25] = 29;
	// keyb->assignment[26] = 33;
	// keyb->assignment[27] = 34;
	// keyb->assignment[28] = 35;
	// keyb->assignment[29] = 36;
	// keyb->assignment[30] = 37;

//transladado e espelhado

	keyb->grid[1] = 18;
	keyb->grid[2] = 11;
	keyb->grid[3] = 12;
	keyb->grid[4] = 0;
	keyb->grid[5] = 9;
	keyb->grid[6] = 8;
	keyb->grid[7] = 17;
	keyb->grid[8] = 21;
	keyb->grid[11] = 24;
	keyb->grid[12] = 2;
	keyb->grid[13] = 1;
	keyb->grid[14] = 10;
	keyb->grid[15] = 16;
	keyb->grid[16] = 5;
	keyb->grid[17] = 13;
	keyb->grid[18] = 20;
	keyb->grid[19] = 23;
	keyb->grid[21] = 25;
	keyb->grid[22] = 15;
	keyb->grid[23] = 7;
	keyb->grid[24] = 6;
	keyb->grid[25] = 3;
	keyb->grid[26] = 4;
	keyb->grid[27] = 14;
	keyb->grid[28] = 19;
	keyb->grid[29] = 22;
	keyb->grid[33] = 26;
	keyb->grid[34] = 27;
	keyb->grid[35] = 28;
	keyb->grid[36] = 29;
	keyb->grid[37] = 30;

	keyb->assignment[0] = 4;
	keyb->assignment[1] = 13;
	keyb->assignment[2] = 12;
	keyb->assignment[3] = 25;
	keyb->assignment[4] = 26;
	keyb->assignment[5] = 16;
	keyb->assignment[6] = 24;
	keyb->assignment[7] = 23;
	keyb->assignment[8] = 6;
	keyb->assignment[9] = 5;
	keyb->assignment[10] = 14;
	keyb->assignment[11] = 2;
	keyb->assignment[12] = 3;
	keyb->assignment[13] = 17;
	keyb->assignment[14] = 27;
	keyb->assignment[15] = 22;
	keyb->assignment[16] = 15;
	keyb->assignment[17] = 7;
	keyb->assignment[18] = 1;
	keyb->assignment[19] = 28;
	keyb->assignment[20] = 18;
	keyb->assignment[21] = 8;
	keyb->assignment[22] = 29;
	keyb->assignment[23] = 19;
	keyb->assignment[24] = 11;
	keyb->assignment[25] = 21;
	keyb->assignment[26] = 33;
	keyb->assignment[27] = 34;
	keyb->assignment[28] = 35;
	keyb->assignment[29] = 36;
	keyb->assignment[30] = 37;


	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			if (i == 0 && j == 0){
				cout << " ";
			}
			if (keyb->grid[count] != -1)
				cout << setw(3) << data->char_list[keyb->grid[count]];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}
}

void hybPt (Gendata *data, Keyboard *keyb){
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
//E A O S R I D N T M  C  U  P  L  V  F  G  B  Q  H  Z  J  X  W  Y  K  _  _  _  _  _
	
	// keyb->kcols = 10;
	// keyb->krows = 4;

	// keyb->grid = new int [keyb->ksize];

	// for (int i = 0; i < keyb->ksize; i++){
	// 	keyb->grid[i] = -1;
	// }
	
	// keyb->assignment = new int [data->size];

	// for (int i = 0; i < data->size; i++){
	// 	keyb->assignment[i] = -1;
	// }

	// keyb->grid[1] = 22;
	// keyb->grid[2] = 18;
	// keyb->grid[3] = 11;
	// keyb->grid[4] = 8;
	// keyb->grid[5] = 7;
	// keyb->grid[6] = 10;
	// keyb->grid[7] = 14;
	// keyb->grid[8] = 20;
	// keyb->grid[11] = 21;
	// keyb->grid[12] = 16;
	// keyb->grid[13] = 9;
	// keyb->grid[14] = 0;
	// keyb->grid[15] = 3;
	// keyb->grid[16] = 1;
	// keyb->grid[17] = 5;
	// keyb->grid[18] = 15;
	// keyb->grid[19] = 23;
	// keyb->grid[21] = 25;
	// keyb->grid[22] = 17;
	// keyb->grid[23] = 12;
	// keyb->grid[24] = 4;
	// keyb->grid[25] = 2;
	// keyb->grid[26] = 6;
	// keyb->grid[27] = 13;
	// keyb->grid[28] = 19;
	// keyb->grid[29] = 24;
	// keyb->grid[33] = 26;
	// keyb->grid[34] = 27;
	// keyb->grid[35] = 28;
	// keyb->grid[36] = 29;
	// keyb->grid[37] = 30;

	// keyb->assignment[0] = 14;
	// keyb->assignment[1] = 16;
	// keyb->assignment[2] = 25;
	// keyb->assignment[3] = 15;
	// keyb->assignment[4] = 24;
	// keyb->assignment[5] = 17;
	// keyb->assignment[6] = 26;
	// keyb->assignment[7] = 5;
	// keyb->assignment[8] = 4;
	// keyb->assignment[9] = 13;
	// keyb->assignment[10] = 6;
	// keyb->assignment[11] = 3;
	// keyb->assignment[12] = 23;
	// keyb->assignment[13] = 27;
	// keyb->assignment[14] = 7;
	// keyb->assignment[15] = 18;
	// keyb->assignment[16] = 12;
	// keyb->assignment[17] = 22;
	// keyb->assignment[18] = 2;
	// keyb->assignment[19] = 28;
	// keyb->assignment[20] = 8;
	// keyb->assignment[21] = 11;
	// keyb->assignment[22] = 1;
	// keyb->assignment[23] = 19;
	// keyb->assignment[24] = 29;
	// keyb->assignment[25] = 21;
	// keyb->assignment[26] = 33;
	// keyb->assignment[27] = 34;
	// keyb->assignment[28] = 35;
	// keyb->assignment[29] = 36;
	// keyb->assignment[30] = 37;

	// int count = 0;
	
	// for (int i = 0; i < keyb->krows; i++){
	// 	for (int j = 0; j < keyb->kcols; j++){
	// 		if (i == 0 && j == 0){
	// 			cout << " ";
	// 		}
	// 		if (keyb->grid[count] != -1)
	// 			cout << setw(3) << data->char_list[keyb->grid[count]];
	// 		else
	// 			cout<< setw(3) << "*";
	// 		count++;
	// 	}
	// 	cout << endl;
	// }

// Best Solution: 
//   *  J  Q  U  D  O  C  F  Z  *
//   *  X  G  M  E  S  N  I  V  K
//   *  Y  B  P  R  A  T  L  H  W

// -----x-----
// Best Global Solution Cost: 8057857843

//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
//T H E O F A N D I W  S  R  Y  U  B  C  V  M  L  P  K  G  J  Q  X  Z  _  _  _  _  _ 

	keyb->kcols = 10;
	keyb->krows = 4;

	keyb->grid = new int [keyb->ksize];

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = -1;
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}

	keyb->grid[1] = 22;
	keyb->grid[2] = 23;
	keyb->grid[3] = 13;
	keyb->grid[4] = 7;
	keyb->grid[5] = 3;
	keyb->grid[6] = 15;
	keyb->grid[7] = 4;
	keyb->grid[8] = 25;
	keyb->grid[11] = 24;
	keyb->grid[12] = 21;
	keyb->grid[13] = 17;
	keyb->grid[14] = 2;
	keyb->grid[15] = 10;
	keyb->grid[16] = 6;
	keyb->grid[17] = 8;
	keyb->grid[18] = 16;
	keyb->grid[19] = 20;
	keyb->grid[21] = 12;
	keyb->grid[22] = 14;
	keyb->grid[23] = 19;
	keyb->grid[24] = 11;
	keyb->grid[25] = 5;
	keyb->grid[26] = 0;
	keyb->grid[27] = 18;
	keyb->grid[28] = 1;
	keyb->grid[29] = 9;
	keyb->grid[33] = 26;
	keyb->grid[34] = 27;
	keyb->grid[35] = 28;
	keyb->grid[36] = 29;
	keyb->grid[37] = 30;

	keyb->assignment[0] = 14;
	keyb->assignment[1] = 16;
	keyb->assignment[2] = 25;
	keyb->assignment[3] = 15;
	keyb->assignment[4] = 24;
	keyb->assignment[5] = 17;
	keyb->assignment[6] = 26;
	keyb->assignment[7] = 5;
	keyb->assignment[8] = 4;
	keyb->assignment[9] = 13;
	keyb->assignment[10] = 6;
	keyb->assignment[11] = 3;
	keyb->assignment[12] = 23;
	keyb->assignment[13] = 27;
	keyb->assignment[14] = 7;
	keyb->assignment[15] = 18;
	keyb->assignment[16] = 12;
	keyb->assignment[17] = 22;
	keyb->assignment[18] = 2;
	keyb->assignment[19] = 28;
	keyb->assignment[20] = 8;
	keyb->assignment[21] = 11;
	keyb->assignment[22] = 1;
	keyb->assignment[23] = 19;
	keyb->assignment[24] = 29;
	keyb->assignment[25] = 21;
	keyb->assignment[26] = 33;
	keyb->assignment[27] = 34;
	keyb->assignment[28] = 35;
	keyb->assignment[29] = 36;
	keyb->assignment[30] = 37;

	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			if (i == 0 && j == 0){
				cout << " ";
			}
			if (keyb->grid[count] != -1)
				cout << setw(3) << data->char_list[keyb->grid[count]];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}

}

void hybSp (Gendata *data, Keyboard *keyb){

	//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
	//D E Q U N O A L S Y  P  R  M  T  C  I  H  B  G  V  F  Z  J  ñ  K  X  W  _  _  _  _  _

	vector<int> v1;
	vector<int> v2;
	vector<int> v3;
	vector<int> v4;
	vector<int> v5;

	int sp;

	keyb->kcols = 10;
	keyb->krows = 4;

	keyb->grid = new int [keyb->ksize];

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = -1;
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}

	keyb->grid[0] = 20;
	keyb->grid[1] = 18;
	keyb->grid[2] = 13;
	keyb->grid[3] = 8;
	keyb->grid[4] = 5;
	keyb->grid[5] = 7;
	keyb->grid[6] = 10;
	keyb->grid[7] = 9;
	keyb->grid[8] = 26;
	keyb->grid[10] = 2;
	keyb->grid[11] = 3;
	keyb->grid[12] = 4;
	keyb->grid[13] = 1;
	keyb->grid[14] = 11;
	keyb->grid[15] = 6;
	keyb->grid[16] = 16;
	keyb->grid[17] = 21;
	keyb->grid[18] = 24;
	keyb->grid[20] = 25;
	keyb->grid[21] = 19;
	keyb->grid[22] = 14;
	keyb->grid[23] = 15;
	keyb->grid[24] = 0;
	keyb->grid[25] = 12;
	keyb->grid[26] = 17;
	keyb->grid[27] = 22;
	keyb->grid[28] = 23;
	keyb->grid[33] = 27;
	keyb->grid[34] = 28;
	keyb->grid[35] = 29;
	keyb->grid[36] = 30;
	keyb->grid[37] = 31;

	keyb->assignment[0] = 24;
	keyb->assignment[1] = 13;
	keyb->assignment[2] = 10;
	keyb->assignment[3] = 11;
	keyb->assignment[4] = 12;
	keyb->assignment[5] = 4;
	keyb->assignment[6] = 15;
	keyb->assignment[7] = 5;
	keyb->assignment[8] = 3;
	keyb->assignment[9] = 7;
	keyb->assignment[10] = 6;
	keyb->assignment[11] = 14;
	keyb->assignment[12] = 25;
	keyb->assignment[13] = 2;
	keyb->assignment[14] = 22;
	keyb->assignment[15] = 23;
	keyb->assignment[16] = 16;
	keyb->assignment[17] = 26;
	keyb->assignment[18] = 1;
	keyb->assignment[19] = 21;
	keyb->assignment[20] = 0;
	keyb->assignment[21] = 17;
	keyb->assignment[22] = 27;
	keyb->assignment[23] = 28;
	keyb->assignment[24] = 18;
	keyb->assignment[25] = 20;
	keyb->assignment[26] = 8;
	keyb->assignment[27] = 33;
	keyb->assignment[28] = 34;
	keyb->assignment[29] = 35;
	keyb->assignment[30] = 36;
	keyb->assignment[31] = 37;

//transladado

	// keyb->grid[1] = 20;
	// keyb->grid[2] = 18;
	// keyb->grid[3] = 13;
	// keyb->grid[4] = 8;
	// keyb->grid[5] = 5;
	// keyb->grid[6] = 7;
	// keyb->grid[7] = 10;
	// keyb->grid[8] = 9;
	// keyb->grid[9] = 26;
	// keyb->grid[11] = 2;
	// keyb->grid[12] = 3;
	// keyb->grid[13] = 4;
	// keyb->grid[14] = 1;
	// keyb->grid[15] = 11;
	// keyb->grid[16] = 6;
	// keyb->grid[17] = 16;
	// keyb->grid[18] = 21;
	// keyb->grid[19] = 24;
	// keyb->grid[21] = 25;
	// keyb->grid[22] = 19;
	// keyb->grid[23] = 14;
	// keyb->grid[24] = 15;
	// keyb->grid[25] = 0;
	// keyb->grid[26] = 12;
	// keyb->grid[27] = 17;
	// keyb->grid[28] = 22;
	// keyb->grid[29] = 23;
	// keyb->grid[33] = 27;
	// keyb->grid[34] = 28;
	// keyb->grid[35] = 29;
	// keyb->grid[36] = 30;
	// keyb->grid[37] = 31;

	// keyb->assignment[0] = 25;
	// keyb->assignment[1] = 14;
	// keyb->assignment[2] = 11;
	// keyb->assignment[3] = 12;
	// keyb->assignment[4] = 13;
	// keyb->assignment[5] = 5;
	// keyb->assignment[6] = 16;
	// keyb->assignment[7] = 6;
	// keyb->assignment[8] = 4;
	// keyb->assignment[9] = 8;
	// keyb->assignment[10] = 7;
	// keyb->assignment[11] = 15;
	// keyb->assignment[12] = 26;
	// keyb->assignment[13] = 3;
	// keyb->assignment[14] = 23;
	// keyb->assignment[15] = 24;
	// keyb->assignment[16] = 17;
	// keyb->assignment[17] = 27;
	// keyb->assignment[18] = 2;
	// keyb->assignment[19] = 22;
	// keyb->assignment[20] = 1;
	// keyb->assignment[21] = 18;
	// keyb->assignment[22] = 28;
	// keyb->assignment[23] = 29;
	// keyb->assignment[24] = 19;
	// keyb->assignment[25] = 21;
	// keyb->assignment[26] = 9;
	// keyb->assignment[27] = 33;
	// keyb->assignment[28] = 34;
	// keyb->assignment[29] = 35;
	// keyb->assignment[30] = 36;
	// keyb->assignment[31] = 37;

	//  	cout << "\n0." << endl;
	//  	getchar();

	// long long bestSp;

	// for (int i = 0; i < 33; i++){
	// 	bestSp = numeric_limits<long long>::max();
	// 	for (int j = 33; j < 38; j++){

	// 		if(data->b_matrix[i][j] < bestSp){
	// 			bestSp = data->b_matrix[i][j];
	// 			sp = j;
	// 		}
	// 	}
	// 	switch(sp){
	// 		case 33:
	// 			v1.push_back(i);
	// 			break;

	// 		case 34:
	// 			v2.push_back(i);
	// 			break;

	// 		case 35:
	// 			v3.push_back(i);
	// 			break;
			
	// 		case 36:
	// 			v4.push_back(i);
	// 			break;

	// 		case 37:
	// 			v5.push_back(i);
	// 			break;
	// 	}
	// }
	// cout << "\n1." << endl;
	// getchar();

	// cout << "\nv1: ";
	// for (int i = 0; i < v1.size(); i++){
	// 	cout << v1[i] << " ";
	// }
	// cout << endl;
	
	// cout << "\nv2: ";
	// for (int i = 0; i < v2.size(); i++){
	// 	cout << v2[i] << " ";
	// }
	// cout << endl;	
	
	// cout << "\nv3: ";
	// for (int i = 0; i < v3.size(); i++){
	// 	cout << v3[i] << " ";
	// }
	// cout << endl;	
	
	// cout << "\nv4: ";
	// for (int i = 0; i < v4.size(); i++){
	// 	cout << v4[i] << " ";
	// }
	// cout << endl;
	
	// cout << "\nv5: ";
	// for (int i = 0; i < v5.size(); i++){
	// 	cout << v5[i] << " ";
	// }
	// cout << endl;

	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			if (i == 0 && j == 0){
				cout << " ";
			}
			if (i == 1 && j == 0){
				cout << " ";
			}
			if (keyb->grid[count] != -1)
				cout << setw(3) << data->char_list[keyb->grid[count]];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}
}

void hybFr (Gendata *data, Keyboard *keyb){
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
//D E L A ' T S N U Q  I  P  R  O  C  X  V  M  Y  F  B  G  H  J  W  Z  K  _  _  _  _  _
	
	keyb->kcols = 10;
	keyb->krows = 4;

	keyb->grid = new int [keyb->ksize];

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = -1;
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}

	// keyb->grid[0] = 23;
	// keyb->grid[1] = 4;
	// keyb->grid[2] = 0;
	// keyb->grid[3] = 6;
	// keyb->grid[4] = 7;
	// keyb->grid[5] = 13;
	// keyb->grid[6] = 14;
	// keyb->grid[7] = 22;
	// keyb->grid[8] = 25;
	// keyb->grid[10] = 15;
	// keyb->grid[11] = 9;
	// keyb->grid[12] = 8;
	// keyb->grid[13] = 1;
	// keyb->grid[14] = 5;
	// keyb->grid[15] = 10;
	// keyb->grid[16] = 17;
	// keyb->grid[17] = 19;
	// keyb->grid[18] = 26;
	// keyb->grid[21] = 20;
	// keyb->grid[22] = 16;
	// keyb->grid[23] = 2;
	// keyb->grid[24] = 12;
	// keyb->grid[25] = 3;
	// keyb->grid[26] = 11;
	// keyb->grid[27] = 21;
	// keyb->grid[28] = 18;
	// keyb->grid[29] = 24;
	// keyb->grid[33] = 27;
	// keyb->grid[34] = 28;
	// keyb->grid[35] = 29;
	// keyb->grid[36] = 30;
	// keyb->grid[37] = 31;

	// keyb->assignment[0] = 2;
	// keyb->assignment[1] = 13;
	// keyb->assignment[2] = 23;
	// keyb->assignment[3] = 25;
	// keyb->assignment[4] = 1;
	// keyb->assignment[5] = 14;
	// keyb->assignment[6] = 3;
	// keyb->assignment[7] = 4;
	// keyb->assignment[8] = 12;
	// keyb->assignment[9] = 11;
	// keyb->assignment[10] = 15;
	// keyb->assignment[11] = 26;
	// keyb->assignment[12] = 24;
	// keyb->assignment[13] = 5;
	// keyb->assignment[14] = 6;
	// keyb->assignment[15] = 10;
	// keyb->assignment[16] = 22;
	// keyb->assignment[17] = 16;
	// keyb->assignment[18] = 28;
	// keyb->assignment[19] = 17;
	// keyb->assignment[20] = 21;
	// keyb->assignment[21] = 27;
	// keyb->assignment[22] = 7;
	// keyb->assignment[23] = 0;
	// keyb->assignment[24] = 29;
	// keyb->assignment[25] = 8;
	// keyb->assignment[26] = 18;
	// keyb->assignment[27] = 33;
	// keyb->assignment[28] = 34;
	// keyb->assignment[29] = 35;
	// keyb->assignment[30] = 36;
	// keyb->assignment[31] = 37;
//mirrored
	
	keyb->grid[1] = 25;
	keyb->grid[2] = 22;
	keyb->grid[3] = 14;
	keyb->grid[4] = 13;
	keyb->grid[5] = 7;
	keyb->grid[6] = 6;
	keyb->grid[7] = 0;
	keyb->grid[8] = 4;
	keyb->grid[9] = 23;
	keyb->grid[11] = 26;
	keyb->grid[12] = 19;
	keyb->grid[13] = 17;
	keyb->grid[14] = 10;
	keyb->grid[15] = 5;
	keyb->grid[16] = 1;
	keyb->grid[17] = 8;
	keyb->grid[18] = 9;
	keyb->grid[19] = 15;
	keyb->grid[21] = 24;
	keyb->grid[22] = 18;
	keyb->grid[23] = 21;
	keyb->grid[24] = 11;
	keyb->grid[25] = 3;
	keyb->grid[26] = 12;
	keyb->grid[27] = 2;
	keyb->grid[28] = 16;
	keyb->grid[29] = 20;
	keyb->grid[33] = 27;
	keyb->grid[34] = 28;
	keyb->grid[35] = 29;
	keyb->grid[36] = 30;
	keyb->grid[37] = 31;

	keyb->assignment[0] = 7;
	keyb->assignment[1] = 16;
	keyb->assignment[2] = 27;
	keyb->assignment[3] = 25;
	keyb->assignment[4] = 8;
	keyb->assignment[5] = 15;
	keyb->assignment[6] = 6;
	keyb->assignment[7] = 5;
	keyb->assignment[8] = 17;
	keyb->assignment[9] = 18;
	keyb->assignment[10] = 14;
	keyb->assignment[11] = 24;
	keyb->assignment[12] = 26;
	keyb->assignment[13] = 4;
	keyb->assignment[14] = 3;
	keyb->assignment[15] = 19;
	keyb->assignment[16] = 28;
	keyb->assignment[17] = 13;
	keyb->assignment[18] = 22;
	keyb->assignment[19] = 12;
	keyb->assignment[20] = 29;
	keyb->assignment[21] = 23;
	keyb->assignment[22] = 2;
	keyb->assignment[23] = 9;
	keyb->assignment[24] = 21;
	keyb->assignment[25] = 1;
	keyb->assignment[26] = 11;
	keyb->assignment[27] = 33;
	keyb->assignment[28] = 34;
	keyb->assignment[29] = 35;
	keyb->assignment[30] = 36;
	keyb->assignment[31] = 37;

	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			if (i == 0 && j == 0){
				cout << " ";
			}
			if (i == 1 && j == 0){
				cout << " ";
			}
			if (keyb->grid[count] != -1)
				cout << setw(3) << data->char_list[keyb->grid[count]];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}
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

long long qwertyItCalc (Gendata *data, Keyboard *keyb){

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

	for (int i = 0; i < data->size - 5; i++){

		pos = keyb->assignment[i];

		switch (pos % keyb->kcols){
			case 0:
				next = keyb->assignment[26];
				costc += ( data->freq_matrix[i][26] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[26] << " freq: " << data->freq_matrix[i][26] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
			case 1:
				next = keyb->assignment[26];
				costc += ( data->freq_matrix[i][26] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[26] << " freq: " << data->freq_matrix[i][26] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
			case 2:
				next = keyb->assignment[26];
				costc += ( data->freq_matrix[i][26] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[26] << " freq: " << data->freq_matrix[i][26] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
			case 3:
				next = keyb->assignment[26];
				costc += ( data->freq_matrix[i][26] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[26] << " freq: " << data->freq_matrix[i][26] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
			case 4:
				next = keyb->assignment[27];
				costc += ( data->freq_matrix[i][27] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[27] << " freq: " << data->freq_matrix[i][27] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
			case 5:
				next = keyb->assignment[28];
				costc += ( data->freq_matrix[i][28] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[28] << " freq: " << data->freq_matrix[i][28] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
			case 6:
				next = keyb->assignment[29];
				costc += ( data->freq_matrix[i][29] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[29] << " freq: " << data->freq_matrix[i][29] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
			case 7:
				next = keyb->assignment[30];
				costc += ( data->freq_matrix[i][30] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[29] << " freq: " << data->freq_matrix[i][29] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
			case 8:
				next = keyb->assignment[30];
				costc += ( data->freq_matrix[i][30] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[29] << " freq: " << data->freq_matrix[i][29] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
			case 9:
				next = keyb->assignment[30];
				costc += ( data->freq_matrix[i][30] * data->b_matrix[pos][next]);
				//cout << "\ni: " << data->char_list[i] << " j: " << data->char_list[29] << " freq: " << data->freq_matrix[i][29] << " mat: " << data->b_matrix[pos][next] <<  endl;
				break;
		}
	}// for 'i'

	return costc;
}

void optAssign (Gendata *data, Keyboard *keyb){
	
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

	keyb->grid[1] = 22;
	keyb->grid[2] = 4;
	keyb->grid[3] = 9;
	keyb->grid[4] = 14;
	keyb->grid[5] = 24;
	keyb->grid[14] = 23;
	keyb->grid[15] = 13;
	keyb->grid[16] = 3;
	keyb->grid[17] = 0;
	keyb->grid[18] = 1;
	keyb->grid[19] = 15;
	keyb->grid[29] = 17;
	keyb->grid[30] = 10;
	keyb->grid[31] = 26;
	keyb->grid[32] = 2;
	keyb->grid[33] = 11;
	keyb->grid[34] = 20;
	keyb->grid[43] = 19;
	keyb->grid[44] = 8;
	keyb->grid[45] = 6;
	keyb->grid[46] = 5;
	keyb->grid[47] = 12;
	keyb->grid[57] = 25;
	keyb->grid[58] = 21;
	keyb->grid[59] = 7;
	keyb->grid[60] = 18;
	keyb->grid[61] = 16;

	keyb->assignment[0] = 17;
	keyb->assignment[1] = 18;
	keyb->assignment[2] = 32;
	keyb->assignment[3] = 16;
	keyb->assignment[4] = 2;
	keyb->assignment[5] = 46;
	keyb->assignment[6] = 45;
	keyb->assignment[7] = 59;
	keyb->assignment[8] = 44;
	keyb->assignment[9] = 3;
	keyb->assignment[10] = 30;
	keyb->assignment[11] = 33;
	keyb->assignment[12] = 47;
	keyb->assignment[13] = 15;
	keyb->assignment[14] = 4;
	keyb->assignment[15] = 19;
	keyb->assignment[16] = 61;
	keyb->assignment[17] = 29;
	keyb->assignment[18] = 60;
	keyb->assignment[19] = 43;
	keyb->assignment[20] = 34;
	keyb->assignment[21] = 58;
	keyb->assignment[22] = 1;
	keyb->assignment[23] = 14;
	keyb->assignment[24] = 5;
	keyb->assignment[25] = 57;
	keyb->assignment[26] = 31;

	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			if (keyb->grid[count] != -1)
				cout << setw(3) << data->char_list[keyb->grid[count]];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}

	long long costc = 0;
	int pos = 0;
	int next = 0;
	int currCol;

	long long currCost;

	for (int i = 0; i < data->size; i++){

		pos = keyb->assignment[i];

		for (int j = 0; j < data->size; j++){
			if (j != i){
				//cout << "i: " << data->char_list[i] << " j: " << data->char_list[j] << endl;
				next = keyb->assignment[j];

				costc += ( data->freq_matrix[i][j] * data->b_matrix[pos][next]);
			}
		}//for 'j'		
	}// for 'i'

	costc = costc / 2;
	cout << "\nOpt Cost: " << costc << endl;
}

// void newItInst(Gendata *data, Keyboard *keyb){

// 	//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33
// 	//E C H I L A N U è P R  O  D  '  S  ù  M  G  Q  T  é  V  ì  F  Z  ò  à  B  X  W  Y  K  J  ø 

// 	//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
// 	//E C H I L A N U P R  O  D  S  M  G  Q  T  V  F  Z  B  X  W  Y  K  J  _ 

// 	vector<int> vec1 = {0, 3, 5, 7, 8, 11, 15, 20, 22, 25, 26};

// 	//0 + 8 + 20
// 	//3 + 22
// 	//5 + 26
// 	//7 + 15
// 	//11 + 25

// 	long long fmat [data->size][data->size] = {0};

// 	for (int i = 0; i < data->size; i++){
// 		for (int j = 0; j < data->size; j++){
// 			fmat[i][j] = data->freq_matrix[i][j];
// 		}
// 	}

// 	//cout << "\nTeste: " << fmat[12][22] << endl;

// 	for (int i = 0; i < data->size; i++){
// 		for (int j = 0; j < data->size; j++){
// 			if(i == 0){
// 				fmat[0][j] = data->freq_matrix[0][j] + data->freq_matrix[8][j] + data->freq_matrix[20][j];
// 				fmat[j][0] = data->freq_matrix[j][0] + data->freq_matrix[j][8] + data->freq_matrix[j][20];
// 				//cout << j << ": " << fmat[0][j] << endl;
// 			}
// 			else if(i == 3){
// 				fmat[3][j] = data->freq_matrix[3][j] + data->freq_matrix[22][j];
// 				fmat[j][3] = data->freq_matrix[j][3] + data->freq_matrix[j][22];
// 			}
// 			else if(i == 5){
// 				fmat[5][j] = data->freq_matrix[5][j] + data->freq_matrix[26][j];
// 				fmat[j][5] = data->freq_matrix[j][5] + data->freq_matrix[j][26];
// 			}
// 			else if(i == 7){
// 				fmat[7][j] = data->freq_matrix[7][j] + data->freq_matrix[15][j];
// 				fmat[j][7] = data->freq_matrix[j][7] + data->freq_matrix[j][15];
// 			}
// 			else if(i == 11){
// 				fmat[11][j] = data->freq_matrix[11][j] + data->freq_matrix[25][j];
// 				fmat[j][11] = data->freq_matrix[j][11] + data->freq_matrix[j][25];
// 			}
// 			else{
// 				continue;
// 			}
// 		}
// 	}

// 	cout << "n = " << 27 << endl;

// 	for(int i = 0; i < data->size; i++){
// 		if (i == 8 || i == 13 || i == 15 || i == 20 || i == 22 || i == 25 || i == 26){
// 			continue;
// 		}
// 		else{
// 			for(int j = 0; j < data->size; j++){
// 				if (i == j){
// 					fmat[i][j] = 0;
// 				}
// 				if (j == 8 || j == 13 || j == 15 || j == 20 || j == 22 || j == 25 || j == 26){
// 					continue;
// 				}
// 				else{
// 					cout << setw(6) << std::right << fmat[i][j] << " ";
// 				}
// 			}
// 			cout << endl;
// 		}

// 	}
// }

// void newFrInst(Gendata *data, Keyboard *keyb){

// 	//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
// 	//D E L A ' T S à N U  Q  I  P  R  O  C  X  V  M  Y  ê  é  F  ù  B  G  è  H  J  ç  ô  ë  W  Z  â  K  û  î  ï  ä  ø 

// 	//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27
// 	//D E L A ' T S N U Q  I  P  R  O  C  X  V  M  Y  F  B  G  H  J  W  Z  K  ø

// 	//1 + 20 + 21 + 26 + 31
// 	//3 + 7 + 34 + 39 
// 	//9 + 23 + 36
// 	//11 + 37 + 38
// 	//14 + 30
// 	//15 + 29

// 	long long fmat [data->size][data->size] = {0};

// 	for (int i = 0; i < data->size; i++){
// 		for (int j = 0; j < data->size; j++){
// 			fmat[i][j] = data->freq_matrix[i][j];
// 		}
// 	}

// 	for (int i = 0; i < data->size; i++){
// 		for (int j = 0; j < data->size; j++){
// 			if(i == 1){
// 				fmat[1][j] = data->freq_matrix[1][j] + data->freq_matrix[20][j] + data->freq_matrix[21][j] + data->freq_matrix[26][j] + data->freq_matrix[31][j];
// 				fmat[j][1] = data->freq_matrix[j][1] + data->freq_matrix[j][20] + data->freq_matrix[j][21] + data->freq_matrix[j][26] + data->freq_matrix[j][31];
// 				//cout << j << ": " << fmat[0][j] << endl;
// 			}
// 			else if(i == 3){
// 				fmat[3][j] = data->freq_matrix[3][j] + data->freq_matrix[7][j] + data->freq_matrix[34][j] + data->freq_matrix[39][j];
// 				fmat[j][3] = data->freq_matrix[j][3] + data->freq_matrix[j][7] + data->freq_matrix[j][34] + data->freq_matrix[j][39];
// 			}
// 			else if(i == 9){
// 				fmat[9][j] = data->freq_matrix[9][j] + data->freq_matrix[23][j] + data->freq_matrix[36][j];
// 				fmat[j][9] = data->freq_matrix[j][9] + data->freq_matrix[j][23] + data->freq_matrix[j][36];
// 			}
// 			else if(i == 11){
// 				fmat[11][j] = data->freq_matrix[11][j] + data->freq_matrix[37][j] + data->freq_matrix[38][j];
// 				fmat[j][11] = data->freq_matrix[j][11] + data->freq_matrix[j][37] + data->freq_matrix[j][38];
// 			}
// 			else if(i == 14){
// 				fmat[14][j] = data->freq_matrix[14][j] + data->freq_matrix[30][j];
// 				fmat[j][14] = data->freq_matrix[j][14] + data->freq_matrix[j][30];
// 			}
// 			else if(i == 15){
// 				fmat[15][j] = data->freq_matrix[15][j] + data->freq_matrix[29][j];
// 				fmat[j][15] = data->freq_matrix[j][15] + data->freq_matrix[j][29];
// 			}
// 			else{
// 				continue;
// 			}
// 		}
// 	}

// 	cout << "n = " << 28 << endl;

// 	for(int i = 0; i < data->size; i++){
// 		if (i == 7 || i == 20 || i == 21 || i == 23 || i == 26 || i == 29 || i == 30 || i == 31 || i == 34 || i == 36 || i == 37 || i == 38 || i == 39){
// 			continue;
// 		}
// 		else{
// 			for(int j = 0; j < data->size; j++){
// 				if (i == j){
// 					fmat[i][j] = 0;
// 				}
// 				if (j == 7 || j == 20 || j == 21 || j == 23 || j == 26 || j == 29 || j == 30 || j == 31 || j == 34 || j == 36 || j == 37 || j == 38 || j == 39){
// 					continue;
// 				}
// 				else{
// 					cout << setw(7) << std::right << fmat[i][j] << " ";
// 				}
// 			}
// 			cout << endl;
// 		}

// 	}
// }

// void newSpInst(Gendata *data, Keyboard *keyb){

// 	//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 
// 	//D E Q U N O A L S Y  P  R  M  e  T  C  I  a  i  H  B  G  o  V  u  F  Z  J  n  K  X  W  w  _  

// 	//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27
// 	//D E Q U N O A L S Y  P  R  M  T  C  I  H  B  G  V  F  Z  J  ñ  K  X  W  _

// 	//1 + 13
// 	//3 + 24 + 32
// 	//5 + 17
// 	//6 + 22
// 	//16 + 18

// 	long long fmat [data->size][data->size] = {0};

// 	for (int i = 0; i < data->size; i++){
// 		for (int j = 0; j < data->size; j++){
// 			fmat[i][j] = data->freq_matrix[i][j];
// 		}
// 	}

// 	for (int i = 0; i < data->size; i++){
// 		for (int j = 0; j < data->size; j++){
// 			if(i == 1){
// 				fmat[1][j] = data->freq_matrix[1][j] + data->freq_matrix[13][j];
// 				fmat[j][1] = data->freq_matrix[j][1] + data->freq_matrix[j][13];
// 			}
// 			else if(i == 3){
// 				fmat[3][j] = data->freq_matrix[3][j] + data->freq_matrix[24][j] + data->freq_matrix[32][j];
// 				fmat[j][3] = data->freq_matrix[j][3] + data->freq_matrix[j][24] + data->freq_matrix[j][32];
// 			}
// 			else if(i == 5){
// 				fmat[5][j] = data->freq_matrix[5][j] + data->freq_matrix[17][j];
// 				fmat[j][5] = data->freq_matrix[j][5] + data->freq_matrix[j][17];
// 			}
// 			else if(i == 6){
// 				fmat[6][j] = data->freq_matrix[6][j] + data->freq_matrix[22][j];
// 				fmat[j][6] = data->freq_matrix[j][6] + data->freq_matrix[j][22];
// 			}
// 			else if(i == 16){
// 				fmat[16][j] = data->freq_matrix[16][j] + data->freq_matrix[18][j];
// 				fmat[j][16] = data->freq_matrix[j][16] + data->freq_matrix[j][18];
// 			}
// 			else{
// 				continue;
// 			}
// 		}
// 	}

// 	cout << "n = " << 28 << endl;

// 	for(int i = 0; i < data->size; i++){
// 		if (i == 13 || i == 17 || i == 18 || i == 22 || i == 24 || i == 32){
// 			continue;
// 		}
// 		else{
// 			for(int j = 0; j < data->size; j++){
// 				if (i == j){
// 					fmat[i][j] = 0;
// 				}
// 				if (j == 13 || j == 17 || j == 18 || j == 22 || j == 24 || j == 32){
// 					continue;
// 				}
// 				else{
// 					cout << setw(6) << std::right << fmat[i][j] << " ";
// 				}
// 			}
// 			cout << endl;
// 		}

// 	}
// }

// void newPtInst(Gendata *data, Keyboard *keyb){

// 	//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39
// 	//E A O S R I D N T M  C  U  P  L  V  F  Ã  G  B  Q  Ç  H  É  Á  Í  Z  J  X  Ê  Ó  Õ  Ú  À  W  -  Â  Y  K  Ô  _

// 	//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
// 	//E A O S R I D N T M  C  U  P  L  V  F  G  B  Q  H  Z  J  X  W  Y  K  _

// 	//0 + 22 + 28
// 	//1 + 16 + 23 + 32 + 35
// 	//2 + 29 + 30 + 38
// 	//5 + 24
// 	//10 + 20
// 	//11 + 31

// 	long long fmat [data->size][data->size] = {0};

// 	for (int i = 0; i < data->size; i++){
// 		for (int j = 0; j < data->size; j++){
// 			fmat[i][j] = data->freq_matrix[i][j];
// 		}
// 	}

// 	for (int i = 0; i < data->size; i++){
// 		for (int j = 0; j < data->size; j++){
// 			if(i == 0){
// 				fmat[0][j] = data->freq_matrix[0][j] + data->freq_matrix[22][j] + data->freq_matrix[28][j];
// 				fmat[j][0] = data->freq_matrix[j][0] + data->freq_matrix[j][22] + data->freq_matrix[j][28];
// 			}
// 			else if(i == 1){
// 				fmat[1][j] = data->freq_matrix[1][j] + data->freq_matrix[16][j] + data->freq_matrix[23][j] + data->freq_matrix[32][j] + data->freq_matrix[35][j];
// 				fmat[j][1] = data->freq_matrix[j][1] + data->freq_matrix[j][16] + data->freq_matrix[j][23] + data->freq_matrix[j][32] + data->freq_matrix[j][35];
// 			}
// 			else if(i == 2){
// 				fmat[2][j] = data->freq_matrix[2][j] + data->freq_matrix[29][j] + data->freq_matrix[30][j] + data->freq_matrix[38][j];
// 				fmat[j][2] = data->freq_matrix[j][2] + data->freq_matrix[j][29] + data->freq_matrix[j][30] + data->freq_matrix[j][38];
// 			}
// 			else if(i == 5){
// 				fmat[5][j] = data->freq_matrix[5][j] + data->freq_matrix[24][j];
// 				fmat[j][5] = data->freq_matrix[j][5] + data->freq_matrix[j][24];
// 			}
// 			else if(i == 10){
// 				fmat[10][j] = data->freq_matrix[10][j] + data->freq_matrix[20][j];
// 				fmat[j][10] = data->freq_matrix[j][10] + data->freq_matrix[j][20];
// 			}
// 			else if(i == 11){
// 				fmat[11][j] = data->freq_matrix[11][j] + data->freq_matrix[31][j];
// 				fmat[j][11] = data->freq_matrix[j][11] + data->freq_matrix[j][31];
// 			}
// 			else{
// 				continue;
// 			}
// 		}
// 	}

// 	cout << "n = " << 27 << endl;

// 	for(int i = 0; i < data->size; i++){
// 		if (i == 16 || i == 20 || i == 22 || i == 23 || i == 24 || i == 28 || i == 29 || i == 30 || i == 31 || i == 32 || i == 34 || i == 35 || i == 38){
// 			continue;
// 		}
// 		else{
// 			for(int j = 0; j < data->size; j++){
// 				if (i == j){
// 					fmat[i][j] = 0;
// 				}
// 				if (j == 16 || j == 20 || j == 22 || j == 23 || j == 24 || j == 28 || j == 29 || j == 30 || j == 31 || j == 32 || j == 34 || j == 35 || j == 38){
// 					continue;
// 				}
// 				else{
// 					cout << setw(9) << std::right << fmat[i][j] << " ";
// 				}
// 			}
// 			cout << endl;
// 		}

// 	}
// }

void hybENFR (Gendata *data, Keyboard *keyb){

//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
//T H E O F A N D I W S  R  Y  U  B  C  V  M  L  P  K  G  J  Q  X  '  Z  _  _  _  _  _ 
	
	keyb->kcols = 10;
	keyb->krows = 4;

	keyb->grid = new int [keyb->ksize];

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = -1;
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}

//   *  X  Q  U  S  N  O  C  H  W
//   *  J  V  D  E  T  I  M  F  K
//   *  Z  B  '  L  R  A  P  G  Y
//	 *  *  *  _  _  _  _  _  *  *

// -----x-----
// Best Global Solution Cost: 9537192051

	keyb->grid[1] = 24;
	keyb->grid[2] = 23;
	keyb->grid[3] = 13;
	keyb->grid[4] = 10;
	keyb->grid[5] = 6;
	keyb->grid[6] = 3;
	keyb->grid[7] = 15;
	keyb->grid[8] = 1;
	keyb->grid[9] = 9;
	keyb->grid[11] = 22;
	keyb->grid[12] = 16;
	keyb->grid[13] = 7;
	keyb->grid[14] = 2;
	keyb->grid[15] = 0;
	keyb->grid[16] = 8;
	keyb->grid[17] = 17;
	keyb->grid[18] = 4;
	keyb->grid[19] = 20;
	keyb->grid[21] = 26;
	keyb->grid[22] = 14;
	keyb->grid[23] = 25;
	keyb->grid[24] = 18;
	keyb->grid[25] = 11;
	keyb->grid[26] = 5;
	keyb->grid[27] = 19;
	keyb->grid[28] = 21;
	keyb->grid[29] = 12;
	keyb->grid[33] = 27;
	keyb->grid[34] = 28;
	keyb->grid[35] = 29;
	keyb->grid[36] = 30;
	keyb->grid[37] = 31;

	keyb->assignment[0] = 15;
	keyb->assignment[1] = 8;
	keyb->assignment[2] = 14;
	keyb->assignment[3] = 6;
	keyb->assignment[4] = 18;
	keyb->assignment[5] = 26;
	keyb->assignment[6] = 5;
	keyb->assignment[7] = 13;
	keyb->assignment[8] = 16;
	keyb->assignment[9] = 9;
	keyb->assignment[10] = 4;
	keyb->assignment[11] = 25;
	keyb->assignment[12] = 29;
	keyb->assignment[13] = 3;
	keyb->assignment[14] = 22;
	keyb->assignment[15] = 7;
	keyb->assignment[16] = 12;
	keyb->assignment[17] = 17;
	keyb->assignment[18] = 24;
	keyb->assignment[19] = 27;
	keyb->assignment[20] = 19;
	keyb->assignment[21] = 28;
	keyb->assignment[22] = 11;
	keyb->assignment[23] = 2;
	keyb->assignment[24] = 1;
	keyb->assignment[25] = 23;
	keyb->assignment[26] = 21;
	keyb->assignment[27] = 33;
	keyb->assignment[28] = 34;
	keyb->assignment[29] = 35;
	keyb->assignment[30] = 36;
	keyb->assignment[31] = 37;

	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			if (i == 0 && j == 0){
				cout << " ";
			}
			if (i == 1 && j == 0){
				cout << " ";
			}
			if (keyb->grid[count] != -1)
				cout << setw(3) << data->char_list[keyb->grid[count]];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}
}



void hybENSP(Gendata *data, Keyboard *keyb)
{

//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
//T H E O F A N D I W  S  R  Y  U  B  C  V  M  L  P  K  G  J  Q  X  Z  Ñ  _  _  _  _  _  
	
	keyb->kcols = 10;
	keyb->krows = 4;

	keyb->grid = new int [keyb->ksize];

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = -1;
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}

// *  Y  B  L  A  N  D  G  K  *
// Ñ  Q  U  M  R  E  I  C  V  Z
// *  J  F  P  O  S  T  H  W  X
// *  *  *  _  _  _  _  _  *  *

// -----x-----
// Best Global Solution Cost: 1522921294

	keyb->grid[1] = 12;
	keyb->grid[2] = 14;
	keyb->grid[3] = 18;
	keyb->grid[4] = 5;
	keyb->grid[5] = 6;
	keyb->grid[6] = 7;
	keyb->grid[7] = 21;
	keyb->grid[8] = 20;
	keyb->grid[10] = 26;
	keyb->grid[11] = 23;
	keyb->grid[12] = 13;
	keyb->grid[13] = 17;
	keyb->grid[14] = 11;
	keyb->grid[15] = 2;
	keyb->grid[16] = 8;
	keyb->grid[17] = 15;
	keyb->grid[18] = 16;
	keyb->grid[19] = 25;
	keyb->grid[21] = 22;
	keyb->grid[22] = 4;
	keyb->grid[23] = 19;
	keyb->grid[24] = 3;
	keyb->grid[25] = 10;
	keyb->grid[26] = 0;
	keyb->grid[27] = 1;
	keyb->grid[28] = 9;
	keyb->grid[29] = 24;
	keyb->grid[33] = 27;
	keyb->grid[34] = 28;
	keyb->grid[35] = 29;
	keyb->grid[36] = 30;
	keyb->grid[37] = 31;

	keyb->assignment[0] = 26;
	keyb->assignment[1] = 27;
	keyb->assignment[2] = 15;
	keyb->assignment[3] = 24;
	keyb->assignment[4] = 22;
	keyb->assignment[5] = 4;
	keyb->assignment[6] = 5;
	keyb->assignment[7] = 6;
	keyb->assignment[8] = 16;
	keyb->assignment[9] = 28;
	keyb->assignment[10] = 25;
	keyb->assignment[11] = 14;
	keyb->assignment[12] = 1;
	keyb->assignment[13] = 12;
	keyb->assignment[14] = 2;
	keyb->assignment[15] = 17;
	keyb->assignment[16] = 18;
	keyb->assignment[17] = 13;
	keyb->assignment[18] = 3;
	keyb->assignment[19] = 23;
	keyb->assignment[20] = 8;
	keyb->assignment[21] = 7;
	keyb->assignment[22] = 21;
	keyb->assignment[23] = 11;
	keyb->assignment[24] = 29;
	keyb->assignment[25] = 19;
	keyb->assignment[26] = 10;
	keyb->assignment[27] = 33;
	keyb->assignment[28] = 34;
	keyb->assignment[29] = 35;
	keyb->assignment[30] = 36;
	keyb->assignment[31] = 37;

	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			if (i == 0 && j == 0){
				cout << " ";
			}
			if (i == 1 && j == 0){
				cout << " ";
			}
			if (keyb->grid[count] != -1)
				cout << setw(3) << data->char_list[keyb->grid[count]];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}

}
void hybENPT(Gendata *data, Keyboard *keyb)
{

//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
//T H E O F A N D I W  S  R  Y  U  B  C  V  M  L  P  K  G  J  Q  X  Z  _  _  _  _  _ 
	
//   *  X  Q  U  T  N  C  V  Z  *
//   *  J  G  M  E  S  A  I  F  W
//   *  K  B  P  R  O  D  L  H  Y
//   *  *  *  _  _  _  _  _  *  *
// -----x-----
// Best Global Solution Cost: 723415379921

	keyb->kcols = 10;
	keyb->krows = 4;

	keyb->grid = new int [keyb->ksize];

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = -1;
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}

	keyb->grid[1] = 24;
	keyb->grid[2] = 23;
	keyb->grid[3] = 13;
	keyb->grid[4] = 0;
	keyb->grid[5] = 6;
	keyb->grid[6] = 15;
	keyb->grid[7] = 16;
	keyb->grid[8] = 25;
	keyb->grid[11] = 22;
	keyb->grid[12] = 21;
	keyb->grid[13] = 17;
	keyb->grid[14] = 2;
	keyb->grid[15] = 10;
	keyb->grid[16] = 5;
	keyb->grid[17] = 8;
	keyb->grid[18] = 4;
	keyb->grid[19] = 9;
	keyb->grid[21] = 20;
	keyb->grid[22] = 14;
	keyb->grid[23] = 19;
	keyb->grid[24] = 11;
	keyb->grid[25] = 3;
	keyb->grid[26] = 7;
	keyb->grid[27] = 18;
	keyb->grid[28] = 1;
	keyb->grid[29] = 12;
	keyb->grid[33] = 26;
	keyb->grid[34] = 27;
	keyb->grid[35] = 28;
	keyb->grid[36] = 29;
	keyb->grid[37] = 30;

	keyb->assignment[0] = 4;
	keyb->assignment[1] = 28;
	keyb->assignment[2] = 14;
	keyb->assignment[3] = 25;
	keyb->assignment[4] = 18;
	keyb->assignment[5] = 16;
	keyb->assignment[6] = 5;
	keyb->assignment[7] = 26;
	keyb->assignment[8] = 17;
	keyb->assignment[9] = 19;
	keyb->assignment[10] = 15;
	keyb->assignment[11] = 24;
	keyb->assignment[12] = 29;
	keyb->assignment[13] = 3;
	keyb->assignment[14] = 22;
	keyb->assignment[15] = 6;
	keyb->assignment[16] = 7;
	keyb->assignment[17] = 13;
	keyb->assignment[18] = 27;
	keyb->assignment[19] = 23;
	keyb->assignment[20] = 21;
	keyb->assignment[21] = 12;
	keyb->assignment[22] = 11;
	keyb->assignment[23] = 2;
	keyb->assignment[24] = 1;
	keyb->assignment[25] = 8;
	keyb->assignment[26] = 33;
	keyb->assignment[27] = 34;
	keyb->assignment[28] = 35;
	keyb->assignment[29] = 36;
	keyb->assignment[30] = 37;

	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			if (i == 0 && j == 0){
				cout << " ";
			}
			if (keyb->grid[count] != -1)
				cout << setw(3) << data->char_list[keyb->grid[count]];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}

}
void hybENIT(Gendata *data, Keyboard *keyb)
{


//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
//T H E O F A N D I W  S  R  Y  U  B  C  V  M  L  P  K  G  J  Q  X  Z  _  _  _  _  _
	
 // *  W  H  C  O  R  P  V  Y  *
 // *  K  F  S  I  N  E  D  G  X
 // *  Q  Z  U  T  A  L  M  B  J
 // *  *  *  _  _  _  _  _  *  *
// -----x-----
// Best Global Solution Cost: 3431856357

	keyb->kcols = 10;
	keyb->krows = 4;

	keyb->grid = new int [keyb->ksize];

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = -1;
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}

	keyb->grid[1] = 9;
	keyb->grid[2] = 1;
	keyb->grid[3] = 15;
	keyb->grid[4] = 3;
	keyb->grid[5] = 11;
	keyb->grid[6] = 19;
	keyb->grid[7] = 16;
	keyb->grid[8] = 12;
	keyb->grid[11] = 20;
	keyb->grid[12] = 4;
	keyb->grid[13] = 10;
	keyb->grid[14] = 8;
	keyb->grid[15] = 6;
	keyb->grid[16] = 2;
	keyb->grid[17] = 7;
	keyb->grid[18] = 21;
	keyb->grid[19] = 24;
	keyb->grid[21] = 23;
	keyb->grid[22] = 25;
	keyb->grid[23] = 13;
	keyb->grid[24] = 0;
	keyb->grid[25] = 5;
	keyb->grid[26] = 18;
	keyb->grid[27] = 17;
	keyb->grid[28] = 14;
	keyb->grid[29] = 22;
	keyb->grid[33] = 26;
	keyb->grid[34] = 27;
	keyb->grid[35] = 28;
	keyb->grid[36] = 29;
	keyb->grid[37] = 30;

	keyb->assignment[0] = 24;
	keyb->assignment[1] = 2;
	keyb->assignment[2] = 16;
	keyb->assignment[3] = 4;
	keyb->assignment[4] = 12;
	keyb->assignment[5] = 25;
	keyb->assignment[6] = 15;
	keyb->assignment[7] = 17;
	keyb->assignment[8] = 14;
	keyb->assignment[9] = 1;
	keyb->assignment[10] = 13;
	keyb->assignment[11] = 5;
	keyb->assignment[12] = 8;
	keyb->assignment[13] = 23;
	keyb->assignment[14] = 28;
	keyb->assignment[15] = 3;
	keyb->assignment[16] = 7;
	keyb->assignment[17] = 27;
	keyb->assignment[18] = 26;
	keyb->assignment[19] = 6;
	keyb->assignment[20] = 11;
	keyb->assignment[21] = 18;
	keyb->assignment[22] = 29;
	keyb->assignment[23] = 21;
	keyb->assignment[24] = 19;
	keyb->assignment[25] = 22;
	keyb->assignment[26] = 33;
	keyb->assignment[27] = 34;
	keyb->assignment[28] = 35;
	keyb->assignment[29] = 36;
	keyb->assignment[30] = 37;

	int count = 0;
	
	for (int i = 0; i < keyb->krows; i++){
		for (int j = 0; j < keyb->kcols; j++){
			if (i == 0 && j == 0){
				cout << " ";
			}
			if (keyb->grid[count] != -1)
				cout << setw(3) << data->char_list[keyb->grid[count]];
			else
				cout<< setw(3) << "*";
			count++;
		}
		cout << endl;
	}

}

