#include "Process.hpp"

namespace hibpm
{
    Process::Process(hibpm::Declare &declare_kb) : m_declare_kb(declare_kb){
        createAllStates();
    }

    void Process::createAllStates() {
        size_t sigma_size = m_declare_kb.getEvents().size();
        for (Rule &rule : m_declare_kb.getRules()) {
            switch (rule.type)
            {
                // Unary
                case PARTICIPATION: {
                    Participation state{rule, sigma_size};
                    m_states.push_back(&state);
                    break;
                }
                case AT_MOST_ONE: {
                    AtMostOne state{rule, sigma_size};
                    m_states.push_back(&state);
                    break;
                }
                case INIT: {
                    Init state{rule, sigma_size};
                    m_states.push_back(&state);
                    break;
                }
                case END: {
                    End state{rule, sigma_size};
                    m_states.push_back(&state);
                    break;
                }

                    // Binary
                case RESPONDED_EXISTENCE: {
                    RespondedExistence state{rule, sigma_size};
                    m_states.push_back(&state);
                    break;
                }
                case RESPONSE: {
                    Response state{rule, sigma_size};
                    m_states.push_back(&state);
                    break;
                }
                case ALTERNATED_RESPONSE: {
                    AlternatedResponse state{rule, sigma_size};
                    m_states.push_back(&state);
                    break;
                }
                case CHAIN_RESPONSE: {
                    ChainResponse state{rule, sigma_size};
                    m_states.push_back(&state);
                    break;
                }
                case PRECEDENCE: {
                    Precedence state{rule, sigma_size};
                    m_states.push_back(&state);
                    break;
                }
                case ALTERNATED_PRECEDENCE: {
                    AlternatedPrecedence state{rule, sigma_size};
                    m_states.push_back(&state);
                    break;
                }
                case CHAIN_PRECEDENCE: {
                    ChainPrecedence state{rule, sigma_size};
                    m_states.push_back(&state);
                    break;
                }
                case CO_EXISTENCE: {
                    CoExistence state{rule, sigma_size};
                    m_states.push_back(&state);
                    break;
                }
                case SUCCESSION: {
                    Succession state{rule, sigma_size};
                    m_states.push_back(&state);
                    break;
                }
                case ALTERNATED_SUCCESSION: {
                    AlternateSuccession state{rule, sigma_size};
                    m_states.push_back(&state);
                    break;
                }
                case CHAIN_SUCCESSION: {
                    ChainSuccession state{rule, sigma_size};
                    m_states.push_back(&state);
                    break;
                }
                case NOT_CHAIN_SUCCESSION: {
                    NotChainSuccession state{rule, sigma_size};
                    m_states.push_back(&state);
                    break;
                }
                case NOT_SUCCESSION: {
                    NotSuccession state{rule, sigma_size};
                    m_states.push_back(&state);
                    break;
                }
                case NOT_CO_EXISTENCE: {
                    NotCoExistence state{rule, sigma_size};
                    m_states.push_back(&state);
                    break;
                }
            }
        }
    }

    std::vector<State*> Process::getStates() {
        return m_states;
    }
}
