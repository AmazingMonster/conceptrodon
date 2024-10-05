// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_IS_SPECIALIZATION_H
#define CONCEPTRODON_MOULDIVORE_IS_SPECIALIZATION_H

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class Container>
struct IsSpecializationOf
{
    template<typename>
    struct ProtoMold
    { static constexpr bool value = false; };

    template<typename...Elements>
    struct ProtoMold<Container<Elements...>>
    { static constexpr bool value = true; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr bool Mold_v = ProtoMold<Args...>::value;
};

}}

#endif