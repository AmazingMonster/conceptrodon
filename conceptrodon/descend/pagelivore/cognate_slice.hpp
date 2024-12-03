// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_COGNATE_SLICE_H
#define CONCEPTRODON_PAGELIVORE_COGNATE_SLICE_H

#include "conceptrodon/vay.hpp"
#include "conceptrodon/descend/microbiota/varbola/incise.hpp"
#include "conceptrodon/descend/microbiota/varbola/shear.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct CognateSlice
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Amount>
    struct ProtoPage<Amount>
    {
        template<auto...Variables>
        using Page = decltype
        (
            Varbola::Shear<std::make_index_sequence<Amount>>
            ::template idyl<Operation, Vay<Variables>...>()
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<auto...Variables>
        using Page = decltype
        (
            Varbola::Incise<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Operation, Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif