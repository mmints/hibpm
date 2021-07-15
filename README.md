# HIBPM - Handling Inconsistencies in Business Process Modelling
Prototype for removing inconsistency in declare model via remainders.

## Project Structure

The [`parser`](/parser) directory holds all required `Bison` and `Flex` files that represents the logic and grammar
of the Declare-Language. In [`/parser/Declare`](/parser/Declare) is a class definition of the Declare-Lang data
structure. The parser creates an object of this class. To compile this part of the project one has to execute
the script [`build.sh`](/parser/build.sh).

## Meeting Log
Here we're writing down some notes during meeting.

### April 22nd:
- https://www.gnu.org/software/bison/manual/html_node/C_002b_002b-Bison-Interface.html Bison for Parser
- Build the solver in C++
- Grail for Automata Library http://www.csit.upei.ca/~ccampeanu/Grail/ (Old and unsupported, last update 2012(?))

### April 8th:
- [Java Automata Library](https://www.brics.dk/automaton/)
- Carl Coras Repo for BPMN parsing: [inconsistencylibrary](https://gitlab.uni-koblenz.de/fg-bks/inconsistencylibrary)
- The only thing that we need are the test cases and maybe the parser.
