/** @file Voting.c++
 *  @brief Contains function implementations for Collatz project
 */

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include "Voting.h"
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

// -------------
// voting_answer
// -------------

string voting_answer(std::vector<string> &input){
	int numPeople = atoi(input[0].c_str());
	int numBallots = 0;
	assert(numPeople > 0);
	assert(numPeople <= 20);
	std::vector<string> candidates;
	std::vector<vector<string>> ballots (numPeople, std::vector<string>(0));

	//read string input and determine number of people, who candidates are, and initialize array of ballots
	for(unsigned int i = 1; i < input.size(); i++){
		string s = input[i];
		if(numPeople > 0){
			candidates.push_back(s);
			numPeople -= 1;
		}
		else{
			int firstNum = atoi(s.c_str());
			ballots[firstNum - 1].push_back(s);
			numBallots++;
		}
	}

	//main loop that determines the winner of the votes
	string answer = "";
	std::vector<int> removed;
	std::vector<int> tempRemoved;
	std::vector<int> voteCounts;
	int majority = numBallots / 2;
	int maxVote;
	int minVote;
	while(answer.compare("") == 0){
		for(size_t i = 0 ; i < ballots.size(); i ++){
			voteCounts.push_back(ballots[i].size());
		}
		maxVote = -1;
		minVote = 1001;
		//loop to find max, min votes, and in case one voter has a majority, declare the winner.
		for(size_t i = 0; i < voteCounts.size(); i++){
			int votes = voteCounts[i];
			if(votes > maxVote)
				maxVote = voteCounts[i];
			if(votes < minVote && votes != 0)
				minVote = voteCounts[i];
			if(votes > majority){
				answer += candidates[i];
			}
		}
		//Tied winners
		if(minVote == maxVote){
			if(answer.compare("") == 0){
				for(size_t i = 0; i < voteCounts.size(); i++){
					if(voteCounts[i] == maxVote){
						if(answer.compare("") == 0)
							answer += candidates[i];
						else
							answer += "\n" + candidates[i];
					}
				}
			}
		}
		//find tied losers, if any, put them in removed vector, and set their votes to zero, then push ballots to recount to tempBallots
		else{
			for(size_t i = 0; i < voteCounts.size(); i++){
				if(voteCounts[i] == minVote){
					removed.push_back(i);
					tempRemoved.push_back(i);
				}
			}
			for(size_t i = 0; i < tempRemoved.size(); i++){
				std::vector<string> &removalVotes = ballots[tempRemoved[i]];
				for(size_t j = 0; j < removalVotes.size(); j++){
					string line = removalVotes[j];
					int oldNum = atoi(line.c_str());
					for(size_t k = 0; k < removed.size(); k++){
						if(oldNum == (removed[k] + 1)){
							std::vector<string> lineToCut = split(line, ' ');
							string newLine = "";
							for(size_t l = 1; l < lineToCut.size(); l++){
								if(newLine.compare("") == 0)
									newLine += lineToCut[l];
								else
									newLine += " " + lineToCut[l];
							}
							removalVotes[j] = newLine;
							--j;
							break;
						}
					}
				}
			}
			for(size_t i = 0; i < tempRemoved.size(); i++){
				std::vector<string> removalVotes = ballots[tempRemoved[i]];
				for(size_t j = 0; j < removalVotes.size(); j++){
					string line = removalVotes[j];
					int first = atoi(line.c_str());
					ballots[first - 1].push_back(line);
				}
			}
			for(size_t i = 0; i < tempRemoved.size(); i++){
				ballots[tempRemoved[i]].clear();
			}
			tempRemoved.clear();
			voteCounts.clear();
		}
	}
	assert(answer.compare("") != 0);
	return answer;
}

// -----
// split
// -----
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}


// -------------
// voting_solve
// -------------

void voting_solve(istream& r, ostream& w){
    string s;
    getline(r, s);
    int numEntries = atoi(s.c_str());
    assert(numEntries > 0);
    int count = 1;
    bool newEntry = false;
    getline(r, s);
	std::vector<string> lines;
    while (getline(r, s)){
    	if (s.empty()){
    		newEntry = true;
    		string answer = voting_answer(lines);
    		w << answer + "\n" << endl;
    		lines.clear();
    	}
    	else{
    		if(newEntry){
    			newEntry = false;
    			count++;
    		}
    		lines.push_back(s);
    	}
    }
    string answer = voting_answer(lines);
    w << answer << endl;
    assert(count == numEntries);
}

