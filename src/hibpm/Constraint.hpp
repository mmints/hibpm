/**
 * @author: Mark O. Mints
 * @email: mmints@uni-koblenz.de
 */

#pragma once

#include <string>
#include <vector>

#include "Automaton.hpp"

namespace hibpm {
enum ConstraintType {
  // Unary Types
  PARTICIPATION,
  AT_MOST_ONE,
  AT_MOST_TWO,
  AT_MOST_THREE,
  AT_LEAST_ONE,
  INIT,
  END,

  // Binary Types
  RESPONDED_EXISTENCE,
  RESPONSE,
  ALTERNATED_RESPONSE,
  CHAIN_RESPONSE,
  PRECEDENCE,
  ALTERNATED_PRECEDENCE,
  CHAIN_PRECEDENCE,
  CO_EXISTENCE,
  SUCCESSION,
  ALTERNATED_SUCCESSION,
  CHAIN_SUCCESSION,
  NOT_CHAIN_SUCCESSION,
  NOT_SUCCESSION,
  NOT_CO_EXISTENCE
};

struct Event {
  std::string name;
  u_int64_t numericValue; // checking against vector length -> size_t, which is
                          // unsigned long long
};

///// Abstract Constraint Class /////

class Constraint {
public:
  Constraint(size_t sigmaSize, bool isBinary);

  bool isBinary();
  bool isUnary();
  Automaton getAutomata();
  ConstraintType getType();
  std::string getTypeString();

  virtual bool eventsMatch(Constraint &constraint) = 0;

  virtual std::string print() = 0;

protected:
  ConstraintType m_type;
  std::string m_constraintTypeString;
  size_t m_sigmaSize;
  bool m_isBinary;
  Automaton m_automaton;

  virtual void initializeAutomaton() = 0;
};
} // namespace hibpm