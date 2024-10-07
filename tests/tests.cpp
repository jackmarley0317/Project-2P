/*
 * Authors: Joey Lovato & C. Painter Wakefield
 *
 * Tests for the hashtable assignment
 * 
 * Last modified: 10/17/2022
 */

#include <vector>

#include "gtest/gtest.h"
#include "tests-setup.h"

#include "hashtable.h"

#include "header-sans-using-namespace.h"
#include "sneaky-project-requirements.h"     // look for project-requirement circumvention
											 
using namespace std;

// a bad hash function class to test collisions
class bad_hash : hash<string> {
public:
    size_t operator()(const string&) { return 29; }
};

TEST_F(HashtableTest, Empty) {
    hashtable<string> h;
    ASSERT_FALSE(h.contains("apple"));
    ASSERT_EQ(h.size(), 0);
}

TEST_F(HashtableTest, StringInsertRemoveOnce) {
    hashtable<string> h;
    h.insert("apple");
    ASSERT_TRUE(h.contains("apple"));
    ASSERT_EQ(h.size(), 1);
    h.remove("apple");
    ASSERT_FALSE(h.contains("apple"));
    ASSERT_EQ(h.size(), 0);
}

TEST_F(HashtableTest, IntInsertRemoveOnce) {
    hashtable<int> h;
    h.insert(17);
    ASSERT_TRUE(h.contains(17));
    ASSERT_EQ(h.size(), 1);
    h.remove(17);
    ASSERT_FALSE(h.contains(17));
    ASSERT_EQ(h.size(), 0);
}

TEST_F(HashtableTest, InsertTwiceRemoveOnce) {
    hashtable<string> h;
    h.insert("apple");
    h.insert("apple");
    ASSERT_TRUE(h.contains("apple"));
    ASSERT_EQ(h.size(), 1);
    h.remove("apple");
    ASSERT_FALSE(h.contains("apple"));
    ASSERT_EQ(h.size(), 0);
}

TEST_F(HashtableTest, InsertOnceRemoveTwice) {
    hashtable<string> h;
    h.insert("apple");
    ASSERT_TRUE(h.contains("apple"));
    ASSERT_EQ(h.size(), 1);
    h.remove("apple");
    h.remove("apple");
    ASSERT_FALSE(h.contains("apple"));
    ASSERT_EQ(h.size(), 0);
}

TEST_F(HashtableTest, InsertRemoveMany) {
    hashtable<string> h;
    for (size_t i = 0; i < 1000; i++) {
        h.insert(words[i]);
    }

    for (size_t i = 0; i < 1000; i++) {
        ASSERT_TRUE(h.contains(words[i]));
    }

    for (size_t i = 0; i < 1000; i += 2) {
        h.remove(words[i]);
    }

    for (size_t i = 0; i < 1000; i += 2) {
        ASSERT_FALSE(h.contains(words[i]));
    }

    for (size_t i = 1; i < 1000; i += 2) {
        ASSERT_TRUE(h.contains(words[i]));
    }

    for (size_t i = 0; i < 1000; i += 2) {
        h.insert(words[i]);
    }

    for (size_t i = 0; i < 1000; i++) {
        ASSERT_TRUE(h.contains(words[i]));
    }

    for (size_t i = 1; i < 1000; i += 2) {
        h.remove(words[i]);
    }

    for (size_t i = 1; i < 1000; i += 2) {
        ASSERT_FALSE(h.contains(words[i]));
    }

    for (size_t i = 0; i < 1000; i += 2) {
        ASSERT_TRUE(h.contains(words[i]));
    }
}

TEST_F(HashtableTest, CollisionTest) {
    hashtable<string, bad_hash> h;
    for (size_t i = 0; i < 100; i++) {
        h.insert(words[i]);
    }

    for (size_t i = 0; i < 100; i++) {
        ASSERT_TRUE(h.contains(words[i]));
    }

    for (size_t i = 0; i < 100; i += 2) {
        h.remove(words[i]);
    }

    for (size_t i = 0; i < 100; i += 2) {
        ASSERT_FALSE(h.contains(words[i]));
    }

    for (size_t i = 1; i < 100; i += 2) {
        ASSERT_TRUE(h.contains(words[i]));
    }

    for (size_t i = 0; i < 100; i += 2) {
        h.insert(words[i]);
    }

    for (size_t i = 0; i < 100; i++) {
        ASSERT_TRUE(h.contains(words[i]));
    }

    for (size_t i = 1; i < 100; i += 2) {
        h.remove(words[i]);
    }

    for (size_t i = 1; i < 100; i += 2) {
        ASSERT_FALSE(h.contains(words[i]));
    }

    for (size_t i = 0; i < 100; i += 2) {
        ASSERT_TRUE(h.contains(words[i]));
    }
}

TEST_F(HashtableTest, LoadFactorTest) {
    hashtable<string> h;

    // insert some to get the load factor up
    for (size_t i = 0; i < 100; i++) {
        h.insert(words[i]);
        ASSERT_LT(h.load_factor(), 0.76);
    }

    for (size_t i = 0; i < 1000; i++) {
        h.insert(words[i]);
        ASSERT_LT(h.load_factor(), 0.76);   // shouldn't be too full
        ASSERT_GT(h.load_factor(), 0.3);    // shouldn't be too empty, either
    }
}

TEST_F(HashtableTest, LargeTest) {
    hashtable<string> h;
    for (string &s: words) {
        h.insert(s);
    }
    ASSERT_EQ(h.size(), words.size());

    for (string &s: words) {
        ASSERT_TRUE(h.contains(s));
    }

    for (string &s: words) {
        h.remove(s);
    }
    ASSERT_EQ(h.size(), 0);

    for (string &s: words) {
        ASSERT_FALSE(h.contains(s));
    }
}
