// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_RIGHT_REVIEW_H
#define CONCEPTRODON_PAGELIVORE_RIGHT_REVIEW_H

#include "conceptrodon/prefix.hpp"
#include "conceptrodon/monotony.hpp"
#include <utility>

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Predicate>
struct RightReview
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>> 
    {
        template<Prefix<I>..., typename OnDuty, typename...RestVariables>
        static consteval bool idyl()
        { return (...&&Predicate<RestVariables::value, OnDuty::value>::value); }
    };

    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        {
            []<size_t...I>(std::index_sequence<I...>)
            {
                return (...&&(Detail<std::make_index_sequence<I>>::template idyl<Monotony<Variables>...>()));
            }(std::make_index_sequence<sizeof...(Variables) - 1>{})
        };  
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    static constexpr bool Page_v = 
    {
        []<size_t...I>(std::index_sequence<I...>)
        {
            return (...&&(Detail<std::make_index_sequence<I>>::template idyl<Monotony<Variables>...>()));
        }(std::make_index_sequence<sizeof...(Variables) - 1>{})
    }; 
};

}}

#endif