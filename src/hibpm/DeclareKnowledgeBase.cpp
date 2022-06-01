/**
 * @author: Mark O. Mints
 * @email: mmints@uni-koblenz.de
 */

#include "DeclareKnowledgeBase.hpp"

namespace hibpm {
DeclareKnowledgeBase::DeclareKnowledgeBase(DeclareContext &declareContext) {
  m_sigma = declareContext.getEventData();
  m_sigmaSize = declareContext.getEventDataCount();
  initConstraintSet(declareContext);
}

void DeclareKnowledgeBase::initConstraintSet(DeclareContext &declareContext) {
  for (DeclareContext::ConstraintData &constraintData :
       declareContext.getConstraintData()) {
    switch (constraintData.type) {
    // Unary
    case PARTICIPATION: {
      std::shared_ptr<Participation> constraint =
          std::make_shared<Participation>(m_sigmaSize,
                                          constraintData.events.at(0));
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case AT_MOST_ONE: {
      std::shared_ptr<AtMostOne> constraint =
          std::make_shared<AtMostOne>(m_sigmaSize, constraintData.events.at(0));
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case AT_MOST_TWO: {
      std::shared_ptr<AtMostTwo> constraint =
          std::make_shared<AtMostTwo>(m_sigmaSize, constraintData.events.at(0));
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case AT_MOST_THREE: {
      std::shared_ptr<AtMostThree> constraint = std::make_shared<AtMostThree>(
          m_sigmaSize, constraintData.events.at(0));
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case AT_LEAST_ONE: {
      std::shared_ptr<AtLeastOne> constraint = std::make_shared<AtLeastOne>(
          m_sigmaSize, constraintData.events.at(0));
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case INIT: {
      std::shared_ptr<Init> constraint =
          std::make_shared<Init>(m_sigmaSize, constraintData.events.at(0));
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case END: {
      std::shared_ptr<End> constraint =
          std::make_shared<End>(m_sigmaSize, constraintData.events.at(0));
      m_ConstraintSet.push_back(constraint);
      break;
    }

      // Binary
    case RESPONDED_EXISTENCE: {
      std::shared_ptr<RespondedExistence> constraint =
          std::make_shared<RespondedExistence>(m_sigmaSize,
                                               constraintData.events);
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case RESPONSE: {
      std::shared_ptr<Response> constraint =
          std::make_shared<Response>(m_sigmaSize, constraintData.events);
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case ALTERNATED_RESPONSE: {
      std::shared_ptr<AlternatedResponse> constraint =
          std::make_shared<AlternatedResponse>(m_sigmaSize,
                                               constraintData.events);
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case CHAIN_RESPONSE: {
      std::shared_ptr<ChainResponse> constraint =
          std::make_shared<ChainResponse>(m_sigmaSize, constraintData.events);
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case PRECEDENCE: {
      std::shared_ptr<Precedence> constraint =
          std::make_shared<Precedence>(m_sigmaSize, constraintData.events);
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case ALTERNATED_PRECEDENCE: {
      std::shared_ptr<AlternatedPrecedence> constraint =
          std::make_shared<AlternatedPrecedence>(m_sigmaSize,
                                                 constraintData.events);
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case CHAIN_PRECEDENCE: {
      std::shared_ptr<ChainPrecedence> constraint =
          std::make_shared<ChainPrecedence>(m_sigmaSize, constraintData.events);
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case CO_EXISTENCE: {
      std::shared_ptr<CoExistence> constraint =
          std::make_shared<CoExistence>(m_sigmaSize, constraintData.events);
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case SUCCESSION: {
      std::shared_ptr<Succession> constraint =
          std::make_shared<Succession>(m_sigmaSize, constraintData.events);
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case ALTERNATED_SUCCESSION: {
      std::shared_ptr<AlternateSuccession> constraint =
          std::make_shared<AlternateSuccession>(m_sigmaSize,
                                                constraintData.events);
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case CHAIN_SUCCESSION: {
      std::shared_ptr<ChainSuccession> constraint =
          std::make_shared<ChainSuccession>(m_sigmaSize, constraintData.events);
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case NOT_CHAIN_SUCCESSION: {
      std::shared_ptr<NotChainSuccession> constraint =
          std::make_shared<NotChainSuccession>(m_sigmaSize,
                                               constraintData.events);
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case NOT_SUCCESSION: {
      std::shared_ptr<NotSuccession> constraint =
          std::make_shared<NotSuccession>(m_sigmaSize, constraintData.events);
      m_ConstraintSet.push_back(constraint);
      break;
    }
    case NOT_CO_EXISTENCE: {
      std::shared_ptr<NotCoExistence> constraint =
          std::make_shared<NotCoExistence>(m_sigmaSize, constraintData.events);
      m_ConstraintSet.push_back(constraint);
      break;
    }
    }
  }
}

std::vector<std::shared_ptr<Constraint>>
DeclareKnowledgeBase::getConstraintSet() {
  return m_ConstraintSet;
}

std::vector<Event> DeclareKnowledgeBase::getSigma() { return m_sigma; }

u_int64_t DeclareKnowledgeBase::getSigmaSize() { return m_sigmaSize; }
} // namespace hibpm