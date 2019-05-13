/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "LookaheadLR.h"
#include <stack>
#include <set>

namespace syntax{
    LookaheadLR::LookaheadLR(Grammar_sp gram)
    {
        this->gram = gram;
    }
    Item* LookaheadLR::makeItem(Production* prod,int dot)
    {
        std::string hs = Item::HashString(prod,dot);
        if(this->ItemPool.count(hs)==0){
            this->ItemPool[hs] = new Item(prod,dot);
        }
        return this->ItemPool[hs];
    }
    std::pair<std::map<std::string,State_sp>::iterator,bool> LookaheadLR::AddState(State_sp state)
    {
        auto hs = state->HashString();     
        return this->States.insert({hs,state});
    }
    void LookaheadLR::visitItem(std::stack<std::string> &uncheckedNonTerminal,std::set<std::string> &visited,Item* item)
    {
        std::string dotRight = item->DotRight();
        if(dotRight !="" && !this->gram->IsTerminal[dotRight] && visited.count(dotRight)==0)
        {
            uncheckedNonTerminal.push(dotRight);
            visited.insert(dotRight);
        }
    }
    void LookaheadLR::Closure(State_sp state)
    {
        std::stack<std::string> uncheckedNonTerminal;
        std::set<std::string> visited;
        
        for(std::string itemHs:state->Items)
        {
            auto item = this->ItemPool[itemHs];
            visitItem(uncheckedNonTerminal,visited,item);
        }
        
        while(!uncheckedNonTerminal.empty())
        {
            std::string nonTerminal = uncheckedNonTerminal.top();
            uncheckedNonTerminal.pop();
            
            auto prods = this->gram->GetProductionsOfHead(nonTerminal);
            for(auto prod:prods)
            {
                auto item = this->makeItem(prod,0);
                auto addInfo = state->AddItem(item);
                if(addInfo.second)
                {
                    visitItem(uncheckedNonTerminal,visited,item);
                }
            }
        }
    }
    std::map<std::string,State_sp> LookaheadLR::groupGOTOTable(State_sp state)
    {
        std::map<std::string,State_sp> gotoTable; 
        for(std::string itemHs:state->Items)
        {
            auto item = this->ItemPool[itemHs];
            std::string dotRight = item->DotRight();
            if(dotRight !="")
            {
                if(gotoTable.count(dotRight)==0)
                {
                    gotoTable[dotRight] = std::make_shared<State>(this);
                }
                auto peer = this->makeItem(item->Prod,item->Dot+1);

                gotoTable[dotRight]->AddItem(peer);
            }
        }

        return gotoTable;
    }
    void LookaheadLR::BuildCanonicalCollection()
    {
        this->InitialItem = makeItem(this->gram->Productions[0].get(),0);
        
        this->InitialState = std::make_shared<State>(this);
        this->InitialState->AddItem(this->InitialItem);
        
        this->AddState(this->InitialState);
        
        std::stack<State_sp> uncheckedState;
        uncheckedState.push(this->InitialState);
        
        while(!uncheckedState.empty())
        {
           State_sp state =  uncheckedState.top();
           uncheckedState.pop();
           this->Closure(state);
           
           std::map<std::string,State_sp> gotoTable = groupGOTOTable(state);
           for(auto item:gotoTable)
           {
               auto addInfo = this->AddState(item.second);
               if(addInfo.second)
               {
                   uncheckedState.push(addInfo.first->second);
               }
               state->GotoTable[item.first] = addInfo.first->second;
           }
        }
    }
}
