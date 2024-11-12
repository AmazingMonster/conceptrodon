// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_AMIDST_H
#define CONCEPTRODON_VARYBIVORE_AMIDST_H

#include "conceptrodon/prefix.hpp"
#include <utility>

namespace Conceptrodon {

namespace Varbola {

template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    static constexpr auto idyl(Prefix<I> auto..., auto target, ...)
    { return target; };

    template<auto...Variables>
    struct ProtoPage
    { static constexpr auto value { idyl(Variables...) }; };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    static constexpr auto Page_v { idyl(Variables...) };
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
        { Varbola::Midst<std::make_index_sequence<I>>::idyl(Variables...) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<size_t I>
    static constexpr auto Page_v 
    { Varbola::Midst<std::make_index_sequence<I>>::idyl(Variables...) };
};

}}

#endif