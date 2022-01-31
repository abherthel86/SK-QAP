
			if (auxKeyb[i] > -1){
				if (floor(i + keyb->kcols / keyb->kcols) < keyb->krows){
					vpos1 = i + keyb->kcols;
				}
				if (i + 1 % keyb->kcols < keyb->kcols){
					hpos1 = i + 1;
				}
				if (auxKeyb[vpos1] < 0){
					rmvCostV1 = 0;
					pairCostV1 = 0;
				}
				else{
					rmvCostV1 = rmvCost[auxKeyb[vpos1]];
					pairCostV1 = data->freq_matrix[auxKeyb[i]][auxKeyb[vpos1]] * data->b_matrix[i][vpos1];
				}
				if (auxKeyb[hpos1] < 0){
					rmvCostH1 = 0;
					pairCostH1 = 0
				}
				else{
					rmvCostH1 = rmvCost[auxKeyb[hpos1]];
					pairCostH1 = data->freq_matrix[auxKeyb[i]][auxKeyb[hpos1]] * data->b_matrix[i][hpos1];
				}
				for (int j = i + 1; j < keyb->ksize; j++){
					if (auxKeyb[j] > -1){
						if (j != vpos1){
							if (floor(j + keyb->kcols / keyb->kcols) < keyb->krows){
								vpos2 = j + keyb->kcols;
								if (auxKeyb[vpos2] < 0){
									rmvCostV2 = 0;
									pairCostV2 = 0;
								}
								else{
									rmvCostV2 = rmvCost[auxKeyb[vpos2]];					
									pairCostV2 = data->freq_matrix[auxKeyb[j]][auxKeyb[vpos2]] * data->b_matrix[j][vpos2];
								}

								rmv1 = rmvCost[auxKeyb[i]] + rmvCostV1 - 2 * pairCostV1;
								rmv2 = rmvCost[auxKeyb[j]] + rmvCostV2 - 2 * pairCostV2;

								temp = keyb->assignment[auxKeyb[i]];
								keyb->assignment[auxKeyb[i]] = keyb->assignment[auxKeyb[j]];
								keyb->assignment[auxKeyb[j]] = temp;			

								temp = auxKeyb[vpos1];
								auxKeyb[vpos1] = auxKeyb[vpos2];
								auxKeyb[vpos2] = temp;

								ins1 = costcalc (data, auxKeyb[i], keyb) + costcalc (data, auxKeyb[vpos2], keyb) - 2 * pairCostV1;
								ins2 = costcalc (data, auxKeyb[j], keyb) + costcalc (data, auxKeyb[vpos1], keyb) - 2 * pairCostV2;

								deltaFi = - rmv1 - rmv2 + ins1 + ins2;

								if (deltaFi < 0){
									if (deltaFi < bestDeltaFi){
										bestDeltaFi = deltaFi;
										char2 = auxKeyb[j];
										pos1 = keyb->assignment[auxKeyb[i]];
										pos2 = keyb->assignment[auxKeyb[j]];
										imp = 1;
									}
								}

								temp = auxKeyb[vpos2];
								auxKeyb[vpos2] = auxKeyb[vpos1];
								auxKeyb[vpos1] = temp;
							}
						}

						if (j != hpos1){
							if (j + 1 % keyb->kcols < keyb->kcols){
								hpos2 = j + 1;

								if (auxKeyb[hpos2] < 0){
									rmvCostH2 = 0;
									pairCostH2 = 0;
								}
								else{
									rmvCostH2 = rmvCost[auxKeyb[hpos2]];
									pairCostH2 = data->freq_matrix[auxKeyb[j]][auxKeyb[hpos2]] * data->b_matrix[j][hpos2];
								}

								rmv1 = rmvCost[auxKeyb[j]] + rmvCostH1 - 2 * pairCostH1;
								rmv2 = rmvCost[auxKeyb[i]] + rmvCostH2 - 2 * pairCostH2;

								temp = auxKeyb[hpos1];
								auxKeyb[hpos1] = auxKeyb[hpos2];
								auxKeyb[hpos2] = temp;

								ins1 = costcalc (data, auxKeyb[i], keyb) + costcalc (data, auxKeyb[hpos2], keyb) - 2 * pairCostH1;
								ins2 = costcalc (data, auxKeyb[j], keyb) + costcalc (data, auxKeyb[hpos1], keyb) - 2 * pairCostH2;

								deltaFi = - rmv1 - rmv2 + ins1 + ins2;

								if (deltaFi < 0){
									if (deltaFi < bestDeltaFi){
										bestDeltaFi = deltaFi;
										char2 = auxKeyb[j];
										pos1 = keyb->assignment[auxKeyb[i]];
										pos2 = keyb->assignment[auxKeyb[j]];
										imp = 1;
									}
								}

								temp = keyb->assignment[auxKeyb[j]];
								keyb->assignment[auxKeyb[j]] = keyb->assignment[auxKeyb[i]];
								keyb->assignment[auxKeyb[i]] = temp;
							}
						}
					}
				}//for 'j'