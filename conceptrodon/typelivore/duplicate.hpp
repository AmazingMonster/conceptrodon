// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_DUPLICATE_H
#define CONCEPTRODON_TYPELIVORE_DUPLICATE_H

#include <cstddef>
#include <utility>

namespace Conceptrodon {
namespace Typella {

template<typename Element, auto>
using Bundle_t = Element;

}

namespace Typelivore {

template<typename Element>
struct Duplicate
{
    template<typename>
    struct ProtoMold {};

    template<size_t...I>
    struct ProtoMold<std::index_sequence<I...>>
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation
            <Typella::Bundle_t<Element, I>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;

        template<template<typename...> class Operation>
        using UniRoad = Operation
        <Typella::Bundle_t<Element, I>...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<size_t I>
    struct ProtoPage
    : public ProtoMold<std::make_index_sequence<I>>
    {};

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif