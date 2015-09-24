/** @file RunVoting.c++
 *	@brief Contains main method for testing with I/O
 */

// --------
// includes
// --------

#include <iostream> // cin, cout

#include "Voting.h"

// ----
// main
// ----

int main () {
    using namespace std;
    voting_solve(cin, cout);
    return 0;}

/*
% g++ -pedantic -std=c++11 -Wall Voting.c++ RunVoting.c++ -o RunVoting



% cat RunVoting.in
1 10
100 200
201 210
900 1000



% RunVoting < RunVoting.in > RunVoting.out



% cat RunVoting.out
1 10 1
100 200 1
201 210 1
900 1000 1



% doxygen -g
// That creates the file Doxyfile.
// Make the following edits to Doxyfile.
// EXTRACT_ALL            = YES
// EXTRACT_PRIVATE        = YES
// EXTRACT_STATIC         = YES



% doxygen Doxyfile
// That creates the directory html/.
*/
