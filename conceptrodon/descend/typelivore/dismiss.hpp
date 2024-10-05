// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_DISMISS_H
#define CONCEPTRODON_TYPELIVORE_DISMISS_H

#include "conceptrodon/descend/microbiota/typella/ditch.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Dismiss
{
    template<size_t Index>
    struct ProtoPage
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (Typella::Ditch<std::make_index_sequence<Index>>::template lark<Agreements..., Elements...>());

        template<template<typename...> class Operation=Capsule>
        using UniRoad = decltype
        (Typella::Ditch<std::make_index_sequence<Index>>::template lark<Operation, Elements...>());
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif