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
    struct ProtoMold
    { using type = decltype(idyl<Elements...>()); };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;

    template<typename...Elements>
    using Mold_t = ProtoMold<Elements...>::type;
};

}

namespace Typelivore {

template<typename...Elements>
struct Amidst
{
    template<size_t I>
    struct ProtoPage
    {
        using type = decltype
        (Typella::Midst<std::make_index_sequence<I>>::template idyl<Elements...>());
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    using Page_t = ProtoPage<Args...>::type;

    template<size_t I>
    using UniPage = decltype
    (Typella::Midst<std::make_index_sequence<I>>::template idyl<Elements...>());
};

}}

#endif



