// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_TRIM_H
#define CONCEPTRODON_TYPELIVORE_TRIM_H

#include "conceptrodon/descend/microbiota/typella/shear.hpp"

namespace Conceptrodon {

namespace Typelivore {

template<typename...Elements>
struct Trim
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (Typella::Shear<std::make_index_sequence<Amount>>::template lark<Agreements..., Elements...>());

        template<template<typename...> class Operation=Capsule>
        using UniRoad = decltype
        (Typella::Shear<std::make_index_sequence<Amount>>::template lark<Operation, Elements...>());
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif