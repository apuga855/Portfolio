#include "random_values.h"

using namespace std;

unsigned int RANDOM_SEED=0;

int randomInt(int min, int max)
{
		  if (RANDOM_SEED ==0)
		  {
					 RANDOM_SEED=time(NULL);
		  }
		  srand(RANDOM_SEED);
		  return ( ( rand() % (max-min) ) + min);
}

double randomDouble(int min, int max)
{
		  if (RANDOM_SEED ==0)
		  {
					 RANDOM_SEED=time(NULL);
		  }
		  srand(RANDOM_SEED);
		  return ( ( rand() / (max-min) ) * 1.325 + min);
}
