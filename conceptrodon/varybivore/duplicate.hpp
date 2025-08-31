// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_DUPLICATE_H
#define CONCEPTRODON_VARYBIVORE_DUPLICATE_H

#include <cstddef>
#include <utility>

namespace Conceptrodon {
namespace Varbola {

template<auto Variable, auto>
static constexpr auto Bundle_v = Variable;

}

namespace Varybivore {

template<auto Variable>
struct Duplicate
{
    template<typename>
    struct ProtoMold {};

    template<size_t...I>
    struct ProtoMold<std::index_sequence<I...>>
    {
        template<template<auto...> class Operation>
        struct Detail
        {
            using type = Operation
            <Varbola::Bundle_v<Variable, I>...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;

        template<template<auto...> class Operation>
        using UniRail = Operation
        <Varbola::Bundle_v<Variable, I>...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<size_t I>
    struct ProtoPage
    : ProtoMold<std::make_index_sequence<I>>
    {};

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif