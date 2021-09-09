#pragma once

#include <stdio.h>
#include "Automaton/Automaton.hpp"

namespace hibpm
{

    class Process
    {
    public:
        virtual void initialiseAutomaton(int SigmaS, int eventLetter);

    private:
        Automaton m_automaton;
    };


// Unary Processes

    class ProcessInit : public Process
    {
        void initialiseAutomaton(int SigmaS, int eventLetter) {

            // only transition (0)---|evLetter|--->(1)
            m_automaton.addTransition(0, 1, eventLetter);
            // transition (1)---|Sigma|--->(1)
            for (int a = 0; a < SigmaS; a++) {
                m_automaton.addTransition(1, 1, a);
            }

            // only final state is 0
            m_automaton.addFinal(0);
        }

    };

    class ProcessEnd : public Process
    {
        void initialiseAutomaton(int SigmaS, int eventLetter) {
            for (int a = 0; a < SigmaS; a++) {
                if (a != eventLetter) {
                    m_automaton.addTransition(0, 0, a);
                    m_automaton.addTransition(1, 0, a);
                }
            }

            m_automaton.addTransition(0, 1, eventLetter);
            m_automaton.addTransition(1, 1, eventLetter);

            m_automaton.addFinal(1);
        }

    };

    class ProcessMostOne : public Process
    {
        void initialiseAutomaton(int SigmaS, int eventLetter) {

            for (int a = 0; a < SigmaS; a++) {
                if (a != eventLetter) {
                    m_automaton.addTransition(0, 0, a);
                    m_automaton.addTransition(1, 1, a);
                }
            }

            //only transition (0)---|evLetter|--->(1)
            m_automaton.addTransition(0, 1, eventLetter);
            //transition (1)---|Sigma|--->(1)

            m_automaton.addFinal(0);
            m_automaton.addFinal(1);
        }
    };
}