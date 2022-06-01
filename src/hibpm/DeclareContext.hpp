/**
 * @author: Mark O. Mints
 * @email: mmints@uni-koblenz.de
 */

#pragma once

#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "Constraint.hpp"

namespace hibpm {
// This Class is an object representation of DECLARE
class DeclareContext {
public:
  struct ConstraintData {
    ConstraintType type;
    std::vector<Event> events;
  };

  DeclareContext();
  ~DeclareContext() = default;

  // This is used in declare.yy
  void addUnaryConstraintData(ConstraintType type,
                              const std::string &event_val);
  void addBinaryConstraintData(ConstraintType type,
                               const std::string &activation_val,
                               const std::string &target_val);

  std::vector<ConstraintData> getConstraintData();
  std::vector<Event> getEventData();
  u_int64_t getEventDataCount();

private:
  std::vector<Event> m_eventData;
  std::vector<ConstraintData> m_constraintData;

  void addConstraintDataAndEventDataToSet(
      ConstraintType type, const std::vector<std::string> &event_names);
  bool checkEventDataExistence(const std::string &event_name);
  u_int64_t eventNameToNumericValue(const std::string &event_name);
};
} // namespace hibpm