/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LookaheadLR.h
 * Author: nur
 *
 * Created on May 5, 2019, 10:22 AM
 */

#ifndef LOOKAHEADLR_H
#define LOOKAHEADLR_H
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <memory>

#include "Grammar.h"
#include "State.h"

namespace syntax{
    class LookaheadLR
    {
        Item* makeItem(Production* prod,int dot);
        std::pair<std::map<std::string,State_sp>::iterator,bool> AddState(State_sp state);
        void Closure(State_sp state);
        void visitItem(std::stack<std::string> &uncheckedNonTerminal,std::set<std::string> &visited,Item* item);
        std::map<std::string,State_sp> groupGOTOTable(State_sp state);
    public:
        Grammar *gram;
        std::map<std::string,Item*> ItemPool;
        std::map<std::string,State_sp> States;        
        State_sp InitialState;
        Item *InitialItem;
        
        LookaheadLR(Grammar *gram);
        void BuildCanonicalCollection();
    };
}
#endif /* LOOKAHEADLR_H */

