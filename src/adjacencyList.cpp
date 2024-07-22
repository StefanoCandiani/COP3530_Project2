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
        //Think about what member variables you need to initialize
        // Unordered_map storing a link and the links it points to
        unordered_map<string, vector<string>> linksTo;
        // map storing a link and the links pointing to it
        map<string, vector<pair<string,float>>> linksFrom;
        // String version of the page rank for catch testing
        string strVerPR;
        // Count of vertices in graph
        int vCount;

    public:
        //Think about what helper functions you will need in the algorithm

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
            auto iter = linksFrom.begin();
            for(; iter != linksFrom.end(); iter++) {
                for(int i = 0; i < iter -> second.size(); i++) {
                    string from = (iter -> second)[i].first;
                    (iter -> second)[i].second = (1.0/(float)(linksTo[from].size()));
                }
            }
        }

        /// Display each page in the adjacency list and its connections
        void display() {
            cout << "Adjacency list vertex count = " << vCount << endl;
            auto iter = linksFrom.begin();
            for(; iter != linksFrom.end(); iter++) {
                cout << iter -> first << " linked by: ";
                for(int i = 0; i < (iter -> second).size(); i++) {
                    cout << (iter -> second)[i].first << " 1/d_" << (iter -> second)[i].first << " = ";
                    cout << (iter -> second)[i].second << ", ";
                }
                cout << endl;
            }
        }

        /// Page Rank calculation
        void PageRank(int n) {
        // prints the PageRank of all pages after p powerIterations in
        // ascending alphabetical order of webpages and rounding rank to
        // two decimal places

            map<string, float> rank;
            map<string, float> tempRank;
            auto populator = linksFrom.begin();
            for(; populator != linksFrom.end(); populator++) {
                rank[populator -> first] = (1.0f/vCount);
            }

            // Perform multiplication
            float sum = 0.0f;
            string from;
            while(n > 1) {
                auto iter1 = linksFrom.begin();
                for(; iter1 != linksFrom.end(); iter1++){
                    for(pair<string,float> i : iter1 -> second) {
                        sum += i.second * rank[i.first];
                    }
                    tempRank[iter1 -> first] = sum;
                    sum = 0.0f;
                }
                rank = tempRank;
                n--;
            }

            int rankSize = rank.size();
            auto iter2 = rank.begin();
            for(; iter2 != rank.end(); iter2++) {
                stringstream tempStream;
                // ceilf(val * 100) / 100 rounding up method from: https://stackoverflow.com/questions/1343890  (Setprecision wasn't rounding up properly)
                if(rankSize > 1) {
                    tempStream << iter2 -> first << " " << fixed << showpoint << setprecision(3) << /*(ceilf(*/iter2 -> second/* * 100) / 100)*/ << endl;
                } else {
                    tempStream << iter2 -> first << " " << fixed << showpoint << setprecision(3) << /*(ceilf(*/iter2 -> second/* * 100) / 100)*/;
                }
                strVerPR += tempStream.str();
                cout << tempStream.str();
                rankSize--;
            }

        }

        /** Catch Testing Functions **/
        void parseInput(const string input){
            string line = input.substr(0, input.find("\n"));
            int numLines = stoi(line.substr(0, line.find(" ")));
            int numIter = stoi(line.substr(line.find(" ") + 1, line.size() - line.find(" ")));
            int nextLineIndex = line.size() + 1;
            string tempInput = input.substr(nextLineIndex, input.size() - nextLineIndex);
            string from, to;
            while(numLines > 0) {
                // cout << nextLineIndex << " " << tempInput.find("\n") << endl;
                if(input.size() > nextLineIndex) {
                    tempInput = input.substr(nextLineIndex, input.size() - nextLineIndex);
                    line = input.substr(nextLineIndex, tempInput.find("\n"));
                    from = line.substr(0, line.find(" "));
                    to = line.substr(line.find(" ") + 1, line.size() - line.find(" "));
                    nextLineIndex += line.size() + 1;
                    numLines--;
                    this -> insert(from, to);
                }
            }
            this -> calculateOutdegrees();
            // Restrict printing from cout, link: https://stackoverflow.com/questions/30184998
            cout.setstate(ios_base::failbit);
            this -> PageRank(numIter);
            cout.clear();

        }

        string getStringRepresentation() {
            return strVerPR;
        }

};
