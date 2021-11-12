//
// Created by Jandson on 12.11.21.
//

#pragma once
#include "Automaton.hpp"
#include <set>

namespace hibpm {



    class ConcreteState;
    class StateInterface;
    class ComposedState;
    class ComposedAutomaton;

    class AbstractAutomaton {



    public:
        virtual StateInterface *nextStates(StateInterface *originState, int symbol) = 0;
        virtual StateInterface *getInitialState() = 0;
       // virtual StateInterface *insertState(StateInterface *state) = 0;

        bool isEmpty();
        virtual int getAlphabetSize() = 0;
        virtual StateInterface* insertState(StateInterface *state) = 0;



    };

    class ConcreteAutomaton: public AbstractAutomaton{
    protected:

        vector<ConcreteState> states;
        StateInterface* initialState;

    public:
        Automaton *automaton;
        explicit ConcreteAutomaton(Automaton *automaton);
        ConcreteState* getState(int num);

        StateInterface *nextStates(StateInterface *originState, int symbol) override;
        StateInterface *getInitialState() override;

        int getAlphabetSize() override;

        StateInterface *insertState(StateInterface *state) override;

        //StateInterface *insertState(StateInterface *state) override;


    };

    class StateInterface{

    public:
        virtual StateInterface* nextState(int symbol) =0;
        virtual list<int> listRepresentation() = 0;

        virtual bool isFinal() {return false;};
    };

    class ConcreteState: public  StateInterface{
    private:
        ConcreteAutomaton *automaton;
        bool isFinalState;

    public:
        //ConcreteState(){};
        ConcreteState( ConcreteAutomaton *automaton, int stateNum);
        StateInterface *nextState(int symbol) override;

        list<int> listRepresentation() override;
        int stateNum;

        bool isFinal() override;

    };

    class ComposedState: public  StateInterface{

    private:
        ComposedAutomaton *automaton;
        StateInterface *stateRight, *stateLeft;
        list<int> representationList;
        int alphabetSize;
        bool isFinalState;

    public:
        ComposedState(ComposedAutomaton *automaton, int alphabetS, StateInterface *stateRight, StateInterface *stateLeft);
        StateInterface *nextState(int symbol) override;
        list<int> listRepresentation() override;
        vector<StateInterface*> toState;
        vector<bool> alreadyCalculates;

        bool isFinal() override;


    };

    class ComposedAutomaton: public AbstractAutomaton{
    protected:

        struct compLists {
            bool operator() ( const pair<list<int>,ComposedState*> &l1, const pair<list<int>,ComposedState*> &l2) const {

                list<int>::const_iterator  it1 = l1.first.begin(), it2 = l2.first.begin();

                for (; it1 != l1.first.end(); it1++, it2++) {
                    if (*it1 < *it2){
                        return true;
                    }
                }
                return false;
            }

        };
    private:
        AbstractAutomaton *automatonRight, *automatonLeft;
        ComposedState initialState;
        set<pair<list<int>,ComposedState*>,compLists> computedSets;
        int alphaSize;
        list<ComposedState*> createdPointers;

    public:
        ComposedAutomaton(AbstractAutomaton *automatonRight, AbstractAutomaton *automatonLeft);
        StateInterface *nextStates(StateInterface *originState, int symbol) override;
        StateInterface *getInitialState() override;

        int getAlphabetSize() override;

        StateInterface *insertState(StateInterface *state) override;
        ComposedState  *insertComposedState(ComposedState *state);


    };

}

