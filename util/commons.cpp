/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iterator>
#include <sstream>
#include <ostream>
#include <algorithm>
#include <numeric>
#include <fstream>
#include "commons.h"

namespace util{
    
    std::string join_strings(std::vector<std::string> &vs,std::string sep)
    {
        return std::accumulate(std::begin(vs), std::end(vs), std::string(),
                    [&sep](const std::string &str0, const std::string &str1)
                    {
                        return str0.empty() ? str1 : str0 + sep + str1;
                    });        
    }  
    std::string join_strings(std::set<std::string> &vs,std::string sep)
    {
        return std::accumulate(std::begin(vs), std::end(vs), std::string(),
                    [&sep](const std::string &str0, const std::string &str1)
                    {
                        return str0.empty() ? str1 : str0 + sep + str1;
                    }); 
    }  
    std::string file_to_str(std::string file)
    {
        std::ifstream in(file);
        std::string text((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());     
        return text;
    }
    std::string trim(const std::string &s)
    {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && isspace(*it))
            it++;

        std::string::const_reverse_iterator rit = s.rbegin();
        while (rit.base() != it && isspace(*rit))
            rit++;

        return std::string(it, rit.base());
    }
    std::vector<std::string> split(std::string const &input) { 
        std::istringstream buffer(input);
        std::vector<std::string> ret((std::istream_iterator<std::string>(buffer)), 
                                     std::istream_iterator<std::string>());
        return ret;
    }
}