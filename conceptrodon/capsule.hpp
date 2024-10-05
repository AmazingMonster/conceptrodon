// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_CAPSULE_H
#define CONCEPTRODON_CAPSULE_H

namespace Conceptrodon {
    
template<typename...Elements>
struct Capsule
{
    static constexpr size_t size() { return sizeof...(Elements); }

    template<template<typename...> class Container>
    struct ProtoRoad { using type = Container<Elements...>; };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>::type;

    template<template<typename...> class Container>
    using UniRoad = Container<Elements...>;
};
 
}

#endif