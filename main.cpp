#include <iostream>
#include <cmath>
#include <random>

using namespace std;
typedef unsigned int uint;

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

const double Pm = 0.07;

double f(double x) {
    return sin(pow((4 * x - exp(x - 12)), 3)) + sin(x * x);
}

uint toGreyCode(uint x) {
    return x ^ (x >> 1);
}

uint fromGreyCode(uint x) {
    int inv = 0;
    for (; x; x = x >> 1)
        inv ^= x;
    return inv;
}

uint mutate(uint x) {
    for (uint i = 1, counter = 0; i > 0; i <<= 1, counter++) {
        auto chance = random<double>(0.0, 1.0);
        if (chance <= Pm) {
            cout << counter << endl;
            x ^= i;
        }

    }
    return x;
}

int main() {
    cout << 0xFF << endl;
    cout << mutate(0xFF) << endl;
    return 0;
}
