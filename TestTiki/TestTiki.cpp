#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "tools/syntax/grammar/grammar.h"
#include "tools/util/commons.h"

void test_GRAMMAR() {
    {
        GRAMMAR *gram = new GRAMMAR("re_grammar.txt");
        for(auto &prod:gram->Productions)
        {
            std::cout<<prod->ToString()<<std::endl;
        }
        REQUIRE(gram->Productions.size() == 15);
        REQUIRE(gram->Nullable.size() == 1);
        for(auto &kv:gram->FST)
        {
            if(kv.first =="exp")
            {
                std::string nodes = util::join_strings(kv.second," ");
                REQUIRE(nodes == "ARRAY CHAR DOT LITERAL LPAREN");
            }
        }
    }
    {
        GRAMMAR *gram = new GRAMMAR("dnf.txt");
        for(auto &prod:gram->Productions)
        {
            std::cout<<prod->ToString()<<std::endl;
        }
        REQUIRE(gram->Productions.size() == 143);
        REQUIRE(gram->Nullable.size() == 4);
        for(auto &kv:gram->FST)
        {
            if(kv.first =="exp")
            {
                std::string nodes = util::join_strings(kv.second," ");
                REQUIRE(nodes == "DEC FALSE FLOATING ID INC INTEGER LPAREN NEW NOT NULL SCOPE_ID STRING SUB TRUE");
            }
            if(kv.first =="ini_exp")
            {
                std::string nodes = util::join_strings(kv.second," ");
                REQUIRE(nodes == "BOOLEAN CHAR COMMA DEC FALSE FLOAT FLOATING ID INC INT INTEGER LPAREN NEW NOT NULL SCOPE_ID STATIC STRING SUB TRUE VOID");
            }
            if(kv.first =="method_definition")
            {
                std::string nodes = util::join_strings(kv.second," ");
                REQUIRE(nodes == "BOOLEAN CHAR FLOAT ID INT SCOPE_ID STATIC VOID");
            }
        }    
    }
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    test_GRAMMAR();
}