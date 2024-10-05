// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_IS_FREEWAY_H
#define CONCEPTRODON_OMENNIVORE_IS_FREEWAY_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct IsFreeway
{ static constexpr bool value {false}; };

template
<
    template<template<typename...> class...> class Warehouse,
    template<typename...> class...Containers
>
struct IsFreeway<Warehouse<Containers...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsFreeway_v {false};

template
<
    template<template<typename...> class...> class Warehouse,
    template<typename...> class...Containers
>
constexpr bool IsFreeway_v<Warehouse<Containers...>> {true};

}}

#endif