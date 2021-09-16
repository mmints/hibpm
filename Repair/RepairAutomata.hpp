//
// Created by Jandson on 14.09.21.
//

#ifndef DECLARE_PARSER_REPAIRAUTOMATA_HPP
#define DECLARE_PARSER_REPAIRAUTOMATA_HPP

#include "Automaton/Automaton.hpp"
class RepairAutomata {

public:
    list<hibpm::Automaton> expand(list<hibpm::Automaton> automata);
    list<hibpm::Automaton> shrinkInc(list<hibpm::Automaton> automata,
                                     list<hibpm::Automaton> prevProds);

};


#endif //DECLARE_PARSER_REPAIRAUTOMATA_HPP
