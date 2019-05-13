/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "State.h"
#include "LookaheadLR.h"
#include "../../util/commons.h"

namespace syntax{
    Item::Item(Production *prod,int dot)
    {
        this->Prod = prod;
        this->Dot = dot;
    }
    std::string Item::HashString(Production *prod,int dot)
    {
        std::string nodes = util::join_strings(prod->Nodes,"+");

        return util::format("%s/%s/%d",prod->Head.c_str(),nodes.c_str(),dot);
    }
    std::string Item::HashString()
    {
        return HashString(this->Prod,this->Dot);
    }
    std::string Item::DotRight()
    {
	if (this->Prod->IsNull()) {
		return "";
	}
	if (this->Dot < this->Prod->Nodes.size()) {
            return this->Prod->Nodes[this->Dot];
	}
	return "";
    }
    bool Item::IsKernel()
    {
	if (this->Prod->IsNull()) {
		return false;
	}
	if (this->Prod->Head == syntax::SymbolStart) {
		return true;
	}
	return this->Dot != 0;
    }
    State::State(LookaheadLR *lalr)
    {
        this->lalr = lalr;
    }
    std::string State::HashString()
    {
        std::vector<std::string> hsList;
        for(auto itemHs:this->Items)
        {
            auto item = this->lalr->GetItem(itemHs);
            hsList.push_back(item->HashString());
        }
        return util::join_strings(hsList,"@");
    }
    std::pair<std::set<std::string>::iterator,bool> State::AddItem(Item *item)
    {
        std::string hs = item->HashString();
        
        return this->Items.insert(hs);
    }
    std::vector<Item*> State::GetKernelItems()
    {
        std::vector<Item*> ks;
        for(auto itemHs:this->Items)
        {
            auto item = this->lalr->GetItem(itemHs);
            if(item->IsKernel())
                ks.push_back(item);
        }
        return ks;
    }
}
