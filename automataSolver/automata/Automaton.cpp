//
//  Automaton.cpp
//  declareSolver
//
//  Created by Jandson on 27.04.21.
//

#include "Automaton.hpp"


Automaton::Automaton(int numState, int sigmaSize){
    
    
    
    this->transitionsTo = new vector<vector<int> >(numState);
    this->incoming = new vector<vector<list<int> > >(numState);
    
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

Automaton* Automaton::product(Automaton *a1, Automaton *a2){
    
        
    unsigned long
        sizeA1 = a1->transitionsTo->size(),
        sizeA2 = a2->transitionsTo->size(),
        sigmaS = a1->transitionsTo->at(0).size();
    
    
    vector<vector<unsigned long> > mat(sizeA1, vector<unsigned long>(sizeA2,-1));
    
    mat[0][0] = 0;
    
    struct cell{
        pair<int, int> nState;
        vector<int> transitions;
        
        void init(int x, int y, unsigned long vsize){
            nState.first = x;
            nState.second = y;
            transitions.resize(vsize);
        }
    };
    
    cell *c = new cell;
    c->init(0, 0, sigmaS);
    
    list<cell*> nStates;
    nStates.push_back(c);
    
    int controlStates = 0;
    
    
    for (list<cell*>::iterator it = nStates.begin(); it != nStates.end(); it++) {
        
        int cx = (*it)->nState.first,
        cy = (*it)->nState.second;
//        
        for (int a = 0; a < sigmaS; a++) {
//           
            int x1 = a1->transitionsTo->at(cx)[a],
                x2 = a2->transitionsTo->at(cy)[a];
//            
//            
            if (mat[x1][x2] == -1) {
                controlStates++;
                mat[x1][x2] = controlStates;
                c = new cell;
                c->init(x1, x2, sigmaS);
                nStates.push_back(c);
            }
////
//            unsigned long pairDecod = mat[x1][x2];
////
//            (*it)->transitions[a] = pairDecod;
////
        }
        
    }
    
    
    
    Automaton *result = new Automaton(controlStates+1, sigmaS);
    
//    int i = 0;
//    for (list<cell*>::iterator it = nStates.begin(); it != nStates.end() ; it++) {
//
//        int x =(*it)->nState.first,
//        y = (*it)->nState.second;
////
//
//        cout << x << ":" << y << "\n";
//        int state = mat[x][y];
////
//        cout << state<< "\n";
//        if (a1->areFinalStates[(*it)->nState.first] && a2->areFinalStates[(*it)->nState.second] &&
//            !result->areFinalStates[state]) {
//            result->addFinal(state);
//        }
//
//        for (int a = 0; a < sigmaS; a++) {
//            cout << a << "--" << sigmaS <<  "\n";
//            cout << (*it)->transitions.size() << "------\n";
//            if((*it)->transitions[a] >= 0){
//                result->addTransition(state, (*it)->transitions[a], a);
//            }
//        }
////
//        i++;
////
////
//    }
    
    return result;
    
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


