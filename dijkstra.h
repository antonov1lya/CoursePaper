#ifndef COURSE_PAPER_DIJKSTRA_H
#define COURSE_PAPER_DIJKSTRA_H

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

class Dijkstra {
private:
    int n = 0, m = 0, start = 0, finish = 0;
    std::vector<std::vector<std::pair<long long, long long>>> adjacencyList;
//    std::vector<std::vector<long long>> adjacencyMatrix;
    long long C = 0, inf = 9223372036854775807;
public:
    Dijkstra(std::string path);

    void NaiveImplementation();

//    void NaiveImplementationMatrix();

    void MLBImplementationArray();

    void MLBImplementationHeap();

    void DHeapImplementation(long long D);

    void FibonacciImplementation();


};

#endif //COURSE_PAPER_DIJKSTRA_H
