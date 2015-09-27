/** @file TestVoting.c++
 *  @brief Contains unit tests for each method in Voting.c++
 */

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <vector>
#include "gtest/gtest.h"

#include "Voting.h"

using namespace std;

// -----------
// TestCollatz
// -----------

// ----
// voting_answer
// ----

TEST(VotingFixture, voting1){
    std::vector<string> s = {"2","A","B", "1 2", "1 2"};
    string str = voting_answer(s);
    ASSERT_EQ( "A", str);
}

TEST(VotingFixture, voting2){
    std::vector<string> s = {"3","Alpha","Beta", "Charlie", "1 2 3", "2 3 1", "3 1 2"};
    string str = voting_answer(s);
    ASSERT_EQ( "Alpha\nBeta\nCharlie", str);
}

TEST(VotingFixture, voting3){
    std::vector<string> s = {"4","A","B", "C", "D", "1 2 4 3", "1 2 4 3", "2 1 4 3", "2 1 4 3"};
    string str = voting_answer(s);
    ASSERT_EQ( "A\nB", str);
}

TEST(VotingFixture, voting4){
    std::vector<string> s = {"3", "one", "two", "three", "1 2 3", "1 2 3", "1 2 3"};
    string str = voting_answer(s);
    ASSERT_EQ( "one", str);
}

TEST(VotingFixture, voting5){
    std::vector<string> s = {"3", "help", "me", "please", "3 2 1", "1 2 3", "1 2 3"};
    string str = voting_answer(s);
    ASSERT_EQ( "help", str);
}


// -----
// split
// -----
TEST(VotingFixture, split1){
    string s = "one two three four";
    std::vector<string> strs = split(s, ' ');
    std::vector<string> ans {"one", "two", "three", "four"};
    for(unsigned int i = 0; i < strs.size(); i++){
        ASSERT_EQ(strs[i], ans[i]);
    }
}

TEST(VotingFixture, split2){
    string s = "one:two:three four";
    std::vector<string> strs = split(s, ':');
    std::vector<string> ans {"one", "two", "three four"};
    for(unsigned int i = 0; i < strs.size(); i++){
        ASSERT_EQ(strs[i], ans[i]);
    }
}

TEST(VotingFixture, split3){
    string s = "onetwothreefour";
    std::vector<string> strs = split(s, 't');
    std::vector<string> ans {"one", "wo", "hreefour"};
    for(unsigned int i = 0; i < strs.size(); i++){
        ASSERT_EQ(strs[i], ans[i]);
    }
}

// -----
// solve
// -----

TEST(VotingFixture, solve){
    istringstream r("1\n\n2\nA\nB\n1 2\n1 2");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("A\n", w.str());
}

/*
% g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread



% valgrind TestCollatz                                         >  TestCollatz.out 2>&1
% gcov -b Collatz.c++     | grep -A 5 "File 'Collatz.c++'"     >> TestCollatz.out
% gcov -b TestCollatz.c++ | grep -A 5 "File 'TestCollatz.c++'" >> TestCollatz.out



% cat TestCollatz.out
==14225== Memcheck, a memory error detector
==14225== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==14225== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==14225== Command: TestCollatz
==14225==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from Collatz
[ RUN      ] Collatz.read
[       OK ] Collatz.read (31 ms)
[ RUN      ] Collatz.eval_1
[       OK ] Collatz.eval_1 (5 ms)
[ RUN      ] Collatz.eval_2
[       OK ] Collatz.eval_2 (3 ms)
[ RUN      ] Collatz.eval_3
[       OK ] Collatz.eval_3 (3 ms)
[ RUN      ] Collatz.eval_4
[       OK ] Collatz.eval_4 (3 ms)
[ RUN      ] Collatz.print
[       OK ] Collatz.print (17 ms)
[ RUN      ] Collatz.solve
[       OK ] Collatz.solve (10 ms)
[----------] 7 tests from Collatz (88 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test case ran. (132 ms total)
[  PASSED  ] 7 tests.
==14225==
==14225== HEAP SUMMARY:
==14225==     in use at exit: 0 bytes in 0 blocks
==14225==   total heap usage: 495 allocs, 495 frees, 70,302 bytes allocated
==14225==
==14225== All heap blocks were freed -- no leaks are possible
==14225==
==14225== For counts of detected and suppressed errors, rerun with: -v
==14225== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
File 'Collatz.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Collatz.c++.gcov'
File 'TestCollatz.c++'
Lines executed:100.00% of 26
Branches executed:57.14% of 224
Taken at least once:28.57% of 224
Calls executed:54.07% of 209
Creating 'TestCollatz.c++.gcov'
*/
