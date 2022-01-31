#ifndef LOCALSEARCH_H_INCLUDED
#define LOCALSEARCH_H_INCLUDED

#include "functions.h"

void swap (Gendata*, Keyboard*, Stats*);
void swapPair (Gendata*, Keyboard*, Stats*);
void moveContour (Gendata *data, Keyboard *keyb, Stats*);
void SF_RVND (Gendata *data, Keyboard *keyb, Stats *stat);
void SFpert1(Gendata *data, Keyboard *keyb);
void SFpert2(Gendata *data, Keyboard *keyb);
void perturbation (Gendata *data, Keyboard *keyb, int *pertC);

//Funcoes para múltiplos espacos

void mswap (Gendata *data, Keyboard *keyb, Stats *stat, vector<int>& bSpaces, vector<int>& spaceVec, vector<int>& charVec);
void mswapPair (Gendata *data, Keyboard *keyb, Stats *stat, vector<int>& bSpaces, vector<int>& spaceVec, vector<int>& charVec);
void mtSF_RVND (Gendata *data, Keyboard *keyb, Stats *stat, vector<int>& bSpaces, vector<int>& spaceVec, vector<int>& charVec);
void mtSFpert1(Gendata *data, Keyboard *keyb, vector<int>& bSpaces, vector<int>& spaceVec, vector<int>& charVec);
void mtSFpert2(Gendata *data, Keyboard *keyb, vector<int>& bSpaces, vector<int>& spaceVec, vector<int>& charVec);
void mperturbation (Gendata *data, Keyboard *keyb, int *pertC, vector<int>& bSpaces, vector<int>& spaceVec, vector<int>& charVec);

#endif
