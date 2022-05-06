#ifndef COURSE_PAPER_DIJKSTRA_H
#define COURSE_PAPER_DIJKSTRA_H

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

class Dijkstra {
private:
    int n = 0, m = 0, start = 0, finish = 0;
    std::vector<std::vector<std::pair<int, long long>>> adjacencyList;
    long long C = 0;
public:
    Dijkstra(std::string path);

    void NaiveImplementation();

    void MLBImplementationArray();

    void MLBImplementationList();

    void DHeapImplementation(int D);

    void FibonacciImplementation();

    void PriorityQueue();
};

#endif //COURSE_PAPER_DIJKSTRA_H
