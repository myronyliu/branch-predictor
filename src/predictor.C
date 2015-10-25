#include "predictor.h"
#include <stdio.h>
#include <math.h>

void init_predictor ()
{
    for (int i = 0; i < n; ++i)
    {
	t[i] = m / 2; // initially, we predict all weakly taken
    }
    h = 0; // initialize the history to all zero bits
}

bool make_prediction (unsigned int pc)
{
    int i = (pc % n) ^ h;
    return t[i] >= m / 2;
}

void train_predictor (unsigned int pc, bool outcome)
{
    int i = (pc % n) ^ h;

    int sat = ((int)t[i] + 2*(int)outcome - 1); // increment or decrement the saturating counter
    sat = (sat < 0) ? 0 : (sat > m-1) ? m-1 : sat; // and clamp it to the proper range

    t[i] = sat;
    h = (h << 1) % n + outcome;
}
