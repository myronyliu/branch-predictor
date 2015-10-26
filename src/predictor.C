#include "predictor.h"
#include <stdio.h>
#include <math.h>

void init_predictor ()
{
    for (int i = 0; i < n1; ++i)
    {
	t1[i] = 0; // initialize all histories to zeros
    }
    for (int i = 0; i < n2; ++i)
    {
	t2[i] = n3 / 2; // initially, we predict all weakly taken
    }
}

bool make_prediction (unsigned int pc)
{
    return t2[t1[pc % n1]] >= n3 / 2;
}

void train_predictor (unsigned int pc, bool outcome)
{
    int sat = ((int)t2[t1[pc % n1]] + 2*(int)outcome-1);
    sat = (sat < 0) ? 0 : (sat > n3-1) ? n3-1 : sat;

    t2[t1[pc % n1]] = sat;
    t1[pc % n1] = (t1[pc % n1] << 1) % n2 + outcome;
}
