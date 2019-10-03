#include "structures.h"

typedef struct 
{
	FValue fv[10];
	int leftover;
} From3_to_1;

typedef struct 
{
	FValue fv[10];
	int leftover;
} From3_to_2;

typedef struct 
{
	SubHeader1 sh1_to1;
	SubHeader2 sh2_to1;
	SubHeader1 sh1_to2;
	SubHeader2 sh2_to2;
} From3_to_4;

typedef struct 
{
    PBlock pbout[10];
} From1_to_4;

typedef struct 
{
    PBlock pbout[10];
} From2_to_4;
