#pragma once

#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>

using namespace std;

namespace hibpm {

class Automaton{
public:

    struct cellProd{
        bool stacked;
        unsigned int mappedNum;
        cellProd(){
            stacked = false;
            mappedNum = 0;
        }

    };

//    struct simpleCell{
//        int cx, cy;
//        vector<pair<int, int>> transition;
//
//        simpleCell(int x, int y, int sigmaS){
//            cx = x;
//            cy = y;
//            transition.resize(sigmaS, pair<int, int>(-1,-1));
//        }
//    };
    
//    struct triplett{
//        simpleCell *scell = NULL;
//        int mapping;
//        bool visited, useful, stacked, mapped;
//
//        triplett(){
//            mapping = 0;
//            mapped = false;
//            visited = false;
//            useful = false;
//            stacked = false;
//        }
//        void assingMapping(int m){
//            mapping = m;
//            mapped = true;
//        }
//
//    };
    

    unsigned int sigSize, numSt;
    vector<vector<int> > transitionsTo;
    vector<vector< list<int> > > incoming;
    //int initialState = 0;
    vector<bool> areFinalStates;
    list<int> finalStates;
     
    
    Automaton(int numStates, int sigmaSize);
    Automaton(int numStates, int sigmaSize, list<int> &finals);
    
    void addTransition(int stateFrom, int stateTo, int viaSymbol);
    void addFinal(int state);
    
    void print();
    
    
    
    Automaton product(Automaton *a1, Automaton *a2);
    
    Automaton* reduceHopcrof();
    bool isEmptyMinusEmptyString();
        
    Automaton full_product(Automaton &a1, Automaton &a2);
    
private:
    
        
//    bool checkUseful(int x, int y, vector<vector<triplett> > &mat);

        void reachFinals(Automaton *a1, Automaton *a2, list<pair<int, int>> stacked, list<pair<int, int>> finals);
    };

}