void moveContour (Gendata *data, Keyboard *keyb){

	vector <int> auxKeyb;
	vector <int> auxAssign;
	vector <int> contourInter;
	vector <unsigned int> rmvCost;

	list <int> contourPos;	
	list <int> newContour;
	list <int>::iterator it;
	list <int>::iterator it2;

	long long iniCost;
	long long newCost;
	long long testCost = 0; 
	long long f_Cost;
	long long s_Cost;
	long long deltaFi;
	long long ins;
	long long bestDeltaFi = -1;
	long long rmv;

	bool f_imp;
	bool s_imp;
	bool imp = 1;
	bool ns_imp;

	int f_pos1;
	int f_pos2;
	int ns_pos1;
	int ns_pos2;
	int s_pos1;
	int s_pos2;
	int pos1;
	int pos2;
	int f_char;
	int ns_char;
	int s_char;
	int charac;
	int temp;
	int posFi;
	int t = 0;

	for (int i = 0; i < data->size; i++){
		rmvCost.push_back(0);
	}

	for (int i = 0; i < keyb->ksize; i++){
		auxKeyb.push_back(keyb->grid[i]);
	}

	for (int i = 0; i < data->size; i++){
		auxAssign.push_back(keyb->assignment[i]);
	}

	contourSet(data, keyb, contourPos, auxKeyb, -1);
	
	iniCost = keyb->cost;
	
	while (imp > 0){
		
		imp = 0;
		newContour.clear();

		//cout << "\nInitial Cost: "<< iniCost << endl;

		/*cout << "\nPosicoes de Contorno: ";
		for (it2 = contourPos.begin(); it2 != contourPos.end(); it2++){
			cout << *it2 << " "; 
		}
		cout << endl;*/

		for (int i = 0; i < data->size - 1; i++){

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

				/*cout << "\nCaractere testado: " << data->char_list[i] << "\nPosicao: " << *it << "\ndeltaFi: " << deltaFi << "\nbestDeltaFi: " << bestDeltaFi << endl;
				
				cout << "\nPosicoes de Contorno: ";
				for (it2 = contourPos.begin(); it2 != contourPos.end(); it2++){
					cout << *it2 << " "; 
				}
				cout << endl;
				
				if (imp > 0){
					cout << "\nNovas Posicoes de Contorno: ";
					for (it2 = newContour.begin(); it2 != newContour.end(); it2++){
						cout << *it2 << " "; 
					}
					cout << endl;
				}*/

				if (deltaFi < 0){
					if (deltaFi < bestDeltaFi){

						bestDeltaFi = deltaFi; 
						pos1 = *it;
						pos2 = temp;
						charac = i;

						if (imp > 0){
							s_imp = 1;
							//f_imp = 0;
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

				/*cout<< "\n0Assignment (iterador ns): " << endl;
				for(int i = 0; i < data->size; i++){
					cout << data->char_list[i] << ": " << keyb->assignment[i] << "  ";
				}
				cout << endl;
*/
				for (it = newContour.begin(); it != newContour.end(); it++){
				
					temp = keyb->assignment[i];
					keyb->assignment[i] = *it;
								
					ins = costcalc (data, i, keyb);

					deltaFi = - rmv + ins;
					//cout << "\nCaractere testado: " << data->char_list[i] << "\nPosicao: " << *it << "\ndeltaFi: " << deltaFi << endl;
					
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

/*				contourPos.remove(f_pos1);
				rmvContour(keyb, contourPos, auxKeyb, f_pos2);*/

				keyb->assignment[i] = f_pos1;

				testCost = costcalc(data, -2, keyb);
				
/*				cout<< "\n1Assignment (f) do custo calculado: " << endl;
				for(int i = 0; i < data->size; i++){
					cout << data->char_list[i] << ": " << keyb->assignment[i] << "  ";
				}
				cout << endl;*/
				
				//cout << "\nCusto calculado (f): " << testCost << endl;
				
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
				
/*				cout << "\nNovas Posicoes de Contorno: ";
					for (it2 = newContour.begin(); it2 != newContour.end(); it2++){
						cout << *it2 << " "; 
					}
				cout << endl;*/
/*
				cout << "\nCaractere Atual(f_imp): " << data->char_list[f_char] << "\nAntiga posicao(f_imp): " << f_pos2 << "\nNova posicao(f_imp): " << f_pos1 << "\nMelhora: " << bestDeltaFi <<  endl;
				cout << endl;
				printSol(data, keyb, auxKeyb);
				
				cout << "\nF - Z(fi) para " << data->char_list[i] << ": " << iniCost << endl;
				cout << "\nF - Z(fi') para " << data->char_list[i] << ": " << f_Cost << endl;
				cout << "\nF - Z(fi'') para " << data->char_list[i] << ": " << s_Cost << endl;

				cout<< "\n1Assignment (f): " << endl;
				for(int i = 0; i < data->size; i++){
					cout << data->char_list[i] << ": " << keyb->assignment[i] << "  ";
				}
				cout << endl;*/
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

/*				contourPos.remove(ns_pos1);
				rmvContour(keyb, contourPos, auxKeyb, ns_pos2);*/

				keyb->assignment[i] = ns_pos1;

				testCost = costcalc(data, -2, keyb);

/*				cout<< "\n2Assignment (ns) do custo calculado: " << endl;
				for(int i = 0; i < data->size; i++){
					cout << data->char_list[i] << ": " << keyb->assignment[i] << "  ";
				}
				cout << endl;*/

				//cout << "\nCusto calculado (ns): " << testCost << endl;
				
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
				
				//contourPos.remove(ns_pos1);
				rmvContour(keyb, contourPos, auxKeyb, ns_pos2);
				
				/*cout << "\nNovas Posicoes de Contorno (ns): ";
					for (it2 = newContour.begin(); it2 != newContour.end(); it2++){
						cout << *it2 << " "; 
					}
				cout << endl;*/
				
				f_pos1 = ns_pos1;
				f_pos2 = ns_pos2;
				f_char = ns_char;
				
				/*cout << "\nCaractere Atual(ns_imp)(end): " << data->char_list[ns_char] << "\nAntiga posicao(ns_imp): " << ns_pos2 << "\nNova posicao(ns_imp): " << ns_pos1 << "\nMelhora: " << bestDeltaFi <<  endl;
				cout << endl;
				printSol(data, keyb, auxKeyb);
				
				cout << "\nNS - Z(fi) para " << data->char_list[i] << ": " << iniCost << endl;
				cout << "\nNS - Z(fi') para " << data->char_list[i] << ": " << f_Cost << endl;
				cout << "\nNS - Z(fi'') para " << data->char_list[i] << ": " << s_Cost << endl;
				
				cout<< "\n2Assignment (ns): " << endl;
				for(int i = 0; i < data->size; i++){
					cout << data->char_list[i] << ": " << keyb->assignment[i] << "  ";
				}
				cout << endl;*/
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

				testCost = costcalc(data, -2, keyb);

				/*cout<< "\n3Assignment (s) do custo calculado: " << endl;

				for(int i = 0; i < data->size; i++){
					cout << data->char_list[i] << ": " << keyb->assignment[i] << "  ";
				}
				cout << endl;
				
				cout << "\nCusto calculado (s): " << testCost << endl;*/

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
				
				//contourPos.remove(s_pos1);
				rmvContour(keyb, contourPos, auxKeyb, s_pos2);
				
				/*cout << "\nNovas Posicoes de Contorno (s): ";
					for (it2 = newContour.begin(); it2 != newContour.end(); it2++){
						cout << *it2 << " "; 
					}
				cout << endl;
				
				cout << "\nFreq entre " << data->char_list[f_char] << " e " << data->char_list[s_char] << "\naij= " << data->freq_matrix[f_char][s_char] << endl;
				cout << "\nPosicoes: " << "\nj: " << f_pos1 << " fi(i): " << f_pos2 << " l: " << s_pos1 << " fi(h): " << s_pos2 << "\nbjl= " << data->b_matrix[f_pos1][s_pos1]<< " bfi(i)l= " << data->b_matrix[f_pos2][s_pos1] << " bfi(h)j= " << data->b_matrix[f_pos1][s_pos2]<< " bfi(i)fi(l)= " << data->b_matrix[f_pos2][s_pos2] << endl;
*/
				f_pos1 = s_pos1;
				f_pos2 = s_pos2;
				f_char = s_char;

				/*cout << "\nCaractere Atual(s_imp)(end): " << data->char_list[f_char] << "\nAntiga posicao(f_imp): " << s_pos2 << "\nNova posicao(s_imp): " << s_pos1 << "\nMelhora: " << bestDeltaFi << endl;
				cout << endl;
				printSol(data, keyb, auxKeyb);

				cout << "\nS - Z(fi) para " << data->char_list[i] << ": " << iniCost << endl;
				cout << "\nS - Z(fi') para " << data->char_list[i] << ": " << f_Cost << endl;
				cout << "\nS - Z(fi'') para " << data->char_list[i] << ": " << s_Cost << endl;
				
				cout<< "\n3Assignment (s): " << endl;

				for(int i = 0; i < data->size; i++){
					cout << data->char_list[i] << ": " << keyb->assignment[i] << "  ";
				}
				cout << endl;*/
			}
		}//for 'i'
		if(imp > 0){
			keyb->assignment[f_char] = f_pos1;
			iniCost = newCost;
			//bestCost = newCost;
		}
		t++;
		//cout << "\nFim dos is" << endl;

		//printSol(data, keyb, auxKeyb);

		contourPos.merge(newContour);
		contourPos.sort();

	}//while

	for (int i = 0; i < keyb->ksize; i++){
		keyb->grid[i] = auxKeyb[i];
	}

	cout << "Final Cost(Move Contour): " << newCost << endl;
	keyb->cost = newCost;
	
	testCost = costcalc(data, -2, keyb);
	cout << "\nCusto calculado final: " << testCost << endl;

	cout << "\nNew Solution: " << endl;

	printSol(data, keyb, auxKeyb);
	
	cout<< "\n4Assignment (final): " << endl;
	for(int i = 0; i < data->size; i++){
		cout << data->char_list[i] << ": " << keyb->assignment[i] << "  ";
	}
	cout << endl;

}//end moveContour