// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_NEGATION_H
#define CONCEPTRODON_PAGELIVORE_NEGATION_H

namespace Conceptrodon {
namespace Pagelivore {

template <template<auto...>  class Predicate>
struct Negation
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value 
        = not Predicate<Variables...>::value;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    = not Predicate<Variables...>::value;
};

}}

#endif