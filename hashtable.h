/*
 * hashtable.h
 *
 * A basic hashtable implementation.  This hashtable uses vectors,
 * rather than linked lists, to implement chaining.
 * 
 * Author: Jack Marley
 */

#include <functional>   // for std::hash
#include <vector>       // for vector 
#include <algorithm>    // for swap

/***
 * DO NOT put unscoped 'using namespace std;' in header files!
 * Instead put them at the beginning of class or function definitions
 * (as demonstrated below).
 */

template <class T, class H = std::hash<T>>
class hashtable {
public:
    // constructor
    hashtable()
    {
        table = std::vector<std::vector<T>>(4); // initialize vector of size four, this is the initial size of table
        numberOfElements = 0; // create number of elements equal to 0 
    }

    // basic hashset operations
    void insert(const T& key)
    {
        if (contains(key) == true) { return; } // if key is located within the contains function, simply return

        numberOfElements = numberOfElements + 1; // increment number of elements 

        if (load_factor() > 0.75) // if load factor > 0.75
        {
            std::vector<std::vector<T>> newTable(table.size() * 2); // create new table with double the size

            // rehash and re-insert into new table 
            for (int i = 0; i < table.size(); i++) // iterate through each bucket (i)
            {
                for (int j = 0; j < table[i].size(); j++) // iterate through each chained value (element) in table 
                {
                    // re-compute the hash table values 
                    int newHashValue = hash(table[i][j]) % newTable.size();

                    // insert key into the appropriate chain in newTable 
                    newTable[newHashValue].push_back(table[i][j]);
                }
            }
            table = newTable; // reassigning table to new table
        }
        // the new table has been creating
        // must now insert new hash values into 
        // the correct bucket
        int hashValue = hash(key) % table.size();
        table[hashValue].push_back(key);
    }

    void remove(const T& key)
    {
        if (contains(key) == false) { return; } // if key not found in table, return

        numberOfElements = numberOfElements - 1; // decrement number of elements 

        int location = hash(key) % table.size(); // find the hash value for the current chain
        std::vector<T>& chain = table[location]; // get chain at the location of the table

        // loop through the entire chain to find the key
        for (int i = 0; i < chain.size(); i++)
        {
            // if found, remove the key
            if (chain[i] == key) // if the chain contains the key
            {
                chain.erase(chain.begin() + i); // remove that key
                break;
            }
        }
    }

    bool contains(const T& key)
    {
        int hashValueOfKey = hash(key) % table.size(); // compute hash value of key

        // check chain at hash value's index
        const std::vector<T>& chain = table[hashValueOfKey];

        // iterate through every occurring chain to check 
        // and see if a key exists
        for (int i = 0; i < chain.size(); i++)
        {
            if (chain[i] == key) // if key exists
            {
                return true;
            }
        }
        return false; // if key is not found
    }

    size_t size() 
    {
        return numberOfElements;
    }

    // diagnostic functions
    double load_factor()
    {
        //double numberOfElements;
        return static_cast<double>(numberOfElements) / table.size();
    }

    // convenience method, invokes the "hash" template parameter
    static size_t hash(const T &key) 
    {
        H h;
        return h(key);
    }

private:
    std::vector<std::vector<T>> table;
    size_t numberOfElements;
};
