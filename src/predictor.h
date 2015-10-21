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

#define n1 1024 // 10 bits to track the program counter
#define n2 8192 // 13 bits to track the local branch history
#define n3 4 // 2 bits to track the pattern history (given a branch history)

static unsigned int t1[n1]; // local branch history registers 
static unsigned int t2[n2]; // shared pattern history table

/*
  Let b1 be the number of bits we use to keep track of the program counter
  Let b2 be the width of the entries a branch history register
  Let b3 be the width of the entries in the pattern history table

  Then the memory requirement for our two-level-local-predictor (in bits) is...
    (2^b1 * b2) + (2^b2 * b3)
  
  We must pick [b1, b2, b3] such as to not exceed the limit of 32K+256
  e.g. One choice might be to use [b1, b2, b3] = [10, 13, 2]
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
