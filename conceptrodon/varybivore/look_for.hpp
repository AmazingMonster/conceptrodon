// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_LOOK_FOR_H
#define CONCEPTRODON_VARYBIVORE_LOOK_FOR_H

#include <type_traits>

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct LookFor
{
    template<template<auto...> class Predicate>
    struct ProtoRail
    {
        static constexpr auto value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {0};
                return
                (...||( (++counter, Predicate<Variables>::value) ? true : false)) ? 
                counter : -1;
            }()
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;

    template<template<auto...> class Predicate>
    static constexpr auto Rail_v
    {
        []() -> std::make_signed_t<size_t>
        {
            std::make_signed_t<size_t> counter {-1};
            return
            (...||( (++counter, Predicate<Variables>::value) ? true : false)) ? 
            counter : -1;
        }()
    };
};

}}

#endif