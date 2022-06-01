/**
 * @author:  Dr. Jandson Santos Ribeiro Santos
 * @email: jandson.ribeiro@fernuni-hagen.de
 */

#pragma once

#include <memory>
#include <vector>

#include "Automaton.hpp"
#include "Constraint.hpp"
#include "DeclareKnowledgeBase.hpp"
#include "RemainderComposition.hpp"

//#include "GraphSolver.h"

namespace hibpm {
class RepairAutomata {
public:
  list<shared_ptr<Constraint>> shrinkGraph(list<shared_ptr<Constraint>> set,
                                           int numEv);
  RemainderComposition expandGraph(vector<shared_ptr<Constraint>> &ruleSet,
                                   int numEvs);

  list<Automaton> expand(list<Automaton> &automata);

  list<Automaton> shrinkInc(list<Automaton> &automata,
                            list<Automaton> &prevProds);

  Automaton maxRemainder(DeclareKnowledgeBase &declareKnowledgeBase);

  list<shared_ptr<Constraint>>
  controlShrink(list<shared_ptr<Constraint>> &ruleSet,
                shared_ptr<Constraint> alpha, list<Automaton> &products);

  RemainderComposition
  controlExpand(DeclareKnowledgeBase &declareKnowledgeBase);

  RemainderComposition lazyExpands(DeclareKnowledgeBase &declareKnowledgeBase);
  list<shared_ptr<Constraint>> lazyShrink(list<shared_ptr<Constraint>> &ruleSet,
                                          shared_ptr<Constraint> alpha);
  list<shared_ptr<Constraint>> oneKernelN(list<shared_ptr<Constraint>> &ruleSet,
                                          shared_ptr<Constraint> alpha,
                                          int size);
};
} // namespace hibpm
