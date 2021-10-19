//
// Created by Jandson on 15.10.21.
//

#include "TopoGraph.h"

TopoGraph::TopoGraph(vector<std::shared_ptr<State>> &process, int numEvents) {
    this->order.resize(process.size());
    buildAtivationLink(process, numEvents);
}

bool TopoGraph::isSubSumedBy(Rule r1, Rule r2) {

    if (r1.events[0].numericValue == r2.events[0].numericValue) {

        switch (r1.type) {
            case RuleType::INIT:
                if (r2.type == RuleType::INIT ||
                    r2.type == RuleType::PARTICIPATION) {
                    return true;
                }
                break;
            case RuleType::END:
                if (r2.type == RuleType::END ||
                    r2.type == RuleType::PARTICIPATION) {
                    return true;
                }
                break;
        }

        if(r1.events[1].numericValue == r2.events[1].numericValue){
            switch (r1.type) {

                case RuleType::CHAIN_PRECEDENCE:
                    if (r2.type == RuleType::CHAIN_PRECEDENCE ||
                        r2.type == RuleType::ALTERNATED_PRECEDENCE ||
                        r2.type == RuleType::PRECEDENCE ){
                        return true;
                    }
                    break;
                case RuleType::ALTERNATED_PRECEDENCE:
                    if (r2.type == RuleType::ALTERNATED_PRECEDENCE ||
                        r2.type == RuleType::PRECEDENCE ){
                        return true;
                    }
                    break;

                case RuleType::CHAIN_SUCCESSION:
                    if (r2.type == RuleType::CHAIN_SUCCESSION ||
                        r2.type == RuleType::ALTERNATED_SUCCESSION ||
                        r2.type == RuleType::SUCCESSION ||
                        r2.type == RuleType::CO_EXISTENCE){
                        return true;
                    }
                    break;
                case RuleType::ALTERNATED_SUCCESSION:
                    if (r2.type == RuleType::ALTERNATED_SUCCESSION ||
                        r2.type == RuleType::SUCCESSION ||
                        r2.type == RuleType::CO_EXISTENCE){
                        return true;
                    }
                    break;
                case RuleType::SUCCESSION:
                    if (r2.type == RuleType::SUCCESSION ||
                        r2.type == RuleType::CO_EXISTENCE){
                        return true;
                    }
                    break;

                case RuleType::CHAIN_RESPONSE:
                    if (r2.type == RuleType::CHAIN_RESPONSE||
                        r2.type == RuleType::ALTERNATED_RESPONSE ||
                        r2.type == RuleType::RESPONSE ||
                        r2.type == RuleType::RESPONDED_EXISTENCE){
                        return true;
                    }
                    break;

                case RuleType::ALTERNATED_RESPONSE:
                    if (r2.type == RuleType::ALTERNATED_RESPONSE||
                        r2.type == RuleType::RESPONSE ||
                        r2.type == RuleType::RESPONDED_EXISTENCE){
                        return true;
                    }
                    break;
                case RuleType::RESPONSE:
                    if (r2.type == RuleType::RESPONSE ||
                        r2.type == RuleType::RESPONDED_EXISTENCE){
                        return true;
                    }
                    break;

                case RuleType::NOT_CO_EXISTENCE:
                    if (r2.type == RuleType::NOT_CO_EXISTENCE ||
                        r2.type == RuleType::NOT_SUCCESSION ||
                        r2.type == RuleType::NOT_CHAIN_SUCCESSION){
                        return true;
                    }
                    break;
                case RuleType::NOT_SUCCESSION:
                    if (r2.type == RuleType::NOT_SUCCESSION ||
                        r2.type == RuleType::NOT_CHAIN_SUCCESSION){
                        return true;
                    }
                    break;

            }

        }

    }else if ((r1.type == RuleType::CHAIN_PRECEDENCE ||
            r1.type == RuleType::ALTERNATED_PRECEDENCE ||
            r1.type == RuleType::PRECEDENCE) &&
            r2.type == RuleType::RESPONDED_EXISTENCE &&
            r1.events[0].numericValue == r2.events[1].numericValue &&
            r1.events[1].numericValue == r2.events[0].numericValue){

        switch (r1.type) {
            case RuleType::CHAIN_PRECEDENCE:
                return true;
            case RuleType::ALTERNATED_PRECEDENCE:
                return true;
            case RuleType::PRECEDENCE:
                return true;
        }
                
        }

    return false;
}

TopoGraph::~TopoGraph() {

//    for (Cell* c: this->grounded) {
//        delete c->value;
//
//    }

}

