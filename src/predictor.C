#include "predictor.h"

// A very stupid predictor.  It will always predict not taken.

int clamp(int lower, int value, int upper)
{
    if (value < lower) return lower;
    if (value > upper) return upper;
    return value;
}

void init_predictor ()
{
    // GLOBAL
    hG1 = 0; // initialize the history to 0 (as per the addendum)
    for (int i = 0; i < nG2; ++i)
    {
	tG2[i] = 2; // predict weakly taken for the 2-bit-sat-counter (as per the addendum)
    }

    // LOCAL
    for (int i = 0; i < nL1; ++i)
    {
	tL1[i] = 0; // initialize all histories to 0 (as per the addendum) 
    }
    for (int i = 0; i < nL2; ++i)
    {
	tL2[i] = 4; // predict weakly taken for the 3-bit-sat-counter (as per the addendum)
    }

    // SELECTOR
    for (int i = 0; i < nS; ++i)
    {
	tS[i] = 2; // initialize selector to weakly prefer the local predictor (as per the addendum)
    }
}

bool make_prediction (unsigned int pc)
{
    int s = tS[pc % nS]; // query the SELECTOR entry that corresponds to pc

    if (s < 2) // select the GLOBAL predictor
    {
    	return tG2[hG1] >= 2; 
    }
    else // select the LOCAL predictor
    {
	return tL2[tL1[pc % nL1]] >= 4;
    }
}

void train_predictor (unsigned int pc, bool outcome)
{
    // Get the predictions for both methods
    bool pG = tG2[hG1] >= 2;
    bool pL = tL2[tL1[pc % nL1]] >= 4;

    // Get the SELECTOR entry that corresponds to pc
    int s = tS[pc % nS];

    // If only one of the predictors is correct, update the selector accordingly
    if (pG == outcome && pL != outcome)
    {
	tS[pc % nS] = clamp(0, s - 1, 3);
    }
    else if (pL == outcome && pG != outcome)
    {
	tS[pc % nS] = clamp(0, s + 1, 3);
    }

    // Update both predictors

    int inc = 2*outcome - 1; // increment: 1 for taken, -1 for not taken

    tG2[hG1] =		    clamp(0, (int)tG2[hG1] + inc,	    3);
    tL2[tL1[pc % nL1]] =    clamp(0, (int)tL2[tL1[pc % nL1]] + inc, 7);

    hG1 = (hG1 << 1) % nG2 + outcome;
    tL1[pc % nL1] = (tL1[pc % nL1] << 1) % nL2 + outcome;
}
