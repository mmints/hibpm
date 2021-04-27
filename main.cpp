//
//  main.cpp
//  declareSolver
//
//  Created by Jandson on 27.04.21.
//

#include <iostream>
#include "Automaton.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    
    int states =4 , symbols = 2;

        
    Automaton a(states, symbols);
    
    for (int i=0; i < states; i++) {
        for (int j = 0; j< symbols; j++) {
            a.addTransition(i, j, 1);
        }
    }
    a.print();
    
      
    return 0;
}
