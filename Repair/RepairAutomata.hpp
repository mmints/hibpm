#pragma once

#include <vector>

#include "Process/Process.hpp"
#include "Automaton/Automaton.hpp"

namespace hibpm
{
    struct RemainderComposition
    {
        list<shared_ptr<State>> hittingSet;
        list<list<shared_ptr<State>>> kernelSet;
        list<shared_ptr<State>> solutionSet; // TODO: Change to list
    };

    class RepairAutomata
    {
    public:
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
