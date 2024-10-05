// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_RIGHT_REVIEW_H
#define CONCEPTRODON_MOULDIVORE_RIGHT_REVIEW_H

#include "conceptrodon/prefix.hpp"
#include <utility>

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Predicate>
struct RightReview
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>> 
    {
        template<Prefix<I>..., typename OnDuty, typename...RestElements>
        static consteval bool idyl()
        { return (...&&Predicate<RestElements, OnDuty>::value); }
    };

    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value
        {
            []<size_t...I>(std::index_sequence<I...>)
            {
                return (...&&(Detail<std::make_index_sequence<I>>::template idyl<Elements...>()));
            }(std::make_index_sequence<sizeof...(Elements) - 1>{})
        };  
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    static constexpr bool Mold_v
    {
        []<size_t...I>(std::index_sequence<I...>)
        {
            return (...&&(Detail<std::make_index_sequence<I>>::template idyl<Elements...>()));
        }(std::make_index_sequence<sizeof...(Elements) - 1>{})
    };
};

}}

#endif