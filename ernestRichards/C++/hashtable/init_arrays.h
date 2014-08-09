#pragma once
#include <stdlib.h>
#include "random_values.h"

using namespace std;

void initArraySentinel (int *a, const unsigned long int size, const int sentinel);
void initArraySentinel (double *a, const unsigned long int size, const double sentinel);
void initArraySentinel (char *a, const unsigned long int size, const char sentinel);
void initArrayNull (int *a, const unsigned long int size);
void initArrayNull (double *a, const unsigned long int size);
void initArrayNull (char *a, const unsigned long int size);
void initArrayRand (int *a, const unsigned long int size);
void initArrayRand (double *a, const unsigned long int size);
/*
void initArrayRand (char *a, const unsigned long int size);
*/
