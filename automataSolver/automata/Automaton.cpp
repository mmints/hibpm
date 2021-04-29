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

	vector<vector<unsigned long> > mat(sizeA1,
			vector<unsigned long>(sizeA2, -1));

	mat[0][0] = 0;

	struct cell {
		pair<int, int> nState;
		vector<int> transitions;

		void init(int x, int y, unsigned long vsize) {
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

	for (list<cell*>::iterator it = nStates.begin(); it != nStates.end();
			it++) {

		int cx = (*it)->nState.first, cy = (*it)->nState.second;
//        
		for (int a = 0; a < sigmaS; a++) {
//
			int x1 = a1->transitionsTo->at(cx)[a], x2 = a2->transitionsTo->at(
					cy)[a];
//            //TODO consider case that X1,X2 = -1
//            
			if (x1 != -1 && x2 != -1) {

				if (mat[x1][x2] == -1) {
					controlStates++;
					mat[x1][x2] = controlStates;
					c = new cell;
					c->init(x1, x2, sigmaS);
					nStates.push_back(c);
				}
////
				unsigned long pairDecod = mat[x1][x2];
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

		cout << x << ":" << y << "\n";
		int state = mat[x][y];
//
		cout << state << "\n";
		if (a1->areFinalStates[(*it)->nState.first]
				&& a2->areFinalStates[(*it)->nState.second]
				&& !result->areFinalStates[state]) {
			result->addFinal(state);
		}

		for (int a = 0; a < sigmaS; a++) {
			cout << a << "--" << sigmaS << "\n";
			cout << (*it)->transitions.size() << "------\n";
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

					//TODO continue from here

				}
			}
			//TODO working here

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
////
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

	for (int i = 0; i < this->transitionsTo->size(); i++) {

		int nSymbols = this->transitionsTo->at(i).size();
		for (int j = 0; j < nSymbols; j++) {

			std::cout << this->transitionsTo->at(i)[j] << " | ";

		}
		std::cout << "\n";

	}
}

