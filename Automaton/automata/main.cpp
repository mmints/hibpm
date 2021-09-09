//
//  main.cpp
//  declareSolver
//
//  Created by Jandson on 27.04.21.
//

// Just for testing?

#include <iostream>
#include "Automaton/Automaton.hpp"

using namespace std;

int main(int argc, const char *argv[]) {
    // insert code here...


    int states = 2, symbols = 2;




    Automaton a(states, symbols), b(states, symbols), c(states, symbols);

    for (int i = 0; i < states; i++) {
        for (int j = 0; j < symbols; j++) {
            a.addTransition(i, j, 1);
        }
    }

    a.addFinal(0);
    // a.product(&a, &a)->print();
    a.semi_product(&a, &a)->print();
    b.reduceHopcrof();
    b.print();

    // a.reduceHopcrof();
    //a.print();




    list<int> ll;
    ll.push_back(2);
    int *x = &ll.front();
    (*x) = 3;

    cout << ll.front() << endl;

    if (!NULL) {
        cout << "OK" << endl;
    }


    return 0;
}
