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

    std::list<shared_ptr<State>> RepairAutomata::controlShrink(list<shared_ptr<State>> &states,
                                                               shared_ptr<State> alpha,
                                                               list<Automaton> &products)
    {
        list<shared_ptr<State>> solution; // Symbols

        // Assign first formula to S and
        solution.push_back(alpha);
        Automaton rightProd = alpha->getAutomata();

        Automaton auxProd;
        Automaton phi;

        list<Automaton>::reverse_iterator  itProd = products.rbegin();
        list<shared_ptr<State>>::reverse_iterator itStates = states.rbegin(), itRendP = states.rend();

        itRendP++;

        //int i = states.size() - 1;

        while(itStates != itRendP && !rightProd.isEmptyMinusEmptyString())
        //while (i > 0 && !rightProd.isEmptyMinusEmptyString()) // while i>1 AND L(rightProd)̸=∅
        {
            list<Automaton>::reverse_iterator itProdPrev = itProd;
            itProd--;
            //auxProd = rightProd.product(&products[i-1], &rightProd);
            auxProd = rightProd.product(&(*itProdPrev), &rightProd);

            if (!auxProd.isEmptyMinusEmptyString()) {
                //solution.push_back(states[i]);
                solution.push_back((*itStates));
                phi = (*itStates)->getAutomata();
                rightProd = rightProd.product(&phi, &rightProd);
            }
            //i--;
            itStates--;
        }

        // Add the last element to S
        if (!rightProd.isEmptyMinusEmptyString()) {
            solution.push_back(states.front());
        }
        return solution;
    }

    RemainderComposition RepairAutomata::controlExpand(Process& process)
    {
        vector<shared_ptr<State>> states = process.getStates();
        RemainderComposition remainderComposition;
        list<Automaton> products; // TODO: change to list (also in the controlShrink)

        Automaton auxProd;
        Automaton phiAutomata;
        list<shared_ptr<State>> tempKernel; // C in Algo 7

        remainderComposition.solutionSet.push_back(states[0]);
        products.push_back(states[0]->getAutomata());
        Automaton productAccumulator = states[0]->getAutomata();
        int reduceCount = 1;

        for (int i = 1; i < states.size(); i++, reduceCount++)
        {
            std::cout << "Running: " << i << std::endl;
            std::cout << "Size Automaton " << productAccumulator.numSt << std::endl;
            std::cout << "Num Finals " << productAccumulator.finalStates.size() << std::endl;
            phiAutomata = states[i]->getAutomata();
 //           if (reduceCount >=50){
//                std::cout << "-- Reducing ---- Running: " << i << std::endl;
//                productAccumulator = productAccumulator.reduceHopcrof();
//                std::cout << "------- Reduced: Size Automaton " << productAccumulator.numSt << std::endl;
//                std::cout << "------- Reduced: Num Finals " << productAccumulator.finalStates.size() << std::endl;
//                reduceCount = 0;
  //          }
            auxProd = productAccumulator.product(&productAccumulator, &phiAutomata);
            if (!auxProd.isEmptyMinusEmptyString())
            {
                remainderComposition.solutionSet.push_back(states[i]);
                products.push_back(auxProd);
                productAccumulator = auxProd;
            }
            else {
                std::cout << ">>>>>>>>>> Setting the Kernel" << std::endl;
                tempKernel = controlShrink(remainderComposition.solutionSet,
                                           states[i],
                                           products);
                remainderComposition.kernelSet.push_back(tempKernel);
                remainderComposition.hittingSet.push_back(states[i]);
                std::cout << ">>>>>>>>>> Size >>>>>>>>>>>>>>> " << tempKernel.size() << std::endl;
            }
        }
        return remainderComposition;
    }

    RemainderComposition RepairAutomata::lazyExpands(Process &process) {

        RemainderComposition remainderComposition;
        vector<std::shared_ptr<State>> states =process.getStates();

        list<Automaton> accAutomata;

        Automaton first = states[0]->getAutomata();
        remainderComposition.solutionSet.push_back(states[0]);

        for (int i = 1; i < states.size(); ++i) {

            //std::cout << "iteration " << i << std::endl;
            //std::cout << "iteration " << i << std::endl;

            accAutomata.push_back(states[i]->getAutomata());
            if(!first.lazyProducts(accAutomata)){
                accAutomata.pop_back();
                remainderComposition.hittingSet.push_back(states[i]);
//                list<shared_ptr<State>> temK = oneKernelN(remainderComposition.solutionSet,states[i],3);
//                remainderComposition.kernelSet.push_back(temK);
                //std::cout << "FOUNDCONFLICT " << i << std::endl;
                //list<shared_ptr<State>> remL = lazyShrink(remainderComposition.solutionSet,states[i]);
                //remainderComposition.kernelSet.push_back(remL);
                //std::cout << "FOUNDCONFLICT " << temK.size() << " Sike Kern " << std::endl;

                //std::cout << "FOUNDCONFLICT " << i << "HT ::" <<
               // remainderComposition.hittingSet.size() << std::endl;
            }else{
                remainderComposition.solutionSet.push_back(states[i]);
            }

        }

        return remainderComposition;
    }

    list<shared_ptr<State>>
    RepairAutomata::lazyShrink(list<shared_ptr<State>> &states, shared_ptr<State> alpha) {

        list<shared_ptr<State>> res;
        res.push_back(alpha);

        list<Automaton> accumRight;
        accumRight.push_back(alpha->getAutomata());

        list<shared_ptr<State>>::iterator it = states.end();
        it--;

        for( ; it != states.begin(); it--){
            list<Automaton> aux(accumRight);

            for (list<shared_ptr<State>>::iterator sit = states.begin(); sit != it ; sit++) {
                aux.push_back((*sit)->getAutomata());
            }

            if(alpha->getAutomata().lazyProducts(aux)){
                accumRight.push_back((*it)->getAutomata());
                res.push_back(*it);
            }

        }

        return res;
    }

    list<shared_ptr<State>> RepairAutomata::oneKernelN(list<shared_ptr<State>> &states,
                                                       shared_ptr<State> alpha, int size) {

        list<shared_ptr<State>> res;
        list<Automaton> aut;
        aut.push_back(alpha->getAutomata());
        res.push_back(alpha);

        for (list<shared_ptr<State>>::iterator s = states.begin(); s != states.end();s++) {

            aut.push_back((*s)->getAutomata());
            if(!alpha->getAutomata().lazyProducts(aut)){
                res.push_back(*s);
                return res;
            }

            list<shared_ptr<State>>::iterator it2 = s;

            for ( ++it2; it2 != states.end() ; it2++ ) {
                aut.push_back((*it2)->getAutomata());
                if(!alpha->getAutomata().lazyProducts(aut)){
                    res.push_back(*it2);
                    return res;
                }
                aut.pop_back();

            }

            aut.pop_back();

        }

        return list<shared_ptr<State>>();
    }

}
