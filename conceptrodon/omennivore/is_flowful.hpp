// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_IS_FLOWFUL_H
#define CONCEPTRODON_OMENNIVORE_IS_FLOWFUL_H

namespace Conceptrodon {
namespace Omennivore {
    
template<typename>
struct IsFlowful
{ static constexpr bool value {false}; };

template
<
    template<template<template<typename...> class...> class...> class Sorrow,
    template<template<typename...> class...> class...Warehouses
>
struct IsFlowful<Sorrow<Warehouses...>>
{ static constexpr bool value {true}; };

template<typename>
constexpr bool IsFlowful_v {false};

template
<
    template<template<template<typename...> class...> class...> class Sorrow,
    template<template<typename...> class...> class...Warehouses
>
constexpr bool IsFlowful_v<Sorrow<Warehouses...>> {true};

}}

#endif