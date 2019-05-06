/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   commons.h
 * Author: nur
 *
 * Created on May 1, 2019, 10:37 PM
 */

#ifndef COMMONS_H
#define COMMONS_H

#include <memory>
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <set>

namespace util
{
    template<typename ... Args>
    std::string format( const std::string& format, Args ... args )
    {
        size_t size = snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
        std::unique_ptr<char[]> buf( new char[ size ] ); 
        snprintf( buf.get(), size, format.c_str(), args ... );
        return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
    }
    
    std::string join_strings(std::vector<std::string> &vs,std::string sep);
    std::string join_strings(std::set<std::string> &vs,std::string sep);
    std::string file_to_str(std::string file);
    std::string trim(const std::string &s);
    std::vector<std::string> split(std::string const &input);
}

#endif /* COMMONS_H */

