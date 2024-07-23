 #include <iostream>
 #include "adjacencyList.cpp"
 using namespace std;

 int main() {

     int no_of_lines, power_iterations;
     AdjacencyList Alist;
     string from, to;

     cin >> no_of_lines;
     cin >> power_iterations;

     for(int i = 0; i < no_of_lines; i++) {
         cin >> from;
         cin >> to;
         Alist.insert(from, to);
     }

     //Create a graph object
     Alist.calculateOutdegrees();
     Alist.PageRank(power_iterations);


 }
