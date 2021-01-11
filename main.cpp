#include "functions/common.h"
#include "functions/crossingovers.h"
#include "functions/mutations.h"
#include "functions/reductions.h"
#include "functions/replications.h"


uint ga(pairs_to_replicate (*)(const vector<candidate> &),
        uint (*)(uint, uint),
        uint (*)(uint, uint),
        void (*)(vector<candidate> &),
        const vector<uint> &,
        uint,
        uint);

vector<pair<uint, uint>> answers;

int main() {
    vector<uint> start;
    for (int i = 0; i < SIZE; i++) {
        start.push_back(random(0, UINT32_MAX));
    }
    uint i = 0;
    double real_max = 0;
    double real_max_x = 0;
    uint real_max_index = 0;
    /*for (int pm = 7; pm < 17; pm++) {
        for (auto cross : crossFunctions) {
            for (auto mutate: mutateFunctions) {
                for (auto reduce: reductionFunctions) {
                    for (auto replicate: replicationFunctions) {
                        ga(replicate, cross, mutate, reduce, start, i++, pm);
                    }
                }
            }
        }
        cout << "pm = " << pm << endl;
        for (auto answer: answers) {
            if(f(getX(answer.first)) > real_max){
                real_max = f(getX(answer.first));
                real_max_x = getX(answer.first);
                real_max_index = answer.second;
            }
            cout << answer.second << ": x = " << getX(answer.first)
                 << "\nf(x) = " << f(getX(answer.first)) << "\n";
        }
        answers.clear();
        cout << endl;
    }
    */
    /*
    ga(randomReplication, bitwiseCross, bitwiseMutate, tournamentReduction, start, 0, 8);
    for (auto answer: answers) {
        if(f(getX(answer.first)) > real_max){
            real_max = f(getX(answer.first));
            real_max_x = getX(answer.first);
            real_max_index = answer.second;
        }
        cout << answer.second << ": x = " << getX(answer.first)
             << "\nf(x) = " << f(getX(answer.first)) << "\n";
    }
    answers.clear();

    cout <<"best result" << endl;
    cout << real_max_index << ": x = " << real_max_x
         << "\nf(x) = " << real_max << "\n\n";
    */

    cout << toGreyCode(fromGreyCode(123)) << endl;
    //cout << fromGreyCode(123) << endl;
}


uint ga(pairs_to_replicate (replication)(const vector<candidate> &),
        uint (crossingover)(uint, uint),
        uint (mutation)(uint, uint),
        void (reduction)(vector<candidate> &),
        const vector<uint> &startPopulation,
        uint index,
        uint pm) {
    uint result = 0;
    auto population = vector<candidate>(startPopulation.size());
    for (uint val: startPopulation) {
        population.emplace_back(pair(val, f(getX(val))));
    }

    for (int i = 0; i < ITERATIONS; i++) {
        auto to_repl = replication(population);
        for (auto repl: to_repl) {
            uint son = crossingover(repl.first, repl.second);
            population.emplace_back(pair(son, f(getX(son))));
        }
        for (int j = 0; j < population.size(); j++) {
            uint mutant = mutation(population[j].first, pm);
            population[j] = pair(mutant, f(getX(mutant)));
        }
        reduction(population);
    }
    double max = population[0].second;
    for (auto value: population) {
        if (value.second > max) {
            max = value.second;
            result = value.first;
        }
    }
    answers.emplace_back(result, index);
    return result;
}
