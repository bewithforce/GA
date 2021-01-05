#pragma once

#include "common.h"

void tournamentReduction(vector<candidate> &);

void fiftyFiftyReduction(vector<candidate> &);

void truncationReduction(vector<candidate> &);

const vector<void (*)(vector<candidate> &)> reductionFunctions = {tournamentReduction,
                                                                        fiftyFiftyReduction,
                                                                        truncationReduction};