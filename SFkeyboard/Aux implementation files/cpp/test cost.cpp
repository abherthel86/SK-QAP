
void testcost (Gendata *data, Keyboard *keyb){
	
	vector<int> testVec;
	int cost;

	for (int k = 0; k < keyb->ksize; k++){
		testVec.push_back(-1);
	}
	
	keyb->assignment = new int [data->size];

	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = -1;
	}
	
	testVec[47] = 22;
	testVec[48] = 4;
	testVec[49] = 9;
	testVec[50] = 14;
	testVec[51] = 24;
	
	testVec[60] = 23;
	testVec[61] = 13;
	testVec[62] = 3;
	testVec[63] = 0;
	testVec[64] = 1;
	testVec[65] = 15;

	testVec[75] = 17;
	testVec[76] = 10;
	testVec[77] = 28;
	testVec[78] = 2;
	testVec[79] = 11;
	testVec[80] = 20;

	testVec[89] = 19;
	testVec[90] = 8;
	testVec[91] = 6;
	testVec[92] = 5;
	testVec[93] = 12;
	testVec[94] = 27;

	testVec[103] = 26;
	testVec[104] = 21;
	testVec[105] = 7;
	testVec[106] = 18;
	testVec[107] = 16;

	testVec[119] = 25;
	cout << "\nTeste1" << endl;

	cout << "\nTeste2" << endl;

	keyb->assignment[0] = 63;
	keyb->assignment[1] = 64;
	keyb->assignment[2] = 78;
	keyb->assignment[3] = 62;
	keyb->assignment[4] = 48;
	
	keyb->assignment[5] = 92;
	keyb->assignment[6] = 91;
	keyb->assignment[7] = 105;
	keyb->assignment[8] = 90;
	keyb->assignment[9] = 49;
	keyb->assignment[10] = 76;

	keyb->assignment[11] = 79;
	keyb->assignment[12] = 93;
	keyb->assignment[13] = 61;
	keyb->assignment[14] = 50;
	keyb->assignment[15] = 65;
	keyb->assignment[16] = 107;

	keyb->assignment[17] = 75;
	keyb->assignment[18] = 106;
	keyb->assignment[19] = 89;
	keyb->assignment[20] = 80;
	keyb->assignment[21] = 104;
	keyb->assignment[22] = 47;

	keyb->assignment[23] = 60;
	keyb->assignment[24] = 51;
	keyb->assignment[25] = 119;
	keyb->assignment[26] = 103;
	keyb->assignment[27] = 94;

	keyb->assignment[28] = 77;

/*	for (int i = 0; i < data->size; i++){
		keyb->assignment[i] = testVec[i];
	}*/
	cout << "\nassign: " << keyb->assignment[0] << endl;

	int count = 0;
	for (int i = 0; i < ROW; i++){
		for (int j = 0; j < COL; j++){
			if (testVec[count] != -1)
				cout << setw(3) << data->char_list[testVec[count]];
			else
				cout<< setw(3) << "*";
			count++;

		}
		cout<<endl;
	}
	cout << "\nTeste3" << endl;

	cost = costcalc(data, -2, keyb);
	cout<<"COST: "<< cost <<endl;
	cout << "\nTeste4" << endl;

}