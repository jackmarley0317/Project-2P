/*
 * hash_functions.cpp
 *
 * Author: C. Painter-Wakefield and J. Lovato
 *
 * Some string hashing functions for use in the hashtable assignment.
 *
 * Last modified: 10/17/2022
 */

#ifndef _HASH_FUNCTIONS_H
#define _HASH_FUNCTIONS_H

#include <string>

/***
 * DO NOT put unscoped 'using namespace std;' in header files!
 * Instead put them at the beginning of class or function definitions
 * (as demonstrated below).
 */

class hash0 : std::hash<std::string> {
public:
    size_t operator()(const std::string &);
};

class hash1 : std::hash<std::string> {
public:
    size_t operator()(const std::string &);
};

class hash2 : std::hash<std::string> {
public:
    size_t operator()(const std::string &);
};

class hash3 : std::hash<std::string> {
public:
    size_t operator()(const std::string &);
};

class hash4 : std::hash<std::string> {
public:
    size_t operator()(const std::string &);
};

#endif
