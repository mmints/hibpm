//
// Created by Jandson on 15.10.21.
//

#ifndef DECLARE_PARSER_TOPOGRAPH_H
#define DECLARE_PARSER_TOPOGRAPH_H

#include "Process/State.hpp"

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
    TopoGraph();
    list<list<State*>> grounded;

    void add(State &state);

    ~TopoGraph();

    bool isSubSumedBy(Rule r1, Rule r2);

};


#endif //DECLARE_PARSER_TOPOGRAPH_H
