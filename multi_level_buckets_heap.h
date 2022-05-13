#ifndef MULTI_LEVEL_BUCKETS_MULTI_LEVEL_BUCKETS_H
#define MULTI_LEVEL_BUCKETS_MULTI_LEVEL_BUCKETS_H

#include "d_heap.h"
#include <vector>
#include <list>
#include <cmath>

class MLBHeap {
    struct Bucket {
        DHeap<std::pair<long long, long long>> *v;
        long long size = 0;
    };
    long long size;
    std::vector<Bucket> top;
    long long l_top, r_top, r_bot, start;
public:
    MLBHeap(long long C) {
        r_top = sqrt(C + 1) + 2;
        r_bot = sqrt(C + 1) + 1;

        top.resize(r_top);
        start = 0, l_top = 0;
        size = 0;
    }

    void push(long long a, long long b) {
        long long c;
        if (start <= a and a < start + r_top * r_bot) {
            c = (a - start) / r_bot;
        } else {
            c = (a - start - r_top * r_bot) / r_bot;
        }
        if (top[c].v == nullptr) {
            top[c].v = new DHeap<std::pair<long long, long long>>(4);
        }
        top[c].v->push(std::make_pair(a, b));
        top[c].size++;
        ++size;
    }

    long long pop() {
        if (size != 0) {
            if (top[l_top].size == 0) {
                while (top[l_top].size == 0) {
                    l_top++;
                    if (l_top == r_top) {
                        l_top = 0;
                        start += r_top * r_bot;
                    }
                }
            }
            long long extract = top[l_top].v->pop().second;
            top[l_top].size--;
            size--;
            return extract;

        } else {
            return -1;
        }
    }

    bool empty() {
        return !size;
    }
};

#endif //MULTI_LEVEL_BUCKETS_MULTI_LEVEL_BUCKETS_H
