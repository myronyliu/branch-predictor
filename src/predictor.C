#include "predictor.h"

inline int abs(int num)
{
    if (num < 0) return -num;
    return num;
}

inline int clamp(int lower, int value, int upper)
{
    if (value < lower) return lower;
    if (value > upper) return upper;
    return value;
}

void init_predictor ()
{
    // Initialize all history bits and addresses to 0
    for (int i = 0; i < h; ++i)
    {
		GHR[i] = -1;
		GA[h] = 0;
    }

    // Initialize all weights to 0
    for (int i = 0; i < n; ++i)
    {
		for (int j = 0; j < m; ++j)
		{
		    for (int k = 0; k < h; ++k)
		    {
				W[i][j][k] = 0;
		    }
		}
		bias[i] = 0;
    }
}

bool make_prediction (unsigned int pc)
{
    int B = pc % n; // modded address of the branch to be predicted

    int y = bias[B]; // initialize the prediction to the bias

    for (int i = 0; i < h; ++i) // accumulate the dot product of history with weights
    {
		y += W[B][GA[i]][i] * GHR[i];
    }
    return y >= 0;
}

void train_predictor (unsigned int pc, bool outcome)
{
    int B = pc % n; // modded address of the branch to be predicted

    int sgn = 2*outcome - 1; // the outcome converted to +1 -1

    ////////////////////////////
    //// Get the prediction ////
    ////////////////////////////

    int y = bias[B];

    for (int i = 0; i < h; ++i)
    {
		y += W[B][GA[i]][i] * GHR[i];
    }
    bool t = (y >= 0);

    ///////////////////////////////////////////////////////////////////////////
    //// Update weights if we predicted incorrectly or with low confidence ////
    ///////////////////////////////////////////////////////////////////////////

    if (t != outcome || abs(y) < theta)
    {
		for (int i = 0; i < h; ++i)
		{
		    W[B][GA[i]][i] = clamp(wMin, W[B][GA[i]][i] + sgn * GHR[i], -wMin - 1);
		    // i.e. increment W[B][GA[i]][i] if GHR[i] == t; decrement otherwise
		}
		bias[B] = clamp(wMin, bias[B] + sgn, -wMin - 1);
    }

    ///////////////////////////
    //// Update GHR and GA ////
    ///////////////////////////

    for (int i = 1; i < h; ++i)
    {
		GHR[i - 1] = GHR[i]; 
		GA[i - 1] = GA[i];
    }
    GHR[h-1] = sgn;
    GA[h-1] = B % m;
}
