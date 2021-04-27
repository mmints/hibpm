//
//  Automaton.cpp
//  declareSolver
//
//  Created by Jandson on 27.04.21.
//

#include "Automaton.hpp"


Automaton::Automaton(int numState, int sigmaSize){
    
    
    
    this->transitionsTo = new vector<vector<int>>(numState);
    this->incoming = new vector<vector<list<int>>>(numState);
    
    for (int i=0; i < numState; i++) {
        this->transitionsTo->at(i).resize(sigmaSize,-1);
        this->incoming->at(i).resize(sigmaSize);
    }
    
    this->areFinalStates.resize(numState, false);
    
    
}

Automaton::Automaton(int numStates, int sigmaSize, list<int> *finals){
    
    Automaton(numStates, sigmaSize);
    
    this->finalStates.insert(this->finalStates.end(), 0);
}

void Automaton::addTransition(int stateFrom, int stateTo, int viaSymbol){
    
    this->transitionsTo->at(stateFrom)[viaSymbol] = stateTo;
    
    this->incoming->at(stateTo)[viaSymbol].push_back(stateFrom);
    
}

void Automaton::addFinal(int state){
    this->areFinalStates[state] = true;
    this->finalStates.push_back(state);
}




void Automaton::print(){
    
    for (int i =0; i< this->transitionsTo->size(); i++) {
        
        int nSymbols = this->transitionsTo->at(i).size();
        for (int j = 0; j< nSymbols; j++) {
            
            std::cout << this->transitionsTo->at(i)[j] << " | ";
            
        }
        std::cout << "\n";
        
    }
}


