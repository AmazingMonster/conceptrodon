// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_MINIMUM_H
#define CONCEPTRODON_VARYBIVORE_MINIMUM_H

#include <algorithm>
#include <array>

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Minimum
{ 
    static constexpr auto value 
    {
        []()
        {
            std::array array {Variables...};
            return std::ranges::min(array);
        }()
    }; 
};

template<auto...Variables>
constexpr auto Minimum_v 
{
    []()
    {
        std::array array {Variables...};
        return std::ranges::min(array);
    }()
}; 

}}

#endif