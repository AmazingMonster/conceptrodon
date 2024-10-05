// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_FRONT_H
#define CONCEPTRODON_TYPELIVORE_FRONT_H

#include "conceptrodon/descend/microbiota/typella/fore.hpp"

namespace Conceptrodon {
namespace Typelivore {

template<typename...Elements>
struct Front
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (Typella::Fore<std::make_index_sequence<Amount>>::template lark<Agreements..., Elements...>());

        template<template<typename...> class Operation=Capsule>
        using UniRoad = decltype
        (Typella::Fore<std::make_index_sequence<Amount>>::template lark<Operation, Elements...>());
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

}}

#endif