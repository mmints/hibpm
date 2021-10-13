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

    std::list<shared_ptr<State>> RepairAutomata::controlShrink(vector<shared_ptr<State>> &states,
                                                               shared_ptr<State> alpha,
                                                               vector<Automaton> &products)
    {
        list<shared_ptr<State>> solution; // Symbols

        // Assign first formula to S and
        solution.push_back(alpha);
        Automaton rightProd = alpha->getAutomata();

        Automaton auxProd;
        Automaton phi;

        int i = states.size() - 1;
        while (i > 0 && !rightProd.isEmptyMinusEmptyString()) // while i>1 AND L(rightProd)̸=∅
        {
            auxProd = rightProd.product(&products[i-1], &rightProd);

            if (!auxProd.isEmptyMinusEmptyString()) {
                solution.push_back(states[i]);
                phi = states[i]->getAutomata();
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

    RemainderComposition RepairAutomata::controlExpand(Process& process)
    {
        vector<shared_ptr<State>> states = process.getStates();
        RemainderComposition remainderComposition;
        vector<Automaton> products; // TODO: change to list (also in the controlShrink)

        Automaton auxProd;
        Automaton phiAutomata;
        list<shared_ptr<State>> tempKernel; // C in Algo 7

        remainderComposition.solutionSet.push_back(states[0]);
        products.push_back(states[0]->getAutomata());
        Automaton productAccumulator = states[0]->getAutomata();

        for (int i = 1; i < states.size(); i++)
        {
            std::cout << "Running: " << i << std::endl;
            phiAutomata = states[i]->getAutomata();
            auxProd = productAccumulator.product(&productAccumulator, &phiAutomata);
            if (!auxProd.isEmptyMinusEmptyString())
            {
                remainderComposition.solutionSet.push_back(states[i]);
                products.push_back(auxProd);
                productAccumulator = auxProd;
            }
            else {
                std::cout << "Setting the Kernel" << std::endl;
                tempKernel = controlShrink(remainderComposition.solutionSet,
                                           states[i],
                                           products);
                remainderComposition.kernelSet.push_back(tempKernel);
                remainderComposition.hittingSet.push_back(states[i]);
            }
        }
        return remainderComposition;
    }
}
