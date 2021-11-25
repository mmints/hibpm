//
// Created by Jandson on 12.11.21.
//

#include "AbstractAutomaton.hpp"

namespace hibpm {

    StateInterface *ConcreteState::nextState(int symbol) {

        int targetState = this->automaton->automaton->transitionsTo[this->stateNum][symbol];

        if (targetState >= 0){
            return this->automaton->getState(targetState);
        }

        return nullptr;
    }

    ConcreteState::ConcreteState(ConcreteAutomaton *automaton, int numState) {
        this->automaton = automaton;
        this->stateNum = numState;
        if (numState > -1){
            this->isFinalState = this->automaton->automaton->areFinalStates[this->stateNum];
        }

    }

    list<int> ConcreteState::listRepresentation() {
        return list<int>(1,this->stateNum);
    }

    bool ConcreteState::isFinal() {
        if (this->stateNum > -1){
            return this->automaton->automaton->areFinalStates[this->stateNum];
        }
        return false;
    }


    ConcreteAutomaton::ConcreteAutomaton(Automaton *automaton):
        states(automaton->numSt,ConcreteState(this,-1)) {
        this->automaton = automaton;
        for (int i = 0; i < automaton->numSt; ++i) {
            this->states[i] = ConcreteState(this, i);
        }

        this->initialState = &(this->states[0]);
    }

    ConcreteState *ConcreteAutomaton::getState(int num) {
        if (num < 0 || num > this->states.size()){
            return nullptr;
        }

        return &(this->states[num]);
    }

    StateInterface *ConcreteAutomaton::nextStates(StateInterface *originState, int symbol) {

        return originState->nextState(symbol);

    }

    StateInterface *ConcreteAutomaton::getInitialState() {
        return this->initialState;
    }

    int ConcreteAutomaton::getAlphabetSize() {
        return this->automaton->sigSize;
    }

    StateInterface *ConcreteAutomaton::insertState(StateInterface *state) {
        ConcreteState *cs = dynamic_cast<ConcreteState*> (state);
        return &this->states[cs->stateNum];

    }


    StateInterface *ComposedAutomaton::nextStates(StateInterface *originState, int symbol) {

        //TODO

        return nullptr;
    }

    ComposedAutomaton::ComposedAutomaton(AbstractAutomaton *automatonRight,AbstractAutomaton *automatonLeft):
        initialState(this, automatonRight->getAlphabetSize(),
                     automatonLeft->getInitialState(), automatonRight->getInitialState()) {

        this->alphaSize = automatonRight->getAlphabetSize();
        this->automatonRight = automatonRight;
        this->automatonLeft = automatonLeft;
        pair<list<int>, ComposedState*> pair;
        pair.first = this->initialState.listRepresentation();
        pair.second = &this->initialState;
        this->computedSets.insert(pair);

    }



    StateInterface *ComposedAutomaton::getInitialState() {
        return &this->initialState;
    }

    ComposedState* ComposedAutomaton::insertComposedState(ComposedState *state) {

        pair<list<int>,ComposedState*> p(state->listRepresentation(), state);

        pair<set<pair<list<int>,ComposedState*>,compLists>::iterator, bool> res = this->computedSets.insert(p);

        if (state == res.first->second){
            this->createdPointers.push_back(state);
        }

        return  state; //res.first->second;
    }

    int ComposedAutomaton::getAlphabetSize() {
        return this->alphaSize;
    }

    StateInterface *ComposedAutomaton::insertState(StateInterface *state) {

        ComposedState *cs = dynamic_cast<ComposedState*> (state);
        return this->insertComposedState(cs);
//        pair<list<int>,ComposedState*> p(state->listRepresentation(),cs);
//
//        pair<set<pair<list<int>,ComposedState*>>::iterator ,bool> res = this->computedSets.insert(p);
//
//        return res.first->second;
    }

    ComposedState::ComposedState(ComposedAutomaton *automaton, int alphabetS, StateInterface *stateRight, StateInterface *stateLeft) {

        this->automaton = automaton;
        this->stateRight = stateRight;
        this->stateLeft = stateLeft;
        this->alphabetSize = alphabetS;

        this->representationList.resize(0);

        for (int i : stateLeft->listRepresentation()) {
            this->representationList.push_back(i);
        }

        for (int i : stateRight->listRepresentation()) {
            this->representationList.push_back(i);
        }

        this->toState.resize(this->alphabetSize, nullptr);
        this->alreadyCalculates.resize(this->alphabetSize, false);
        this->isFinalState = this->stateRight->isFinal() && this->stateLeft->isFinal();

    }

    StateInterface *ComposedState::nextState(int symbol) {

        if (this->toState[symbol] != nullptr){
            return this->toState[symbol];
        }else if(this->alreadyCalculates[symbol]){
            return nullptr;
        }

        this->alreadyCalculates[symbol] = true;

        StateInterface *stRighRes = this->stateRight->nextState(symbol);
        StateInterface *stLeftRes = this->stateLeft->nextState(symbol);


        if (stLeftRes != nullptr && stRighRes != nullptr){
            ComposedState *cs = new ComposedState(this->automaton, this->alphabetSize, stRighRes, stLeftRes);
            this->automaton->insertState(cs);
            this->toState[symbol] = cs;

            return cs;
            //TODO delete pointers in the destructor
        }



        return nullptr;
    }

     list<int> ComposedState::listRepresentation() {
        return this->representationList;
    }

    bool ComposedState::isFinal() {
        return this->isFinalState;
    }


    bool AbstractAutomaton::isEmpty() {

        list<StateInterface*> stackStates;
        stackStates.push_back(this->getInitialState());

        for (StateInterface *state : stackStates) {

            for (int i = 0; i < this->getAlphabetSize(); ++i) {

                StateInterface *nState = state->nextState(i);

                if (nState != nullptr){
                    if (nState->isFinal()) {
                        return false;
                    }
                    StateInterface *insRes = this->insertState(nState);

                    if (nState == insRes){
                        stackStates.push_back(nState);
                    }

                }
            }

        }

        return true;
    }
}