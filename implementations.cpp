#include <set>
#include "functions/common.h"
#include "functions/crossingovers.h"
#include "functions/mutations.h"
#include "functions/reductions.h"
#include "functions/replications.h"


//max{sin((4 x - 12)^3) + sin(x^2)|-2.5<=x<=2.5}≈1.98155 at x≈-1.17405
// required function
double f(double x) {
    return sin(pow((4 * x - 12), 3)) + sin(x * x);
}

// double argument from grey code
double getX(uint code) {
    return (5.0 * fromGreyCode(code) / UINT32_MAX) - 2.5;
}

// unsigned int32 to Grey code
uint toGreyCode(uint x) {
    return x ^ (x >> 1);
}

// Grey code to unsigned int32
uint fromGreyCode(uint x) {
    int inv = 0;
    for (; x; x = x >> 1)
        inv ^= x;
    return inv;
}

random_device rd;
mt19937 mt(rd());

uint random(uint from, uint to) {
    // default_random_engine generator;
    uniform_int_distribution<uint> distribution(from, to);
    return distribution(mt);
}



//--------------------------------
//crossingover

bool flag = false;

uint crossLine = 1;

// magic number for static lines
uint getCrossLine() {
    if (flag) {
        return crossLine;
    }
    for (int i = 1; i < LINE_POINT; i++) {
        crossLine <<= 1;
        crossLine += 1;
    }
    flag = true;
    return crossLine;
}

uint staticPlaceLineCross(uint a, uint b) {
    uint magicNumber = getCrossLine();
    return (a & !magicNumber) + (b & magicNumber);
}

uint randomPlaceLineCross(uint a, uint b) {
    uint crossPoint = random(1, 31);
    uint magicNumber = 1;
    for (int i = 1; i < crossPoint; i++) {
        magicNumber <<= 1;
        magicNumber += 1;
    }
    return (a & !magicNumber) + (b & magicNumber);
}

uint bitwiseCross(uint a, uint b) {
    uint result = 0xFFFFFFFF;
    for (uint magic = 1; magic > 0; magic <<= 1) {
        int chance = random(0, 100);
        if (chance < 50) {
            result &= (a & magic);
        } else {
            result &= (b & magic);
        }
    }
    return result;
}


//--------------------------------
//mutation

// simple bitwise mutation, independent for every bit
uint bitwiseMutate(uint x, uint probability) {
    for (uint i = 1, counter = 0; i > 0; i <<= 1, counter++) {
        auto chance = random(0, 100);
        if (chance <= probability) {
            x ^= i;
        }
    }
    return x;
}

// simple bitwise mutation, but probability of mutation decreases with each one
uint bitwisePseudoRandomMutate(uint x, uint probability) {
    vector<int> indexes(32);
    iota(indexes.begin(), indexes.end(), 0);
    shuffle(indexes.begin(), indexes.end(), mt);
    for (uint i = 1, counter = 0; i > 0; i <<= 1, counter++) {
        auto chance = random(0, 100);
        if (chance <= probability) {
            probability -= 5;
            x ^= i;
        }
    }
    return x;
}

// mutation of random bit
uint singleBitMutate(uint x, uint) {
    return x ^ 1 << (random(0, 31) - 1);
}



//--------------------------------
//reduction

void tournamentReduction(vector<candidate> &population) {
    while (population.size() > SIZE) {
        int i1 = random(0, population.size() - 1);
        int i2 = random(0, population.size() - 1);
        while (i2 == i1) {
            i2 = random(0, population.size() - 1);
        }
        if (population[i1].second < population[i2].second) {
            population.erase(population.begin() + i1);
        } else {
            population.erase(population.begin() + i2);
        }
    }
}

void fiftyFiftyReduction(vector<candidate> &population) {
    sort(population.begin(), population.end(), [](candidate a, candidate b) -> bool {
        return a.second < b.second;
    });
    while (population.size() > SIZE) {
        int index = random(SIZE / 2, population.size() - 1);
        population.erase(population.begin() + index);
    }
}

void truncationReduction(vector<candidate> &population) {
    sort(population.begin(), population.end(), [](candidate a, candidate b) -> bool {
        return a.second < b.second;
    });
    population.erase(population.begin() + SIZE, population.end());
}

//--------------------------------
//replication

pairs_to_replicate randomReplication(const vector<candidate> &population) {
    pairs_to_replicate result;
    for (int i = 0; i < SIZE / 2; i++) {
        int a = random(0, population.size());
        int b = random(0, population.size());
        result.emplace_back(pair(population[a].first, population[b].first));
    }
    return result;
}

pairs_to_replicate rankSelectionReplication(const vector<candidate> &temp) {
    auto population = temp;
    sort(population.begin(), population.end(), [](candidate a, candidate b) -> bool {
        return a.second > b.second;
    });
    pairs_to_replicate result;
    int lim = (population.size() - 1) / 2 * population.size();
    for (int i = 0; i < population.size() / 2; i++) {
        int a = random(0, lim);
        int t = 0;
        while (a > 0) {
            a -= t++;
        }
        uint first = population[population.size() - t].first;
        uint second = population[random(0, population.size() - 1)].first;
        result.emplace_back(pair(first, second));
    }
    return result;
}

pairs_to_replicate rouletteWheelReplication(const vector<candidate> &temp) {
    auto population = temp;
    sort(population.begin(), population.end(), [](candidate a, candidate b) -> bool {
        return a.second > b.second;
    });
    double sum = 0.0;
    for (auto val: population) {
        sum += val.second;
    }
    pairs_to_replicate result;
    uniform_real_distribution<double> distribution(0.0, sum);
    for (int i = 0; i < population.size() / 2; i++) {
        double magic = distribution(mt);
        int t = 0;
        while (magic > 0) {
            magic -= population[t++].second;
        }
        uint first = population[population.size() - t].first;
        uint second = population[random(0, population.size() - 1)].first;
        result.emplace_back(pair(first, second));
    }
    return result;
}