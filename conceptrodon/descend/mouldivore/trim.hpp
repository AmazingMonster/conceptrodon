// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_TRIM_H
#define CONCEPTRODON_MOULDIVORE_TRIM_H

#include "conceptrodon/descend/microbiota/typella/shear.hpp"

namespace Conceptrodon {

namespace Mouldivore {

template<template<typename...> class Operation=Capsule>
struct Trim
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<typename...Elements>
        using Mold = decltype
        (Typella::Shear<std::make_index_sequence<Amount>>::template lark<Operation, Elements...>());
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif