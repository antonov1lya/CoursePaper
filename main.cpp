#include <iostream>
#include <chrono>
#include "dijkstra.h"
int main() {
    std::string path = "C:/Users/a222i/PycharmProjects/tests/output.txt";
    Dijkstra a(path);

    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

//    std::cout << "Naive implementation" << std::endl;
//    begin = std::chrono::steady_clock::now();
//    a.NaiveImplementation();
//    end = std::chrono::steady_clock::now();
//    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
//    std::cout << "The time: " << elapsed_ms.count() << " ms" << std::endl << std::endl;

    std::cout << "MLB implementation" << std::endl;
    begin = std::chrono::steady_clock::now();
    a.MLBImplementation();
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms" << std::endl << std::endl;

    std::cout << "8DHeap implementation" << std::endl;
    begin = std::chrono::steady_clock::now();
    a.DHeapImplementation(8);
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms" << std::endl << std::endl;

    std::cout << "4DHeap implementation" << std::endl;
    begin = std::chrono::steady_clock::now();
    a.DHeapImplementation(4);
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms" << std::endl << std::endl;

    std::cout << "2DHeap implementation" << std::endl;
    begin = std::chrono::steady_clock::now();
    a.DHeapImplementation(2);
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms" << std::endl << std::endl;

    std::cout << "Fibonacci implementation" << std::endl;
    begin = std::chrono::steady_clock::now();
    a.FibonacciImplementation();
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms" << std::endl << std::endl;

    std::cout << "PriorityQueue implementation" << std::endl;
    begin = std::chrono::steady_clock::now();
    a.FibonacciImplementation();
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms" << std::endl << std::endl;

    return 0;
}
