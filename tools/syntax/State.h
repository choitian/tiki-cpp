/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State.h
 * Author: nur
 *
 * Created on May 5, 2019, 10:24 AM
 */

#ifndef STATE_H
#define STATE_H
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

#include "Grammar.h"

namespace syntax{
    class Item
    {
    public:
        Production *Prod;
        int Dot;
        std::map<std::string,std::set<std::string>> SpontaneousTable;
        std::set<std::string> PropagateTable;
        
        Item(Production *prod,int dot);
        std::string HashString();
        static std::string HashString(Production *prod,int dot);
        std::string DotRight();
        bool IsKernel();
    };

    class LookaheadLR;
    class State;
    typedef std::shared_ptr<State> State_sp;
    class State
    {
       LookaheadLR *lalr;
    public:
       std::set<std::string> Items;
       std::map<std::string,State_sp> GotoTable;
       std::map<std::string,std::set<std::string>> LookaheadTable;
       std::map<std::string,std::string> ParsingActionTable;
       int Id;
       
       State(LookaheadLR *lalr);
       std::string HashString();
       std::pair<std::set<std::string>::iterator,bool> AddItem(Item *item);
       std::vector<Item*> GetKernelItems();
    };
}

#endif /* STATE_H */

