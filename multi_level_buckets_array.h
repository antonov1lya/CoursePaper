#ifndef COURSE_PAPER_MULTI_LEVEL_BUCKETS_ARRAY_H
#define COURSE_PAPER_MULTI_LEVEL_BUCKETS_ARRAY_H

#include <cmath>

class MLBArray {
    struct Bucket {
        std::list<std::pair<long long, long long>> v;
        long long size = 0;
    };
    long long size;
    std::vector<Bucket> top;
    std::vector<std::list<long long>> bot;
    long long l_top, l_bot, r_top, r_bot, start;
public:
    MLBArray(long long C) {
        r_top = sqrt(C + 1) + 2;
        r_bot = sqrt(C + 1) + 1;
        top.resize(r_top);
        bot.resize(r_bot);
        start = 0, l_top = 0, l_bot = 0;
        size = 0;
    }

    void push(long long a, long long b) {
        if (start <= a and a < start + r_top * r_bot) {
            if (start + r_bot * l_top <= a and a < start + r_bot * l_top + r_bot) {
                bot[a - start - l_top * r_bot].emplace_back(b);
                top[l_top].size++;
                if (a - start - l_top * r_bot < l_bot) {
                    l_bot = a - start - l_top * r_bot;
                }
            } else {
                top[(a - start) / r_bot].v.emplace_back(std::make_pair((a - start) % r_bot, b));
                top[(a - start) / r_bot].size++;
            }
            ++size;
        } else {
            top[(a - start - r_top * r_bot) / r_bot].v.emplace_back(
                    std::make_pair((a - start - r_top * r_bot) % r_bot, b));
            top[(a - start - r_top * r_bot) / r_bot].size++;
            ++size;
        }
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
                l_bot = r_bot;
                for (auto i: top[l_top].v) {
                    bot[i.first].emplace_back(i.second);
                    if (i.first < l_bot) {
                        l_bot = i.first;
                    }
                }
                top[l_top].v.clear();
            }
            while (bot[l_bot].empty()) {
                l_bot++;
            }
            long long extract = bot[l_bot].front();
            bot[l_bot].pop_front();
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

#endif //COURSE_PAPER_MULTI_LEVEL_BUCKETS_ARRAY_H
