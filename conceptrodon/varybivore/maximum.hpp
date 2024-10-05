// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_MAXIMUM_H
#define CONCEPTRODON_VARYBIVORE_MAXIMUM_H

#include <algorithm>
#include <array>

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Maximum
{ 
    static constexpr auto value 
    {
        []()
        {
            std::array array {Variables...};
            return *std::ranges::max_element(array);
        }()
    }; 
};

template<auto...Variables>
constexpr auto Maximum_v 
{
    []()
    {
        std::array array {Variables...};
        return *std::ranges::max_element(array);
    }()
}; 

}}

#endif