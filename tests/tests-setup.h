/*
 * Tests for the hashtable assignment
 */

#ifndef HASHTABLE_TESTS_SETUP_H
#define HASHTABLE_TESTS_SETUP_H

#include <string>
#include <vector>

#include "gtest/gtest.h"

// fixture to set up unique random word vector for use in large testswords.size()
class HashtableTest: public ::testing::Test {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static std::vector<std::string> words;
};


#endif
