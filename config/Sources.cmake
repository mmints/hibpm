set(hibpm_sources
    ${hibpm_source}/hibpm/Parser.cpp
    ${hibpm_source}/hibpm/Parser.hpp
    
    ${hibpm_source}/hibpm/Declare.cpp
    ${hibpm_source}/hibpm/Declare.hpp

    ${hibpm_source}/hibpm/Automaton.cpp
    ${hibpm_source}/hibpm/Automaton.hpp

    ${hibpm_source}/hibpm/Process.cpp
    ${hibpm_source}/hibpm/Process.hpp

    ${hibpm_source}/hibpm/State.cpp
    ${hibpm_source}/hibpm/State.hpp

    ${hibpm_source}/hibpm/Unary.cpp
    ${hibpm_source}/hibpm/Unary.hpp

    ${hibpm_source}/hibpm/Unary/Participation.cpp
    ${hibpm_source}/hibpm/Unary/AtMostOne.cpp
    ${hibpm_source}/hibpm/Unary/Init.cpp
    ${hibpm_source}/hibpm/Unary/End.cpp

    ${hibpm_source}/hibpm/Binary.cpp
    ${hibpm_source}/hibpm/Binary.hpp

    ${hibpm_source}/hibpm/Binary/RespondedExistence.cpp
    ${hibpm_source}/hibpm/Binary/Response.cpp
    ${hibpm_source}/hibpm/Binary/AlternatedResponse.cpp
    ${hibpm_source}/hibpm/Binary/ChainResponse.cpp
    ${hibpm_source}/hibpm/Binary/Precedence.cpp
    ${hibpm_source}/hibpm/Binary/AlternatedPrecedence.cpp
    ${hibpm_source}/hibpm/Binary/ChainPrecedence.cpp
    ${hibpm_source}/hibpm/Binary/CoExistence.cpp
    ${hibpm_source}/hibpm/Binary/Succession.cpp
    ${hibpm_source}/hibpm/Binary/AlternateSuccession.cpp
    ${hibpm_source}/hibpm/Binary/ChainSuccession.cpp
    ${hibpm_source}/hibpm/Binary/NotChainSuccession.cpp
    ${hibpm_source}/hibpm/Binary/NotSuccession.cpp
    ${hibpm_source}/hibpm/Binary/NotCoExistence.cpp

    ${hibpm_source}/hibpm/RepairAutomata.cpp
    ${hibpm_source}/hibpm/RepairAutomata.hpp

    #${hibpm_source}/hibpm/TopoGraph.cpp
    #${hibpm_source}/hibpm/TopoGraph.h

    ${BISON_DeclareParser_OUTPUTS}
    ${FLEX_DeclareScanner_OUTPUTS}
)