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
	for(unsigned int i = 0; i < input.size(); i++){
		string s = input[i];
		if(i == 0){
			numPeople = atoi(s.c_str());
			assert(numPeople > 0);
			assert(numPeople <= 20);
		}
		else{
			if(numPeople > 0){
				candidates.push_back(s);
				numPeople -= 1;
			}
			else{
				ballots.push_back(s);
			}
		}
	}

	//sort ballots by first vote and find indexes where each first char changes
	//this allows counting of eliminated ballots without searching through whole ballot array
	assert(ballots.size() <= 1000);
	assert(ballots.size() > 0);
	//std::sort(ballots.begin(), ballots.end());
	std::sort(ballots.begin(), ballots.end(), [](const string& a, const string b) {
		std::vector<string> aVec = split(a, ' ');
		std::vector<string> bVec = split(b, ' ');
		int aNum = atoi(aVec[0].c_str());
		int bNum = atoi(bVec[0].c_str());
	  	return aNum< bNum;
	});
	std::vector<unsigned int> indices;
	unsigned int num = 1;
	indices.push_back(0);
	for(unsigned int i = 0; i < ballots.size(); i++){
		string s = ballots[i];
		std::vector<string> nums = split(s, ' ');
		unsigned int tmp = atoi(nums[0].c_str());
		if(tmp != num){
			unsigned int diff = tmp - num;
			if(diff > 1){
				while(diff > 1){
					indices.push_back(i);
					diff--;
					num++;
				}
			}
			indices.push_back(i);
			num++;
		}
	}
	if(indices.size() < candidates.size()){
		while(num <= candidates.size()){
			indices.push_back(ballots.size());
			num++;
		}
	}
	indices.push_back(ballots.size());
	//main loop that determines the winner of the votes
	string answer = "";
	std::vector<int> removed;
	std::vector<int> tempRemoved;
	std::vector<string> tempBallots;
	std::vector<int> voteCounts(candidates.size(), 0);
	while(answer.compare("") == 0){

		//loop through ballots and count votes initially
		if(removed.size() == 0){
			for(unsigned int i = 0; i < ballots.size(); i++){
				string s = ballots[i];
				int voteChar = atoi(s.c_str());
				int voteIndex = voteChar - 1;
				voteCounts[voteIndex] ++;
			}
		}
		//loop through temp ballots and add loser votes to remaining candidates
		else{
			for(unsigned int i = 0; i < tempBallots.size(); i++){
				string s2 = tempBallots[i];
				int voteChar2 = atoi(s2.c_str());
				int voteIndex2 = voteChar2 - 1;
				voteCounts[voteIndex2]++;
			}
		}

			if(removed.size() > 2){
				for(unsigned int g = 0; g < voteCounts.size(); g++){
					answer += std::to_string(voteCounts[g]) + " ";
				}
				break;
			}
		int maxVote = -1;
		int minVote = 1001;
		int majority = ballots.size() / 2;
		//loop to find max, min votes, and in case one voter has a majority, declare the winner.
		for(unsigned int i = 0; i < voteCounts.size(); i++){
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
				for(unsigned int i = 0; i < voteCounts.size(); i++){
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
			for(unsigned int i = 0; i < voteCounts.size(); i++){
				if(voteCounts[i] == minVote){
					removed.push_back(i);
					tempRemoved.push_back(i);
					voteCounts[i] = 0;
				}
			}
			std::vector<int> startIndices;
			std::vector<int> endIndices;
			for(unsigned int i = 0; i < tempRemoved.size(); i++){
				if(indices[tempRemoved[i]] != ballots.size()){
					startIndices.push_back(indices[tempRemoved[i]]);
					endIndices.push_back(indices[tempRemoved[i] + 1]);
				}
			}
			for(unsigned int p = 0; p < startIndices.size(); p++){
				for(int j = startIndices[p]; j < endIndices[p]; j++){
					tempBallots.push_back(ballots[j]);
				}
			}
			for(unsigned int j = 0; j < tempBallots.size(); j++){
				std::vector<string> splitVotes = split(tempBallots[j], ' ');
				int firstVote = atoi(splitVotes[0].c_str());
				for(unsigned int p = 0; p < removed.size(); p++){
					if(firstVote == removed[p] + 1){
						std::vector<string> newVotes;
						for(unsigned int m = 1; m < splitVotes.size(); m++)
							newVotes.push_back(splitVotes[m]);
						string newString = "";
						for(unsigned int l = 0; l < newVotes.size(); l++){
							if(l == 0)
								newString += newVotes[l];
							else
								newString += " " + newVotes[l];
						}
						tempBallots.at(j) = newString;
						j--;
					}
				}
			}
			if(removed.size() > 2){
				for(unsigned int i = 0; i < startIndices.size(); i++){
					answer+= std::to_string(startIndices[i]) + " <- here to here -> " + std::to_string(endIndices[i]) ;
				}
				break;
			}

			tempRemoved.clear();
			startIndices.clear();
			endIndices.clear();
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
    w << answer + "\n" << endl;
    assert(count == numEntries);
}

