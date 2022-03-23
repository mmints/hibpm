#include "DeclareKnowledgeBase.hpp"

namespace hibpm
{

    DeclareKnowledgeBase::DeclareKnowledgeBase(DeclareContext &declareContext)
    {
        m_sigma = declareContext.getEventData();
        m_sigmaSize = declareContext.getEventDataCount();
        initRuleSet(declareContext);
    }

    void DeclareKnowledgeBase::initRuleSet(DeclareContext &declareContext)
    {
        for (DeclareContext::RuleData &ruleData : declareContext.getRuleData()) {
            switch (ruleData.type)
            {
                // Unary
                case PARTICIPATION: {
                    std::shared_ptr<Participation> rule
                            = std::make_shared<Participation>(m_sigmaSize, ruleData.events.at(0));
                    m_RuleSet.push_back(rule);
                    break;
                }
                case AT_MOST_ONE: {
                    std::shared_ptr<AtMostOne> rule
                            = std::make_shared<AtMostOne>(m_sigmaSize, ruleData.events.at(0));

                    m_RuleSet.push_back(rule);
                    break;
                }
                case INIT: {
                    std::shared_ptr<Init> rule
                            = std::make_shared<Init>(m_sigmaSize, ruleData.events.at(0));
                    m_RuleSet.push_back(rule);
                    break;
                }
                case END: {
                    std::shared_ptr<End> rule
                            = std::make_shared<End>(m_sigmaSize, ruleData.events.at(0));
                    m_RuleSet.push_back(rule);
                    break;
                }

                    // Binary
                case RESPONDED_EXISTENCE: {
                    std::shared_ptr<RespondedExistence> rule
                            = std::make_shared<RespondedExistence>(m_sigmaSize, ruleData.events);
                    m_RuleSet.push_back(rule);
                    break;
                }
                case RESPONSE: {
                    std::shared_ptr<Response> rule
                            = std::make_shared<Response>(m_sigmaSize, ruleData.events);
                    m_RuleSet.push_back(rule);
                    break;
                }
                case ALTERNATED_RESPONSE: {
                    std::shared_ptr<AlternatedResponse> rule
                            = std::make_shared<AlternatedResponse>(m_sigmaSize, ruleData.events);
                    m_RuleSet.push_back(rule);
                    break;
                }
                case CHAIN_RESPONSE: {
                    std::shared_ptr<ChainResponse> rule
                            = std::make_shared<ChainResponse>(m_sigmaSize, ruleData.events);
                    m_RuleSet.push_back(rule);
                    break;
                }
                case PRECEDENCE: {
                    std::shared_ptr<Precedence> rule
                            = std::make_shared<Precedence>(m_sigmaSize, ruleData.events);
                    m_RuleSet.push_back(rule);
                    break;
                }
                case ALTERNATED_PRECEDENCE: {
                    std::shared_ptr<AlternatedPrecedence> rule
                            = std::make_shared<AlternatedPrecedence>(m_sigmaSize, ruleData.events);
                    m_RuleSet.push_back(rule);
                    break;
                }
                case CHAIN_PRECEDENCE: {
                    std::shared_ptr<ChainPrecedence> rule
                            = std::make_shared<ChainPrecedence>(m_sigmaSize, ruleData.events);
                    m_RuleSet.push_back(rule);
                    break;
                }
                case CO_EXISTENCE: {
                    std::shared_ptr<CoExistence> rule
                            = std::make_shared<CoExistence>(m_sigmaSize, ruleData.events);
                    m_RuleSet.push_back(rule);
                    break;
                }
                case SUCCESSION: {
                    std::shared_ptr<Succession> rule
                            = std::make_shared<Succession>(m_sigmaSize, ruleData.events);
                    m_RuleSet.push_back(rule);
                    break;
                }
                case ALTERNATED_SUCCESSION: {
                    std::shared_ptr<AlternateSuccession> rule
                            = std::make_shared<AlternateSuccession>(m_sigmaSize, ruleData.events);
                    m_RuleSet.push_back(rule);
                    break;
                }
                case CHAIN_SUCCESSION: {
                    std::shared_ptr<ChainSuccession> rule
                            = std::make_shared<ChainSuccession>(m_sigmaSize, ruleData.events);
                    m_RuleSet.push_back(rule);
                    break;
                }
                case NOT_CHAIN_SUCCESSION: {
                    std::shared_ptr<NotChainSuccession> rule
                            = std::make_shared<NotChainSuccession>(m_sigmaSize, ruleData.events);
                    m_RuleSet.push_back(rule);
                    break;
                }
                case NOT_SUCCESSION: {
                    std::shared_ptr<NotSuccession> rule
                            = std::make_shared<NotSuccession>(m_sigmaSize, ruleData.events);
                    m_RuleSet.push_back(rule);
                    break;
                }
                case NOT_CO_EXISTENCE: {
                    std::shared_ptr<NotCoExistence> rule
                            = std::make_shared<NotCoExistence>(m_sigmaSize, ruleData.events);
                    m_RuleSet.push_back(rule);
                    break;
                }
            }
        }
    }

    std::vector<std::shared_ptr<Constraint>> DeclareKnowledgeBase::getRuleSet() {
        return m_RuleSet;
    }

    std::vector<Event> DeclareKnowledgeBase::getSigma() {
        return m_sigma;
    }

    u_int64_t DeclareKnowledgeBase::getSigmaSize() {
        return m_sigmaSize;
    }
}