// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_SLICE_H
#define CONCEPTRODON_VARYBIVORE_SLICE_H

#include "conceptrodon/utilities/vay.hpp"
#include "conceptrodon/metafunctions/microbiota/varbola/incise.hpp"
#include "conceptrodon/metafunctions/microbiota/varbola/shear.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Slice
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Amount>
    struct ProtoPage<Amount>
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Varbola::Shear<std::make_index_sequence<Amount>>
            ::template idyl<Agreements...>(Vay<Variables>{}...)
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Varbola::Incise<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Agreements...>(Vay<Variables>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif