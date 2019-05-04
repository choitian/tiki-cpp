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
#include "tools/syntax/grammar/grammar.h"
#include "tools/util/commons.h"
/*
 * 
 */
int main(int argc, char** argv) {
    GRAMMAR *gram = new GRAMMAR("re_grammar.txt");
    for(auto &kv:gram->FST)
    {
        std::cout<<kv.first<<"+++\n";
        
        std::string nodes = util::join_strings(kv.second," ");
        std::cout<<nodes<<"\n";
    }
    return 0;
}

