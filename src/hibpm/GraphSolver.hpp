/**
 * @author:  Dr. Jandson Santos Ribeiro Santos
 * @email: jandson.ribeiro@fernuni-hagen.de
 */

#pragma once

#include "Binary.hpp" // Why only Binary?
#include "State.hpp"
#include <memory>
#include <vector>

using namespace std;

namespace hibpm {

class GraphSolver {

protected:
  enum DIRECTION { FORWARD, BACKWARDS, BIDIRECTION, EXISTENCIAL_OL, POS, NEG };

  enum DIMENSION { FUTURE, NEXT, PREV, PAST, EXISTENCIAL };

  struct Cell {
    bool FUTURE_POS, FUTURE_NEG, NEXT_POS, NEXT_NEG, PREV_POS, PREV_NEG,
        PAST_POS, PAST_NEG, EXISTS_POS, EXISTS_NEG;

    // int FUTURE, NEXT, PREV, PAST, EXISTS;
    Cell() {
      FUTURE_POS = FUTURE_NEG = false;
      NEXT_POS = NEXT_NEG = false;
      PREV_POS = PREV_NEG = false;
      PAST_POS = PAST_NEG = false;
      EXISTS_POS = EXISTS_NEG = false;
    }

    bool isDIMENSIONUnknown(DIMENSION AXIS) {
      switch (AXIS) {
      case DIMENSION::FUTURE:
        return !FUTURE_POS && !FUTURE_NEG;
      case DIMENSION::NEXT:
        return !NEXT_POS && !NEXT_NEG;
      case DIMENSION::PREV:
        return !PREV_POS && !PREV_NEG;
      case DIMENSION::PAST:
        return !PAST_POS && !PAST_NEG;
      case EXISTENCIAL:
        return !EXISTS_POS && !EXISTS_NEG;
      }
    }

    bool changeToValue(DIMENSION AXIS, bool nV) {
      switch (AXIS) {
      case DIMENSION::FUTURE:
        nV ? FUTURE_POS = true : FUTURE_NEG = true;
        break;
      case DIMENSION::NEXT:
        nV ? NEXT_POS = true : NEXT_NEG = true;
        break;
      case DIMENSION::PAST:
        nV ? PAST_POS = true : PAST_NEG = true;
        break;
      case DIMENSION::PREV:
        nV ? PREV_POS = true : PREV_NEG = true;
        break;
      case EXISTENCIAL:
        nV ? EXISTS_POS = true : EXISTS_NEG = true;
        break;
      }

      return true;
    }

    bool isConsistent(DIMENSION AXIS) {
      switch (AXIS) {
      case DIMENSION::FUTURE:
        return !(FUTURE_POS && FUTURE_NEG);
      case DIMENSION::NEXT:
        return !(NEXT_POS && NEXT_NEG);
      case DIMENSION::PAST:
        return !(PAST_POS && PAST_NEG);
      case DIMENSION::PREV:
        return !(PREV_POS && PREV_NEG);
      case EXISTENCIAL:
        return !(EXISTS_POS && EXISTS_NEG);
      }
    }

    bool canChangeToValue(DIMENSION AXIS, bool nV) {
      switch (AXIS) {
      case DIMENSION::FUTURE:
        return nV ? !FUTURE_NEG : !FUTURE_POS;

      case DIMENSION::NEXT:
        return nV ? !NEXT_NEG : !NEXT_POS;
        break;
      case DIMENSION::PREV:
        return nV ? !PREV_NEG : !PREV_POS;

      case DIMENSION::PAST:
        return nV ? !PAST_NEG : !PAST_POS;
      case EXISTENCIAL:
        return nV ? !EXISTS_NEG : !EXISTS_POS;
      }
    }
  };

private:
  vector<int> eventsStatus;
  vector<vector<Cell>> matrix;
  bool status;
  int numEvs, countNegated;

public:
  bool checkCyclesForwardPos(int ev1, int ev2);
  void transitionForward(int ev1, int ev2);

  void modifyStatus(int ev, int newStatus);

  // FUTURE
  bool addForwardPos(int ev1, int ev2);

  bool addForwardNEG(int ev1, int ev2);

  // NEXT
  bool addNextPos(int ev1, int ev2);

  bool addNextNEG(int ev1, int ev2);

  // PAST
  bool addPastPos(int ev1, int ev2);

  bool addPastNEG(int ev1, int ev2);

  // PAST
  bool addPrevPos(int ev1, int ev2);

  bool addPrevNEG(int ev1, int ev2);

  void transitionBackward(int ev1, int ev2);

  void checkCyclesBackwardsPos(int ev1, int ev2);

  // EXISTENCIAL
  bool addEXISTPos(int ev1, int ev2);

  bool addEXISTNeg(int ev1, int ev2);

  void transitionForwardExistencial(int ev1, int ev2);

  void modifyMatrix(int ev1, int ev2, DIMENSION AXIS, bool nValue);

public:
  GraphSolver(int numEvents);

  bool increment(shared_ptr<State> state);

  bool getStatus();

  bool incrementAll(list<shared_ptr<State>> set);
};
} // namespace hibpm
