#include "structures.h"

// (64+32)*10+1 = 961 words 
typedef struct 
{
	FValue fv[10];
    int leftover;
} From3_to_1;

// (3+3+7)+1 = 14 words
typedef struct 
{
	SubHeader1 sh1;
    char emp;
    int leftover;
} From3_to_2;

// 10+3 = 13 words
typedef struct 
{
	SubHeader2 sh2;
} From3_to_4;

// 32 words
typedef struct 
{
    PBlock pbout[10];
} From1_to_2;

// 3072/4 = 768 words
typedef struct 
{
    ColorBuffer cbout;
} From2_to_4;
