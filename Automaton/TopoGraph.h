#pragma once

#include "Process/State.hpp"
#include <memory>

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

        TopoGraph(vector<std::shared_ptr<State>> &process, int numEvents);

        list<list<State *>> grounded;

        void add(State &state);

        ~TopoGraph();

        bool isLesssThan(shared_ptr<State> s1, shared_ptr<State> s2);


        void sortN(vector<shared_ptr<State>> &vet);

        void sortTriple(vector<shared_ptr<State>> &vet);

        bool isSubSumedBy(Rule r1, Rule r2);

        bool isSubSumRel(Rule r1, Rule r2);

        bool isLessThanByType(Rule r1, Rule r2);

        bool isTypeSubs(Rule r1, Rule r2);

        bool isPosition(Rule r1);

        bool isCardinality(Rule r1);

        bool IsCoupling(Rule r1);

        bool IsForwardBackwards(Rule r1);

        bool isNegative(Rule r1);

        void buildAtivationLink(vector<std::shared_ptr<State>> &process, int numEvents);

        bool isLessThenActivation(Rule r1, Rule r2);

        void sortTripleDESC(vector<shared_ptr<State>> &vet);

        void buildMatrixEvent(vector<std::shared_ptr<State>> &process, int numEvents);

    };
}
