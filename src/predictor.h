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

#define nG2 4096    // 12 bit global history

#define nL1 1024    // 10 bit program counter (for the LOCAL predictor)
#define nL2 1024    // 10 bit local history

#define nS 4096	    // 12 bit program counter (for the SELECTOR)

static unsigned int hG1;
static unsigned int tG2[nG2];

static unsigned int tL1[nL1];
static unsigned int tL2[nL2];

static unsigned int tS[nS]; // the selector

/*
    The number of bits used is:
	12 + 4096*2	    for the GLOBAL predictor
	1024*10 + 1024*3    for the LOCAL  predictor
	4096*2		    for the SELECTOR
    This gives a total usage of  29696 bits,
    which is less than 32K+256 = 33024 bits.
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
