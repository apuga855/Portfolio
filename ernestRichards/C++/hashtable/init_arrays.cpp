#include "init_arrays.h"

void initArraySentinel (int *a, const unsigned long int size, const int sentinel)
{
		  for (unsigned long int i = 0; i < size; i++)
					 a[i] = sentinel;
}

void initArraySentinel (double *a, const unsigned long int size, const double sentinel)
{
		  for (unsigned long int i = 0; i < size; i++)
					 a[i] = sentinel;
}

void initArraySentinel (char *a, const unsigned long int size, const char sentinel)
{
		  for (unsigned long int i = 0; i < size; i++)
					 a[i] = sentinel;
}

void initArrayNull (int *a, const unsigned long int size)
{
		  for (unsigned long int i = 0; i < size; i++)
					 a[i] = 0;
}

void initArrayNull (double *a, const unsigned long int size)
{
		  for (unsigned long int i = 0; i < size; i++)
					 a[i] = 0.0;
}

void initArrayNull (char *a, const unsigned long int size)
{
		  for (unsigned long int i = 0; i < size; i++)
					 a[i] = '\0';
}

void initArrayRand (int *a, const unsigned long int size)
{
		  for (unsigned long int i = 0; i < size; i++)
					 a[i] = randomInt(1,99);
}

void initArrayRand (double *a, const unsigned long int size)
{
		  for (unsigned long int i = 0; i < size; i++)
					 a[i] = randomDouble(1,99);
}

void initArrayRand (char *a, const unsigned long int size)
{
		  for (unsigned long int i = 0; i < size; i++)
					 a[i] = alphaPosition(randomInt(1, 52));
}

char alphaPosition (const int & in)
{
		  if (in < 27)
		  {
					 return ((char)(in + 96));
		  }
		  return ((char)(in + 64));
}
