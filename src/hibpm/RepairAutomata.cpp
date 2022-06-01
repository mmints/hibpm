/**
 * @author:  Dr. Jandson Santos Ribeiro Santos
 * @email: jandson.ribeiro@fernuni-hagen.de
 */

#include "RepairAutomata.hpp"
#include "hibpm/Constraint.hpp"

namespace hibpm {
list<Automaton> RepairAutomata::expand(list<Automaton> &automata) {

  list<Automaton> res;
  list<Automaton>::iterator itA = automata.begin();

  res.push_back(*itA);

  Automaton prod = (*itA);

  for (++itA; itA != automata.end(); itA++) {
    Automaton stepProd = prod.product(&prod, &(*itA));
    if (!stepProd.isEmptyMinusEmptyString()) {
      prod = stepProd;
      res.push_back(*itA);
    }
  }
  return res;
}

/*
    list<shared_ptr<State>> RepairAutomata::shrinkGraph(list<shared_ptr<State>>
   set, int numEv){

        if(set.size() <= 1){
            return set;
        }

        list<shared_ptr<State>> res;

        list<shared_ptr<State>>::iterator it = set.end();
        //it--;
        GraphSolver gs(numEv);
        for (--it; it != set.begin() ; it--) {



            gs = GraphSolver(numEv);

            list<shared_ptr<State>> auxT(set.begin(), it);
            gs.incrementAll(auxT);
            gs.incrementAll(res);

            if (gs.getStatus()){//gs is consistent, we need add alpha in it++
                //list<shared_ptr<State>>::iterator itAux = it;
                //itAux++;
                shared_ptr<State> ss = (*it);
                res.push_back(*it);
            }

        }

        GraphSolver gs2(numEv);
        //gs = GraphSolver(numEv);
        gs2.incrementAll(res);

        if (gs2.getStatus()){
            res.push_back(*set.begin());
        }


        return res;
    }

    RemainderComposition RepairAutomata::expandGraph(vector<shared_ptr<State>>
   &ruleSet, int numEvs) {


        RemainderComposition rc;

        GraphSolver gs(numEvs), gsAux(numEvs);

        int i = 1;

        for (shared_ptr<State> strP: ruleSet) {

            gsAux.increment(strP);
            if (gsAux.getStatus()){
                gs = gsAux;
                rc.solutionSet.push_back(strP);
            }else{
                std::cout <<"iterat9on with conflic ----- " << i << std::endl;
                gsAux = gs;
                rc.hittingSet.push_back(strP);
                list<shared_ptr<State>> accum = rc.solutionSet;
                accum.push_back(strP);
                list<shared_ptr<State>> kern = this->shrinkGraph(accum, numEvs);
                rc.kernelSet.push_back(kern);
                std::cout <<"###### ----- Kernel size " << kern.size() <<
   std::endl; Automaton ac; list<Automaton> lAc;
                lAc.push_back(strP->getAutomata());
                for (shared_ptr<State> s: kern) {
                    lAc.push_back(s->getAutomata());
                }
                std::cout <<"###### ----- >>>>>>>Confirmation " <<
   ac.lazyProducts(lAc) << std::endl;


            }
            i++;

        }
        return rc;

    }
*/

list<Automaton> RepairAutomata::shrinkInc(list<Automaton> &automata,
                                          list<Automaton> &prevProds) {

  list<Automaton> res;

  list<Automaton>::reverse_iterator itA = automata.rbegin();
  list<Automaton>::reverse_iterator itProds = prevProds.rbegin();

  return res;
}

Automaton
RepairAutomata::maxRemainder(DeclareKnowledgeBase &declareKnowledgeBase) {
  Automaton result;
  Automaton auxProd;
  Automaton a;

  result = declareKnowledgeBase.getConstraintSet().at(0)->getAutomata();
  for (int i = 1; i < declareKnowledgeBase.getConstraintSet().size(); i++) {
    // Debug Print
    // std::cout << "Iteration: " << i << " - Automata Size: " << result.numSt
    // << std::endl;
    a = declareKnowledgeBase.getConstraintSet().at(i)->getAutomata();

    auxProd = a.product(&a, &result);
    if (!auxProd.isEmptyMinusEmptyString()) {
      result = auxProd;
    }
  }
  return result;
}

std::list<shared_ptr<Constraint>>
RepairAutomata::controlShrink(list<shared_ptr<Constraint>> &ruleSet,
                              shared_ptr<Constraint> alpha,
                              list<Automaton> &products) {
  list<shared_ptr<Constraint>> solution; // Symbols

  // Assign first formula to S and
  solution.push_back(alpha);
  Automaton rightProd = alpha->getAutomata();

  Automaton auxProd;
  Automaton phi;

  list<Automaton>::reverse_iterator itProd = products.rbegin();
  list<shared_ptr<Constraint>>::reverse_iterator itConstraints =
                                                     ruleSet.rbegin(),
                                                 itRendP = ruleSet.rend();

  itRendP++;

  // int i = ruleSet.size() - 1;

  while (itConstraints != itRendP && !rightProd.isEmptyMinusEmptyString())
  // while (i > 0 && !rightProd.isEmptyMinusEmptyString()) // while i>1 AND
  // L(rightProd)̸=∅
  {
    list<Automaton>::reverse_iterator itProdPrev = itProd;
    itProd--;
    // auxProd = rightProd.product(&products[i-1], &rightProd);
    auxProd = rightProd.product(&(*itProdPrev), &rightProd);

    if (!auxProd.isEmptyMinusEmptyString()) {
      // solution.push_back(ruleSet[i]);
      solution.push_back((*itConstraints));
      phi = (*itConstraints)->getAutomata();
      rightProd = rightProd.product(&phi, &rightProd);
    }
    // i--;
    itConstraints--;
  }

  // Add the last element to S
  if (!rightProd.isEmptyMinusEmptyString()) {
    solution.push_back(ruleSet.front());
  }
  return solution;
}

RemainderComposition
RepairAutomata::controlExpand(DeclareKnowledgeBase &declareKnowledgeBase) {
  vector<shared_ptr<Constraint>> ruleSet =
      declareKnowledgeBase.getConstraintSet();
  RemainderComposition remainderComposition;
  list<Automaton> products; // TODO: change to list (also in the controlShrink)

  Automaton auxProd;
  Automaton phiAutomata;
  list<shared_ptr<Constraint>> tempKernel; // C in Algo 7

  remainderComposition.solutionSet.push_back(ruleSet[0]);
  products.push_back(ruleSet[0]->getAutomata());
  Automaton productAccumulator = ruleSet[0]->getAutomata();
  int reduceCount = 1;

  for (int i = 1; i < ruleSet.size(); i++, reduceCount++) {
    std::cout << "Running: " << i << std::endl;
    std::cout << "Size Automaton " << productAccumulator.numSt << std::endl;
    std::cout << "Num Finals " << productAccumulator.finalStates.size()
              << std::endl;
    phiAutomata = ruleSet[i]->getAutomata();
    //           if (reduceCount >=50){
    //                std::cout << "-- Reducing ---- Running: " << i <<
    //                std::endl; productAccumulator =
    //                productAccumulator.reduceHopcrof(); std::cout << "-------
    //                Reduced: Size Automaton " << productAccumulator.numSt <<
    //                std::endl; std::cout << "------- Reduced: Num Finals " <<
    //                productAccumulator.finalStates.size() << std::endl;
    //                reduceCount = 0;
    //          }
    auxProd = productAccumulator.product(&productAccumulator, &phiAutomata);
    if (!auxProd.isEmptyMinusEmptyString()) {
      remainderComposition.solutionSet.push_back(ruleSet[i]);
      products.push_back(auxProd);
      productAccumulator = auxProd;
    } else {
      std::cout << ">>>>>>>>>> Setting the Kernel" << std::endl;
      tempKernel =
          controlShrink(remainderComposition.solutionSet, ruleSet[i], products);
      remainderComposition.kernelSet.push_back(tempKernel);
      remainderComposition.hittingSet.push_back(ruleSet[i]);
      std::cout << ">>>>>>>>>> Size >>>>>>>>>>>>>>> " << tempKernel.size()
                << std::endl;
    }
  }
  return remainderComposition;
}

RemainderComposition
RepairAutomata::lazyExpands(DeclareKnowledgeBase &declareKnowledgeBase) {

  RemainderComposition remainderComposition;
  vector<std::shared_ptr<Constraint>> ruleSet =
      declareKnowledgeBase.getConstraintSet();

  list<Automaton> accAutomata;

  Automaton first = ruleSet[0]->getAutomata();
  remainderComposition.solutionSet.push_back(ruleSet[0]);
  accAutomata.push_back(first);

  for (int i = 1; i < ruleSet.size(); ++i) {

    std::cout << "iteration " << i << std::endl;

    accAutomata.push_back(ruleSet[i]->getAutomata());
    if (!first.lazyProducts(accAutomata)) {
      accAutomata.pop_back();
      remainderComposition.hittingSet.push_back(ruleSet[i]);
      list<shared_ptr<Constraint>> temK =
          oneKernelN(remainderComposition.solutionSet, ruleSet[i], 3);
      remainderComposition.kernelSet.push_back(temK);
      std::cout << "FOUNDCONFLICT >>>>>>>>>>>>>>>>>>>>>>> " << i << std::endl;
      list<shared_ptr<Constraint>> remL =
          lazyShrink(remainderComposition.solutionSet, ruleSet[i]);
      remainderComposition.kernelSet.push_back(remL);

      // std::cout << "FOUNDCONFLICT " << i << "HT ::" <<
      // remainderComposition.hittingSet.size() << std::endl;
    } else {
      remainderComposition.solutionSet.push_back(ruleSet[i]);
    }
  }

  return remainderComposition;
}

list<shared_ptr<Constraint>>
RepairAutomata::lazyShrink(list<shared_ptr<Constraint>> &ruleSet,
                           shared_ptr<Constraint> alpha) {

  list<shared_ptr<Constraint>> res;
  res.push_back(alpha);

  list<Automaton> accumRight;
  accumRight.push_back(alpha->getAutomata());

  list<shared_ptr<Constraint>>::iterator it = ruleSet.end();
  it--;

  for (; it != ruleSet.begin(); it--) {
    list<Automaton> aux(accumRight);

    for (list<shared_ptr<Constraint>>::iterator sit = ruleSet.begin();
         sit != it; sit++) {
      aux.push_back((*sit)->getAutomata());
    }

    if (alpha->getAutomata().lazyProducts(aux)) {
      accumRight.push_back((*it)->getAutomata());
      res.push_back(*it);
    }
  }

  return res;
}

list<shared_ptr<Constraint>>
RepairAutomata::oneKernelN(list<shared_ptr<Constraint>> &ruleSet,
                           shared_ptr<Constraint> alpha, int size) {

  list<shared_ptr<Constraint>> res;
  list<Automaton> aut;
  aut.push_back(alpha->getAutomata());
  res.push_back(alpha);

  for (list<shared_ptr<Constraint>>::iterator s = ruleSet.begin();
       s != ruleSet.end(); s++) {

    aut.push_back((*s)->getAutomata());
    if (!alpha->getAutomata().lazyProducts(aut)) {
      res.push_back(*s);
      return res;
    }

    list<shared_ptr<Constraint>>::iterator it2 = s;

    for (++it2; it2 != ruleSet.end(); it2++) {
      aut.push_back((*it2)->getAutomata());
      if (!alpha->getAutomata().lazyProducts(aut)) {
        res.push_back(*it2);
        return res;
      }
      aut.pop_back();
    }

    aut.pop_back();
  }

  return list<shared_ptr<Constraint>>();
}

} // namespace hibpm
