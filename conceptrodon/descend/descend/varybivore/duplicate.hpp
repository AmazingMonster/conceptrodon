// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_DUPLICATE_H
#define CONCEPTRODON_VARYBIVORE_DUPLICATE_H

#include "conceptrodon/descend/stamp.hpp"
#include "conceptrodon/shuttle.hpp"
#include <utility>

namespace Conceptrodon {
namespace Varybivore {

template<auto Variable>
struct Duplicate
{
    template<typename>
    struct ProtoMold {};

    template<size_t...I>
    struct ProtoMold<std::index_sequence<I...>>
    : public Stamp<Variable, I>...
    { 
        using Stamp<Variable, I>::idyl...;

        template<template<auto...> class Operation=Shuttle>
        struct Detail
        {
            using type = Operation
            <idyl(std::integral_constant<size_t, I>{})...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;

        template<template<auto...> class Operation=Shuttle>
        using UniRail = Operation
        <idyl(std::integral_constant<size_t, I>{})...>;
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