#include "RepairAutomata.hpp"

namespace hibpm
{
    list<Automaton> RepairAutomata::expand(list<Automaton> automata) {

        list<Automaton> res;
        list<Automaton>::iterator itA = automata.begin();

        res.push_back(*itA);

        Automaton prod = (*itA);

        for (++itA ; itA != automata.end(); itA++ ) {

            Automaton stepProd = prod.product(&prod,&(*itA));
            if (!stepProd.isEmptyMinusEmptyString()){
                prod = stepProd;
                res.push_back(*itA);
            }

        }


        return res;

    }

    list<Automaton> RepairAutomata::shrinkInc(list<Automaton> automata,
                                                     list<Automaton> prevProds) {

        list<Automaton> res;

        list<Automaton>::reverse_iterator itA = automata.rbegin();
        list<Automaton>::reverse_iterator itProds = prevProds.rbegin();

        return res;
    }
}
