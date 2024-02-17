/*
Potentiometer (Pot)
MBR_Pot.h library at https://github.com/matteblackrobotics/MBR_Pot
*/

#ifndef Pot_h
#define Pot_h

#include <MBR_Pot.h>

MBR_Pot pot1(6,5.00);

int potRaw;
int potRawMin = 0;
int potRawMax = 1023;

int potNorm;
int potNormMin = -100;
int potNormMax = 100;

#endif