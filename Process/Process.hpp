#pragma once

#include <memory>

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
        std::vector<std::shared_ptr<State>> getStates();
        std::vector<Event> getEvents();
        list<list<shared_ptr<State>>> spliSytantic();

    private:
        Declare m_declare_kb;
        std::vector<std::shared_ptr<State>> m_states;

        void createAllStates();


    };
}

