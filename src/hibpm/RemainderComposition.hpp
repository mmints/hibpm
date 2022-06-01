/**
 * @author: Mark O. Mints
 * @email: mmints@uni-koblenz.de
 */

#pragma once
namespace hibpm {
struct RemainderComposition {
  list<shared_ptr<Constraint>> hittingSet;
  list<list<shared_ptr<Constraint>>> kernelSet;
  list<shared_ptr<Constraint>> solutionSet;
};
} // namespace hibpm