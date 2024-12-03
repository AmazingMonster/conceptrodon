// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_COGNATE_INJECT_H
#define CONCEPTRODON_PAGELIVORE_COGNATE_INJECT_H

#include "conceptrodon/vay.hpp"
#include "conceptrodon/descend/microbiota/varbola/enrich.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct CognateInject
{
    template<size_t Index>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...NewVariables>
            struct ProtoPage
            {
                template<auto...Variables>
                using Page = decltype
                (
                    Varbola::Enrich<std::make_index_sequence<Index>>
                    ::template ProtoPage<NewVariables...>
                    ::template idyl<Operation, Vay<Variables>...>()
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