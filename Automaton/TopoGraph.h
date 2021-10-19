//
// Created by Jandson on 15.10.21.
//

#ifndef DECLARE_PARSER_TOPOGRAPH_H
#define DECLARE_PARSER_TOPOGRAPH_H

#include "Process/State.hpp"
#include <memory>

using namespace hibpm;
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
    vector<pair<Rule,int>> order;
    TopoGraph(vector<std::shared_ptr<State>> &process, int numEvents);
    list<list<State*>> grounded;

    void add(State &state);

    ~TopoGraph();

    bool isSubSumedBy(Rule r1, Rule r2);
    bool isLessThanByType(Rule r1, Rule r2);

    bool isPosition(Rule r1);

    bool isCardinality(Rule r1);

    bool IsCoupling(Rule r1);

    bool IsForwardBackwards(Rule r1);

    bool isNegative(Rule r1);

    void buildAtivationLink(vector<std::shared_ptr<State>> &process, int numEvents);

    bool isLessThenActivation(Rule r1, Rule r2);
};


#endif //DECLARE_PARSER_TOPOGRAPH_H
