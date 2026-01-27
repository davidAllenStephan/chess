#pragma once
#include <utility>

struct PairHash {
        std::size_t operator()(const std::pair<int, int> &p) const noexcept {
                return static_cast<std::size_t>(p.first) * 31u + static_cast<std::size_t>(p.second);
        }
};
