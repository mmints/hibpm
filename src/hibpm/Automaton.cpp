/**
 * @author:  Dr. Jandson Santos Ribeiro Santos
 * @email: jandson.ribeiro@fernuni-hagen.de
 */

#include "Automaton.hpp"
#include <math.h>

namespace hibpm {

Automaton::Automaton(int numState, int sigmaSize) {

  this->sigSize = sigmaSize;
  this->numSt = numState;

  this->transitionsTo.resize(numState); // new vector<vector<int> >(numState);
  this->incoming.resize(
      numState); // = new vector<vector<list<int> > >(numState);

  for (int i = 0; i < numState; i++) {
    this->transitionsTo.at(i).resize(sigmaSize, -1);
    this->incoming.at(i).resize(sigmaSize);
  }

  this->areFinalStates.resize(numState, false);
}

Automaton::Automaton(int numStates, int sigmaSize, list<int> &finals) {

  Automaton(numStates, sigmaSize);

  for (list<int>::iterator it = finals.begin(); it != finals.end(); it++) {
    this->addFinal(*it);
  }

  //        this->finalStates.insert(this->finalStates.end(), 0);
}

void Automaton::addTransition(int stateFrom, int stateTo, int viaSymbol) {

  this->transitionsTo.at(stateFrom)[viaSymbol] = stateTo;

  if (stateTo >= 0) {
    this->incoming.at(stateTo)[viaSymbol].push_back(stateFrom);
  }
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
    return;
  }

  cout << "Sigma Size: " << this->sigSize << endl;
  cout << "Number of States: " << this->numSt << endl;

  for (int i = 0; i < this->transitionsTo.size(); i++) {

    int nSymbols = this->transitionsTo.at(i).size();
    for (int j = 0; j < nSymbols; j++) {

      std::cout << this->transitionsTo.at(i)[j] << " | ";
    }
    std::cout << "\n" << endl;
  }
}

Automaton Automaton::product(Automaton *a1, Automaton *a2) {
  if (a1->numSt == 0) {
    return *a1;
  } else if (a2->numSt == 0) {
    return *a2;
  }

  vector<vector<cellMat>> matrix(a1->numSt);
  // vector<vector<list<pair<int,int>>>> incoming(a1->numSt);

  // Initialise matrix
  for (int i = 0; i < a1->numSt; ++i) {
    matrix.at(i).resize(a2->numSt, cellMat(a1->sigSize));
    // incoming.at(i).resize(a2->numSt);
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

      int sx = a1->transitionsTo.at(it->first).at(a);
      int sy = a2->transitionsTo.at(it->second).at(a);

      if (sx >= 0 && sy >= 0) {
        matrix.at(sx).at(sy).incoming.push_back(
            pair<int, int>(it->first, it->second));
        // incoming.at(sx).at(sy).
        // std::cout << matrix.at(sx).at(sy).incoming.size() << std::endl;
        // std::cout << it->first << ":" << it->second << std::endl;
        // std::cout << ">>>>>> " << sx << ":" << sy << std::endl;
        if (!matrix.at(sx).at(sy).stacked) {
          matrix.at(sx).at(sy).stacked = true;
          visitedStack.push_back(pair<int, int>(sx, sy));
        }
      }
    }
  }

  // removing useless states (that is, those who do not reach final states)

  visitedStack = this->removeUselessStates(finalCandidates, matrix);

  //        list<pair<int,int>> usefullStates =
  //        this->removeUselessStates(finalCandidates,matrix);
  //
  //        for (list<pair<int,int>>::iterator it = visitedStack.begin(); it !=
  //        visitedStack.end(); it++){
  //            if (!this->isIn(*it,usefullStates)){
  //                matrix.at(it->first).at(it->second).stacked = false;
  //                visitedStack.erase(it);
  //            }
  //        }

  // encoding to generate new automata prod

  int lastN = 0;

  // std::cout << visitedStack.front().first << ", " <<
  // visitedStack.front().second << std::endl;

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
        res.addTransition(matrix.at(it->first).at(it->second).mappedNum,
                          resDest, a);
      }
    }
  }

  for (list<pair<int, int>>::iterator it = finalCandidates.begin();
       it != finalCandidates.end(); it++) {

    res.addFinal(matrix.at(it->first).at(it->second).mappedNum);
  }

  return res;
}

