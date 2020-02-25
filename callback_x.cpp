/*
    callback_x.cpp

    Experiments with different implementations of callbacks
*/

#include <iostream>
#include <iomanip>
#include <array>
#include <numeric>
#include <algorithm>
#include <chrono>

typedef std::array<int, 100000> Container_t;

// count of elements that don't get moved
int count(const Container_t::const_iterator begin,
          const Container_t::const_iterator end) {

    int count = 0;
    for (auto p = begin; p != end; ++p) {
        for (auto p2 = p; p2 != end; ++p2) {
            if (*p < *p2)
                ++count;
        }
    }

    return count;
}

Container_t ar;

int main() {

    // fill the array
    std::iota(ar.begin(), ar.end(), 1);

    {
        auto start = std::chrono::steady_clock::now();

        // @NOTE count using operator<
        auto counter = count(ar.begin(), ar.end());

        auto elapsed = std::chrono::steady_clock::now() - start;
        std::cout << std::setw(12) << elapsed.count() << ": operator<" << '\n';
    }

    return 0;
}
