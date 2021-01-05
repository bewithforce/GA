#pragma once

#include "common.h"

typedef vector<pair<uint, uint>> pairs_to_replicate;

pairs_to_replicate randomReplication(const vector<candidate> &);

pairs_to_replicate rankSelectionReplication(const vector<candidate> &);

pairs_to_replicate rouletteWheelReplication(const vector<candidate> &);

const vector<pairs_to_replicate (*)(const vector<candidate> &)> replicationFunctions = {randomReplication,
                                                                                        rankSelectionReplication,
                                                                                        rouletteWheelReplication};