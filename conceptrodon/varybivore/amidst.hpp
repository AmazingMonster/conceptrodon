// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_AMIDST_H
#define CONCEPTRODON_VARYBIVORE_AMIDST_H

#include "conceptrodon/utilities/prefix.hpp"
#include "conceptrodon/utilities/vay.hpp"
#include <utility>

namespace Conceptrodon {

namespace Varbola {

template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    template<typename Target>
    static constexpr auto idyl
    (
        Prefix<I> auto...,
        Target,
        ...
    )
    -> Target;
};

}

namespace Varybivore {

template<auto...Variables>
struct Amidst
{
    template<size_t I>
    struct ProtoPage
    {
        static constexpr auto value 
        {
            decltype
            (
                Varbola::Midst<std::make_index_sequence<I>>
                ::idyl(Vay<Variables>{}...)
            )
            ::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<size_t I>
    static constexpr auto Page_v 
    {
        decltype
        (
            Varbola::Midst<std::make_index_sequence<I>>
            ::idyl(Vay<Variables>{}...)
        )
        ::value
    };
};

}}

#endif