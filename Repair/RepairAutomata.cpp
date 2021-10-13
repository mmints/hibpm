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

    Automaton RepairAutomata::maxRemainder(Process &process)
    {
        Automaton result;
        Automaton auxProd;
        Automaton a;

        result = process.getStates().at(0)->getAutomata();
        for (int i = 1; i < process.getStates().size(); i++)
        {
            // Debug Print
            // std::cout << "Iteration: " << i << " - Automata Size: " << result.numSt << std::endl;
            a = process.getStates().at(i)->getAutomata();

            auxProd = a.product(&a, &result);
            if(!auxProd.isEmptyMinusEmptyString()) {
                result = auxProd;
            }
        }
        return result;
    }

    std::vector<int> RepairAutomata::controlShrink(Process& process)
    {
        vector<shared_ptr<State>> states = process.getStates();
        std::vector<int> S; // Symbols

        // Get the first element
        if (states[0]->isBinary()) { // Binary
            S.push_back(states[0]->getRule().events[0].numericValue);
            S.push_back(states[0]->getRule().events[1].numericValue);
        }
        else { // Unary
            S.push_back(states[0]->getRule().events.at(0).numericValue);
        }
        Automaton rightProd = states[0]->getAutomata();
        Automaton auxProd;
        Automaton phi;

        int i = states.size();
        while (i > 1 && !rightProd.isEmptyMinusEmptyString()) // while i>1 AND L(rightProd)̸=∅
        {
            phi = states[i]->getAutomata();
            auxProd = rightProd.product(&phi, &rightProd);

            if (!auxProd.isEmptyMinusEmptyString()) {
                if (states[i]->isBinary()) { // Binary
                    S.push_back(states[i]->getRule().events[0].numericValue);
                    S.push_back(states[i]->getRule().events[1].numericValue);
                }
                else { // Unary
                    S.push_back(states[i]->getRule().events.at(0).numericValue);
                }
                rightProd = rightProd.product(&phi, &rightProd);
            }
            i--;
        }

        // Add the last element to S
        if (!rightProd.isEmptyMinusEmptyString()) {
            if (states[1]->isBinary()) { // Binary
                S.push_back(states[1]->getRule().events[0].numericValue);
                S.push_back(states[1]->getRule().events[1].numericValue);
            }
            else { // Unary
                S.push_back(states[1]->getRule().events.at(0).numericValue);
            }
        }
        return S;
    }
}
