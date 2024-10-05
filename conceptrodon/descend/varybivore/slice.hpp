// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_SLICE_H
#define CONCEPTRODON_VARYBIVORE_SLICE_H

#include "conceptrodon/descend/microbiota/varbola/incise.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Slice
{
    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Varbola::Incise<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template lark<Agreements..., Monotony<Variables>...>()
        );
        
        template<template<auto...> class Operation=Shuttle>
        using UniRail = decltype
        (
            Varbola::Incise<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template lark<Operation, Monotony<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif