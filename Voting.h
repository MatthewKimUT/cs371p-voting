/** @file Voting.h
 *	@brief Contains function definitions
 */

#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair

using namespace std;

// ------------
// voting_answer
// ------------

/**
 * read string vector
 * @param input a string vector
 * @return a string answer, one that answers who wins the ballot
 */
string voting_answer(std::vector<string> input);

// -----
// split
// -----

/**
 * @param s string to split into array
 * @param delim char: the delimiter
 * @return vector of strings from s split by the delimiter
 */
std::vector<std::string> split(const std::string &s, char delim);

// -------------
// voting_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void voting_solve(istream& r, ostream& w);

#endif // Collatz_h
