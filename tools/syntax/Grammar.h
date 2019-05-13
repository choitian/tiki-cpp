/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   grammar.h
 * Author: nur
 *
 * Created on May 1, 2019, 10:10 PM
 */

#ifndef GRAMMAR_H
#define GRAMMAR_H
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

namespace syntax{

    const std::string SymbolStart  = "__START__";
    const std::string SymbolEnd  = "__END__";
    const std::string SymbolNull  = "__NULL__";

    class Production;
    typedef std::shared_ptr<Production> Production_sp;
    class Production
    {
    public:
        Production(std::string head);
        std::string Head;
        std::vector<std::string> Nodes;
        std::string Script;
        int Id; 

        std::string ToString();
        bool IsNull();
    };

    class Grammar;
    typedef std::shared_ptr<Grammar> Grammar_sp;
    class Grammar
    {
        void loadProductions(std::string &symbol,std::string &prods);
        void CalcFst(std::vector<std::string> &symbols,std::set<std::string> &fst, bool &nullable);
        void computeAttributes();
    public:
        std::vector<Production_sp> Productions;
        std::map<std::string,std::set<std::string>> FST;
        std::map<std::string,bool> IsTerminal;
        std::set<std::string> Nullable;

        Grammar(std::string file);
        std::vector<Production*> GetProductionsOfHead(std::string head);
    };
    
}
#endif /* GRAMMAR_H */

