#pragma once

#include <cmath>
#include <random>
#include <vector>
#include <iostream>
#include <random>
#include <vector>
#include <thread>


using namespace std;

typedef unsigned int uint;
typedef pair<uint, double> candidate;

const uint SIZE = 100;
const uint ITERATIONS = 100;

uint random(uint, uint);

double f(double);

double getX(uint);

uint toGreyCode(uint);

uint fromGreyCode(uint);


/*
template<typename Numeric, typename Generator = std::mt19937>
Numeric random(Numeric from, Numeric to) {
    thread_local static Generator gen(std::random_device{}());

    using dist_type = typename std::conditional
            <
                    std::is_integral<Numeric>::value, std::uniform_int_distribution<Numeric>, std::uniform_real_distribution<Numeric>
            >::type;

    thread_local static dist_type dist;

    return dist(gen, typename dist_type::param_type{from, to});
}
*/




