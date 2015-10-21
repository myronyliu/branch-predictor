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

#define nHR 512 //512
#define nPH 64 //64
#define nPatBits 2

static unsigned int HR[nHR]; // 9 bits to track the instruction
static unsigned int PH[nPH]; // 6 bits to track the branch history
// each entry of PH is a two bit saturating counter

/*
  Let bPC be the number of bits we use to keep track of the instructions
  Let bHR be the number of bits we use to keep track of the branch history
  Let bPH be the number of bits we use to keep track of the pattern history

  Then the memory requirement for our two-level-local-predictor (int bits) is...
    (2^bPC * 2^bHR) + (2^bPT * 2^bHR) = 2^bHR (2^bPC + 2^bPT)
  
  As can be seen, for [bPC, bHR, bPH] = [9, 6, 2], we get exactly 32K + 256
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
