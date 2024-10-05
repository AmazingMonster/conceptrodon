// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_ERASE_H
#define CONCEPTRODON_TYPELIVORE_ERASE_H

#include "conceptrodon/descend/microbiota/typella/expunge.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Erase
{
    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Typella::Expunge<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template lark<Agreements..., Elements...>()
        );

        template<template<typename...> class Operation=Capsule>
        using UniRoad = decltype
        (
            Typella::Expunge<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template lark<Operation, Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif