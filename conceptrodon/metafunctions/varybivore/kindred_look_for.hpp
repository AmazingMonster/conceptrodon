// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_KINDRED_LOOK_FOR_H
#define CONCEPTRODON_VARYBIVORE_KINDRED_LOOK_FOR_H

#include <cstddef>
#include <type_traits>

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct KindredLookFor
{
    template<template<auto...> class Predicate>
    struct ProtoRail
    {
        static constexpr std::make_signed_t<size_t> value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {-1};
                return
                (...||(++counter, Predicate<Variables>::value)) ? 
                counter : -1;
            }()
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;

    template<template<auto...> class Predicate>
    static constexpr std::make_signed_t<size_t> Rail_v
    {
        []() -> std::make_signed_t<size_t>
        {
            std::make_signed_t<size_t> counter {-1};
            return
            (...||(++counter, Predicate<Variables>::value)) ? 
            counter : -1;
        }()
    };
};

}}

#endif