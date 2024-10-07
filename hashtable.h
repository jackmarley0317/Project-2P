/*
 * hashtable.h
 *
 * A basic hashtable implementation.  This hashtable uses vectors,
 * rather than linked lists, to implement chaining.
 * 
 * Author: <your name here>
 */

#ifndef _HASHTABLE_PROJECT_H
#define _HASHTABLE_PROJECT_H

#include <functional>   // for std::hash

/***
 * DO NOT put unscoped 'using namespace std;' in header files!
 * Instead put them at the beginning of class or function definitions
 * (as demonstrated below).
 */

template <class T, class H = std::hash<T>>
class hashtable {
public:
    // constructor
    hashtable();

    // basic hashset operations
    void insert(const T& key);
    void remove(const T& key);
    bool contains(const T& key);
    size_t size();

    // diagnostic functions
    double load_factor();

    // convenience method, invokes the "hash" template parameter
    // function object to get a hash code
    static size_t hash(const T &key) {
        H h;
        return h(key);
    }

private:
 
};

#endif
