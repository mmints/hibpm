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

Automaton* Automaton::semi_product(Automaton *a1, Automaton *a2) {
    
    unsigned long
        sizeA1 = a1->transitionsTo->size(),
        sizeA2 = a2->transitionsTo->size();
            
    if(sizeA1 == 0 || sizeA2 == 0){
        return new Automaton(0,0);
    }
    
     int sigmaS = a1->transitionsTo->at(0).size();
    
    vector<vector<cellPaired* > > mat(sizeA1,
                        vector<cellPaired*>(sizeA2,NULL));
    
    list<pair<int, int> > finalVisited;
    
       
    
    //cellPaired *c = new cellPaired(0,0, sigmaS);
    
    list<cellPaired> nStates;
    nStates.push_back(cellPaired(0,0,sigmaS));
    mat[0][0] = &nStates.front();
    
    //mat[0][0].stacked = true;
    
    if(a1->areFinalStates[0] && a2->areFinalStates[0]){
        finalVisited.push_back(pair<int, int>(0,0));
        mat[0][0]->useful = true;
    }
    
    //int controlStates = 0;
    
    for (list<cellPaired>::iterator it = nStates.begin(); it != nStates.end();
         it++) {
        
        int cx = (it)->nState.first,
            cy = (it)->nState.second;
        //
        for (int a = 0; a < sigmaS; a++) {
            //
            int x1 = a1->transitionsTo->at(cx)[a],
                x2 = a2->transitionsTo->at(cy)[a];
            
            if (x1 != -1 && x2 != -1) {
                
                if (!mat[x1][x2]) {
                    //controlStates++;
                    //mat[x1][x2].mapping = controlStates;
                    //c = new cell(x1, x2, sigmaS);
                    //c->init(x1, x2, sigmaS);
                    nStates.push_back(cellPaired(x1, x2, sigmaS));
                    mat[x1][x2] = &nStates.back();
                    if (a1->areFinalStates[x1] && a2->areFinalStates[x2] ) {
                        finalVisited.push_back(pair<int,int>(x1,x2));
                        mat[x1][x2]->useful = true;
                    }
                }
                ////
//                int pairDecod = mat[x1][x2].mapping;
//                //
//                (*it)->transitions[a] = pairDecod;
                it->transitions[a].first = x1;
                it->transitions[a].second = x2;
//                //
            }
        }
        
    }
    
    //remove useless states
    
    //vector<vector<pair<bool, bool> > > matControl(sizeA1,vector<pair<bool,bool>>(sizeA2, pair<bool, bool>(false, false)) );
    
    bool res = recCheck(*mat[0][0], mat);
    
    if (!res) {
        return new Automaton(0, a1->transitionsTo[0].size());
    }
    
    for (list<cellPaired>::iterator it = nStates.begin(); it != nStates.end(); it++) {
        if(!it->useful){
            mat[it->nState.first][it->nState.second]->useful = false;
            mat[it->nState.first][it->nState.second] = NULL;
            nStates.erase(it);
        }
    }
    
    Automaton *atRes = new Automaton(nStates.size(), sigmaS);
    
    int controllMap = 0;
    mat[0][0]->mapping = 0;
    
    
    for (list<cellPaired>::iterator it = nStates.begin(); it != nStates.end(); it++) {
        
        if(it->mapping == -1 && it->useful){
            it->mapping = ++controllMap;
        }
        
        //add transitions
        
        for (int a = 0 ; a <sigmaS ; a++) {
            
            pair<int, int> targetPair = it->transitions[a];
            
            if(targetPair.first != -1 && targetPair.second != -1){
                
                if( mat[targetPair.first][targetPair.second] &&  mat[targetPair.first][targetPair.second]->useful){
                    
                    if(mat[targetPair.first][targetPair.second]->mapping == -1){
                        mat[targetPair.first][targetPair.second]->mapping = ++controllMap;
                    }
                   
                    //if (mat[targetPair.first][targetPair.second]->mapping < nStates.size()) {
                        atRes->addTransition(it->mapping, mat[targetPair.first][targetPair.second]->mapping, a);
                    //}
                    
                    
                }
                
            }
        }
        
        
    }
    
    for (list<pair<int, int> >::iterator it = finalVisited.begin(); it != finalVisited.end(); it++) {
        
        atRes->addFinal(mat[it->first][it->second]->mapping);
        
    }
    
    if (nStates.size() == 1) {
        for (int a = 0; a < sigmaS; a++) {
            if (atRes->transitionsTo->at(0)[a] != -1) {
                return atRes;
            }
        }
    }
        
    atRes->transitionsTo->resize(0);
    return atRes;
}

bool Automaton::recCheck( Automaton::cellPaired &currentCel, vector<vector<cellPaired*> > &mat){
    
    currentCel.visited = true;
      
        
    for (int a = 0; a < currentCel.transitions.size(); a++) {
        
        pair<int, int> child = currentCel.transitions[a];
        if(child.first != -1 && child.second != -1 && !mat[child.first][child.second]->visited &&  recCheck(*mat[child.first][child.second], mat)){
            mat[child.first][child.second]->useful = true;
            //return true;
        }
        
    }
    
    return currentCel.useful;
    
    
}

void Automaton::removeUselessStates(){
    
    //start backtrascking from final ones
    
    for (list<int>::iterator  itF = this->finalStates.begin(); itF != this->finalStates.end(); itF++) {
        
        
        
    }
    
    
}

//bool Automaton::recCheck(pair<int, int> pos, vector<vector<pair<bool, bool> > > &parseMat, ){
//    
//    
//    
//    return true;
//}

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
    
    Automaton * result = new Automaton(controlStates + 1, sigmaS);
    
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

bool Automaton::isEmptyMinusEmptString() {
    
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

