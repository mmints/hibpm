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

    Automaton::Automaton(int numStates, int sigmaSize, list<int> &finals) {

        Automaton(numStates, sigmaSize);

        for (list<int>::iterator it = finals.begin();
                it != finals.end(); it++) {
            this->addFinal(*it);
        }

//        this->finalStates.insert(this->finalStates.end(), 0);

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

        vector<vector<cellMat>> matrix(a1->numSt);
        //vector<vector<list<pair<int,int>>>> incoming(a1->numSt);

        // Initialise matrix
        for (int i = 0; i < a1->numSt; ++i) {
            matrix.at(i).resize(a2->numSt, cellMat(a1->sigSize));
            //incoming.at(i).resize(a2->numSt);
        }

        list<pair<int, int>> visitedStack(1, pair<int, int>(0, 0));
        list<pair<int, int>> finalCandidates;

        matrix.at(0).at(0).stacked = true;

        for (list<pair<int, int>>::iterator it = visitedStack.begin();
             it != visitedStack.end(); it++) {

            int sigS = a1->sigSize;

            if (a1->areFinalStates.at(it->first) && a2->areFinalStates.at(it->second)) {
                finalCandidates.push_back(pair<int, int>(it->first, it->second));
            }

            for (int a = 0; a < sigS; ++a) {

                int sx = a1->transitionsTo.at(0).at(0);
                int sy = a2->transitionsTo.at(0).at(0);

                if (sx >= 0 && sy >= 0){
                    matrix.at(sx).at(sy).incoming.push_back(pair<int,int>(it->first, it->second));
                    //incoming.at(sx).at(sy).
                }

                if (sx >= 0 && sy >= 0 && !matrix.at(sx).at(sy).stacked) {
                    matrix.at(sx).at(sy).stacked = true;
                    visitedStack.push_back(pair<int, int>(sx, sy));
                }

            }

        }

        //removing useless states (that is, those who do not reach final states)

        list<pair<int,int>> usefullStates = this->removeUselessStates(finalCandidates,matrix);

        for (list<pair<int,int>>::iterator it = visitedStack.begin(); it != visitedStack.end(); it++){
            if (!this->isIn(*it,usefullStates)){
                matrix.at(it->first).at(it->second).stacked = false;
                visitedStack.erase(it);
            }
        }

        //encoding to generate new automata prod

        int lastN = 0;

        for (list<pair<int, int>>::iterator it = visitedStack.begin();
             it != visitedStack.end(); it++) {

            if (!matrix.at(it->first).at(it->second).mapped) {
                matrix.at(it->first).at(it->second).mapped = true;
                matrix.at(it->first).at(it->second).mappedNum = lastN;
                lastN++;
            }

        }


        Automaton res(visitedStack.size(), a1->sigSize);

        for (list<pair<int, int>>::iterator it = visitedStack.begin();
             it != visitedStack.end(); it++) {

            for (int a = 0; a < a1->sigSize; ++a) {
                int desA1 = a1->transitionsTo.at(it->first).at(a);
                int desA2 = a2->transitionsTo.at(it->second).at(a);

                int resDest = -1;

                if (desA1 >= 0 && desA2 >= 0) {
                    resDest = matrix.at(desA1).at(desA2).mappedNum;
                }

                res.addTransition(matrix.at(it->first).at(it->second).mappedNum,
                                  resDest, a);
            }

        }

        for (list<pair<int, int>>::iterator it = finalCandidates.begin();
             it != finalCandidates.end(); it++) {

            res.addFinal(matrix.at(it->first).at(it->second).mappedNum);

        }


        return res;
    }

    bool Automaton::isIn(pair<int,int> p, list<pair<int,int>> l1){

        for (pair<int,int> pl: l1) {
            if (pl.first == p.first && pl.second == p.second)
                return true;
        }

        return false;
    }

    bool Automaton::isEmptyMinusEmptyString() {
        //We assume that the automaton is strongly connected from initial state 0
        if (!this->finalStates.empty()) {

            if (this->finalStates.size() > 1 || !this->areFinalStates[0]) {
                return false;
            } else {
                return this->incoming.at(0).empty();
            }

        }

        return true;
    }

    list<pair<int,int>> Automaton::removeUselessStates(list<pair<int, int>> &finalStates, vector<vector<cellMat>> &matRef) {

        list<pair<int,int>> res(finalStates);
        vector<vector<bool>> usefullMat(matRef.size(),vector<bool>(matRef.at(0).size(),false));

        for (list<pair<int,int>>::iterator it = res.begin() ; it != res.end(); it++) {
            usefullMat.at(it->first).at(it->second) = true;
        }

        for (list<pair<int,int>>::iterator it = res.begin() ; it != res.end(); it++) {

            //usefullMat.at(it->first).at(it->second) = true;
            for ( list<pair<int,int>>::iterator itin = matRef.at(it->first).at(it->second).incoming.begin();
                        itin != matRef.at(it->first).at(it->second).incoming.end(); itin++) {

                if (!usefullMat.at(itin->first).at(itin->second)){
                    res.push_back(pair<int,int>(it->first, it->second));
                    usefullMat.at(itin->first).at(itin->second) = true;
                }

            }


        }

        return res;

    }



//    void Automaton::removeUselessStates() {
//        // We assume that tge automaton has at least one valid final state
//
//        list<int> stacked(this->finalStates.size());
//        vector<bool> isStacked( this->numSt, false);
//
//        for (list<int>::iterator it = this->finalStates.begin();
//                it != this->finalStates.end(); it++) {
//            stacked.push_back(*it);
//            isStacked.at(*it) = true;
//        }
//
//        for (list<int>::iterator it = this->finalStates.begin();
//             it != this->finalStates.end(); it++) {
//
//            for (int a = 0; a < this->sigSize; ++a) {
//
//                list<int> incStates = this->incoming.at(*it).at(a);
//                for (list<int>::iterator itx = incStates.begin();
//                        itx != incStates.end(); itx++) {
//
//                    if (!isStacked.at(*itx)){
//                        isStacked.at(*itx) = true;
//                        stacked.push_back(*itx);
//                    }
//
//                }
//
//            }
//
//        }
//
//        // TODO reshape the atomaton removing the states tar are not in stacked;
//
//        vector<int> deductionMap(this->numSt,0);
//
//        if (stacked.size() == this->numSt){
//            return;
//        }
//
//
//
//    }


}
