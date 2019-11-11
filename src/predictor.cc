//========================================================//
//  predictor.c                                           //
//  Source file for the Branch Predictor                  //
//                                                        //
//  Implement the various branch predictors below as      //
//  described in the README                               //
//========================================================//
#include <stdio.h>
#include <stdlib.h>
#include <memory>

#include "predictor.hpp"
#include "gshare.hpp"
#include "tournament.hpp"
#include "2bc-gskew.hpp"

using std::unique_ptr;

//
// TODO:Student Information
//
const char *studentName = "NAME";
const char *studentID   = "PID";
const char *email       = "EMAIL";

//------------------------------------//
//      Predictor Configuration       //
//------------------------------------//

// Handy Global for use in output routines
const char *bpName[4] = { "Static", "Gshare",
                          "Tournament", "Custom" };

int ghistoryBits; // Number of bits used for Global History
int lhistoryBits; // Number of bits used for Local History
int pcIndexBits;  // Number of bits used for PC index
int bpType;       // Branch Prediction Type
int verbose;

//------------------------------------//
//      Predictor Data Structures     //
//------------------------------------//

unique_ptr<GSharePredictor> gshareP;
unique_ptr<TournamentPredictor> tournamentP;
unique_ptr<TwoBCgskewPredictor> twoBCgskewP;

//------------------------------------//
//        Predictor Functions         //
//------------------------------------//

// Initialize the predictor
//
void
init_predictor()
{
  switch (bpType) {
    case GSHARE:
      gshareP=std::move(std::make_unique<GSharePredictor>(ghistoryBits));
      break;
    case TOURNAMENT:
      tournamentP=std::move(std::make_unique<TournamentPredictor>(ghistoryBits,
        pcIndexBits,
        lhistoryBits));
      break;
    case CUSTOM:
      twoBCgskewP=std::move(std::make_unique<TwoBCgskewPredictor>());
      break;
    default:
      break;
  }
}

// Make a prediction for conditional branch instruction at PC 'pc'
// Returning TAKEN indicates a prediction of taken; returning NOTTAKEN
// indicates a prediction of not taken
//
uint8_t
make_prediction(uint32_t pc)
{
  //
  //TODO: Implement prediction scheme
  //

  // Make a prediction based on the bpType
  switch (bpType) {
    case STATIC:
      return TAKEN;
    case GSHARE:
      return gshareP->getPrediction(pc);
    case TOURNAMENT:
      return tournamentP->getPrediction(pc);
    case CUSTOM:
      return twoBCgskewP->getPrediction(pc);
    default:
      break;
  }

  // If there is not a compatable bpType then return NOTTAKEN
  return NOTTAKEN;
}

// Train the predictor the last executed branch at PC 'pc' and with
// outcome 'outcome' (true indicates that the branch was taken, false
// indicates that the branch was not taken)
//
void
train_predictor(uint32_t pc, uint8_t outcome)
{
  switch (bpType) {
    case GSHARE:
      gshareP->updatePredictor(pc,outcome);
      break;
    case TOURNAMENT:
      tournamentP->updatePredictor(pc,outcome);
      break;
    case CUSTOM:
      twoBCgskewP->updatePredictor(pc,outcome);
    default:
      break;
  }
}
