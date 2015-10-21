#include "predictor.h"
#include <stdio.h>
#include <math.h>

void init_predictor ()
{
    for (int i = 0; i < n; ++i)
    {
	t[i] = 0; // initially, we predict all strongly not taken
    }
}

bool make_prediction (unsigned int pc)
{
    int i = (pc % n) ^ h;
    return t[i] >= m / 2;
}

void train_predictor (unsigned int pc, bool outcome)
{
    int i = (pc % n) ^ h;

    int dSat = 2*(int)outcome - 1;
    int sat = ((int)t[i] + 2*outcome-1);
    sat = (sat < 0) ? 0 : (sat >= m) ? m-1 : sat;

    t[i] = sat;
    h = (h << 1) % n + outcome;
}
