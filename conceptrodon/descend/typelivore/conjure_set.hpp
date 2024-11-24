// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_TYPICAL_CONJURE_SET_H
#define CONCEPTRODON_TYPELIVORE_TYPICAL_CONJURE_SET_H

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/prefix.hpp"
#include "conceptrodon/cotanivore/paste.hpp"
#include <utility>

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct TypicalConjureSet
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    {
        template<Prefix<I>...FrontElements, typename Inspecting, typename...>
        static consteval auto idyl()
        -> std::conditional_t
        <
            (...||std::is_same_v<FrontElements, Inspecting>),
            Capsule<>,
            Capsule<Inspecting>
        >;
    };

    template<typename>
    struct Hidden {};

    template<size_t...I>
    struct Hidden<std::index_sequence<I...>>
    {
        using type = Cotanivore::Paste
        <
            decltype
            (
                Detail<std::make_index_sequence<I>>
                ::template idyl<Elements...>()
            )...
        >;
    };

    using type = Hidden<std::make_index_sequence<sizeof...(Elements)>>::type;
};

template<typename...Elements>
using ConjureSet = TypicalConjureSet<Elements...>::type;

}}

#endif