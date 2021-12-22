#pragma once

#include <memory>

#include "Rule.hpp"

namespace hibpm {

    class TopoGraph {

//    struct Cell {
////        State* value;
////        list<Cell*> cellsAbove, cellsBelow;
////        Cell *nextCell, *prevCell;
////        Cell(State *s){
////            value = s;
////        }
//        State* value;
//        list<Cell> cellsAbove;
//    };



    public:
        vector<pair<Rule, int>> order;
        vector<vector<vector<int>>> orderMat;

        TopoGraph(vector<std::shared_ptr<Rule>> &process, int numEvents);

        list<list<std::shared_ptr<Rule>>> grounded;

        void add(Rule &rule);

        ~TopoGraph();

        bool isLesssThan(shared_ptr<Rule> s1, shared_ptr<Rule> s2);


        void sortN(vector<shared_ptr<Rule>> &vet);

        void sortTriple(vector<shared_ptr<Rule>> &vet);

        bool isSubSumedBy(Rule &r1, Rule &r2);

        bool isSubSumRel(Rule &r1, Rule &r2);

        bool isLessThanByType(Rule &r1, Rule &r2);

        bool isTypeSubs(Rule &r1, Rule &r2);

        bool isPosition(Rule &r1);

        bool isCardinality(Rule &r1);

        bool isCoupling(Rule &r1);

        bool isForwardBackwards(Rule &r1);

        bool isNegative(Rule &r1);

        void buildActivationLink(vector<std::shared_ptr<Rule>> &process, size_t sigmaSize);

        bool isLessThenActivation(Rule &r1, Rule &r2);

        void sortTripleDESC(vector<shared_ptr<Rule>> &vet);

        void buildMatrixEvent(vector<std::shared_ptr<Rule>> &process, size_t sigmaSize);

    };
}
