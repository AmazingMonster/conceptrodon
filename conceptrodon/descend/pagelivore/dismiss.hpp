// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_DISMISS_H
#define CONCEPTRODON_PAGELIVORE_DISMISS_H

#include "conceptrodon/descend/microbiota/varbola/ditch.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation=Shuttle>
struct Dismiss
{
    template<size_t Index>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = decltype
        (Varbola::Ditch<std::make_index_sequence<Index>>::template lark<Operation, Monotony<Variables>...>());
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif