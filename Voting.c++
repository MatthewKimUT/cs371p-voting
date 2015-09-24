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

string voting_answer(std::vector<string> input){
	int numPeople = 0;
	std::vector<string> candidates;
	std::vector<string> ballots;

	//read string input and determine number of people, who candidates are, and initialize array of ballots
	for(std::vector<string>::iterator it = input.begin(); it != input.end(); it++){
		string s = *it;
		s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
		if(it == input.begin()){
			numPeople = atoi(s.c_str());
			assert(numPeople > 0);
			assert(numPeople <= 20);
		}
		else{
			if(numPeople > 0){
				candidates.push_back(s)
				numPeople -= 1;
			}
			else{
				ballots.push_back(s)
			}
		}
	}

	//sort ballots by first vote and find indexes where each first char changes
	//this allows counting of eliminated ballots without searching through whole ballot array
	assert(ballots.size() <= 1000);
	assert(ballots.size() > 0);
	std::sort(ballots.begin(), ballots.end());
	std::vector<int> indices;
	int num = 1;
	indices.push_back(0);
	for(int i = 0; i < ballots.size(); i++){
		string s = *it;
		int tmp = atoi(s.c_str());
		if(tmp != num){
			indices.push_back(i);
			num++;
		}
	}
	assert(indices.size() == candidates.size());
	indices.push_back(ballots.size());
	//main loop that determines the winner of the votes
	string answer = "";
	std::vector<int> removed;
	std:vector<int> voteCounts(candidates.size(), 0);
	while(answer.compare("") == 0){

		//loop through ballots and count votes initially
		if(removed.size() == 0){
			for(int i = 0; i < ballots.size(); i++){
				string s = ballots[i];
				int voteChar = atoi(s.c_str());
				int voteIndex = voteChar - 1;
				votecounts[voteIndex] ++;
			}
		}
		//loop through ballots and add loser votes to remaining candidates
		else{
			std::vector<int> startIndices;
			std::vector<int> endIndices;
			for(int i = 0; i < removed.size(); i++){
				startIndices.push_back(indices[removed[i]]);
				endIndices.push_back(indices[removed[i] + 1]);
			}
			for(int i = 0; i < startIndices.size(); i++){
				for(int j = startIndices[i]; j < endIndices[i]; j++){
					int voteChar = 0;
					int voteIndex = -1;
					vector<string> tokens = split(ballots[j], ' ');
					int tempNum = 1;
					int tempChar = atoi(tokens[tempNum].c_str());
					while(voteChar == 0){
						bool removed = false;
						for(int k = 0; k < removed.size(); k++){
							if(removed[k] == tempChar ){
								tempNum++;
								tempChar = atoi(tokens[tempNum].c_str()); 
								removed = true;
							}
						}
						if(!removed){
							voteChar = tempChar;
							voteIndex = voteChar - 1;
							voteCounts[voteIndex] ++;
						}
					}
				}
			}

		}
		int maxVote = -1;
		int minVote = 1001;
		int majority = candidates.size() / 2;
		int majWinIndex = -1;
		//loop to find max, min votes, and in case one voter has a majority, declare the winner.
		for(int i = 0; i < voteCounts.size(); i++){
			int votes = voteCounts[i]
			if(votes > maxVote)
				maxVote = voteCounts[i];
			if(votes < minVote)
				minVote = voteCounts[i];
			if(votes > majority){
				answer += candidates[i];
				break;
			}
		}
		//Tied winners
		if(minVote == maxVote){
			for(int i = 0; i < voteCounts.size(); i++){
				if(voteCounts[i] == maxVote){
					answer += candidates[i] + "\n"
				}
			}
			answer += "\n";
		}
		//find tied losers, if any, put them in removed vector, and set their votes to zero
		else{
			for(int i = 0; i < voteCounts.size(); i++){
				if(voteCounts[i] == minVote){
					removed.push_back(i + 1);
					voteCounts[i] = 0;
				}
			}
		}


	}
	assert(answer.compare("") != 0);
	return answer;
}

// -----
// split
// -----

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
    getline(r, s);
    count = 0;
    while (getline(r, s)){
    	if(atoi(s.c_str()) > 0){
    		count++;
    		std::vector<string> lines;
    		while(getline(r, s) && s != "\n"){
    			lines.push_back(s);
    		}
    		string answer = voting_answer(lines);
    		w << answer << endl;
    	}
    }
    assert(count == numEntries);
}

