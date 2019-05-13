/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Grammar.h"
#include "../../util/commons.h"
#include <iterator>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <list>
#include <regex>

namespace syntax{
    Production::Production(std::string head)
    {
        this->Head = head;
    }
    std::string Production::ToString()
    {
        std::string nodes = util::join_strings(this->Nodes,"+");

        return util::format("%s:%s",this->Head.c_str(),nodes.c_str());
    }
    bool Production::IsNull()
    {
        return Nodes.size() == 1 && Nodes[0] == SymbolNull;
    }
    void Grammar::loadProductions(std::string &symbol,std::string &prods)
    {
        std::smatch matches;
        std::regex e ("((\\s*\\w+\\s*)+)(\\s*\\{.*\\}\\s*)?\\|?");   // matches words beginning by "sub"

        std::string content_s = prods;
        while (std::regex_search (content_s,matches,e)) {
            std::shared_ptr<Production> prod = std::make_shared<Production>(symbol);

            std::string nodeList = util::trim(matches[1]);
            std::string script = util::trim(matches[3]);
            std::vector<std::string> nodes = util::split(nodeList);
            for(auto node:nodes)
            {
                prod->Nodes.push_back(util::trim(node));
            }
            prod->Script = script;

            this->Productions.push_back(prod);

            content_s = matches.suffix().str();
        }    
    }
    void Grammar::CalcFst(std::vector<std::string> &symbols,std::set<std::string> &fst, bool &nullable)
    {
        fst.clear();
        nullable = false;

        for(size_t i=0;i<symbols.size();i++)
        {
            auto &symbol = symbols[i];

            if (symbol != SymbolNull) {
                auto &vs = this->FST[symbol];
                fst.insert(vs.begin(),vs.end());
            }    
            if(this->Nullable.count(symbol)==0)
                break;

            if (i == symbols.size()-1)
                nullable = true;
        }    
    }
    void Grammar::computeAttributes()
    {
        //initialize special symbols
        this->Nullable.insert(SymbolNull);
        this->IsTerminal[SymbolEnd] = true;
        this->FST[SymbolEnd].insert(SymbolEnd); 

        //initialize IsTerminal
        for(size_t i=0;i<this->Productions.size();i++)
        {
            auto prod = this->Productions.at(i);
            this->IsTerminal[prod->Head] = false;
            prod->Id = i;
        }   
        //if not exist in IsTerminal as not being a head,then Is Terminal.
        for(size_t i=0;i<this->Productions.size();i++)
        {
            auto prod = this->Productions.at(i);
            for(auto symbol:prod->Nodes)
            {
                if(this->IsTerminal.count(symbol)==0)
                {
                    this->IsTerminal[symbol] = true;
                    this->FST[symbol].insert(symbol);
                }
            }
        } 
        bool nothingChanged = false;
        while(!nothingChanged)
        {
            nothingChanged = true; 
            for(auto prod: this->Productions)
            {
                std::string &head = prod->Head;
                std::set<std::string> fst;
                bool nullable;
                CalcFst(prod->Nodes,fst,nullable);
                if(nullable && this->Nullable.count(head)==0)
                {
                    this->Nullable.insert(head);
                    nothingChanged = false;
                }

                size_t  oldSize = this->FST[head].size();
                this->FST[head].insert(fst.begin(),fst.end());
                if(this->FST[head].size() > oldSize)
                {
                    nothingChanged = false;
                }
            }
        }   
    }
    Grammar::Grammar(std::string file)
    {
        std::string content = util::file_to_str(file);

        std::smatch matches;
        std::regex e ("(\\s*\\w+\\s*)\\:(((\\s*\\w+\\s*)+(\\s*\\{.*\\}\\s*)?\\|?)+)\\s*;");   // matches words beginning by "sub"

        std::string content_s = content;
        Production_sp prod = std::make_shared<Production>(SymbolStart);
        this->Productions.push_back(prod);
        while (std::regex_search (content_s,matches,e)) {
            std::string symbol = util::trim(matches[1]);
            std::string prods = util::trim(matches[2]);

            loadProductions(symbol,prods);

            content_s = matches.suffix().str();
        }
        if (this->Productions.size() > 1) {
            prod->Nodes.push_back(this->Productions[1]->Head);
        }

        computeAttributes();
    }
    std::vector<Production*> Grammar::GetProductionsOfHead(std::string head)
    {
        std::vector<Production*> prods;
        for(auto prod:this->Productions)
        {
            if(prod->Head == head)
                prods.push_back(prod.get());
        }
        return prods;
    }
}

