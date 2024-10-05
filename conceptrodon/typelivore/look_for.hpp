// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_LOOK_FOR_H
#define CONCEPTRODON_TYPELIVORE_LOOK_FOR_H

#include <type_traits>

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct LookFor
{
    template<template<typename...> class Predicate>
    struct ProtoRoad
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

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;

    template<template<typename...> class Predicate>
    static constexpr auto Road_v
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