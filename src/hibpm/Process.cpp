#include "Process.hpp"

#include <memory>

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
                    std::shared_ptr<Participation> state
                            = std::make_shared<Participation>(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case AT_MOST_ONE: {
                    std::shared_ptr<AtMostOne> state
                            = std::make_shared<AtMostOne>(rule, sigma_size);

                    m_states.push_back(state);
                    break;
                }
                case INIT: {
                    std::shared_ptr<Init> state
                            = std::make_shared<Init>(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case END: {
                    std::shared_ptr<End> state
                            = std::make_shared<End>(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }

                    // Binary
                case RESPONDED_EXISTENCE: {
                    std::shared_ptr<RespondedExistence> state
                        = std::make_shared<RespondedExistence>(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case RESPONSE: {
                    std::shared_ptr<Response> state
                            = std::make_shared<Response>(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case ALTERNATED_RESPONSE: {
                    std::shared_ptr<AlternatedResponse> state
                            = std::make_shared<AlternatedResponse>(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case CHAIN_RESPONSE: {
                    std::shared_ptr<ChainResponse> state
                            = std::make_shared<ChainResponse>(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case PRECEDENCE: {
                    std::shared_ptr<Precedence> state
                            = std::make_shared<Precedence>(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case ALTERNATED_PRECEDENCE: {
                    std::shared_ptr<AlternatedPrecedence> state
                            = std::make_shared<AlternatedPrecedence>(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case CHAIN_PRECEDENCE: {
                    std::shared_ptr<ChainPrecedence> state
                            = std::make_shared<ChainPrecedence>(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case CO_EXISTENCE: {
                    std::shared_ptr<CoExistence> state
                            = std::make_shared<CoExistence>(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case SUCCESSION: {
                    std::shared_ptr<Succession> state
                            = std::make_shared<Succession>(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case ALTERNATED_SUCCESSION: {
                    std::shared_ptr<AlternateSuccession> state
                            = std::make_shared<AlternateSuccession>(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case CHAIN_SUCCESSION: {
                    std::shared_ptr<ChainSuccession> state
                            = std::make_shared<ChainSuccession>(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case NOT_CHAIN_SUCCESSION: {
                    std::shared_ptr<NotChainSuccession> state
                            = std::make_shared<NotChainSuccession>(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case NOT_SUCCESSION: {
                    std::shared_ptr<NotSuccession> state
                            = std::make_shared<NotSuccession>(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
                case NOT_CO_EXISTENCE: {
                    std::shared_ptr<NotCoExistence> state
                            = std::make_shared<NotCoExistence>(rule, sigma_size);
                    m_states.push_back(state);
                    break;
                }
            }
        }
    }

    std::vector<std::shared_ptr<State>> Process::getStates() {
        return m_states;
    }

    std::vector<Event> Process::getEvents() {
        return this->m_declare_kb.getEvents();
    }

    list<list<shared_ptr<State>>> Process::spliSytantic(){

        vector<list<shared_ptr<State>>*> res(this->getEvents().size(),nullptr);




    }

}
