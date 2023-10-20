
#include "algorithm.h"
#include <queue>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  UC with Strict Expanded List
//
// Move Generator:
//
////////////////////////////////////////////////////////////////////////////////////////////
string uc_explist(string const initialState, string const goalState, int& pathLength, int& numOfStateExpansions, int& maxQLength,
    float& actualRunningTime, int& numOfDeletionsFromMiddleOfHeap, int& numOfLocalLoopsAvoided, int& numOfAttemptedNodeReExpansions) {

    string path = "";
    clock_t startTime;

    numOfDeletionsFromMiddleOfHeap = 0;
    numOfLocalLoopsAvoided = 0;
    numOfAttemptedNodeReExpansions = 0;

    actualRunningTime = 0.0;
    startTime = clock();

    

    return path;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  A* with the Strict Expanded List
//
// Move Generator:
//
////////////////////////////////////////////////////////////////////////////////////////////
string aStar_ExpandedList(string const initialState, string const goalState, int& pathLength, int& numOfStateExpansions, int& maxQLength,
                          float& actualRunningTime, int& numOfDeletionsFromMiddleOfHeap, int& numOfLocalLoopsAvoided, int& numOfAttemptedNodeReExpansions, heuristicFunction heuristic) {

    string path;
    clock_t startTime;

    numOfDeletionsFromMiddleOfHeap = 0;
    numOfLocalLoopsAvoided = 0;
    numOfAttemptedNodeReExpansions = 0;

    actualRunningTime = 0.0;
    startTime = clock();

    Puzzle initialPuzzle(initialState, goalState);
    initialPuzzle.updateHCost(heuristic);
    initialPuzzle.updateFCost();

    vector<Puzzle> Q;
    unordered_map<string, Puzzle> expandedList;
    unordered_map<string, Puzzle> statesInQ;

    // Use a priority queue with custom comparator for A*.
    priority_queue<Puzzle, vector<Puzzle>, Puzzle::PuzzleComparator> pq;
    pq.push(initialPuzzle);

    statesInQ.emplace(initialPuzzle.getString(), initialPuzzle);

    while (!pq.empty()) {
        if (pq.size() > maxQLength) {
            maxQLength = pq.size();
        }

        Puzzle searchNode = pq.top();
        pq.pop();
        statesInQ.erase(searchNode.getString());

        if (searchNode.getString() == goalState) {
            path = searchNode.getPath();
            break;
        }

        numOfStateExpansions++;

        // Define your movement logic based on the specified order (Up, Right, Down, Left).
        // For each movement direction, create a new puzzle state, calculate costs, and handle duplicates.
        // You can use a loop or write separate code for each direction.

        // Example for moving Up:
        if (searchNode.canMoveUp()) {
            Puzzle* upSearchNode = searchNode.moveUp();
            auto search = expandedList.find(upSearchNode->getString());
            auto search2 = statesInQ.find(upSearchNode->getString());

            if (search == expandedList.end()) {
                if (search2 == statesInQ.end()) {
                    upSearchNode->updateHCost(heuristic);
                    upSearchNode->updateFCost();
                    pq.push(*upSearchNode);
                    statesInQ.emplace(upSearchNode->getString(), *upSearchNode);
                }
            }
            
        }

        // Example for moving Right:
        if (searchNode.canMoveRight()) {
            Puzzle* rightSearchNode = searchNode.moveRight();
            auto search = expandedList.find(rightSearchNode->getString());
            auto search2 = statesInQ.find(rightSearchNode->getString());

            if (search == expandedList.end()) {
                if (search2 == statesInQ.end()) {
                    rightSearchNode->updateHCost(heuristic);
                    rightSearchNode->updateFCost();
                    pq.push(*rightSearchNode);
                    statesInQ.emplace(rightSearchNode->getString(), *rightSearchNode);
                }
            }
        }

// Repeat the above logic for moving Down:
        if (searchNode.canMoveDown()) {
            Puzzle* downSearchNode = searchNode.moveDown();
            auto search = expandedList.find(downSearchNode->getString());
            auto search2 = statesInQ.find(downSearchNode->getString());

            if (search == expandedList.end()) {
                if (search2 == statesInQ.end()) {
                    downSearchNode->updateHCost(heuristic);
                    downSearchNode->updateFCost();
                    pq.push(*downSearchNode);
                    statesInQ.emplace(downSearchNode->getString(), *downSearchNode);
                }
            }
        }

// Repeat the above logic for moving Left:
        if (searchNode.canMoveLeft()) {
            Puzzle* leftSearchNode = searchNode.moveLeft();
            auto search = expandedList.find(leftSearchNode->getString());
            auto search2 = statesInQ.find(leftSearchNode->getString());

            if (search == expandedList.end()) {
                if (search2 == statesInQ.end()) {
                    leftSearchNode->updateHCost(heuristic);
                    leftSearchNode->updateFCost();
                    pq.push(*leftSearchNode);
                    statesInQ.emplace(leftSearchNode->getString(), *leftSearchNode);
                }
            }
        }

        expandedList.emplace(searchNode.getString(), searchNode);
    }

    actualRunningTime = ((float)(clock() - startTime) / CLOCKS_PER_SEC);
    pathLength = path.size();
    return path;
}