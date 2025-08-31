// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_KINDRED_LOOK_FOR_H
#define CONCEPTRODON_TYPELIVORE_KINDRED_LOOK_FOR_H

#include <cstddef>
#include <type_traits>

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct KindredLookFor
{
    template<template<typename...> class Predicate>
    struct ProtoRoad
    {
        static constexpr std::make_signed_t<size_t> value
        {
            []() -> std::make_signed_t<size_t>
            {
                std::make_signed_t<size_t> counter {-1};
                return
                (...||(++counter, Predicate<Elements>::value)) ? 
                counter : -1;
            }()
        };
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;

    template<template<typename...> class Predicate>
    static constexpr std::make_signed_t<size_t> Road_v
    {
        []() -> std::make_signed_t<size_t>
        {
            std::make_signed_t<size_t> counter {-1};
            return
            (...||(++counter, Predicate<Elements>::value)) ? 
            counter : -1;
        }()
    };
};

}}

#endif