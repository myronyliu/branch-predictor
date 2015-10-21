#include "predictor.h"
#include <stdio.h>
#include <math.h>

void init_predictor ()
{
    for (int i = 0; i < n1; ++i)
    {
	t1[i] = i; // we do this to avoid aliasing
    }
    for (int i = 0; i < n2; ++i)
    {
	t2[i] = 0; // initially, we predict all strongly not taken
    }
}

bool make_prediction (unsigned int pc)
{
    return t2[t1[pc % n1]] >= n3 / 2;
}

void train_predictor (unsigned int pc, bool outcome)
{
    // note the order of operations
    t2[t1[pc % n1]] = (t2[t1[pc % n1]] + 1) % n3;
    t1[pc % n1] = (t1[pc % n1] << 1) % n2 + outcome;
}
