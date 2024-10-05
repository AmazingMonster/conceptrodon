// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_REVERIE_H
#define CONCEPTRODON_REVERIE_H

namespace Conceptrodon {
    
template<template<typename...> class...Containers>
struct Reverie
{
    static constexpr size_t size() { return sizeof...(Containers); }

    template<template<template<typename...> class...> class Warehouse>
    struct ProtoFlow { using type = Warehouse<Containers...>; };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = ProtoFlow<Warehouses...>::type;

    template<template<template<typename...> class...> class Warehouse>
    using UniFlow = Warehouse<Containers...>;
};
 
}

#endif