bool Automaton::isIn(pair<int, int> p, list<pair<int, int>> l1) {

  for (pair<int, int> pl : l1) {
    if (pl.first == p.first && pl.second == p.second)
      return true;
  }

  return false;
}

bool Automaton::isEmptyMinusEmptyString() {
  // We assume that the automaton is strongly connected from initial state 0
  if (!this->finalStates.empty()) {

    if (this->finalStates.size() > 1 || !this->areFinalStates[0]) {
      for (int i = 0; i < this->transitionsTo.at(0).size(); ++i) {
        if (this->transitionsTo.at(0).at(i) != -1)
          return false;
      }
      return true;
    } else {
      return this->incoming.at(0).empty();
    }
  }

  return true;
}

list<pair<int, int>>
Automaton::removeUselessStates(list<pair<int, int>> &finalStates,
                               vector<vector<cellMat>> &matRef) {

  list<pair<int, int>> res(finalStates);
  vector<vector<bool>> usefullMat(matRef.size(),
                                  vector<bool>(matRef.at(0).size(), false));

  for (list<pair<int, int>>::iterator it = res.begin(); it != res.end(); it++) {
    usefullMat.at(it->first).at(it->second) = true;
    // std::cout << "finals :" << it->first << "," << it->second << std::endl;
  }

  for (list<pair<int, int>>::iterator it = res.begin(); it != res.end(); it++) {

    // std::cout << "incoming of " << it->first << "," << it->second <<
    // std::endl; usefullMat.at(it->first).at(it->second) = true;
    for (list<pair<int, int>>::iterator itin =
             matRef.at(it->first).at(it->second).incoming.begin();
         itin != matRef.at(it->first).at(it->second).incoming.end(); itin++) {

      // std::cout << itin->first << "," << itin->second << std::endl;

      if (!usefullMat.at(itin->first).at(itin->second)) {
        if (itin->first == 0 && itin->second == 0) {
          res.push_front(pair<int, int>(itin->first, itin->second));
        } else {
          res.push_back(pair<int, int>(itin->first, itin->second));
        }
        usefullMat.at(itin->first).at(itin->second) = true;
      }
    }
  }

  // std::cout << "------- front ---- (" << res.front().first << " , " <<
  // res.front().second << ")" << std::endl;

  return res;
}

void Automaton::interComlement(set<int> A, set<int> B, set<int> &complement,
                               set<int> &intersect) {

  for (int x : A) {
    if (B.find(x) != B.end()) {
      intersect.insert(x);
    } else {
      complement.insert(x);
    }
  }
}

