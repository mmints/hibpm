//
//  Automaton.hpp
//  declareSolver
//
//  Created by Jandson on 27.04.21.
//

#ifndef Automaton_hpp
#define Automaton_hpp

#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
using namespace std;

class Automaton{
            

    
public:
    
    vector<vector<int> > *transitionsTo;
    vector<vector< list<int> > > *incoming;
    int initialState = 0;
    vector<bool> areFinalStates;
    list<int> finalStates;
     
    
    Automaton(int numStates, int sigmaSize);
    Automaton(int numStates, int sigmaSize, list<int> *finals);
    
    void addTransition(int stateFrom, int stateTo, int viaSymbol);
    void addFinal(int state);
    
    void print();
    
    Automaton* product(Automaton *a1, Automaton *a2);
    
    
    
};

#endif /* Automaton_hpp */
