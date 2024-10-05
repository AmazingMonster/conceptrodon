// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_DISMISS_H
#define CONCEPTRODON_MOULDIVORE_DISMISS_H

#include "conceptrodon/descend/microbiota/typella/ditch.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Operation=Capsule>
struct Dismiss
{
    template<size_t Index>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = decltype
        (Typella::Ditch<std::make_index_sequence<Index>>::template lark<Operation, Elements...>());
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif