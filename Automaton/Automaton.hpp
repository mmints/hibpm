#pragma once

#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>

using namespace std;

namespace hibpm {

class Automaton{
public:
    
    struct simpleCell{
        int cx, cy;
        vector<pair<int, int>> transition;
        
        simpleCell(int x, int y, int sigmaS){
            cx = x;
            cy = y;
            transition.resize(sigmaS, pair<int, int>(-1,-1));
        }
    };
    
    struct triplett{
        simpleCell *scell = NULL;
        int mapping;
        bool visited, useful, stacked, mapped;
        
        triplett(){
            mapping = 0;
            mapped = false;
            visited = false;
            useful = false;
            stacked = false;
        }
        void assingMapping(int m){
            mapping = m;
            mapped = true;
        }
        
    };
    
    struct triple{
        int mapping =-1;
        bool stacked = false, useful = false;
        triple(){
            mapping = -1;
            stacked = false;
            useful = false;
        }
        triple(int m, bool stk, bool us){
            mapping = m;
            stacked = stk;
            useful = us;
        }
    };
    
    struct cell {
        pair<int, int> nState;
        vector<int> transitions;
        
        cell(int x, int y, unsigned long vsize) {
            nState.first = x;
            nState.second = y;
            transitions.resize(vsize);
        }
    };
    
    struct cellPaired {
        pair<int, int> nState;
        vector<pair<int, int> > transitions;
        bool visited = false, useful = false;
        int mapping =-1;
        
        cellPaired(int x, int y, unsigned long vsize) {
            nState.first = x;
            nState.second = y;
            
            transitions.resize(vsize, pair<int, int>(-1,-1));
            
            visited = false;
            useful = false;
            mapping = -1;
        }
        
        cellPaired(int sizeV){
            cellPaired(0,0, sizeV);
        }
    };
    
    vector<vector<int> > *transitionsTo;
    vector<vector< list<int> > > *incoming;
    //int initialState = 0;
    vector<bool> areFinalStates;
    list<int> finalStates;
     
    
    Automaton(int numStates, int sigmaSize);
    Automaton(int numStates, int sigmaSize, list<int> *finals);
    
    void addTransition(int stateFrom, int stateTo, int viaSymbol);
    void addFinal(int state);
    
    void print();
    
    
    
    Automaton* product(Automaton *a1, Automaton *a2);
    
    Automaton* reduceHopcrof();
    bool isEmptyMinusEmptString();
        
    Automaton full_product(Automaton &a1, Automaton &a2);
    
private:
    
        
    bool checkUseful(int x, int y, vector<vector<triplett> > &mat);
};

}