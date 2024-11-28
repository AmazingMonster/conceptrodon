// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_LOOK_FOR_H
#define CONCEPTRODON_PAGELIVORE_LOOK_FOR_H

#include <type_traits>

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Predicate>
struct LookFor
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr auto value
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

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    static constexpr auto Page_v
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