// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARBOLA_OBSERVE_H
#define CONCEPTRODON_VARBOLA_OBSERVE_H

#include <algorithm>
#include <array>
#include "conceptrodon/utilities/tyy.hpp"

namespace Conceptrodon {
namespace Varbola {

template<template<auto...> class Operation, bool...Phenomena>
static consteval auto stare()
{
    return []<size_t...I>(std::index_sequence<I...>)
    {
        return []<size_t...J>(std::index_sequence<J...>)
        {
            constexpr auto result = []()
            {
                std::array phenomena {Phenomena...};
                std::array indices {I...};
                
                auto comp = [&phenomena](size_t i, size_t j)
                {
                    return 
                        (phenomena[i] && ! phenomena[j]) 
                    ||  (phenomena[i] && phenomena[j] && i < j);
                };
                
                std::ranges::sort(indices, comp);

                return indices;
            }();
            return Tyy<Operation<result.at(J)...>> {};
        }(std::make_index_sequence<(...+Phenomena)>{});
    }(std::make_index_sequence<sizeof...(Phenomena)>{});
};

}}

#endif