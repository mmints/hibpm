#pragma once

#include <memory>
#include <vector>

#include "DeclareContext.hpp"

#include "Constraint.hpp"
#include "Unary.hpp"
#include "Binary.hpp"

namespace hibpm
{
    class DeclareKnowledgeBase
    {
    public:
        explicit DeclareKnowledgeBase(DeclareContext &declareContext);

        std::vector<std::shared_ptr<Constraint>> getConstraintSet();
        std::vector<Event> getSigma();
        u_int64_t getSigmaSize();

    private:
        std::vector<std::shared_ptr<Constraint>> m_ConstraintSet;
        std::vector<Event> m_sigma;
        u_int64_t m_sigmaSize;

        void initConstraintSet(DeclareContext &declareContext);

    };
}
