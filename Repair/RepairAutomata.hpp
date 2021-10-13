#pragma once

#include "Automaton/Automaton.hpp"

namespace hibpm
{
    class RepairAutomata
    {
    public:
        list<Automaton> expand(list<Automaton> automata);

        list<Automaton> shrinkInc(list<Automaton> automata,
                                  list<Automaton> prevProds);
    };

}
