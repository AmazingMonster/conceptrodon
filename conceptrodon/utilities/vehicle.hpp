// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VEHICLE_H
#define CONCEPTRODON_VEHICLE_H

#include <cstddef>

namespace Conceptrodon {
    
template<template<typename...> class...Containers>
struct Vehicle
{
    static constexpr size_t size() { return sizeof...(Containers); }

    template<template<template<typename...> class...> class Warehouse>
    struct Detail { using type = Warehouse<Containers...>; };

    template<template<template<typename...> class...> class...Warehouses>
    using Flow = Detail<Warehouses...>::type;

    template<template<template<typename...> class...> class Warehouse>
    using UniFlow = Warehouse<Containers...>;
};
 
}

#endif