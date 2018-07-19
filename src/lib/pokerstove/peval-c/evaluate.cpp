#include <pokerstove/penum/ShowdownEnumerator.h>
#include <boost/program_options.hpp>
#include <iostream>
#include <vector>

#include "evaluate.h"

using namespace pokerstove;
namespace po = boost::program_options;
using namespace std;

int32_t evaluate_holdem(const char* board, const char* hands, double *equity, size_t *size) {

    // extract the options
    string game("h");
    std::string s(hands);
    std::stringstream ss(s);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    vector<string> vhands(begin, end);

    bool quiet = false;

    // allocate evaluator and create card distributions
    boost::shared_ptr<PokerHandEvaluator> evaluator = PokerHandEvaluator::alloc(game);
    vector<CardDistribution> handDists;
    for (const string& hand : vhands) {
        handDists.emplace_back();
        handDists.back().parse(hand);
    }

    // fill with random if necessary
    if (handDists.size() == 1) {
        handDists.emplace_back();
        handDists.back().fill(evaluator->handSize());
    }

    // calcuate the results and print them
    ShowdownEnumerator showdown;
    vector<EquityResult> results =
        showdown.calculateEquity(
            handDists,
            CardSet(board),
            evaluator);

    double total = 0.0;
    for (const EquityResult& result : results) {
        total += result.winShares + result.tieShares;
    }

    if ( results.size() <= *size )
    {
        // return the results size
        *size = results.size();

        // cumulate wins
        if (!quiet) {
            for (size_t i = 0; i < results.size(); ++i) {

                equity[i] = (results[i].winShares + results[i].tieShares) / total;

                // show result
                // double equity = (results[i].winShares + results[i].tieShares) / total;
                // string handDesc =
                //     (i < vhands.size()) ? "The hand " + vhands[i] : "A random hand";
                // cout << handDesc << " has " << equity[i] * 100. << " % equity ("
                //         << results[i].str() << ")" << endl;
            }
        }
    } else {
        return 0;
    }

    return (int32_t) total;
}
