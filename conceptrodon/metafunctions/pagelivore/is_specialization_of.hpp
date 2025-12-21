// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_IS_SPECIALIZATION_OF_H
#define CONCEPTRODON_PAGELIVORE_IS_SPECIALIZATION_OF_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Sequence>
struct IsSpecializationOf
{
    template<typename>
    struct ProtoMold
    { static constexpr bool value = false; };

    template<auto...Variables>
    struct ProtoMold<Sequence<Variables...>>
    { static constexpr bool value = true; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr bool Mold_v = ProtoMold<Args...>::value;
};

}}

#endif