Automaton Automaton::reduceHopcrofHard() {

  struct hopStruct {
    unsigned int id;
    set<int> elements;
    hopStruct(unsigned int x, list<int> elementsY) {
      id = x;
      elements.insert(elementsY.begin(), elementsY.end());
    }
    hopStruct(unsigned int x, set<int> elementsY) {
      id = x;
      elements.insert(elementsY.begin(), elementsY.end());
    }
    hopStruct(unsigned int x) { id = x; }
  };

  if (this->finalStates.size() == 0) {
    return Automaton(1, this->sigSize);
  }

  list<hopStruct> partSet, wSet;
  vector<int> equivClassIds(this->numSt);

  hopStruct hopNonFinals(1);
  hopStruct hopFinals(0, this->finalStates);

  for (int i = 0; i < this->numSt; ++i) {
    if (!this->areFinalStates[i]) {
      hopNonFinals.elements.insert(i);
      // equivClassIds[i] = 1; //non-Final ID class
    }
    //            else{
    //                equivClassIds[i] = 0; //final ID classes
    //            }
  }

  partSet.push_back(hopFinals);
  wSet.push_back(hopFinals);

  if (!hopNonFinals.elements.empty()) {
    partSet.push_back(hopNonFinals);
  }

  while (!wSet.empty()) {
    hopStruct setA = wSet.front();
    wSet.pop_front();

    for (int a = 0; a < this->sigSize; ++a) {
      set<int> incidence;
      for (int x : setA.elements) {
        incidence.insert(this->incoming[x][a].begin(),
                         this->incoming[x][a].end());
      }

      for (list<hopStruct>::iterator itP = partSet.begin();
           itP != partSet.end();) {
        set<int> intersect, complement;

        bool removed = false;
        this->interComlement(itP->elements, incidence, complement, intersect);

        if (!intersect.empty() && !complement.empty()) {
          bool inW = false;
          hopStruct inY(itP->id, intersect), cY(partSet.size(), complement);

          for (list<hopStruct>::iterator itW = wSet.begin(); itW != wSet.end();
               itW++) {
            if (itW->id == itP->id) {
              inW = true;
              wSet.erase(itW);
              wSet.push_back(inY);
              wSet.push_back(cY);
              break;
            }
          }
          list<hopStruct>::iterator itAux = itP;
          itP++;
          removed = true;
          partSet.erase(itAux);
          partSet.push_back(inY);
          partSet.push_back(cY);
          if (!inW) {
            if (inY.elements.size() <= cY.elements.size()) {
              wSet.push_back(inY);
            } else {
              wSet.push_back(cY);
            }
          }
        }
        if (!removed) {
          itP++;
        }
      }
    }
  }

  //        for (list<hopStruct>::iterator it = partSet.begin() ; it !=
  //        partSet.end() ; it++) {
  //            if(it->elements.find(0) != it->elements.end()){
  //                hopStruct hop = *it;
  //                partSet.push_front(hop);
  //                partSet.erase(it);
  //                break;
  //            }
  //        }

  // start enconding

  int count = 1;
  for (list<hopStruct>::iterator it = partSet.begin(); it != partSet.end();
       it++) {
    if (it->elements.find(0) != it->elements.end()) {
      it->id = 0;
      for (int x : it->elements) {
        equivClassIds[x] = 0;
      }
    } else {
      it->id = count;
      for (int x : it->elements) {
        equivClassIds[x] = count;
      }
      count++;
    }
  }

  Automaton reducedAut = Automaton(partSet.size(), this->sigSize);

  for (hopStruct eq : partSet) {

    for (int a = 0; a < this->sigSize; ++a) {
      int equivState = *(eq.elements.begin());
      int targetTrans = this->transitionsTo.at(equivState).at(a);
      int equivTarget =
          (targetTrans == -1) ? -1 : equivClassIds.at(targetTrans);
      reducedAut.addTransition(eq.id, equivTarget, a);
      if (equivState != -1 && this->areFinalStates.at(equivState)) {
        reducedAut.addFinal(eq.id);
      }
    }
  }

  return reducedAut;
}

Automaton Automaton::reduceHopcrof() {

  struct equivClass {
    unsigned int id = 0;
    list<int> elements;
    equivClass(unsigned int nId) { this->id = nId; }
  };

  list<equivClass> equivClasses;
  vector<int> equivClassIds(this->numSt);

  if (this->finalStates.size() == 0) {
    return *this;
  }

  int finalId = (this->areFinalStates.at(0)) ? 0 : 1;

  equivClasses.push_back(equivClass(finalId));     // id for final
  equivClasses.push_back(equivClass(1 - finalId)); // id_c for non final

  for (int i = 0; i < this->numSt; ++i) {
    if (this->areFinalStates.at(i)) {
      equivClasses.front().elements.push_back(i);
      equivClassIds.at(i) = finalId;
    } else {
      equivClasses.back().elements.push_back(i);
      equivClassIds.at(i) = 1 - finalId;
    }
  }

  if (equivClasses.back().elements.empty()) {
    equivClasses.pop_back();
  }

  // starts equiv class computation

  for (list<equivClass>::iterator it = equivClasses.begin();
       it != equivClasses.end(); it++) {

    list<int>::iterator itS = it->elements.begin();
    int x = *itS;
    // itS++;
    equivClass auxEquivClass(equivClasses.size());

    for (++itS; itS != it->elements.end();) {

      bool itsModified = false;

      for (int a = 0; a < this->sigSize; ++a) {
        int stateFirstTo = transitionsTo.at(x).at(a);
        int stateSecondTo = transitionsTo.at(*itS).at(a);

        if (stateFirstTo != stateSecondTo) { // id different then we check, if
                                             // equal then same equiv for now
          if (stateFirstTo == -1 ||
              stateSecondTo == -1) { // the we should separate
            auxEquivClass.elements.push_back(*itS);
            // it->elements.erase(itS);
            equivClassIds.at(*itS) = auxEquivClass.id;
            list<int>::iterator itAux = itS;
            itS++;
            // int sizeS = it->elements.size();
            it->elements.erase(itAux);
            //                            if (sizeS <= it->elements.size()){
            //                                std::cout << "########## Problem
            //                                here" << std::endl;
            //                            }
            itsModified = true;
            break;
          } else if (equivClassIds.at(stateFirstTo) !=
                     equivClassIds.at(stateSecondTo)) {
            auxEquivClass.elements.push_back(*itS);
            equivClassIds.at(*itS) = auxEquivClass.id;
            list<int>::iterator itAux = itS;
            itS++;
            // int sizeS = it->elements.size();
            it->elements.erase(itAux);
            //                            if (sizeS <= it->elements.size()){
            //                                std::cout << "########## Problem
            //                                here" << std::endl;
            //                            }
            itsModified = true;
            // it->elements.erase(itS);
            break;
          }
        }
      }

      if (!itsModified) {
        itS++;
      }
    }

    if (!auxEquivClass.elements.empty()) {
      equivClasses.push_back(auxEquivClass);
    }

    // std::cout << it->id << std::endl;
  }

  if (equivClasses.size() == this->numSt) {
    return *this;
  }

  Automaton reducedAut = Automaton(equivClasses.size(), this->sigSize);

  for (equivClass eq : equivClasses) {

    for (int a = 0; a < this->sigSize; ++a) {
      int equivState = *(eq.elements.begin());
      int targetTrans = this->transitionsTo.at(equivState).at(a);
      int equivTarget =
          (targetTrans == -1) ? -1 : equivClassIds.at(targetTrans);
      reducedAut.addTransition(eq.id, equivTarget, a);
      if (equivState != -1 && this->areFinalStates.at(equivState)) {
        reducedAut.addFinal(eq.id);
      }
    }
  }

  return reducedAut;
}

