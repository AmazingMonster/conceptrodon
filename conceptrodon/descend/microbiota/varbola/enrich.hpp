// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARBOLA_ENRICH_H
#define CONCEPTRODON_VARBOLA_ENRICH_H

#include "conceptrodon/prefix.hpp"
#include <utility>

namespace Conceptrodon {

namespace Varbola {

template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<auto...NewVariables>
    struct ProtoPage
    {
        template
        <
            template<auto...> class Operation,
            Prefix<I>...FrontTargets,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Operation<FrontTargets::value..., NewVariables..., BackTargets::value...>;
    };

    template<auto...NewVariables>
    using Page = ProtoPage<NewVariables...>;
};

}}

#endif