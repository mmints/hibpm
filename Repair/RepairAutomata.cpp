//
// Created by Jandson on 14.09.21.
//

#include "RepairAutomata.hpp"

list<hibpm::Automaton> RepairAutomata::expand(list<hibpm::Automaton> automata) {

    list<hibpm::Automaton> res;
    list<hibpm::Automaton>::iterator itA = automata.begin();

    res.push_back(*itA);

    hibpm::Automaton prod = (*itA);

    for (++itA ; itA != automata.end(); itA++ ) {

        hibpm::Automaton stepProd = prod.product(&prod,&(*itA));
        if (!stepProd.isEmptyMinusEmptyString()){
            prod = stepProd;
            res.push_back(*itA);
        }

    }


    return res;

}

list<hibpm::Automaton> RepairAutomata::shrinkInc(list<hibpm::Automaton> automata,
                                                 list<hibpm::Automaton> prevProds) {

    list<hibpm::Automaton> res;

    list<hibpm::Automaton>::reverse_iterator itA = automata.rbegin();
    list<hibpm::Automaton>::reverse_iterator itProds = prevProds.rbegin();





    return res;
}


