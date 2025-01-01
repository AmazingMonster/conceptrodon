// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_ERASE_H
#define CONCEPTRODON_VARYBIVORE_ERASE_H

#include "conceptrodon/vay.hpp"
#include "conceptrodon/descend/microbiota/varbola/ditch.hpp"
#include "conceptrodon/descend/microbiota/varbola/expunge.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Erase
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Varbola::Ditch<std::make_index_sequence<Index>>
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
            Varbola::Expunge<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Agreements...>(Vay<Variables>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif