//
//  Automaton.cpp
//  declareSolver
//
//  Created by Jandson on 27.04.21.
//

#include "Automaton.hpp"

Automaton::Automaton(int numState, int sigmaSize) {
    
    this->transitionsTo = new vector<vector<int> >(numState);
    this->incoming = new vector<vector<list<int> > >(numState);
    
    for (int i = 0; i < numState; i++) {
        this->transitionsTo->at(i).resize(sigmaSize, -1);
        this->incoming->at(i).resize(sigmaSize);
    }
    
    this->areFinalStates.resize(numState, false);
    
}

Automaton::Automaton(int numStates, int sigmaSize, list<int> *finals) {
    
    Automaton(numStates, sigmaSize);
    
    this->finalStates.insert(this->finalStates.end(), 0);
}

void Automaton::addTransition(int stateFrom, int stateTo, int viaSymbol) {
    
    this->transitionsTo->at(stateFrom)[viaSymbol] = stateTo;
    
    this->incoming->at(stateTo)[viaSymbol].push_back(stateFrom);
    
}

void Automaton::addFinal(int state) {
    
    if (!this->areFinalStates[state]) {
        this->finalStates.push_back(state);
        this->areFinalStates[state] = true;
    }
}






Automaton* Automaton::product(Automaton *a1, Automaton *a2) {
    
    unsigned long sizeA1 = a1->transitionsTo->size(), sizeA2 =
    a2->transitionsTo->size(), sigmaS = a1->transitionsTo->at(0).size();
    
    vector<vector<triple> > mat(sizeA1,
                                vector<triple>(sizeA2, triple()));
    
    mat[0][0].mapping = 0;
    
//    struct cell {
//        pair<int, int> nState;
//        vector<int> transitions;
//
//        cell(int x, int y, unsigned long vsize) {
//            nState.first = x;
//            nState.second = y;
//            transitions.resize(vsize);
//        }
//    };
    

    
    cell *c = new cell(0,0, sigmaS);
    //c->init(0, 0, sigmaS);
    
    list<cell*> nStates;
    nStates.push_back(c);
    
    int controlStates = 0;
    
    for (list<cell*>::iterator it = nStates.begin(); it != nStates.end();
         it++) {
        
        int cx = (*it)->nState.first,
        cy = (*it)->nState.second;
        //
        for (int a = 0; a < sigmaS; a++) {
            //
            int x1 = a1->transitionsTo->at(cx)[a],
            x2 = a2->transitionsTo->at(cy)[a];
            //            //TODO consider case that X1,X2 = -1
            //
            if (x1 != -1 && x2 != -1) {
                
                if (mat[x1][x2].mapping == -1) {
                    controlStates++;
                    mat[x1][x2].mapping = controlStates;
                    c = new cell(x1, x2, sigmaS);
                    //c->init(x1, x2, sigmaS);
                    nStates.push_back(c);
                }
                ////
                int pairDecod = mat[x1][x2].mapping;
                //
                (*it)->transitions[a] = pairDecod;
                //
            }
        }
        
    }
    
    Automaton *result = new Automaton(controlStates + 1, sigmaS);
    
    int i = 0;
    for (list<cell*>::iterator it = nStates.begin(); it != nStates.end();
         it++) {
        
        int x = (*it)->nState.first, y = (*it)->nState.second;
        //
        
        //cout << x << ":" << y << "\n";
        int state = mat[x][y].mapping;
        //
        //cout << state << "\n";
        if (a1->areFinalStates[(*it)->nState.first]
            && a2->areFinalStates[(*it)->nState.second]
            && !result->areFinalStates[state]) {
            result->addFinal(state);
        }
        
        for (int a = 0; a < sigmaS; a++) {
            
            if ((*it)->transitions[a] >= 0) {
                result->addTransition(state, (*it)->transitions[a], a);
            }
        }
        //
        i++;
        //
        //
    }
    
    return result;
    
}

Automaton* Automaton::reduceHopcrof() {
    
    struct cellPartition {
        list<int> *container, *splittingArea;
        bool inTheStack = false;
        bool visited = false;
        int partCode = -1;
        void init() {
            container = new list<int>();
            splittingArea = new list<int>();
            inTheStack = false;
            visited = false;
        }
        cellPartition* split() {
            cellPartition *res = new cellPartition;
            
            res->container = splittingArea;
            res->splittingArea = new list<int>();
            res->inTheStack = false;
            res->visited = false;
            
            splittingArea = new list<int>();
            
            return res;
        }
        
    };
    
    struct cellV {
        cellPartition *cellP;
        list<int>::iterator itContainer;
        
        void init(cellPartition *cp, list<int>::iterator it) {
            cellP = cp;
            itContainer = it;
        }
        void check() {
            
            cellP->splittingArea->push_back(*itContainer);
            //
            cellP->container->erase(itContainer);
            //
            itContainer = --(cellP->splittingArea->end());
            
        }
    };
    
    vector<cellV> stateMap(this->transitionsTo->size());
    
    list<cellPartition*> partitions;
    
    cellPartition *p1 = new cellPartition, *p2 = new cellPartition;
    
    p1->init(); //partition of final states
    p2->init(); //partiiton of non final states
    
    //initialise the two first partitions
    for (int i = 0; i < this->transitionsTo->size(); i++) {
        
        //stateMap[i].checked = false;
        
        list<int>::iterator itaux;
        
        if (this->areFinalStates[i]) {
            p1->container->push_back(i);
            itaux = --(p1->container->end());
            stateMap[i].cellP = p1;
        } else {
            p2->container->push_back(i);
            itaux = --(p2->container->end());
            stateMap[i].cellP = p2;
        }
        
        stateMap[i].itContainer = itaux;
        
    }
    
    partitions.push_back(p1);
    
    //sort by size
    if (p1->container->size() < p2->container->size()) {
        partitions.push_back(p2);
    } else {
        partitions.push_front(p2);
    }
    
    for (list<cellPartition*>::iterator it = partitions.begin();
         it != partitions.end(); it++) {
        
        cellPartition *celP = (*it);
        celP->visited = true;
        //
        for (int a = 0; a < this->transitionsTo->at(0).size(); a++) {
            //list<int> incidingSet;
            list<pair<cellPartition*, list<cellPartition*>::iterator> > checkedPartitions;
            
            for (int i = 0; i < celP->container->size(); i++) {
                list<int> *inSet = &(this->incoming->at(i)[a]);
                
                for (int j = 0; j < inSet->size(); j++) {
                    
                    if (!celP->inTheStack) {
                        pair<cellPartition*, list<cellPartition*>::iterator> pairCell(
                                                                                      celP, it);
                        checkedPartitions.push_back(pairCell);
                        celP->inTheStack = true;
                    }
                    
                    stateMap[j].check();
                    
                    
                }
            }
            
            
            for (; !checkedPartitions.empty(); checkedPartitions.pop_front()) {
                
                pair<cellPartition*, list<cellPartition*>::iterator> frontEl =
                checkedPartitions.front();
                
                cellPartition *cp = frontEl.first;
                
                cp->inTheStack = false;
                
                if (cp->container->empty()) {
                    //swap
                    list<int> *cAux = cp->splittingArea;
                    cp->splittingArea = cp->container;
                    cp->container = cAux;
                } else {
                    
                    cellPartition *nPart = cp->split();
                    
                    for (list<int>::iterator ito = nPart->container->begin();
                         ito != nPart->container->end(); ito++) {
                        stateMap[*ito].cellP = nPart;
                        
                    }
                    
                    //checked if it was visited already, i.e,
                    if (!cp->visited) {
                        partitions.push_back(cp);
                        partitions.push_back(nPart);
                    } else {
                        
                        if (nPart->container->size() <= cp->container->size()) {
                            partitions.push_back(nPart);
                        } else {
                            //partitions.push_back(cp);
                            cp->visited = false;
                            nPart->visited = true;
                            partitions.push_front(nPart);
                            partitions.erase(frontEl.second);
                            partitions.push_back(cp);
                            
                        }
                        
                    }
                    
                }
                
            }
            
        }
        
    }
    
    //// creating result automaton
    Automaton *res = new Automaton(partitions.size(),
                                   this->transitionsTo[0].size());
    ////
    //
    //
    stateMap[0].cellP->partCode = 0;
    int countP = 0;
    ////
    for (list<cellPartition*>::iterator it = partitions.begin();
         it != partitions.end(); it++) {
        
        if ((*it)->partCode == -1) {
            
            (*it)->partCode = ++countP;
            
        }
        
    }
    
    
    ////
    for (list<cellPartition*>::iterator it = partitions.begin();
         it != partitions.end(); it++) {
        
        for (int a = 0; a < this->transitionsTo[0].size(); a++) {
            
            int stateinPart = (*it)->container->front();
            int reachState = this->transitionsTo->at(stateinPart)[a];
            
            if (reachState >= 0) {
                
                res->addTransition((*it)->partCode,
                                   stateMap[reachState].cellP->partCode, a);
                
            }
            //
            if (this->areFinalStates[stateinPart]) {
                res->addFinal((*it)->partCode);
            }
            
        }
        
    }
    ////
    ////
    return res;
    //	return NULL;
    
}

bool Automaton::checkUseful(int x, int y, vector<vector<triplett> > &mat){
    
    if (mat[x][y].visited) {
        return mat[x][y].useful;
    }
    
    mat[x][y].visited = true;
    
    for (int a = 0; a < mat[x][y].scell->transition.size(); a++) {
        
        int cx, cy;
        
        cx = mat[x][y].scell->transition[a].first;
        cy = mat[x][y].scell->transition[a].second;
        
        if(cx >= 0 && cy <= 0){
            
            if (checkUseful(cx, cy, mat)) {
                mat[x][y].useful = true;
            }
            
        }
        
        
    }
    
    
    return mat[x][y].useful;
}


Automaton Automaton::full_product(Automaton &a1, Automaton &a2){
    
    
    list<simpleCell> stack;
    
    vector<vector<triplett> > mat(a1.transitionsTo->size(), vector<triplett>(a2.transitionsTo->size(), triplett()));
    
    int sigmaS = a1.transitionsTo->at(0).size();
    
    stack.push_back(simpleCell(0,0,sigmaS));
    
    //mat[0][0].assingMapping(0);
    mat[0][0].stacked = true;
    mat[0][0].scell = &stack.back();
    
    for (list<simpleCell>::iterator it = stack.begin(); it != stack.end(); it++) {
           
        
        
        for (int a = 0; a < sigmaS; a++) {
            
            int cx, cy;
            cx = a1.transitionsTo->at(it->cx)[a];
            cy = a2.transitionsTo->at(it->cx)[a];
            
            it->transition[a].first = cx;
            it->transition[a].second = cy;
            
            if (cx >= 0 && cy >= 0) {
                
                if (!mat[cx][cy].stacked) {
                    mat[cx][cy].stacked = true;
                    stack.push_back(simpleCell(cx, cy, sigmaS));
                    mat[cx][cy].scell = &stack.back();
                }
                
                
                if (a1.areFinalStates[cx] && a2.areFinalStates[cy]) {
                    mat[cx][cy].useful = true;
                }
                
            }
                        
            
        }
        
    }
    
    // parse to remove useless states
    checkUseful(0, 0, mat);
    
    for (list<simpleCell>::iterator it = stack.begin(); it != stack.end(); it ++) {
        
        if (!mat[it->cx][it->cy].useful) {
            stack.erase(it);
        }
        
    }
    
    
    int controlMap = 0;
    
    Automaton res(stack.size(), sigmaS);
    
    for (list<simpleCell>::iterator it = stack.begin(); it != stack.end(); it ++) {
     
        if (!mat[it->cx][it->cy].mapped) {
            mat[it->cx][it->cy].assingMapping(controlMap);
            controlMap++;
        }
        
        if (a1.areFinalStates[it->cx] && a2.areFinalStates[it->cy]) {
            res.addFinal(mat[it->cx][it->cy].mapping);
        }
        
        for (int a = 0; a < sigmaS; a++) {
            
            int cx, cy;
            
            cx = it->transition[a].first;
            cy = it->transition[a].second;
            
            if(cx >= 0 && cy >= 0 && mat[cx][cy].useful){
                
                if(!mat[cx][cy].mapped){
                    mat[cx][cy].assingMapping(controlMap);
                    controlMap++;
                }
                
                
                res.addTransition(mat[it->cx][it->cy].mapping, mat[cx][cy].mapping, a);
                
                
            }
        }
        
        
    }
    
    
    return res;
}




bool Automaton::isEmptyMinusEmptString() {
    
    if (this->transitionsTo->size() == 0) {
        return true;
    }
    
    if(this->finalStates.size() == 0){
        return true;
    }
    
    if (this->finalStates.size()==1 && this->areFinalStates[0]){
        
        for( int a = 0; a <  this->transitionsTo[0].size(); a++){
            
            if(this->incoming[0][a].size() > 0){
                return false;
            }
            
        }
        return true;
    }
    
    
    return false;
}

void Automaton::print() {
    
    if (this->transitionsTo->size() == 0) {
        cout << "empty automaton" << endl;
    }
    
    for (int i = 0; i < this->transitionsTo->size(); i++) {
        
        int nSymbols = this->transitionsTo->at(i).size();
        for (int j = 0; j < nSymbols; j++) {
            
            std::cout << this->transitionsTo->at(i)[j] << " | ";
            
        }
        std::cout << "\n";
        
    }
}

