// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_IS_ROADFUL_H
#define CONCEPTRODON_OMENNIVORE_IS_ROADFUL_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct IsRoadful
{ static constexpr bool value {false}; };

template
<
    template<template<typename...> class...> class Warehouse,
    template<typename...> class...Containers
>
struct IsRoadful<Warehouse<Containers...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsRoadful_v {false};

template
<
    template<template<typename...> class...> class Warehouse,
    template<typename...> class...Containers
>
constexpr bool IsRoadful_v<Warehouse<Containers...>> {true};

}}

#endif