#include "structures.h"

// (6+7)+(13)+(64+32)*10 = 986 words 
typedef struct 
{
	SubHeader1 sh1;
	SubHeader2 sh2;
	FValue fv[10];
    char emp;
} From3_to_1;

typedef struct 
{
	SubHeader1 sh1;
	SubHeader2 sh2;
	FValue fv[10];
    char emp;
} From3_to_2;

typedef struct 
{
	SubHeader1 sh1;
	SubHeader2 sh2;
	FValue fv[10];
    char emp;
} From3_to_4;

typedef struct 
{
    SubHeader1 sh1;
    char emp;
	SubHeader2 sh2;
    PBlock pbout[10]
    //ColorBuffer cbout;
} From1_to_4;

typedef struct 
{
    SubHeader1 sh1;
    char emp;
	SubHeader2 sh2;
    PBlock pbout[10]
    //ColorBuffer cbout;
} From2_to_3;
