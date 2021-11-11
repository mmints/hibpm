#pragma once

#include <memory>

#include "Automaton/Automaton.hpp"
#include "Declare/Declare.hpp"
#include "State.hpp"
#include "Unary.hpp"
#include "Binary.hpp"

namespace hibpm
{
    /**
     * The Process Class represents the full chain of rules in a given Declare Object.
     * A Process is created by handing over a parsed Declare Object to the constructor.
     * The simple Rule and Event Structs from the Declare Object are then transformed
     * into State Classes with more advanced functionality.
     *
     * Use this Class as main container for handling operations on the Declare Process.
     */
    class Process
    {
    public:
        /**
         * Creates States for all Rules from the given Declare Object and store them
         * in a vector of std::shared_ptr<State>.
         *
         * @param declare_kb: Knowledge Base from the Parser
         */
        explicit Process(Declare &declare_kb);

        /**
         * Hand over a Vector of all States of any RuleType.
         * @return std::shared_ptr<State>
         */
        std::vector<std::shared_ptr<State>> getStates();

        /**
         * Hand over the alphabet of used Events/Atoms.
         * @return std::vector<Event>
         */
        std::vector<Event> getEvents();

        // What is this function?
        list<list<shared_ptr<State>>> spliSytantic();

    private:
        Declare m_declare_kb;
        std::vector<std::shared_ptr<State>> m_states; // TODO: Change Vector to List for quicker filling

        /**
         * Creates States for all Rules form the Declare KB and store
         * Events in a separated Vector.
         */
        void createAllStates();


    };
}

