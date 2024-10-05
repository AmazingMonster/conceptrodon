// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_DISMISS_H
#define CONCEPTRODON_VARYBIVORE_DISMISS_H

#include "conceptrodon/descend/microbiota/varbola/ditch.hpp"

namespace Conceptrodon {
namespace Varybivore {

template<auto...Variables>
struct Dismiss
{
    template<size_t Index>
    struct ProtoPage
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (Varbola::Ditch<std::make_index_sequence<Index>>::template lark<Agreements..., Monotony<Variables>...>());
        
        template<template<auto...> class Operation=Shuttle>
        using UniRail = decltype
        (Varbola::Ditch<std::make_index_sequence<Index>>::template lark<Operation, Monotony<Variables>...>());
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif