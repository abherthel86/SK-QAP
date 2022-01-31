#include "keybCalc.h"
#define ROW 10
#define COL 14
#define  KEYS 140

void qMetropolisAssign (Gendata *data, Keyboard *keyb){

//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
//T H E O F A N D I W  S  R  Y  U  B  C  V  M  L  P  K  G  J  Q  X  Z

	keyb->kcols = 7;
	keyb->krows = 7;

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