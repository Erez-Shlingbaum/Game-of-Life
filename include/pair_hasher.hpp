#pragma once

#include <utility>

struct PairHasher
{
    template<class T1, class T2>
    size_t operator()(const std::pair<T1, T2> &pair) const
    {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};