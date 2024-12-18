// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_AMIDST_H
#define CONCEPTRODON_TYPELIVORE_AMIDST_H

#include "conceptrodon/prefix.hpp"
#include <utility>

namespace Conceptrodon {
namespace Typella {

template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    template<Prefix<I>..., typename Target, typename...>
    static constexpr auto idyl() -> Target;

    template<typename...Elements>
    struct Detail
    { using type = decltype(idyl<Elements...>()); };

    template<typename...Elements>
    using Mold = Detail<Elements...>::type;
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
        (Typella::Midst<std::make_index_sequence<I>>::template idyl<Elements...>());
    };

    template<auto...Agreements>
    using Page = Detail<Agreements...>::type;

    template<size_t I>
    using UniPage = decltype
    (Typella::Midst<std::make_index_sequence<I>>::template idyl<Elements...>());
};

}}

#endif



