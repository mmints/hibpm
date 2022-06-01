/**
 * @author:  Dr. Jandson Santos Ribeiro Santos
 * @email: jandson.ribeiro@fernuni-hagen.de
 */

#include "GraphSolver.hpp"

namespace hibpm {

GraphSolver::GraphSolver(int numEvents)
    : matrix(numEvents, vector<Cell>(numEvents, Cell())),
      eventsStatus(numEvents, -1) {
  status = true;
  this->numEvs = numEvents;
  this->countNegated = 0;
}

void GraphSolver::transitionForward(int ev1, int ev2) {

  list<int> stackN;
  // projects if n->ev1 then n->ev2
  for (int i = 0; i < this->numEvs; ++i) {
    if (this->matrix[i][ev1].FUTURE_POS) {
      this->modifyMatrix(i, ev2, DIMENSION::FUTURE, true);
      stackN.push_back(i); // SAVES that i->ev1
    }
  }
  // projects if n->ev1 and ev2->y then n->y
  stackN.push_back(ev1);
  for (int n : stackN) {
    for (int i = 0; i < this->numEvs; ++i) {
      if (this->matrix[ev2][i].FUTURE_POS) {
        this->modifyMatrix(n, i, DIMENSION::FUTURE, true);
      }
    }
  }
}

bool GraphSolver::checkCyclesForwardPos(int ev1, int ev2) {

  this->transitionForward(ev1, ev2);

  if (this->matrix[ev2][ev1].FUTURE_POS) { // then there is a cycle forward

    this->modifyStatus(ev1, 0);
    this->modifyStatus(ev2, 0);

    // COMPUTE CYCLES
    // CYCLES COMPRISES EXATLY ev1, ev2 and all those who insie on ev1 and on
    // ev2
    for (int i = 0; i < this->numEvs; ++i) {
      if (this->matrix[i][ev1].FUTURE_POS && this->matrix[ev2][i].FUTURE_POS) {
        this->modifyStatus(i, 0);
      }
    }

    return true;
  }

  return false; // NO CYCLES
}

bool GraphSolver::addForwardNEG(int ev1, int ev2) {

  this->modifyMatrix(ev1, ev2, DIMENSION::FUTURE, 0);
  this->addNextNEG(ev1, ev2);

  return this->status;
}

bool GraphSolver::addForwardPos(int ev1, int ev2) {

  this->modifyMatrix(ev1, ev2, DIMENSION::FUTURE, 1);

  if (!this->status) {
    return false;
  }

  return !this->checkCyclesForwardPos(ev1, ev2);
}

void GraphSolver::modifyStatus(int ev, int newStatus) {

  if (this->eventsStatus[ev] == -1) {
    this->eventsStatus[ev] = newStatus;
    if (newStatus == 0) {
      this->countNegated++;
      if (this->countNegated == this->numEvs) {
        this->status = false;
      }
    }
  } else {
    if (this->eventsStatus[ev] != newStatus && newStatus != -1) {
      this->status = false;
    } else {
      this->eventsStatus[ev] = newStatus;
    }
  }
}

void GraphSolver::modifyMatrix(int ev1, int ev2, DIMENSION AXIS, bool nValue) {

  switch (AXIS) {

  case DIMENSION::FUTURE:
    if (!this->matrix[ev1][ev2].isDIMENSIONUnknown(AXIS) ||
        this->matrix[ev1][ev2].canChangeToValue(DIMENSION::FUTURE, nValue)) {

      this->matrix[ev1][ev2].changeToValue(DIMENSION::FUTURE, nValue);
      if (!nValue) {
        this->modifyMatrix(ev1, ev2, DIMENSION::NEXT, false);
      }
    } else {
      this->modifyStatus(ev1, 0);
    }

    return;
  case DIMENSION::NEXT:

    if (!this->matrix[ev1][ev2].isDIMENSIONUnknown(AXIS) ||
        this->matrix[ev1][ev2].canChangeToValue(AXIS, nValue)) {
      this->matrix[ev1][ev2].changeToValue(AXIS, nValue);
      if (nValue) {
        this->modifyMatrix(ev1, ev2, DIMENSION::FUTURE, nValue);
      }
    } else {
      this->modifyStatus(ev1, 0);
    }

    return;
  case DIMENSION::PAST:
    if (this->matrix[ev1][ev2].isDIMENSIONUnknown(AXIS) ||
        this->matrix[ev1][ev2].canChangeToValue(AXIS, nValue)) {
      this->matrix[ev1][ev2].changeToValue(AXIS, nValue);
    } else {
      this->modifyStatus(ev2, 0);
    }
    return;
  case DIMENSION::PREV:
    if (this->matrix[ev1][ev2].isDIMENSIONUnknown(AXIS) ||
        this->matrix[ev1][ev2].canChangeToValue(AXIS, nValue)) {
      this->matrix[ev1][ev2].changeToValue(AXIS, nValue);
    } else {
      this->modifyStatus(ev2, 0);
    }
    return;

  case EXISTENCIAL:
    if (this->matrix[ev1][ev2].isDIMENSIONUnknown(AXIS) ||
        this->matrix[ev1][ev2].canChangeToValue(AXIS, nValue)) {
      this->matrix[ev1][ev2].changeToValue(AXIS, nValue);
      // this->modifyMatrix(ev1,ev2,AXIS,nValue);
    } else {
      this->modifyStatus(ev1, 0);
    }

    if (this->matrix[ev1][ev2].EXISTS_POS &&
        this->matrix[ev2][ev1].EXISTS_NEG) {
      this->modifyStatus(ev1, 0);
    } else if (this->matrix[ev1][ev2].EXISTS_NEG &&
               this->matrix[ev2][ev1].EXISTS_POS) {
      this->modifyStatus(ev2, 0);
    }

    break;
  }
}

bool GraphSolver::increment(shared_ptr<State> state) {

  RuleType rt = state->getRule().type;
  int ev1 = state->getRule().events[0].numericValue,
      ev2 = state->getRule().getTarget().numericValue;

  // UNARY ONES
  if (!state->isBinary() && state->getRule().type != RuleType::AT_MOST_ONE) {
    this->modifyStatus(state->getRule().events[0].numericValue, 1);
    for (int i = 0; i < this->numEvs; ++i) {
      if (this->matrix[ev1][i].EXISTS_POS) {
        this->modifyStatus(state->getRule().events[0].numericValue, 1);
      } else if (this->matrix[ev1][i].EXISTS_POS) {
        this->modifyStatus(state->getRule().events[0].numericValue, 0);
      }
    }
    return this->status;
  }

  switch (rt) {
  case RuleType::RESPONSE:
    this->addForwardPos(ev1, ev2);
    break;

  case RuleType::CHAIN_RESPONSE:
    this->addNextPos(ev1, ev2);
    break;

  case RuleType::RESPONDED_EXISTENCE:
    this->addEXISTPos(ev1, ev2);
    break;

  case RuleType::CO_EXISTENCE: {

    Rule r1 = {RESPONDED_EXISTENCE, state->getRule().events};
    RespondedExistence rp1(r1, this->numEvs);

    this->increment(std::make_shared<RespondedExistence>(rp1));

    r1.events[0] = state->getRule().getTarget();
    r1.events[1] = state->getRule().events[0];

    this->increment(std::make_shared<RespondedExistence>(rp1));
  } break;

  case RuleType::NOT_CO_EXISTENCE: {
    this->addEXISTNeg(ev1, ev2);
    this->addEXISTNeg(ev2, ev1);
  } break;

  case RuleType::NOT_SUCCESSION: {
    this->addForwardNEG(ev1, ev2);
  } break;

  case RuleType::PRECEDENCE: {
    this->addPastPos(ev1, ev2);

  } break;

  case RuleType::SUCCESSION: {
    Rule rResp = {RuleType::RESPONSE, state->getRule().events},
         rPrec = {RuleType::PRECEDENCE, state->getRule().events};

    Response responseState(rResp, this->numEvs);
    Precedence precedenceState(rPrec, this->numEvs);

    this->increment(make_shared<Response>(responseState));
    this->increment(make_shared<Precedence>(precedenceState));

  } break;

  case RuleType::CHAIN_PRECEDENCE: {
    this->addPrevPos(ev1, ev2);

    Rule r = {RuleType::ALTERNATED_PRECEDENCE, state->getRule().events};

    AlternatedPrecedence altR(r, this->numEvs);

    this->increment(make_shared<AlternatedPrecedence>(altR));

    r.type = RuleType::PRECEDENCE;
    Precedence rPrec(r, this->numEvs);

    this->increment(make_shared<Precedence>(rPrec));

    r.type = RuleType::RESPONDED_EXISTENCE;
    r.events[0] = state->getRule().events[1];
    r.events[1] = state->getRule().events[0];

    RespondedExistence repEx(r, this->numEvs);
    this->increment(make_shared<RespondedExistence>(repEx));

  } break;

  case RuleType::CHAIN_SUCCESSION: {

    Rule rChainResp = {RuleType::CHAIN_RESPONSE, state->getRule().events},
         rChainPrec = {RuleType::CHAIN_PRECEDENCE, state->getRule().events};

    ChainResponse chainRep(rChainResp, this->numEvs);
    ChainPrecedence chainPrec(rChainPrec, this->numEvs);

    this->increment(make_shared<ChainResponse>(chainRep));
    this->increment(make_shared<ChainPrecedence>(chainPrec));

  } break;

  case RuleType::NOT_CHAIN_SUCCESSION: {

    this->addNextNEG(ev1, ev2);
    this->addNextNEG(ev2, ev1);

  } break;

  case ALTERNATED_RESPONSE:
    this->addNextNEG(ev1, ev1);
    this->addForwardPos(ev1, ev2);
    break;
  case ALTERNATED_PRECEDENCE: {

    Rule rPrec = {RuleType::PRECEDENCE, state->getRule().events},
         rAltResp = {RuleType::ALTERNATED_RESPONSE, vector<Event>(2)};

    rAltResp.events[0] = state->getRule().getTarget();
    rAltResp.events[1] = state->getRule().events[0];

    Precedence prec(rPrec, this->numEvs);
    AlternatedResponse altResp(rAltResp, this->numEvs);

    this->increment(make_shared<Precedence>(prec));
    this->addNextNEG(ev2, ev2);
    // this->increment(make_shared<AlternatedResponse>(altResp));

  } break;
  case ALTERNATED_SUCCESSION: {

    Rule rAltResp = {RuleType::ALTERNATED_RESPONSE, state->getRule().events},
         rAltPrec = {RuleType::ALTERNATED_PRECEDENCE, state->getRule().events};

    AlternatedResponse altResp(rAltResp, this->numEvs);
    AlternatedPrecedence altPrec(rAltPrec, this->numEvs);

    this->increment(make_shared<AlternatedResponse>(altResp));
    this->increment(make_shared<AlternatedPrecedence>(altPrec));

  } break;

  default:
    return true;
  }

  return this->status;
}

bool GraphSolver::getStatus() { return this->status; }

bool GraphSolver::addNextPos(int ev1, int ev2) {

  this->modifyMatrix(ev1, ev2, DIMENSION::NEXT, 1);
  this->addForwardPos(ev1, ev2);

  // ALL expecept for e2 should be lebelled false
  for (int i = 0; i < this->numEvs; ++i) {
    if (i != ev2) {
      this->modifyMatrix(ev1, i, DIMENSION::NEXT, 0);
      if (this->matrix[ev1][i].NEXT_POS) {
        this->modifyStatus(ev1, 0);
      }
    }
  }

  return this->status;
}

bool GraphSolver::addNextNEG(int ev1, int ev2) {

  this->modifyMatrix(ev1, ev2, DIMENSION::NEXT, 0);

  return this->status;
}

void GraphSolver::transitionForwardExistencial(int ev1, int ev2) {

  list<int> stackN;
  // projects if n->ev1 then n->ev2
  for (int i = 0; i < this->numEvs; ++i) {
    if (this->matrix[i][ev1].EXISTS_POS) {
      this->modifyMatrix(i, ev2, DIMENSION::EXISTENCIAL, true);
      stackN.push_back(i); // SAVES that i->ev1
    }
  }
  // projects if n->ev1 and ev2->y then n->y
  stackN.push_back(ev1);
  for (int n : stackN) {
    for (int i = 0; i < this->numEvs; ++i) {
      if (this->matrix[ev2][i].EXISTS_POS) {
        this->modifyMatrix(n, i, DIMENSION::EXISTENCIAL, true);
      }
    }
  }
}

bool GraphSolver::addEXISTPos(int ev1, int ev2) {

  this->modifyMatrix(ev1, ev2, DIMENSION::EXISTENCIAL, true);
  this->transitionForwardExistencial(ev1, ev2);

  return true;
}

bool GraphSolver::addEXISTNeg(int ev1, int ev2) {

  this->modifyMatrix(ev1, ev2, DIMENSION::EXISTENCIAL, false);

  return false;
}

bool GraphSolver::addPastPos(int ev1, int ev2) {

  this->modifyMatrix(ev1, ev2, DIMENSION::PAST, true);
  this->checkCyclesBackwardsPos(ev1, ev2);

  return this->status;
}

void GraphSolver::checkCyclesBackwardsPos(int ev1, int ev2) {

  this->transitionBackward(ev1, ev2);

  if (this->matrix[ev2][ev1].PAST_POS) { // then there is a cycle forward

    this->modifyStatus(ev1, 0);
    this->modifyStatus(ev2, 0);

    // COMPUTE CYCLES
    // CYCLES COMPRISES EXATLY ev1, ev2 and all those who insie on ev1 and on
    // ev2
    for (int i = 0; i < this->numEvs; ++i) {
      if (this->matrix[i][ev1].PAST_POS && this->matrix[ev2][i].PAST_POS) {
        this->modifyStatus(i, 0);
      }
    }
  }
}

void GraphSolver::transitionBackward(int ev1, int ev2) {

  list<int> stackN;
  // projects if n->ev1 then n->ev2
  for (int i = 0; i < this->numEvs; ++i) {
    if (this->matrix[i][ev1].PAST_POS) {
      this->modifyMatrix(i, ev2, DIMENSION::PAST, true);
      stackN.push_back(i); // SAVES that i->ev1
    }
  }
  // projects if n->ev1 and ev2->y then n->y
  stackN.push_back(ev1);
  for (int n : stackN) {
    for (int i = 0; i < this->numEvs; ++i) {
      if (this->matrix[ev2][i].PAST_POS) {
        this->modifyMatrix(n, i, DIMENSION::PAST, true);
      }
    }
  }
}

bool GraphSolver::addPrevPos(int ev1, int ev2) {

  this->modifyMatrix(ev1, ev2, DIMENSION::PREV, true);
  this->addPastPos(ev1, ev2);

  for (int i = 0; i < numEvs; ++i) {
    if (i != ev1) {
      this->modifyMatrix(i, ev2, DIMENSION::PREV, false);
      if (this->matrix[i][ev2].PREV_POS) {
        this->modifyStatus(ev2, 0);
      }
    }
  }

  return this->status;
}

bool GraphSolver::addPrevNEG(int ev1, int ev2) {

  this->modifyMatrix(ev1, ev2, DIMENSION::PREV, false);

  if (this->matrix[ev1][ev2].PREV_POS) {
    this->modifyStatus(ev2, 0);
  }

  return false;
}

bool GraphSolver::addPastNEG(int ev1, int ev2) {

  this->modifyMatrix(ev1, ev2, DIMENSION::PAST, false);
  this->addPrevNEG(ev1, ev2);

  return false;
}

bool GraphSolver::incrementAll(list<shared_ptr<State>> set) {

  for (shared_ptr<State> st : set) {

    this->increment(st);
  }
  return this->status;
}
} // namespace hibpm