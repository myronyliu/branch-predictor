#include "predictor.h"
#include <stdio.h>
#include <math.h>

void init_predictor ()
{
    for (int i=0; i<nHR; ++i)
    {
	HR[i] = i; // we do this to avoid aliasing
    }
    for (int i=0; i<nPH; ++i)
    {
	PH[i] = pow(2, nPatBits-1); // initially, we predict all weakly taken
    }
}

bool make_prediction (unsigned int pc)
{
    return PH[HR[pc % nHR]] >= pow(2, nPatBits-1);
}

void train_predictor (unsigned int pc, bool outcome)
{
    // note the order of operations
    PH[HR[pc % nHR]] = (PH[HR[pc % nHR]] + 1) % (int)pow(2, nPatBits);
    HR[pc % nHR] = (HR[pc % nHR] << 1) % nHR + outcome;
}
