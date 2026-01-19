// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_RIGHT_REVIEW_H
#define CONCEPTRODON_MOULDIVORE_RIGHT_REVIEW_H

#include "conceptrodon/utilities/tyy.hpp"
#include "conceptrodon/metafunctions/microbiota/moldiae/right_inspect.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Predicate>
struct RightReview
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value
        {
            []<size_t...I>(std::index_sequence<I...>)
            {
                return
                (...&&(
                    decltype
                    (
                        Moldiae::RightInspect<std::make_index_sequence<I>>
                        ::template idyl<Predicate>(Tyy<Elements>{}...)
                    )::value
                ));
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
            return
            (...&&(
                decltype
                (
                    Moldiae::RightInspect<std::make_index_sequence<I>>
                    ::template idyl<Predicate>(Tyy<Elements>{}...)
                )::value
            ));
        }(std::make_index_sequence<sizeof...(Elements) - 1>{})
    }; 
};

}}

#endif