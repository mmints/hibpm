#include <EvalMaxSAT.h>

int main(int argc, char *argv[]) {
    unsigned int paralleleThread = 0;
    auto solver = new EvalMaxSAT(paralleleThread);

    // Create 3 variables
    int a = solver->newVar();
    int b = solver->newVar();
    int c = solver->newVar();

    // Add hard clauses
    solver->addClause({-a, -b});                // !a or !b
    auto card = solver->newCard({a, b, c});
    solver->addClause( {*card <= 2} );          // a + b + c <= 2

    // Add soft clauses
    solver->addWeightedClause({a, b}, 1);       // a or b
    solver->addWeightedClause({c}, 1);          // c
    solver->addWeightedClause({a, -c}, 1);      // a or !c
    solver->addWeightedClause({b, -c}, 1);      // b or !c

    ////// PRINT SOLUTION //////////////////
    if(!solver->solve()) {
        std::cout << "s UNSATISFIABLE" << std::endl;
        return 0;
    }
    std::cout << "s OPTIMUM FOUND" << std::endl;
    std::cout << "o " << solver->getCost() << std::endl;
    std::cout << "a = " << solver->getValue(a) << std::endl;
    std::cout << "b = " << solver->getValue(b) << std::endl;
    std::cout << "c = " << solver->getValue(c) << std::endl;
    ///////////////////////////////////////
}