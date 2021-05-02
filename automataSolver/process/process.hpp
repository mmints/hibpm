//
//  process.hpp
//  automataX
//
//  Created by Jandson on 30.04.21.
//

#ifndef process_hpp
#define process_hpp

#include <stdio.h>
#include "../automata/Automaton.hpp"

class Process{
  
protected:
    Automaton automaton;
    virtual void initialiseAutomaton(int SigmaS, int eventLetter);
    
    
};


// Unary Processess

class ProcessInit: public Process{
    
     void initialiseAutomaton(int SigmaS, int eventLetter){
         
         //only transition (0)---|evLetter|--->(1)
         this->automaton.addTransition(0, 1, eventLetter);
         //transition (1)---|Sigma|--->(1)
         for (int a = 0; a < SigmaS; a++) {
             this->automaton.addTransition(1, 1, a);
         }
         
         //only final state is 0
         this->automaton.addFinal(0);
         
    }
  
};

class ProcessEnd: public Process{
        
    void initialiseAutomaton(int SigmaS, int eventLetter){
        
        for (int a = 0; a < SigmaS; a++) {
            if (a != eventLetter) {
                this->automaton.addTransition(0, 0, a);
                this->automaton.addTransition(1, 0, a);
            }
        }
        
        this->automaton.addTransition(0, 1, eventLetter);
        this->automaton.addTransition(1, 1, eventLetter);
        
        this->automaton.addFinal(1);

    }
    
};

class ProcessMostOne: public Process{
        
    void initialiseAutomaton(int SigmaS, int eventLetter){
                     
            for (int a = 0; a < SigmaS; a++) {
                if (a != eventLetter) {
                    this->automaton.addTransition(0, 0, a);
                    this->automaton.addTransition(1, 1, a);
                }
            }
            
            //only transition (0)---|evLetter|--->(1)
            this->automaton.addTransition(0, 1, eventLetter);
            //transition (1)---|Sigma|--->(1)
            
            this->automaton.addFinal(0);
            this->automaton.addFinal(1);
            
    }
  
};

#endif /* process_hpp */
