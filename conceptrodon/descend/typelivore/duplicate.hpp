// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_DUPLICATE_H
#define CONCEPTRODON_TYPELIVORE_DUPLICATE_H

#include "conceptrodon/label.hpp"
#include "conceptrodon/capsule.hpp"
#include <utility>

namespace Conceptrodon {
namespace Typelivore {

template<typename Element>
struct Duplicate
{
    template<typename>
    struct ProtoMold {};

    template<size_t...I>
    struct ProtoMold<std::index_sequence<I...>>
    : public Label<Element, I>...
    {
        using Label<Element, I>::idyl...;
        
        template<template<typename...> class Operation=Capsule>
        struct Detail
        {
            using type = Operation
            <decltype(idyl(std::integral_constant<size_t, I>{}))...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;

        template<template<typename...> class Operation=Capsule>
        using UniRoad = Operation
        <decltype(idyl(std::integral_constant<size_t, I>{}))...>;
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