#pragma once

#include <vector>

#include "Process/Process.hpp"
#include "Automaton/Automaton.hpp"

namespace hibpm
{
    class RepairAutomata
    {
    public:
        list<Automaton> expand(list<Automaton> automata);

        list<Automaton> shrinkInc(list<Automaton> automata,
                                  list<Automaton> prevProds);

        Automaton maxRemainder(Process &process);

        std::vector<Automaton> controlShrink(Process& process);

        void controlExpand();
    };
}
