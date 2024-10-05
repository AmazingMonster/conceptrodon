// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_TRIM_H
#define CONCEPTRODON_VARYBIVORE_TRIM_H

#include "conceptrodon/descend/microbiota/varbola/shear.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Trim
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Varbola::Shear<std::make_index_sequence<Amount>>
            ::template lark<Agreements..., Monotony<Variables>...>()
        );
        
        template<template<auto...> class Operation=Shuttle>
        using UniRail = decltype
        (
            Varbola::Shear<std::make_index_sequence<Amount>>
            ::template lark<Operation, Monotony<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif