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

    std::list<shared_ptr<State>> RepairAutomata::controlShrink(Process& process)
    {
        vector<shared_ptr<State>> states = process.getStates();
        list<shared_ptr<State>> solution; // Symbols

        // Assign first formula to S and
        solution.push_back(states[0]);
        Automaton rightProd = states[0]->getAutomata();

        Automaton auxProd;
        Automaton phi;

        int i = states.size();
        while (i > 1 && !rightProd.isEmptyMinusEmptyString()) // while i>1 AND L(rightProd)̸=∅
        {
            phi = states[i]->getAutomata();
            auxProd = rightProd.product(&phi, &rightProd);

            if (!auxProd.isEmptyMinusEmptyString()) {
                solution.push_back(states[i]);
                rightProd = rightProd.product(&phi, &rightProd);
            }
            i--;
        }

        // Add the last element to S
        if (!rightProd.isEmptyMinusEmptyString()) {
            solution.push_back(states[0]);
        }

        return solution;
    }

    void RepairAutomata::controlExpand()
    {
        std::vector<Automaton> Hs;
        std::vector<Automaton> kernels;

    }
}
