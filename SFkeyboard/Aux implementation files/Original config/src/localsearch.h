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

#endif
