#include "dijkstra.h"
#include "multi_level_buckets_heap.h"
#include "multi_level_buckets_array.h"
#include "d_heap.h"
#include "fibonacci_heap.h"

void Path(std::vector<long long> &path, long long i, long long finish) {
    if (path[i] != -1) {
        if (i != finish) {
            Path(path, path[i], finish);
            std::cout << i + 1 << " ";
        } else {
            Path(path, path[i], finish);
            std::cout << i + 1 << std::endl;
        }
    } else {
        std::cout << i + 1 << " ";
    }
}

Dijkstra::Dijkstra(std::string path) {
    std::fstream fr(path);
    fr >> n >> m;
    fr >> start >> finish;
    --start;
    --finish;
    adjacencyList.resize(n);
//    adjacencyMatrix.resize(n, std::vector<long long>(n,-1));
    std::pair<long long, long long> buffer;
    long long weight = 0;
    for (long long i = 0; i < m; ++i) {
        fr >> buffer.first >> buffer.second >> weight;
        --buffer.first;
        --buffer.second;
        adjacencyList[buffer.first].push_back(std::make_pair(buffer.second, weight));
        adjacencyList[buffer.second].push_back(std::make_pair(buffer.first, weight));
//        adjacencyMatrix[buffer.first][buffer.second]=weight;
//        adjacencyMatrix[buffer.second][buffer.first]=weight;
        if (weight > C) {
            C = weight;
        }
    }
}

void Dijkstra::NaiveImplementation() {
    std::vector<long long> d(n, inf), used(n, 0), path(n, -1);
    long long current = 0;
    d[current] = 0;
    while (current >= 0) {
        if (current == finish) {
            break;
        }
        used[current] = 1;
        for (auto i: adjacencyList[current]) {
            if (!used[i.first]) {
                if (d[current] + i.second < d[i.first]) {
                    d[i.first] = d[current] + i.second;
                    path[i.first] = current;
                }
            }
        }
        current = -1;
        long long min = inf;
        for (long long i = 0; i < n; ++i) {
            if (d[i] < min and !used[i]) {
                current = i;
                min = d[i];
            }
        }
    }
    if (d[finish] == inf) {
        std::cout << "-1" << std::endl;
    } else {
        Path(path, finish, finish);
        std::cout << "Distance: " << d[finish] << std::endl;
    }
}

void Dijkstra::MLBImplementationArray() {
    std::vector<long long> d(n, inf), used(n, 0), path(n, -1);
    long long current = 0;
    d[current] = 0;
    MLBArray q(C);
    q.push(0, start);
    while (!q.empty()) {
        current = q.pop();
        if (current == finish) {
            break;
        }
        if (!used[current]) {
            used[current] = 1;
            for (auto i: adjacencyList[current]) {
                if (!used[i.first]) {
                    if (d[current] + i.second < d[i.first]) {
                        d[i.first] = d[current] + i.second;
                        path[i.first] = current;
                        q.push(d[i.first], i.first);
                    }
                }
            }
        }

    }

    if (d[finish] == inf) {
        std::cout << "-1" << std::endl;
    } else {
        Path(path, finish, finish);
        std::cout << "Distance: " << d[finish] << std::endl;
    }
}

void Dijkstra::DHeapImplementation(long long D) {
    std::vector<long long> d(n, inf), used(n, 0), path(n, -1);
    long long current = 0;
    d[current] = 0;
    DHeap<std::pair<long long, long long>> q(D);
    q.push(std::make_pair(0, current));
    while (!q.empty()) {
        current = q.pop().second;
        if (current == finish) {
            break;
        }
        if (!used[current]) {
            used[current] = 1;
            for (auto i: adjacencyList[current]) {
                if (!used[i.first]) {
                    if (d[current] + i.second < d[i.first]) {
                        d[i.first] = d[current] + i.second;
                        path[i.first] = current;
                        q.push(std::make_pair(d[i.first], i.first));
                    }
                }
            }
        }

    }

    if (d[finish] == inf) {
        std::cout << "-1" << std::endl;
    } else {
        Path(path, finish, finish);
        std::cout << "Distance: " << d[finish] << std::endl;
    }
}

void Dijkstra::FibonacciImplementation() {
    std::vector<long long> d(n, inf), used(n, 0), path(n, -1);
    long long current = 0;
    d[current] = 0;
    FibonacciHeap<std::pair<long long, long long>> q;
    q.insert(std::make_pair(0, current));
    while (!q.empty()) {
        current = q.extractMin().second;
        if (current == finish) {
            break;
        }
        if (!used[current]) {
            used[current] = 1;
            for (auto i: adjacencyList[current]) {
                if (!used[i.first]) {
                    if (d[current] + i.second < d[i.first]) {
                        d[i.first] = d[current] + i.second;
                        path[i.first] = current;
                        q.insert(std::make_pair(d[i.first], i.first));
                    }
                }
            }
        }

    }
    if (d[finish] == inf) {
        std::cout << "-1" << std::endl;
    } else {
        Path(path, finish, finish);
        std::cout << "Distance: " << d[finish] << std::endl;
    }
}

void Dijkstra::MLBImplementationHeap() {
    std::vector<long long> d(n, inf), used(n, 0), path(n, -1);
    long long current = 0;
    d[current] = 0;
    MLBHeap q(C);
    q.push(0, start);
    while (!q.empty()) {
        current = q.pop();
        if (current == finish) {
            break;
        }
        if (!used[current]) {
            used[current] = 1;
            for (auto i: adjacencyList[current]) {
                if (!used[i.first]) {
                    if (d[current] + i.second < d[i.first]) {
                        d[i.first] = d[current] + i.second;
                        path[i.first] = current;
                        q.push(d[i.first], i.first);
                    }
                }
            }
        }

    }

    if (d[finish] == inf) {
        std::cout << "-1" << std::endl;
    } else {
        Path(path, finish, finish);
        std::cout << "Distance: " << d[finish] << std::endl;
    }
}

//void Dijkstra::NaiveImplementationMatrix() {
//    std::vector<long long> d(n, inf), used(n, 0), path(n, -1);
//    long long current = 0;
//    d[current] = 0;
//    while (current >= 0) {
////        if (current == finish) {
////            break;
////        }
//        used[current] = 1;
//        for (int j=0; j<n; ++j) {
//            if (adjacencyMatrix[current][j]!=-1 and !used[j]) {
//                if (d[current] + adjacencyMatrix[current][j] < d[j]) {
//                    d[j] = d[current] + adjacencyMatrix[current][j];
//                    path[j] = current;
//                }
//            }
//        }
//        current = -1;
//        long long min = inf;
//        for (long long i = 0; i < n; ++i) {
//            if (d[i] < min and !used[i]) {
//                current = i;
//                min = d[i];
//            }
//        }
//    }
//    if (d[finish] == inf) {
//        std::cout << "-1" << std::endl;
//    } else {
////        Path(path, finish, finish);
//        std::cout << "Distance: " << d[finish] << std::endl;
//    }
//}





