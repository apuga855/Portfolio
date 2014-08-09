#pragma once
#include <stdlib.h>
#include "random_values.h"

void initArraySentinel (int *, const unsigned long int, const int);
void initArraySentinel (double *, const unsigned long int, const double);
void initArraySentinel (char *, const unsigned long int, const char);
void initArrayNull (int *, const unsigned long int);
void initArrayNull (double *, const unsigned long int);
void initArrayNull (char *, const unsigned long int);
void initArrayRand (int *, const unsigned long int);
void initArrayRand (double *, const unsigned long int);
void initArrayRand (char *, const unsigned long int);
char alphaPosition (const int &);
