#pragma once

#include "Automaton/Automaton.hpp"
#include "Process/Process.hpp"

namespace hibpm
{
    class RepairAutomata
    {
    public:
        list<Automaton> expand(list<Automaton> automata);

        list<Automaton> shrinkInc(list<Automaton> automata,
                                  list<Automaton> prevProds);

        Automaton maxRemainder(Process &process);

        void controlShrink();

        void controlExpand();
    };
}
