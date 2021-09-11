#include "Automaton.hpp"

namespace hibpm {

    Automaton::Automaton(int numState, int sigmaSize) {

        this->sigSize = sigmaSize;
        this->numSt = numState;

        this->transitionsTo.resize(numState); // new vector<vector<int> >(numState);
        this->incoming.resize(numState); // = new vector<vector<list<int> > >(numState);

        for (int i = 0; i < numState; i++) {
            this->transitionsTo.at(i).resize(sigmaSize, -1);
            this->incoming.at(i).resize(sigmaSize);
        }

        this->areFinalStates.resize(numState, false);

    }

    Automaton::Automaton(int numStates, int sigmaSize, list<int> *finals) {

        Automaton(numStates, sigmaSize);

        this->finalStates.insert(this->finalStates.end(), 0);
    }

    void Automaton::addTransition(int stateFrom, int stateTo, int viaSymbol) {

        this->transitionsTo.at(stateFrom)[viaSymbol] = stateTo;

        this->incoming.at(stateTo)[viaSymbol].push_back(stateFrom);

    }

    void Automaton::addFinal(int state) {

        if (!this->areFinalStates[state]) {
            this->finalStates.push_back(state);
            this->areFinalStates[state] = true;
        }
    }




    void Automaton::print() {

        if (this->transitionsTo.size() == 0) {
            cout << "empty automaton" << endl;
        }

        for (int i = 0; i < this->transitionsTo.size(); i++) {

            int nSymbols = this->transitionsTo.at(i).size();
            for (int j = 0; j < nSymbols; j++) {

                std::cout << this->transitionsTo.at(i)[j] << " | ";

            }
            std::cout << "\n";

        }
    }

    Automaton Automaton::product(Automaton *a1, Automaton *a2) {

        struct cellMat{
            bool stacked, mapped;
            unsigned int mappedNum;
            vector<pair<int,int>> sigmaTransition;
            cellMat(int sigmaS){
                mappedNum = -1;
                stacked = false;
                mappedNum = false;
                sigmaTransition.resize(sigmaS, pair<int,int>(-1,-1));
            }
        };

        vector<vector<cellMat>> matrix(a1->numSt);

        // Initialise matrix
        for (int i = 0; i < a1->numSt; ++i) {
            matrix.at(i).resize(a2->numSt, cellMat(a1->sigSize));
        }

        list<pair<int,int>> visitedStack(1, pair<int,int>(0,0));
        list<pair<int,int>> finalCandidates;

        matrix.at(0).at(0).stacked = true;

        for ( list<pair<int,int>>::iterator it = visitedStack.begin() ;
                it != visitedStack.end(); it++) {

            int sigS = a1->sigSize;

            if (a1->areFinalStates.at(it->first) && a2->areFinalStates.at(it->second)){
                finalCandidates.push_back(pair<int,int>(it->first,it->second));
            }

            for (int a = 0; a < sigS; ++a) {

                int sx= a1->transitionsTo.at(0).at(0);
                int sy = a2->transitionsTo.at(0).at(0);

                if (sx >= 0 && sy >= 0 && !matrix.at(sx).at(sy).stacked){
                    matrix.at(sx).at(sy).stacked = true;
                    visitedStack.push_back(pair<int,int>(sx,sy));
                }

            }

        }

        int lastN = 0;

        for (list<pair<int,int>>::iterator it = visitedStack.begin() ;
                it != visitedStack.end(); it++) {

            if (!matrix.at(it->first).at(it->second).mapped){
                matrix.at(it->first).at(it->second).mapped = true;
                matrix.at(it->first).at(it->second).mappedNum = lastN;
                lastN++;
            }

        }


        Automaton res(visitedStack.size(), a1->sigSize);

        for (list<pair<int,int>>::iterator it = visitedStack.begin() ;
             it != visitedStack.end(); it++) {

            for (int a = 0; a < a1->sigSize; ++a) {
                int desA1 = a1->transitionsTo.at(it->first).at(a);
                int desA2 = a2->transitionsTo.at(it->second).at(a);

                int resDest = -1;

                if (desA1 >= 0 && desA2 >= 0){
                    resDest = matrix.at(desA1).at(desA2).mappedNum;
                }

                res.addTransition(matrix.at(it->first).at(it->second).mappedNum,
                                 resDest,a );
            }
            
        }


        return res;
    }





}
