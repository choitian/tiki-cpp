#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "tools/syntax/Grammar.h"
#include "util/commons.h"
#include "tools/syntax/LookaheadLR.h"

void Test_BuildCanonicalCollection() {
    {
        syntax::Grammar_sp gram = std::make_shared<syntax::Grammar>("re_grammar.txt");
        syntax::LookaheadLR_sp lalr = std::make_shared<syntax::LookaheadLR>(gram);
        lalr->BuildCanonicalCollection();
        REQUIRE(lalr->States.size() == 19);
        
        int kernelSum = 0;
        int gotoSum = 0;
        for(auto state:lalr->States)
        {
            kernelSum +=state.second->GetKernelItems().size();
            gotoSum +=state.second->GotoTable.size();
        }
        REQUIRE(kernelSum == 24);
        REQUIRE(gotoSum == 42);
    }
    {
        syntax::Grammar_sp gram = std::make_shared<syntax::Grammar>("dnf.txt");
        syntax::LookaheadLR_sp lalr = std::make_shared<syntax::LookaheadLR>(gram);
        lalr->BuildCanonicalCollection();
        REQUIRE(lalr->States.size() == 245);
        
        int kernelSum = 0;
        int gotoSum = 0;
        for(auto state:lalr->States)
        {
            kernelSum +=state.second->GetKernelItems().size();
            gotoSum +=state.second->GotoTable.size();
        }
        REQUIRE(kernelSum == 374);
        REQUIRE(gotoSum == 1511);
    }
}
void test_Grammar() {
    {
        syntax::Grammar_sp gram = std::make_shared<syntax::Grammar>("re_grammar.txt");
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
        syntax::Grammar_sp gram = std::make_shared<syntax::Grammar>("dnf.txt");
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
    test_Grammar();
    Test_BuildCanonicalCollection();
}