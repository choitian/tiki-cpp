/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: nur
 * 
 * Created on April 30, 2019, 1:01 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include "tools/syntax/Grammar.h"
#include "tools/syntax/LookaheadLR.h"
#include "util/commons.h"
/*
 * 
 */
int main(int argc, char** argv) {
    
    syntax::Grammar_sp gram = std::make_shared<syntax::Grammar>("re_grammar.txt");;
    syntax::LookaheadLR_sp lalr = std::make_shared<syntax::LookaheadLR>(gram);
    lalr->BuildCanonicalCollection();
    
    std::cout<<"lalr->States.size:   "<< lalr->States.size()<<"\n";
    return 0;
}

