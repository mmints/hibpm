#pragma once
namespace hibpm
{
    struct RemainderComposition
    {
        list <shared_ptr<Constraint>> hittingSet;
        list <list<shared_ptr < Constraint>>> kernelSet;
        list <shared_ptr<Constraint>> solutionSet;
    };
}