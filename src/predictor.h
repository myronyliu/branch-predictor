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

#define n 16384 // 14 bits to track the PC_xor_globalHistory
#define m 4 // 2 bits to track the pattern history

static unsigned int h; // the global history
static unsigned int t[n]; // local branch history registers 

/*
  Let B be the number of bits we use to keep track of the PC_xor_globalHistory 
  Let b be the width of the entries in the pattern history table

  Then the memory requirement for our gshare-predictor (in bits) is 2^B * b
  
  We must pick [B, b] such as to not exceed the limit of 32K+256
  e.g. One choice might be to use [B, b] = [14, 2]
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
