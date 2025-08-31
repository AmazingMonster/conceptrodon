// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_LOOK_FOR_H
#define CONCEPTRODON_MOULDIVORE_LOOK_FOR_H

#include <cstddef>
#include <type_traits>

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Predicate>
struct LookFor
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr auto value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {0};
                return
                (...||( (++counter, Predicate<Elements>::value) ? true : false)) ? 
                counter : -1;
            }()
        };
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    static constexpr auto Mold_v
    {
        []() -> std::make_signed_t<size_t>
        {
            std::make_signed_t<size_t> counter {-1};
            return
            (...||( (++counter, Predicate<Elements>::value) ? true : false)) ? 
            counter : -1;
        }()
    };
};

}}

#endif