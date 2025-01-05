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
        template<typename Inspecting>
        static consteval auto idyl
        (
            Prefix<I> auto...front_args,
            Inspecting,
            ...
        )
        -> std::conditional_t
        <
            (...||std::is_same_v<Inspecting, decltype(front_args)>),
            Capsule<>,
            Capsule<typename Inspecting::type>
        >;
    };

    template<typename>
    struct Hidden {};

    template<size_t...I>
    struct Hidden<std::index_sequence<I...>>
    {
        using type = Cotanivore::TypicalPaste
        <
            decltype
            (
                Detail<std::make_index_sequence<I>>
                ::template idyl(std::type_identity<Elements>{}...)
            )...
        >::type;
    };

    using type = Hidden<std::make_index_sequence<sizeof...(Elements)>>::type;
};

template<typename...Elements>
using ConjureSet = TypicalConjureSet<Elements...>::type;

}}

#endif