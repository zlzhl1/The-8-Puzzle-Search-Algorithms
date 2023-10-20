
#include "puzzle.h"
#include <queue>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

string uc_explist(string const initialState, string const goalState, int& pathLength, int& numOfStateExpansions, int& maxQLength,
    float& actualRunningTime, int& numOfDeletionsFromMiddleOfHeap, int& numOfLocalLoopsAvoided, int& numOfAttemptedNodeReExpansions) {

    string path = "";
    clock_t startTime;

    numOfDeletionsFromMiddleOfHeap = 0;
    numOfLocalLoopsAvoided = 0;
    numOfAttemptedNodeReExpansions = 0;

    actualRunningTime = 0.0;
    startTime = clock();

    Puzzle initialPuzzle(initialState, goalState);

    priority_queue<Puzzle, vector<Puzzle>, Puzzle::PuzzleComparator> priorityQueue;
    unordered_set<string> expandedStates;

    priorityQueue.push(initialPuzzle);

    while (!priorityQueue.empty()) {
        const Puzzle currentPuzzle = priorityQueue.top(); 
        priorityQueue.pop();

        if (currentPuzzle.goalMatch()) {
            path = currentPuzzle.getPath();
            pathLength = path.size();
            break;
        }

        string currentStateString = currentPuzzle.getString();

        if (expandedStates.find(currentStateString) != expandedStates.end()) {
            numOfLocalLoopsAvoided++;
            continue;
        }

        expandedStates.insert(currentStateString);
        numOfStateExpansions++;

        vector<Puzzle*> nextPuzzles;
        if (currentPuzzle.canMoveUp()) {
            nextPuzzles.push_back(currentPuzzle.moveUp());
        }
        if (currentPuzzle.canMoveRight()) {
            nextPuzzles.push_back(currentPuzzle.moveRight());
        }
        if (currentPuzzle.canMoveDown()) {
            nextPuzzles.push_back(currentPuzzle.moveDown());
        }
        if (currentPuzzle.canMoveLeft()) {
            nextPuzzles.push_back(currentPuzzle.moveLeft());
        }

        for (Puzzle* nextPuzzle : nextPuzzles) {
            string nextStateString = nextPuzzle->getString();

            if (expandedStates.find(nextStateString) == expandedStates.end()) {
                priorityQueue.push(*nextPuzzle);
            } else {
                const Puzzle existingPuzzle = priorityQueue.top(); // 注意这里改成 const
                if (nextPuzzle->getFCost() < existingPuzzle.getFCost()) {
                    // 更新堆顶的状态，因为它的fCost更小
                    priorityQueue.pop();
                    priorityQueue.push(*nextPuzzle);
                    numOfAttemptedNodeReExpansions++;
                }
                delete nextPuzzle;
            }
        }
    }

    actualRunningTime = ((float)(clock() - startTime) / CLOCKS_PER_SEC);
    maxQLength = priorityQueue.size();

    return path;
}


///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  A* with the Strict Expanded List
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string aStar_ExpandedList(string const initialState, string const goalState, int& pathLength, int &numOfStateExpansions, int& maxQLength,
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions, heuristicFunction heuristic){
											 
   string path;
   clock_t startTime;
   
   numOfDeletionsFromMiddleOfHeap=0;
   numOfLocalLoopsAvoided=0;
   numOfAttemptedNodeReExpansions=0;


    // cout << "------------------------------" << endl;
    // cout << "<<aStar_ExpandedList>>" << endl;
    // cout << "------------------------------" << endl;
	actualRunningTime=0.0;	
	startTime = clock();
	srand(time(NULL)); //RANDOM NUMBER GENERATOR - ONLY FOR THIS DEMO.  YOU REALLY DON'T NEED THIS! DISABLE THIS STATEMENT.
	maxQLength= rand() % 200; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY.
	numOfStateExpansions = rand() % 200; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY


	
	
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	path = "DDRRLLLUUURDLUDURDLUU"; //this is just a dummy path for testing the function
	pathLength = path.size();
	return path;		
		
}