void TopoGraph::add(State &state) {

    for (list<State*> l : this->grounded) {
        bool inThisStack = false;
        for (list<State*>::iterator itS = l.begin() ; itS != l.end(); itS++ ) {

            if (isSubSumedBy((*itS)->getRule(),state.getRule())) {
                inThisStack = true;
            }else if(inThisStack){
                l.insert(itS,&state);
                inThisStack = false;
                return;
            }else if (isSubSumedBy(state.getRule(),(*itS)->getRule())){
                l.insert(itS,&state);
                return;
            }
        }
        if (inThisStack){
            l.push_back(&state);
            return;
        }

    }

    list<State*> lAux;
    lAux.push_back(&state);
    this->grounded.push_back(lAux);

//    Cell *c = new Cell(&state);
//
//    if (this->grounded.empty()){
//        this->grounded.push_back(c);
//        return;
//    }
//
//    for (Cell *x: this->grounded) {
//        if (isSubSumedBy(state.getRule(), x->value->getRule())){
//            //TODO swap cell function
//        }else if(isSubSumedBy(x->value->getRule(), x->value){
//
//        }
//    }

}

bool TopoGraph::isNegative(Rule r1){
    if (r1.type == RuleType::NOT_SUCCESSION ||
        r1.type == RuleType::NOT_CO_EXISTENCE ||
        r1.type == RuleType::NOT_CHAIN_SUCCESSION){
        return true;
    }

    return false;

}

bool TopoGraph::IsForwardBackwards(Rule r1){
    if (r1.type == RuleType::RESPONDED_EXISTENCE ||
        r1.type == RuleType::RESPONSE ||
        r1.type == RuleType::ALTERNATED_RESPONSE ||
        r1.type == RuleType::CHAIN_RESPONSE ||
        r1.type == RuleType::PRECEDENCE ||
        r1.type == RuleType::ALTERNATED_PRECEDENCE ||
        r1.type == RuleType::CHAIN_PRECEDENCE){
        return true;
    }

    return false;

}

bool TopoGraph::IsCoupling(Rule r1){

    if (r1.type == RuleType::CO_EXISTENCE ||
        r1.type == RuleType::SUCCESSION ||
        r1.type == RuleType::ALTERNATED_SUCCESSION ||
        r1.type == RuleType::NOT_CHAIN_SUCCESSION){
        return true;
    }

    return false;

}

bool TopoGraph::isCardinality(Rule r1){

    if (r1.type == RuleType::PARTICIPATION ||
        r1.type == RuleType::AT_MOST_ONE){
        return true;
    }

    return false;

}

bool TopoGraph::isPosition(Rule r1){

    if (r1.type == RuleType::INIT ||
        r1.type == RuleType::END){
        return true;

    }

    return false;

}

bool TopoGraph::isLessThanByType(Rule r1, Rule r2) {

    if (isNegative(r1)){
        return true;
    }else

    if (IsForwardBackwards(r1) && !isNegative(r2)){
        return true;
    }

    if (IsCoupling(r1) &&
        !IsForwardBackwards(r2) &&
        !isNegative(r2)){
        return true;
    }

    if (isCardinality(r1) &&
        !IsCoupling(r1) &&
        !IsForwardBackwards(r2) &&
        !isNegative(r2)){
        return true;
    }

    if(isPosition(r1) && isPosition(r2)){
        return true;
    }

    
    return false;
}

void TopoGraph::buildAtivationLink(vector<std::shared_ptr<State>> &process, int numEvents) {

    //this->order.clear();

    for (int i = 0; i < process.size() ; i++) {
        shared_ptr<State> s= process[i];
        vector<bool> countVars(numEvents,false);
        int total = 0;

        for (shared_ptr<State> s2: process) {
            if (s->getRule().events[0].numericValue == s2->getRule().events[0].numericValue){
                if (!countVars[s2->getRule().getTarget().numericValue]){
                    countVars[s2->getRule().getTarget().numericValue] = true;
                    total++;
                }
            }

        }


        order[i] = pair<Rule,int> (s->getRule(),total);
    }

}

bool TopoGraph::isLessThenActivation(Rule r1, Rule r2){

    int rankR1, rankR2;
    int countB = 0;

    for (pair<Rule,int> rp : this->order) {
        if (rp.first.isEqualTo(r1)){
            rankR1 = rp.second;
            countB++;
        }
        if (rp.first.isEqualTo(r2)){
            rankR2 = rp.second;
            countB++;
        }

        if (countB == 2){
            break;
        }

    }

    if (rankR1 <= rankR2){
        return true;
    }

    return false;

}

