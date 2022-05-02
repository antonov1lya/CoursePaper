#include "dijkstra.h"
#include "multi_level_buckets.h"
#include "d_heap.h"
#include "fibonacci_heap.h"
#include <queue>

void Path(std::vector<int>& path, int i, int finish){
    if(path[i]!=-1) {
        if(i!=finish) {
            Path(path, path[i], finish);
            std::cout << i + 1 << " ";
        }else{
            Path(path, path[i], finish);
            std::cout << i + 1 << std::endl;
        }
    }
    else{
        std::cout << i+1 << " ";
    }
}
void Path(std::vector<long long>& path, int i, int finish){
    if(path[i]!=-1) {
        if(i!=finish) {
            Path(path, path[i], finish);
            std::cout << i + 1 << " ";
        }else{
            Path(path, path[i], finish);
            std::cout << i + 1 << std::endl;
        }
    }
    else{
        std::cout << i+1 << " ";
    }
}

Dijkstra::Dijkstra(std::string path) {
    std::fstream fr(path);
    fr >> n >> m;
    fr >> start >> finish;
    --start;
    --finish;
    adjacencyList.resize(n);
    std::pair<int, int> buffer;
    int weight = 0;
    for (int i = 0; i < m; ++i) {
        fr >> buffer.first >> buffer.second >> weight;
        --buffer.first;
        --buffer.second;
        adjacencyList[buffer.first].push_back(std::make_pair(buffer.second, weight));
        adjacencyList[buffer.second].push_back(std::make_pair(buffer.first, weight));
        if(weight < minWeight){
            minWeight = buffer.second;
        }
        if(weight > maxWeight){
            maxWeight = buffer.second;
        }
    }
}

void Dijkstra::NaiveImplementation() {
    std::vector<int> d(n, 100000000), used(n, 0), path(n, -1);
    int current = 0;
    d[current]=0;
    while (current >= 0){
        if(current==finish){
            break;
        }
        used[current]=1;
        for(auto i: adjacencyList[current]){
            if(!used[i.first]){
                if (d[current]+i.second<d[i.first]){
                    d[i.first]=d[current]+i.second;
                    path[i.first]=current;
                }
            }
        }
        current = -1;
        int min = 100000000;
        for(int i=0; i<n; ++i){
            if (d[i]<min and !used[i]){
                current = i;
                min = d[i];
            }
        }
    }
    if (d[finish]==100000000){
        std::cout << "-1" << std::endl;
    }
    else{
        Path(path, finish, finish);
        std::cout << "Distance: " << d[finish] << std::endl;
    }

}

void Dijkstra::MLBImplementation() {
    std::vector<long long> d(n, 9223372036854775807), used(n, 0), path(n, -1);
    int current = 0;
    d[current] = 0;
    long long min = 9223372036854775807;
    for(auto i: adjacencyList[start]){
        if(i.second<min){
            min = i.second;
        }
    }
//    MLB q((minWeight+maxWeight)/2,min);
    used[start]=1;
    MLB q(5,min);
    for(auto i: adjacencyList[start]){
        if (d[current] + i.second < d[i.first]) {
            d[i.first] = i.second;
            q.push(d[i.first], i.first);
            path[i.first] = current;
        }
    }
    while (!q.empty()) {
        current = q.pop();
        if (current == finish) {
            break;
        }
        if (!used[current]) {
            used[current] = 1;
            for (auto i : adjacencyList[current]) {
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

    if (d[finish] == 9223372036854775807) {
        std::cout << "-1" << std::endl;
    }
    else {
        Path(path, finish, finish);
        std::cout << "Distance: " << d[finish] << std::endl;
    }
}

void Dijkstra::DHeapImplementation(int D) {
    std::vector<long long> d(n, 9223372036854775807), used(n, 0), path(n, -1);
    int current = 0;
    d[current] = 0;
    DHeap<std::pair<int, int>> q(D);
    q.push(std::make_pair(0, current));
    while (!q.empty()) {
        current = q.pop().second;
        if(current==finish){
            break;
        }
        if(!used[current]) {
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

    if (d[finish] == 9223372036854775807) {
        std::cout << "-1" << std::endl;
    } else {
        Path(path, finish, finish);
        std::cout << "Distance: " << d[finish] << std::endl;
    }
}

void Dijkstra::FibonacciImplementation() {
    std::vector<long long> d(n, 9223372036854775807), used(n, 0), path(n, -1);
    int current = 0;
    d[current] = 0;
    FibonacciHeap<std::pair<int, int>> q;
    q.insert(std::make_pair(0, current));
    while (!q.empty()) {
        current = q.extractMin().second;
        if(current==finish){
            break;
        }
        if(!used[current]) {
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

    if (d[finish] == 9223372036854775807) {
        std::cout << "-1" << std::endl;
    } else {
        Path(path, finish, finish);
        std::cout << "Distance: " << d[finish] << std::endl;
    }
}

void Dijkstra::PriorityQueue() {
    std::vector<long long> d(n, 9223372036854775807), used(n, 0), path(n, -1);
    int current = 0;
    d[current] = 0;
    std::priority_queue<std::pair<int, int>> q;
    q.push(std::make_pair(-0, current));
    while (!q.empty()) {
        current = q.top().second;
        q.pop();
        if(current==finish){
            break;
        }
        if(!used[current]) {
            used[current] = 1;
            for (auto i: adjacencyList[current]) {
                if (!used[i.first]) {
                    if (d[current] + i.second < d[i.first]) {
                        d[i.first] = d[current] + i.second;
                        path[i.first] = current;
                        q.push(std::make_pair(-d[i.first], i.first));
                    }
                }
            }
        }

    }

    if (d[finish] == 9223372036854775807) {
        std::cout << "-1" << std::endl;
    } else {
        Path(path, finish, finish);
        std::cout << "Distance: " << d[finish] << std::endl;
    }
}



