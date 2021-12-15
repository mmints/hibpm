#pragma once

#include <vector>

#include "Automaton.hpp"
#include "GraphSolver.h"

namespace hibpm
{
    struct RemainderComposition
    {
        list<shared_ptr<State>> hittingSet;
        list<list<shared_ptr<State>>> kernelSet;
        list<shared_ptr<State>> solutionSet;
    };

    class RepairAutomata
    {
    public:

        list<shared_ptr<State>> shrinkGraph(list<shared_ptr<State>> set, int numEv);
        RemainderComposition expandGraph(vector<shared_ptr<State>> &states, int numEvs);


        list<Automaton> expand(list<Automaton> automata);

        list<Automaton> shrinkInc(list<Automaton> automata,
                                  list<Automaton> prevProds);

        Automaton maxRemainder(Process &process);

        list<shared_ptr<State>> controlShrink(list<shared_ptr<State>> &states, shared_ptr<State> alpha, list<Automaton> &products);

        RemainderComposition controlExpand(Process& process);

        RemainderComposition lazyExpands(Process& process);
        list<shared_ptr<State>> lazyShrink(list<shared_ptr<State>> &states,
                                           shared_ptr<State> alpha);
        list<shared_ptr<State>> oneKernelN(list<shared_ptr<State>> &states, shared_ptr<State> alpha, int size);
    };
}
