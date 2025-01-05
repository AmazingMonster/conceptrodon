// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_COGNATE_SLICE_H
#define CONCEPTRODON_MOULDIVORE_COGNATE_SLICE_H

#include "conceptrodon/microbiota/typella/incise.hpp"
#include "conceptrodon/microbiota/typella/shear.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation>
struct CognateSlice
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Amount>
    struct ProtoPage<Amount>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Typella::Shear<std::make_index_sequence<Amount>>
            ::template idyl<Operation>(std::type_identity<Elements>{}...)
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Typella::Incise
            <
                std::make_index_sequence<Start>,
                std::make_index_sequence<End-Start>
            >
            ::template idyl<Operation>(std::type_identity<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif