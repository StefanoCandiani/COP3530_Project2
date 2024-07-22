//
// Created by Stefano Candiani on 7/16/24.
//

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

class AdjacencyList {

    private:

        /// Variable initialization
        // Unordered_map storing a link and the links it points to
        unordered_map<string, vector<string>> linksTo;
        // map storing a link and the links pointing to it
        map<string, vector<pair<string,float>>> linksFrom;
        // String version of the page rank for catch testing
        string strVerPR;
        // Count of vertices in graph
        int vCount;

    public:

        /// Default constructor
        AdjacencyList() {
            vCount = 0;
        }

        /// Insert function for the adjacency list
        void insert(const string& from, const string& to) {
            // Regular insert for which websites link to it
            if(linksFrom.find(to) == linksFrom.end()) { vCount++; }
            linksFrom[to].emplace_back(from, 0.0f);
            linksTo[from].push_back(to);
            // Add from link in case no website links to it (empty vector)
            if(linksFrom.find(from) == linksFrom.end()) {
                vector<pair<string, float>> tempVec;
                linksFrom[from] = tempVec;
                vCount++;
            }
        }

        /// Calculates the 1/d_x for each of the links
        void calculateOutdegrees() {
            // Iterate through the linksFrom map
            auto iter = linksFrom.begin();
            for(; iter != linksFrom.end(); iter++) {
                // Iterate through the links that link to the current link
                for(int i = 0; i < iter -> second.size(); i++) {
                    // Calculate the 1/outdegree of each link using the linksTo unordered_map
                    string from = (iter -> second)[i].first;
                    (iter -> second)[i].second = (1.0/(float)(linksTo[from].size()));
                }
            }
        }

        /// Display each page in the adjacency list and its connections
        void display() {
            // Print number of vertices
            cout << "Adjacency list vertex count = " << vCount << endl;
            // Iterate through linksFrom map
            auto iter = linksFrom.begin();
            for(; iter != linksFrom.end(); iter++) {
                // Print the current link
                cout << iter -> first << " linked by: ";
                // Iterate through the links that point to the current link
                for(int i = 0; i < (iter -> second).size(); i++) {
                    // Print the link and the 1/outdegree of each of the links
                    cout << (iter -> second)[i].first << " 1/d_" << (iter -> second)[i].first << " = ";
                    cout << (iter -> second)[i].second << ", ";
                }
                // Buffer
                cout << endl;
            }
        }

        /// Page Rank calculation
        void PageRank(int n) {
        // prints the PageRank of all pages after p powerIterations in
        // ascending alphabetical order of webpages and rounding rank to
        // two decimal places

            // Initialize the rank and tempRank maps
            map<string, float> rank;
            map<string, float> tempRank;

            // Populate the rank map with the initial rank of each link (1/numberOfVertices)
            auto populator = linksFrom.begin();
            for(; populator != linksFrom.end(); populator++) {
                rank[populator -> first] = (1.0f/vCount);
            }

            // Perform multiplication n - 1 times
            float sum = 0.0f;
            string from;
            while(n > 1) {
                // Iterate through linksFrom map
                auto iter1 = linksFrom.begin();
                for(; iter1 != linksFrom.end(); iter1++){
                    // Iterate through the links that point to the current link
                    for(pair<string,float> i : iter1 -> second) {
                        // Multiply the (1/outdegree) by the rank at the given link and add to sum
                        sum += i.second * rank[i.first];
                    }
                    // Apply the sum to the rank at the given link for tempRank. Done to ensure that the edge list
                    // multiplication is not affected by changes to rank
                    tempRank[iter1 -> first] = sum;
                    // Reset the sum
                    sum = 0.0f;
                }
                // Apply tempRank to rank to ensure future power iterations are based on the new rank
                rank = tempRank;
                // Decrease the number of power iterations
                n--;
            }

            // Manage string representation storage for catch testing and the printing of the map
            int rankSize = rank.size();
            // Iterate through rank map
            auto iter2 = rank.begin();
            for(; iter2 != rank.end(); iter2++) {
                // Use string streams to apply setprecision
                stringstream tempStream;
                // Apply an endl if current link rank is not the last one and no endl if it is the last one (done for
                // proper string parsing for catch tests)
                if(rankSize > 1) {
                    tempStream << iter2 -> first << " " << fixed << showpoint << setprecision(2) << iter2 -> second << endl;
                } else {
                    tempStream << iter2 -> first << " " << fixed << showpoint << setprecision(2) << iter2 -> second;
                }
                strVerPR += tempStream.str();
                // Printing for main.cpp
                cout << tempStream.str();
                // Decrease rank size count
                rankSize--;
            }

        }

        /** Catch Testing Functions **/

        /// String version of output getter
        string getStringRepresentation() { return strVerPR; }

};
