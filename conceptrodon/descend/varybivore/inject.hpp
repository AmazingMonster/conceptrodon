// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_INJECT_H
#define CONCEPTRODON_VARYBIVORE_INJECT_H

#include "conceptrodon/descend/microbiota/varbola/enrich.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Inject
{
    template<size_t Index>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...NewVariables>
            struct ProtoPage
            {            
                template<template<auto...> class...Agreements>
                using Rail = decltype
                (
                    Varbola::Enrich<std::make_index_sequence<Index>>
                    ::template ProtoPage<NewVariables...>
                    ::template lark<Agreements..., Monotony<Variables>...>()
                );

                template<template<auto...> class Operation=Shuttle>
                using UniRail = decltype
                (
                    Varbola::Enrich<std::make_index_sequence<Index>>
                    ::template ProtoPage<NewVariables...>
                    ::template lark<Operation, Monotony<Variables>...>()
                );
            };
        };

        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif