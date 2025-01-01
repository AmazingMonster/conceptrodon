// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_AMIDST_H
#define CONCEPTRODON_TYPELIVORE_AMIDST_H

#include "conceptrodon/prefix.hpp"
#include <type_traits>
#include <utility>

namespace Conceptrodon {
namespace Typella {

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
    -> Target::type;
};

}

namespace Typelivore {

template<typename...Elements>
struct Amidst
{
    template<size_t I>
    struct Detail
    {
        using type = decltype
        (
            Typella::Midst<std::make_index_sequence<I>>
            ::idyl(std::type_identity<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = Detail<Agreements...>::type;

    template<size_t I>
    using UniPage = decltype
    (
        Typella::Midst<std::make_index_sequence<I>>
        ::idyl(std::type_identity<Elements>{}...)
    );
};

}}

#endif



