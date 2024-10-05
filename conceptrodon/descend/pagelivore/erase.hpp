// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_ERASE_H
#define CONCEPTRODON_PAGELIVORE_ERASE_H

#include "conceptrodon/descend/microbiota/varbola/expunge.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation=Shuttle>
struct Erase
{
    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = decltype
        (
            Varbola::Expunge<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template lark<Operation, Monotony<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif