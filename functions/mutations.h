#pragma once

#include "common.h"

uint bitwiseMutate(uint, uint);

uint bitwisePseudoRandomMutate(uint, uint);

uint singleBitMutate(uint, uint);

const vector<uint (*)(uint, uint)> mutateFunctions = {bitwiseMutate, bitwisePseudoRandomMutate, singleBitMutate};
