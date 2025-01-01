// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_RIGHT_REVIEW_H
#define CONCEPTRODON_PAGELIVORE_RIGHT_REVIEW_H

#include "conceptrodon/descend/microbiota/pagelis/right_inspect.hpp"
#include "conceptrodon/vay.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Predicate>
struct RightReview
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        {
            []<size_t...I>(std::index_sequence<I...>)
            {
                return
                (...&&(
                    decltype
                    (
                        Pagelis::RightInspect<std::make_index_sequence<I>>
                        ::template idyl<Predicate>(Vay<Variables>{}...)
                    )::value
                ));
            }(std::make_index_sequence<sizeof...(Variables) - 1>{})
        }; 
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    static constexpr bool Page_v
    {
        []<size_t...I>(std::index_sequence<I...>)
        {
            return
            (...&&(
                decltype
                (
                    Pagelis::RightInspect<std::make_index_sequence<I>>
                    ::template idyl<Predicate>(Vay<Variables>{}...)
                )::value
            ));
        }(std::make_index_sequence<sizeof...(Variables) - 1>{})
    }; 
};

}}

#endif