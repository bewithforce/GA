#pragma once

#include "common.h"

const int LINE_POINT = 12;

uint getCrossLine();

uint staticPlaceLineCross(uint, uint);

uint randomPlaceLineCross(uint, uint);

uint bitwiseCross(uint, uint);

const vector<uint (*)(uint, uint)> crossFunctions = {bitwiseCross, staticPlaceLineCross, randomPlaceLineCross};



