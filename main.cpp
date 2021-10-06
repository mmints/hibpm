#include "Solver.h"
#include "Process/Process.hpp"

using namespace hibpm;

int main(int argc, char** argv)
{
    Solver solver;
    Declare declareKB;

    declareKB = solver.parseFromFile("../Resources/minimalExample.txt");
    Process process(declareKB);
}
