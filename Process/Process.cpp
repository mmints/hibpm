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
                    auto *state = new Participation(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case AT_MOST_ONE: {
                    auto *state = new AtMostOne(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case INIT: {
                    auto *state = new Init(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case END: {
                    auto *state = new End(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }

                    // Binary
                case RESPONDED_EXISTENCE: {
                    auto *state = new RespondedExistence(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case RESPONSE: {
                    auto *state = new Response(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case ALTERNATED_RESPONSE: {
                    auto *state = new AlternatedResponse(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case CHAIN_RESPONSE: {
                    auto *state = new ChainResponse(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case PRECEDENCE: {
                    auto *state = new Precedence(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case ALTERNATED_PRECEDENCE: {
                    auto *state = new AlternatedPrecedence(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case CHAIN_PRECEDENCE: {
                    auto *state = new ChainPrecedence(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case CO_EXISTENCE: {
                    auto *state = new CoExistence(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case SUCCESSION: {
                    auto *state = new Succession(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case ALTERNATED_SUCCESSION: {
                    auto *state = new AlternateSuccession(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case CHAIN_SUCCESSION: {
                    auto *state = new ChainSuccession(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case NOT_CHAIN_SUCCESSION: {
                    auto *state = new NotChainSuccession(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case NOT_SUCCESSION: {
                    auto *state = new NotSuccession(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case NOT_CO_EXISTENCE: {
                    auto *state = new NotCoExistence(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
            }
        }
    }

    std::vector<State*> Process::getStates() {
        return m_states;
    }
}