bool Automaton::lazyProducts(list<Automaton> automata) {

  struct TupleState {
    vector<int> values;

    TupleState(vector<int> tuple) { values = tuple; }
    bool isEqualTo(vector<int> v) {

      if (v.size() != values.size()) {
        return false;
      }

      for (int i = 0; i < v.size(); ++i) {
        if (v[i] != values[i]) {
          return false;
        }
      }

      return true;
    }

    bool isIn(list<TupleState> l) {

      for (TupleState t : l) {

        if (t.isEqualTo(values)) {
          return true;
        }
      }

      return false;
    }
  };

  // std::cout << std::endl;

  list<TupleState> stack;
  int numAutomata = automata.size();
  // int z = pow(4, numAutomata);
  list<int> visited;

  vector<int> vec(numAutomata, 0);
  // visited.push_back(0);

  visited.push_back(0);
  stack.push_back(TupleState(vec));

  int sigSize = automata.front().sigSize;

  for (TupleState cState : stack) {
    for (int a = 0; a < sigSize; ++a) {
      int i = 0;
      vector<int> targState(numAutomata, 0);
      bool interrupted = false;
      bool isFinal = true;
      for (list<Automaton>::iterator it = automata.begin();
           it != automata.end(); it++, i++) {
        int locState = it->transitionsTo[cState.values[i]][a];
        if (locState == -1) {
          interrupted = true;
          break;
        } else {
          targState[i] = locState;
          isFinal = (isFinal && it->areFinalStates[locState]);
        }
      }

      if (!interrupted) {
        if (isFinal) {
          return true;
        }

        // unsigned int encod =targState[0];
        //                    for (int j = 1; j < numAutomata; ++j) {
        //                        encod += targState[j]*pow(10,j);
        //                    }
        // if(!isInList(visited, encod)){
        TupleState ts(targState);
        if (!ts.isIn(stack)) {
          // visited.push_back(encod);
          // stack.push_back(targState);
          stack.push_back(ts);
          // std::cout << "size stack:: " << stack.size() << std::endl;
        }
      }
    }
  }

  // std::cout << " >>>>>> Result is safe " << std::endl;
  return false;
}

bool Automaton::isInList(list<int> lists, int x) {
  for (int y : lists) {
    if (y == x) {
      return true;
    }
  }

  return false;
}

void Automaton::negate(int symbol) {

  for (int i = 0; i < this->numSt; ++i) {
    this->transitionsTo[i][symbol] = -1;
  }
}

void Automaton::negate(list<int> symbols) {
  for (int i : symbols) {
    this->negate(i);
  }
}

} // namespace hibpm
