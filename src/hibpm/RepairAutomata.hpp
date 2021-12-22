#pragma once

#include <vector>
#include <memory>

#include "Automaton.hpp"
#include "Rule.hpp"
#include "DeclareKnowledgeBase.hpp"

//#include "GraphSolver.h"

namespace hibpm
{
    struct RemainderComposition
    {
        list<shared_ptr<Rule>> hittingSet;
        list<list<shared_ptr<Rule>>> kernelSet;
        list<shared_ptr<Rule>> solutionSet;
    };

    class RepairAutomata
    {
    public:

        list<shared_ptr<Rule>> shrinkGraph(list<shared_ptr<Rule>> set, int numEv);
        RemainderComposition expandGraph(vector<shared_ptr<Rule>> &ruleSet, int numEvs);


        list<Automaton> expand(list<Automaton> &automata);

        list<Automaton> shrinkInc(list<Automaton> &automata,
                                  list<Automaton> &prevProds);

        Automaton maxRemainder(DeclareKnowledgeBase &declareKnowledgeBase);

        list<shared_ptr<Rule>> controlShrink(list<shared_ptr<Rule>> &ruleSet, shared_ptr<Rule> alpha, list<Automaton> &products);

        RemainderComposition controlExpand(DeclareKnowledgeBase &declareKnowledgeBase);

        RemainderComposition lazyExpands(DeclareKnowledgeBase &declareKnowledgeBase);
        list<shared_ptr<Rule>> lazyShrink(list<shared_ptr<Rule>> &ruleSet,
                                           shared_ptr<Rule> alpha);
        list<shared_ptr<Rule>> oneKernelN(list<shared_ptr<Rule>> &ruleSet, shared_ptr<Rule> alpha, int size);
    };
}
