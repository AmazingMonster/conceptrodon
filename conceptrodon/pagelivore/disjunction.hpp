// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_DISJUNCTION_H
#define CONCEPTRODON_PAGELIVORE_DISJUNCTION_H

namespace Conceptrodon {
namespace Pagelivore {

template <template<auto...> class...Predicates>
struct Disjunction
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr auto value
        {(...||Predicates<Variables...>::value)};
    };
    
    template<auto...Variables>
    using Page = ProtoPage<Variables...>;

    template<auto...Variables>
    static constexpr auto Page_v {(...||Predicates<Variables...>::value)};
};

}}

#endif