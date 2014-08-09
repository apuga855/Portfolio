#include "random_values.h"

using namespace std;

unsigned int RANDOM_SEED=0;

int randInt(int min = -10000, int max = 10000)
{
    if (RANDOM_SEED ==0)
    {
        RANDOM_SEED=time(NULL);
        srand(RANDOM_SEED);
    }
    return ( ( rand() % (max-min) ) + min);
}

double randDoub(int min = -10000, int max = 10000)
{
    if (RANDOM_SEED ==0)
    {
        RANDOM_SEED=time(NULL);
        srand(RANDOM_SEED);
    }
    return ( ( rand() / (max-min) ) * 1.325 + min);
}

int randomInt(int min = -10000, int max = 10000)
{
    if (RANDOM_SEED ==0)
    {
        RANDOM_SEED=time(NULL);
        srand(RANDOM_SEED);
    }
    return ( ( rand() % (max-min) ) + min);
}

double randomDouble(int min = -10000, int max = 10000)
{
    if (RANDOM_SEED ==0)
    {
        RANDOM_SEED=time(NULL);
        srand(RANDOM_SEED);
    }
    return ( ( rand() / (max-min) ) * 1.325 + min);
}
