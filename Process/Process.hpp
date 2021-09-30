#pragma once

#include "Automaton/Automaton.hpp"
#include "Declare/Declare.hpp"
#include "State.hpp"
#include "Unary.hpp"
#include "Binary.hpp"

namespace hibpm
{
    class Process
    {
    public:
        explicit Process(Declare &declare_kb);
        std::vector<State*> getStates();

    private:
        Declare m_declare_kb;
        std::vector<State*> m_states {};

        void createAllStates();
    };
}

