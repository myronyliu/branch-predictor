#ifndef PREDICTOR_H
#define PREDICTOR_H

/*
  Define all your tables and their sizes here.
  All tables must be statically-sized.
  Please don't call malloc () or any of its relatives within your
  program.  The predictor will have a budget, namely (32K + 256) bits
  (not bytes).  That encompasses all storage (all tables, plus GHR, if
  necessary -- but not PC) used for the predictor.  That may not be
  the amount of storage your predictor uses, however -- for example,
  you may implement 2-bit predictors with a table of ints, in which
  case the simulator will use more memory -- that's okay, we're only
  concerned about the memory used by the simulated branch predictor.
*/

////////////////////////////////////////////////////////
//// The following predictor follows the paper      ////
//// "Piecewise Linear Branch Prediction" (Jimenez) ////
////////////////////////////////////////////////////////

#define h 16		// number of global history bits (dimension 3 of W)
#define n 16		// number of unique branch PCs in dimension 1 of W
#define m 16		// number of unique branch PCs in dimension 2 of W
#define wMin -128	// the number of bits to store each weight is wBits=log_2(2*|wMin|)

// training threshhold (we train the predictor if theta is not reached)
static float tmp = 2.14*(h + 1) + 20.58;
static int theta = (tmp - (int)tmp < 0.5) ? (int)tmp : (int)tmp + 1;

/*
    W holds the weights.

    Suppose we want to predict branch B given a history {GHR, GA}.
    We look upon 2D array W[B].
    Within W[B], history {GHR, GA} specifies h elements, each of which is a weight.
    These weights are then fed into the perceptron formula.

    For the overall bias of branch B, we look upon bias[B].

    We use an array for GHR as well, so that we can extend the history beyond 64 bits.
    Typically, long long int is sufficient though.
*/

static int W[n][m][h];
static int bias[n]; // the bias of branch pc % n; 

static int GHR[h];  // the global history of taken/not-taken (+1 and -1 respectively)
static int GA[h];   // the branch addresses corresponding to each entry of GHR

/*
    The memory usage in bits is:
		n*m*h*wBits			for W
		n*wBits				for bias
		h					for GHR
		h*ceil(log_2(m))	for GA
*/


/*
  Initialize the predictor.
*/
void init_predictor ();

/*
  Make a prediction for conditional branch instruction at PC 'pc'.
  Returning true indicates a prediction of taken; returning false
  indicates a prediction of not taken.
*/
bool make_prediction (unsigned int pc);

/*
  Train the predictor the last executed branch at PC 'pc' and with
  outcome 'outcome' (true indicates that the branch was taken, false
  indicates that the branch was not taken).
*/
void train_predictor (unsigned int pc, bool outcome);

#endif
