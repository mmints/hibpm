#include <hibpm/Rule.hpp>
#include <EvalMaxSAT.h>

using namespace hibpm;

int main(int argc, char *argv[]) {

    unsigned int paralleleThread = 0;
    auto solver = new EvalMaxSAT(paralleleThread);

    int a = solver->newVar();
    int b = solver->newVar();
    int c = solver->newVar();
    
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;

    return 0;
}