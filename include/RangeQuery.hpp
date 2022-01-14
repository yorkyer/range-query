#pragma once

#include <functional>
#include <iostream>
#include <cmath>
#include <vector>
#include <strings.h> // to use ffs() to find first set bit in an integer.

//#define DEBUG_RangeQuery

template <typename ValueType>
class RangeQuery {
public:
    RangeQuery(int N, int E, std::function<ValueType(int)> func) : N(N), E(E), getElementValue(func) {
        for (int i = E; i < N; i += E) {
            blocks.push_back(std::vector<ValueType>(1 << (N - i)));
        }

        upperLimit = 1 << N;

#ifdef DEBUG_RangeQuery
        for (size_t i = 0; i < blocks.size(); i++) {
            std::cout << i << "-th block's size: 2^" << std::log2(blocks[i].size()) << std::endl;
            size_t j = 0;
            for (; j < blocks[i].size(); j++) {
                std::cout << (1 << (E * (i+1))) * j << " ";
            }
            std::cout << (1 << (E * (i+1))) * j << std::endl;
        }
#endif
    }

    bool update(int x, ValueType diff) {
        if (x >= upperLimit) return false;
        for (int i = E, j = 0; i < N; i += E, j++) {
            blocks[j][x >> i] += diff;
#ifdef DEBUG_RangeQuery
            std::cout << "update " << x << " : blocks[" << j << "][" << (x >> i) << "] = " << blocks[j][x >> i] << std::endl;
#endif
        }
        return true;
    }

    // Not including r
    ValueType query(int l, int r) const {
#ifdef DEBUG_RangeQuery
        std::cout << "(" << l << ", " << r << ")" << " -> ";
#endif
        if (l < 0) l = 0;
        if (r > upperLimit) r= upperLimit;

        ValueType s{0};
        int x = l;
        while (x < r) {
#ifdef DEBUG_RangeQuery
            std::cout << x << " ";
#endif
            int p = ffs(x) - 1;
            p = p / E * E;
            bool ahead = false;
            while (p > 0) {
                int lookAhead = x + (1 << p);
                if (lookAhead <= r) {
                    s += blocks[p / E - 1][x >> p];
                    x = lookAhead;
                    ahead = true;
                    break;
                }
                else {
                    p -= E;
                }
            }

            if (!ahead) {
                s += getElementValue(x);
                x += 1;
            }
        }
#ifdef DEBUG_RangeQuery
        std::cout << std::endl;
#endif
        return s;
    }

private:
    int upperLimit{0};
    int N{0};
    int E{0};
    std::function<ValueType(int)> getElementValue;

    std::vector<std::vector<ValueType>> blocks;
};
