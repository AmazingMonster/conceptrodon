// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_INJECT_H
#define CONCEPTRODON_MOULDIVORE_INJECT_H

#include "conceptrodon/descend/microbiota/typella/enrich.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation=Capsule>
struct Inject
{
    template<size_t Index>
    struct ProtoPage
    {   
        template<typename...NewElements>
        struct ProtoMold
        {
            template<typename...Elements>
            using Mold = decltype
            (
                Typella::Enrich<std::make_index_sequence<Index>>
                ::template ProtoMold<NewElements...>
                ::template lark<Operation, Elements...>()
            );
        };

        template<typename...NewElements>
        using Mold = ProtoMold<NewElements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif